# MatrixMultiplication

Demonstration of matrix multiplication using Strassen's algorithm by comparing serial version vs parallel version using TBB library.

Purpose of this program is demonstration of using TBB library in matrix multiplication. It supports only sizes that are power of two (2^n x 2^n).

<h2> How to use</h2>

Solution consists of 4 projects:

<ol>
<li>MatrixMultiplication</li>
<li>CommonLib</li>
<li>MatrixMultiplicationSerialLib</li>
<li>MatrixMultiplicationParallelLib</li>
</ol>

Before building a solution make sure you have included TBB library in the first 3 projects. You can find it [here](https://www.threadingbuildingblocks.org/download).

<h3> Custom sizes</h3>

Right click on MatrixMultiplication project Properties -> Debugging -> Command Arguments and set prefered size.

You can also run program from a command line after building. Before running make sure you have copied <b>tbb.dll</b> and <b>tbbmalloc.dll</b> from TBB library into the same directory where .exe file is.

<h3>Parameters</h3>
<ul>
<li>-s, --size INTEGER - specify size of the matrices
</li>

<li>-rn, --random - specifies that matrices will be random generated (generation time is not included in the final time)</li>

<li>a, --algorithm TYPE - where TYPE is 1 for serial algorithm and 2 for parallel algorithm (both algorithms will be run if no specified)</li>

<li>--help - More information about usage</li>
<li>etc...</li>
</ul>
You can find more information about usage by typing --help.

<h3>Speed testing </h3>

<h4>Tested on:</h4>

<ul>
<li><b>Laptop</b>: ASUS ROG G56JR</li>

<li><b>CPU</b>: Intel® Core™ i7-4700HQ 2.4 Ghz Base Frequency, 3.4 Ghz Max Turbo Frequency, 4 Cores, 8 Threads</li>

<li><b>Memory</b>: KINGSTON SO-DIMM 16GB (2x8GB) DDR3L HyperX Impact 1600MHz CL9</li>

<li><b>Compiler</b>: Visual C/C++ Optimizing Compiler Version 19.00.23506</li>

<li><b>IDE</b>: Visual Studio 2015</li>

<li><b>OS</b>: Windows 8.1 64bit</li>
</ul>
Below are the results of multiplication:

| Size           | Serial version     | Parallel version   | Serial / Parallel  |
| :------------: |:------------------:|:------------------:|:------------------:|
| 64 x 64        | 0.000197575        | 0.000520453        |0.379622
| 128 x 128      | 0.00257618         | 0.00127996         |2.0127
| 256 x 256      | 0.0106674          | 0.00432528         |2.46628
| 512 x 512      | 0.0745813          | 0.0204786          |3.64192
| 1024 x 1024    | 0.559837           | 0.148849           |3.76112
| 2048 x 2048    |3.77172             |0.952894            |3.95817
| 4096 x 4096    | 25.9821            | 6.29159            |4.12966
| 8192 x 8192    | 226.24             | 44.7409            |5.05667
| 16384 x 16384  | -                  | 319.924            |-

<i>Note</i>: all results are given in seconds

For larger sizes more than 16GB of RAM is needed.

Please don't try large sizes if you are low on RAM, program will end up transfering RAM to disk and eventually it will crash your system by trying to consume more RAM than available.

If you have some trouble with building or running plesae contact me on email: nikolalosic95@gmail.com

