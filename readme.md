<mark>Template for your README. Remove all unused parts and instructions</mark>

# Lab work <mark>NUMBER</mark>: <mark>SHORT TOPIC</mark>
Authors (team):<br> <mark>Orest Chupa - https://github.com/ratatuiii</mark><br> <mark>Nazar Dizhak - https://github.com/NazarDizhak</mark><br> <mark>Kostiantyn Stetsiuk - https://github.com/f1rset</mark><br>
Variant: <mark>none</mark>
## Prerequisites

<mark>g++, cmake, python3. list of required libraries for python in requirements.txt</mark>

### Compilation

<mark>run ./compile.sh in root folder</mark>

### Installation

<mark>just clone the repository</mark>

### Usage

<mark>In /scripts run the program1_runner or program2_runner. You will get statistics of each method (min time, mean time, deviation) into  your terminal, separated with a "\n" inbetween.</mark> <br>
<mark> Here is how to these programs: </mark> <br>
For program1 - "python3 program1_runner.py <datafile> <runs> <clear_cache> <output_csv>"


For program2 - "python3 program2_runner.py <datafile> <runs> <output_csv>"

<mark>Also, running these programs will result in creating the statistics of these runs in the data folder. It can be further used by compute_graph.py to create a graph that would be saved in the same folder for later use of your choice</mark>


### Important!

<mark>compute_graph.py is very prinitive, so any path and name changes of the output have to be changed manually inside the code itself</mark> <br>
Here is a link to the data programs were being tested on - https://drive.google.com/file/d/15H6P-We2uW25ArFWVNZ30c1UuKEAtYK6/view?usp=sharing

### Results

<h2>Program 1 results</h2>
<mark>1. Standard C++ idiom (while(filestream >> word))</mark> <br>
This method reads word by word directly from the file stream, which introduces frequent I/O operations. It’s no surprise that it’s the slowest (min: 2037 ms, mean: 2175.8 ms). Each read incurs some overhead, making it inefficient for large files

<mark>2. Reading the entire file into a std::stringstream first</mark> <br>
This method avoids frequent disk I/O and speeds things up by ~100ms (min: 2164 ms, mean: 2236.2 ms), though it’s still not the best. The overhead from stringstream operations likely keeps it from performing better.

<mark>3. Reading the entire file into memory as a string, then splitting</mark> <br>
This one is even faster (min: 1349 ms, mean: 1402.7 ms). It avoids stringstream overhead and works directly with a std::string, making splitting much more efficient. Predictable improvement.

<mark>4. Optimized large-file approach (minimal copying)</mark> <br>
This gets even better, although within possible deviation from the previous method (min: 1266 ms, mean: 1342.3 ms). The reduction in unnecessary memory allocations and copying helps a lot. The difference compared to the previous method isn't massive, but it’s noticeable.

<mark>5. Using stream iterators for large files (Bad idea #1)</mark> <br>
Surprisingly, this isn't as fast as expected (min: 1862 ms, mean: 1995.5 ms). While stream iterators might seem efficient, they can introduce unexpected overhead due to the way they handle input iterators. This could explain why it's slower than methods 3 and 4. Not really disappointing, considering it was named "bad idea".

Here is the graph to visualize the results:
![graph1](images/program1_graph.png)



<mark>As for the flushing, each method became slower. From first to fifth method in respective order - 620ms, 610ms,500ms, 400ms, 700ms</mark> <br>
Method 1 (while reading word-by-word into a vector): Slowed down significantly since frequent disk access would be required instead of buffering.<br>
Method 2 (reading whole file into a stringstream): Would also be impacted but slighlty less severely, since it already loads everything into memory at once.<br>
Method 3 (reading into a string, then splitting): Got slightly slower, if compared to itself witout flushing, as the initial read suffered from flushing, but splitting in-memory wouldn’t change.<br>
Method 4 (optimized memory reads with minimal copies): Was affected the least since it avoids unnecessary copies and works with pre-allocated memory.<br>
Method 5 (stream iterators): Became even worse since stream iterators already struggle with efficiency.<br>


<h2>Program 2 results</h2>
<mark>1. std::stringstream</mark> – This was the slowest by far. Not surprising, since stringstreams are known to be relatively inefficient due to their overhead in parsing and handling streams. The high standard deviation also suggests inconsistent performance, possibly due to internal memory allocations.

<mark>2. std::atoi() </mark> – Much faster than stringstream, as expected. atoi() is a very basic function that doesn’t handle errors or extra checks, making it quite efficient. The deviation is relatively low, meaning it's consistently fast.

<mark>3. std::stod()</mark> – This one is slower than atoi(), which makes sense. stod() has to handle floating-point parsing, which is more complex than integer conversion. The standard deviation isn't too high, but it's still noticeable.

<mark>4. std::from_chars()</mark> – The fastest method. This is exactly what it was designed for—efficient, low-overhead parsing without unnecessary checks or allocations. The standard deviation is small too, meaning it's both fast and stable.

<mark>5. sscanf()</mark> – Somewhere in the middle. sscanf() is flexible but comes with some overhead from format string parsing. It’s faster than stringstream but not as fast as from_chars().


Here is a graph for the results visualization:
![graph2](images/program2_graph.png)

# Additional tasks
<mark>IF APPLICABLE, LIST ALL THE EXTRA FEATURES YOU ADDED. PROVIDE DETAILS<mark>

# ATTENTION!
  
Additional tasks not listed in the previous paragraph would not be graded.

Be sure to provide a complete list of authors.

