# Exercise 6

**Update this README with your answers to the questions below.**

## Adding Third Party Libraries or Source Code to Your Project

- There is a new file `src/spdlog-hello-world-main.cc`
- It uses the spdlog and fmt libraries. 
  [More info here](https://github.com/gabime/spdlog) - Fast C++ logging 
  library with various sink types and formatting options
- How do you compile this file using the `g++` CLI?
  - `g++ -o logs src/spdlog-hello-world-main.cc -I./spdlog/include -lpthread`
- What do you need to change in your makefile to use this library?
  - Compile `spdlog-hello-world-main.cc` and save executable in build.
  - Add `-lfmt -lpthread` to `LDFLAGS`.
  - Add `spdlog/include` in `INC_DIRS`.
- How many different ways can this library be added into your project?
  - (1) Use `apt` to install 
  - (2) Clone it from github link given
- What are the tradeoffs in the different ways?
  - (1) is easy to install ,and installs to standard paths , but the tradeoff is that it might not be the recent version, and it is hard to modify it.
  - (2) is not very straight forward to install(set appropriate paths), but it is the most recent version , and also customizable.
- Why are there so many different ways to do it?
  - There are so many ways because of different needs for users , maybe they want to customise it according to theor needs , so recent version can be obtained from github.
  
## Static Linking vs Dynamic Linking

- What are the differences between static linking and dynamic linking?
  - Static Linking : Happens at compile time and executable is obtained. 
  - Dynamic Linking : Object files are linked during runtime(external libraries are loaded into memory during runtime)
- What are the tradeoffs?
  - Static Linking : 
  - (1) Binary file is large.
  - (2) Faster (to run)
  - (3) Harder to update libraries.
  - (4) Easy deployment into other systems, as executable can be easily run.
  - Dynamic Linking :
  - (1) Binary file is small.
  - (2) Slightly Slower(as linking is done in runtime).
  - (3) Easier to update libraries.
  - (4) Hard to deploy into other systems.
- How do you enable static linking or dynamic linking in your makefile?
  - Dynamic Linking is default , so no need to do anything in Makefile.
  - Static Linking : Add `-static` to `LDFLAGS` .

## Git Clone and Building from Source

- Where is `g++` looking for the include files and library files?
  - Include files:
  -  `/usr/include/c++/14`
  - `/usr/include/aarch64-linux-gnu/c++/14`
  - `/usr/include/c++/14/backward`
  - `/usr/include/aarch64-linux-gnu`
  - `/usr/include`
  - Additional directories specified by -I flag
  - Library files:
  - `/usr/lib/gcc/aarch64-linux-gnu/14/include`
  - `/usr/local/include`
  - Additional directories specified by -L flag

- How do you find out?
  - I cntrl+clicked on iostream to get the first `/c++/14` path , then I ran `echo | g++ -E -xc++ - -v` to get all the places it searches for.

## C++ Package Managers

- Why are there so many C++ package managers?
  - Due to absence of one dominating build system like `pip` or `npm` in python and Javascript. So,various package managers emerged.
- Which one is the best one?
  - Conan and vcpkg are the most user-friendly and popular choices, according to internet.
- Which are the most notable ways to manage the compilation of C++ projects?
  - Package Managers
  - Use CMake,Makefiles,etc