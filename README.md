# Get-list-of-running-processes-and-delete-specified-processs---c-
C++ program to view list of processes (by process handle name) and delete a proccess specified by user <br />
<br />
This program was created for the purpose of deleting a running process if Taskmanager is not responding <br />
or cannot be opened. <br />
The program will terminate any process specified by the user (if the process is running). <br />
For example, if the user specifies "chrome.exe" all processes with that handle name will be terminated.<br />
<br />
The program also includes a user interface (in the form of text). <br />
<br />
The program has so far been tested (compiled/run) on windows 7 64bit <br />
and was originally compiled in Dev-C++ 5.11 <br />
<br />
Note: to compile the code, you made need to run your compiler with adminstrator privileges (at least for Windows) <br />
<br />
The code is subject to improvement and optimization. <br />
<br />
<br />
A list of tasks accomplished in this code include;<br />
=>get list of processes running on computer <br />
=>terminate a process that is specified by the user <br />
=>storing integers as array (using vector) <br />
=>storing strings as list (also using vector) <br />
=>sorting vector of strings in alphabetic order <br />
=>from a vector of strings, create a new vector which is a list of unique strings from the first vector <br />
=>determine if two strings match [using the strcmp() function] <br />
=>applying for-loop in a single line (not done everywhere in the code)<br />
=>applying if-loop in a single line (not done everywhere in the code) <br />
=>apply argument for two for-loops in a single line (not done everywhere in the code)<br />
=>change color of text in program (after compiling and running as windows .exe) <br />
