# Operating System: Three Easy Steps
[Book Link](https://pages.cs.wisc.edu/~remzi/OSTEP/)

Contains homework and projects for OSTEP course. Links to the original repo is given below

[Projects](https://github.com/remzi-arpacidusseau/ostep-projects)
[Homework](https://github.com/remzi-arpacidusseau/ostep-projects)

## Chapter 1: Introduction
### Homeworks
    - None
### Projects
    - Unix Utilities
    - reverse utility

## Chapter 4: Processes
* Process is an abstraction of a running program provided by operating system
* OS divides resources between process by virtualizaion where process 

### Homework
    - Simulation `process-run.py`

## Chapter 5: Process API
* `fork()` when called from a process creates an exact duplicate
* Unix provides: `fork(), exec(), wait()`
    - a new child process starts right after the fork call with fork_rcode = 0
    - parent process continues with fork_rcode = pid of the child
    - fork returns rc < 0 if it fails to create another process
    - assuming one cpu, which will run first is non deterministic

* `wait()` can be called from parent process after `fork()` and parent process will wait until child is done and then will continue from that point.

* `exec()` is useful when you want to run not the same program but something else. That other program can be passed at arguments to exec. However exec is also not so simple because it hijacks the current process and overrides the current static data, code segment, heap and stack are reinitialized. An so exec call never returns (as there is nothing left to return to).

### How does bash shell execute program
```$ ls -a > out.file```
Shell first calls fork which forks the bash shell. The main shell waits while the child shell sets the stdout redirection. Next the child shell calls `exec`
and loads the `ls` program into itself setting input arguments. The child process is now running `ls` it will complete and return control to the parent process.
