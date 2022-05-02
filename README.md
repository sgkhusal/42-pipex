# 42-pipex

My own code to execute shell commands with pipes and redirections

## Requirements
* The code is written in C language and thus needs the gcc/clang compiler and some standard C libraries to run
* The project was developed for 42-SP School Workspaces system. For Linux and MacOS it may have some different behaviors

## Mandatory part

* run ```make```
* Execute the program as follows: ```./pipex file1 cmd1 cmd2 file2```

It takes 4 arguments:
* file1 (input) and file2 (output) are file names.
* cmd1 and cmd2 are shell commands with their parameters.

It behaves exactly the same as the shell command below:
```< file1 cmd1 | cmd2 > file2```

## Bonus #1

Handle multiple pipes:
* run ```make bonus```
* Execute the program as follows: ```> ./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2```

It behaves exactly the same as the shell command below:
```< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2```

## Bonus #2

Support « and » when the first parameter is "here_doc".
* run ```make bonus```
* Execute the program as follows: ```> ./pipex_bonus here_doc LIMITER cmd cmd1 file```
* LIMITER is the word that you use as delimiter to end the input via keyboard

It behaves exactly the same as the shell command below:
```cmd << LIMITER | cmd1 >> file```

## Tests

In test folder you can find some tests and examples for mandatory and bonus parts:
* ```./mandatory.sh```
* ```./mandatory_errors.sh```
* ```./bonus.sh```
* ```./bonus_errors.sh```

## Useful links to study about pipes, redirection and paralel processes using fork

* [Unix Processes in C](https://www.youtube.com/watch?v=cex9XrZCU14&list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)
* [Process control](https://cs61.seas.harvard.edu/site/2021/ProcessControl/)
* [Process control exercises](https://cs61.seas.harvard.edu/site/2021/Section11/)
