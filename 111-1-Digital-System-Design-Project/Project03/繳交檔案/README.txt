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

NOTICE: In this "State Minimization" project, I used three file to read and write, such as, input.kiss, output.kiss and output.dot.
        So make sure you already have three files and input command in the command line like this,
        $ ./a.out input.kiss output.kiss output.dot
