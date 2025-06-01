# Exercise 5

**Update this README with your answers to the questions below.**

## Comparing File Changes

- What's an easy way to identify the changes in source code from one exercise
  to another?
    - We can use the `diff` command , with appropriate flags like `-u` (unified mode , where first and second file removals and additions(resp) are shown with --- and +++ respectively).
    - Some other flags like , `-c` , `--brief`, etc can be used.
    - `diff exercise-4/src/tcp_echo_client.cpp exercise-5/src/client-main.cc`
## Using Classes

- Here is one way to separate out the code into multiple files
- Is this the best way to do it? 
  - It is good , but may not be the best. Some things which I noticed was to use alias declaration at the start of every function , instead of once.
  - It is still good as you can switch between different namespaces (with) same names (for different functionalities), just by stating the path(the scopes in which it was defined) and use it freely.
  
- What are the advantages and disadvantages?
  - Advantage:It is useful,as mentioned above in big projects , which have some functionality(different) in 2 different scopes, which can be used easily by nesting(stating the scopes), it provides abstaction.
  - Disadvantage: It can get very complex, better not have it sometimes.

## Introduction to Namespace

- There are different ways namespace is being used in this exercise
- Which way is better? What are the advantages and disadvantages?
   - There are 3 ways in which it is written in.
    - (1) `namespace tt::chat::server {  }` : Functions are written inside this.
   
    - (2)  `namespace ttc = tt::chat; ` : Functions in this scope is written as `ttc::func()` . 
    - (3) 'using namespace `tt::chat` 

    - (1) Adv: Groups related functions cleanly — everything inside belongs to `tt::chat::server`
    - (1) Disadv: Every time you use a function outside, you have to prefix it.Also, if any other namespace inside is to be used, have to specify it and use it independently.
    - (2) Adv: Easier to type(makes long types short).
    - (2) Disadv: Still we have to write `xyz::' everytime.
    - (3) Adv: Very very easier to write.
    - (3) Disadv: If multiple prefixes(scopes) are required , this is uselsess, it cannot do anything.

    - I personally like (2) as it can reduce typing everytime and still easy.

## Abstracting Code into Classes

- Abstract the client and server logic into a `Client` and `Server` class
- **Note**: You don't have to use the code in this exercise as a starting point
- You can use the code you wrote from previous exercises instead
- How should you divide the code into files? What namespace and directory structure should you use? Why?
  - I did it as follows:
  - I reused my code from previous exercise.
  - In src, I have a directory `class` , which has `client.cc` , `client.h` , `server.cc` and  `server.h` , with the classes and all the functions.
  - In src, I have `class-main-client.cc` and `class-main-server.cc`, which call the functions in `main()`.
  - I also have `shared.cc` and `shared.h` (which had `check_error` ) which I had done in previous exercise.
  - Finally, I have a seperate `Makefile` in src for compiling these programs, and on compiling, creates a directory `build` in src, which has `class_server` and `class_client` executables. 


## Programming Sense of Taste

- How do you judge what makes a particular choice of namespace and directory
  structure?
   - Clarity in using them(naming,etc) and ease of usage is the top priority for any choice of namespace. 
   - The next major factor is how much modular the code is(which also comes under ease of usage,more modular , more is the ease of usage).
- How do you judge what makes a good naming convention or programming style?
  - A good naming convention is to be consistent across a project or similar,so that a person reading our code can easily understand what our code does. Additionally, the naming must be short, but should perfectly explain the use of it(variables, function names).

## "Senses" in Programming

- Have you ever heard of programmers referring to "code smells"? How can code
  smell?
- What does it mean to have a sense of taste in programming? How can code
  taste?
- Is there an analogue for every sense?
- What other code senses can you think of?
- How many senses do humans have?
- When would you want to see something before you touch it?
- When would you want to touch something before you see it?