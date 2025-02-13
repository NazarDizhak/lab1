import matplotlib.pyplot as plt
import numpy as np
import csv

def plot_execution_stats(csv_file, output_image="execution_stats.png"):
    """
    Reads execution statistics from a CSV file and generates a bar plot.
    
    Each method has two bars:
    - Left bar: Minimum execution time
    - Right bar: Mean execution time with an error bar (standard deviation)
    
    Parameters:
    - csv_file: Path to the CSV file containing execution stats.
    - output_image: Path to save the generated plot.
    """
    methods = []
    min_values = []
    mean_values = []
    stddev_values = []
    
    # Read the CSV file
    with open(csv_file, "r") as f:
        reader = csv.reader(f)
        next(reader)  # Skip header
        for row in reader:
            methods.append(row[0])  # Method number as a string
            min_values.append(float(row[1]))
            mean_values.append(float(row[2]))
            stddev_values.append(float(row[3]))

    x = np.arange(len(methods))  # X-axis positions
    
    width = 0.35  # Width of the bars
    fig, ax = plt.subplots(figsize=(10, 6))

    # Plot Min Values (Left Bars)
    ax.bar(x - width/2, min_values, width, label="Min Time", color="royalblue")

    # Plot Mean Values with Error Bars (Right Bars)
    ax.bar(x + width/2, mean_values, width, yerr=stddev_values, 
           label="Mean Time (±StdDev)", color="orange", capsize=5, alpha=0.8)

    # Labels & Formatting
    ax.set_xlabel("Method")
    ax.set_ylabel("Execution Time, ms")
    ax.set_title("Execution Time Comparison by Method")
    ax.set_xticks(x)
    ax.set_xticklabels(methods)
    ax.legend()

    plt.tight_layout()
    plt.savefig(output_image)
    plt.show()

    print(f"Plot saved as {output_image}")

# Example usage
csv_file = "../data/test_stats.csv"  # Update if needed
plot_execution_stats(csv_file)
