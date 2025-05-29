# Exercise 4

**Update this README with your answers to the questions below.**

## Learning Multi-File C++ Projects

- Move code that can be shared between `tcp_echo_server.cc` and 
  `tcp_echo_client.cc` to separate `.h` and `.cc` files
- How would you compile from the command line?
  - From `src` we run, 
  -   `g++ shared.cpp tcp_echo_client.cpp -o ./client `
- How would you compile using make?
  - Just use the same command in Makefile
- How would you compile using VS Code?
  - In `.vscode` , add `tasks.json` and add required arguments , then `Cntrl+Shit+P` and choose `Run Tasks` and choose Build Server/Client .

### Compiling vs Linking

- What is the difference between compiling and linking in C++?
  - Compiling is the process of converting C++ code into machine readable object code (.o file), linking is the process of creating an executable , by combining multiple .o files , this executable can be run after than.
- What is the difference between creating an executable and creating a 
  library?
   - Creating an executable means to have a program(binary file) which we can run , which is compiled and linked using multiple files
   - Creating a library means , having pre compiled code which doesn't have a `main` , and can be reused with other programs which have a `main`. Ex. `<iostream>`is a standard library.
- How do you compile a library, and then use that library to compile an
  executable?
   - We first compile into an object file. Next we archive it using `ar` (it bundles .o (object) files into an archive) which creates a static library.
   - Next to compile this we use along with `g++ file.cpp -L -l<name>` . `-L` flag tells us to look at current directory and 
   `-l<name>` looks for name.a or name.so, to link . 

### Reminder 
[Quickstart tutorial to make](https://makefiletutorial.com/) - Learn make 
fundamentals with practical examples and common patterns.

## Experiments in Performance

- Is it better to have many small files spread across many directories, or
  a few large files across fewer directories?
   - It is generally better to have small files across many directories as , it has readability , modularity , faster compile time , good in big projects.
- Is there a difference in compilation time between the two?
  - Yes, suppose we make a modification in a big file and compile , everything gets recompiled , but when we have lot of small files , compiling happens only in that file which was modified, so build takes faster.
- How can you assess performance other than compilation speed?
  - We can look at runtime of the code , memory usage,etc.