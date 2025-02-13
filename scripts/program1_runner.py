import subprocess
import sys
import os
import csv
import numpy as np
from scipy.stats import wilcoxon
def flush_os_cache():
    if sys.platform == "linux":
        subprocess.run(["sync"])  # Flush file system buffers
        subprocess.run(["sudo", "sh", "-c", "echo 3 > /proc/sys/vm/drop_caches"])  # Drop caches
    elif sys.platform == "darwin":
        subprocess.run(["sudo", "purge"])  # macOS flush
    else:
        print("OS cache flushing is not supported on this platform.")

def run_test(progname, datafile, method, runs, clear_cache):
    times = []
    results = None
    
    for _ in range(runs):
        if clear_cache:
            flush_os_cache()
        process = subprocess.run([progname, datafile, str(method)], capture_output=True, text=True)
        output = process.stdout.strip().split("\n")
        
        if len(output) < 2:
            print("Error: Unexpected output format.")
            print(output)
            sys.exit(1)
        
        exec_time = int(output[0])
        result_line = output[1]
        times.append(exec_time)
        
        if results is None:
            results = result_line
        elif results != result_line:
            print("Error: Output mismatch detected!")
            sys.exit(1)
    
    return times

def compute_statistics(times):
    return {
        "min": min(times),
        "mean": np.mean(times),
        "stddev": np.std(times, ddof=1)
    }

def compare_methods(method_times, output_file):
    methods = list(method_times.keys())
    
    with open(output_file, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow([""] + methods)
        
        for i, method1 in enumerate(methods):
            row = [method1]
            for j, method2 in enumerate(methods):
                if i == j:
                    row.append("-")
                else:
                    _, p_value = wilcoxon(method_times[method1], method_times[method2])
                    row.append(f"{p_value:.5f}")
            writer.writerow(row)

def write_execution_stats(method_times, output_file):

    with open(output_file, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["Method", "Min", "Mean", "StdDev"])
        
        for method, times in method_times.items():
            stats = compute_statistics(times)
            writer.writerow([method, stats["min"], stats["mean"], stats["stddev"]])
def main():
    if len(sys.argv) != 5:
        print("Usage: python3 program1_runner.py <datafile> <runs> <clear_cache> <output_csv>")
        sys.exit(1)
    
    datafile = sys.argv[1]
    runs = int(sys.argv[2])
    clear_cache = bool(int(sys.argv[3]))
    output_csv = sys.argv[4]
    
    progname = "../bin/io_exe"
    methods = [1, 2, 3, 4, 5]
    
    method_times = {}
    
    for method in methods:
        method_times[method] = run_test(progname, datafile, method, runs, clear_cache)
        stats = compute_statistics(method_times[method])
        
        print(f"{stats['min']}\n" +
              f"{stats['mean']}\n" +
              f"{stats['stddev']}\n")
        print()
    
    compare_methods(method_times, output_csv)
    write_execution_stats(method_times, "../data/test_stats.csv")
    
if __name__ == "__main__":
    main()
