How to compile and execute your CPP program in Ubuntu Linux enviornment?
1. First, make sure your Ubuntu is latest package lists
$ sudo apt-get update
Or, if you like, you can enter this command below to download the latest versions of the system packages.
$ sudo apt-get update && sudo apt-get dist-upgrade

2. Install the GNU compiler tools and the GDB debugger by enter: 
$ sudo apt-get install build-essential gdb

3. Verify that the install succeeded
$ whereis g++
$ whereis gdb

4. Make a programming file (Ex. hello.cpp)

5. Assume you are done your code, let's compile the program.
$ g++ hello.cpp

6. Execute it, and if you want to read and write the file with command-line arguments, you can enter this command.
$ ./a.out INPUT_FILE OUTPUT_FILE



ROBDD????:
1.	??struct node ???,??????Tree????
2.	?????PLA??????
3.	?????Tree?
4.	?PLA??????,?????Tree,???????Recursion????????node?
5.	????,?????????
6.	??DOT?????,????OUTPUT.dot??
