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

`$ ls -a > out.file`

Shell first calls fork which forks the bash shell. The main shell waits while the child shell sets the stdout redirection. 
Next the child shell calls `exec`
and loads the `ls` program into itself setting input arguments. The child process is now running `ls` it will complete and return control to the parent process.

### Orphan and Zombie Process
An orphan process is a process whose parent has exited yet it execute. It will be adopted by the init process and will be reaped when they exit.
How to reap a process? Call wait on it by parent and read its return code, that clears up its record in the process table in the kernal.
Zombies process is a process which has finished but not yet been waited/reaped by exisitng parent. Parent might be hung. I think its normal for a process
to be zombie for a few seconds.

### Homework
    - Simulate `fork.py` -- pretty simple

## Chapter 5: Mechanism: Limited Direct Execution (LDE)
Virtualize CPU by timesharing and context swtiching. This will impact
performance because of overhead and maintain security. Performance is 
achiveved by running the process directly on the CPU but how do you maintain security that the process does not access stuff it does should not have access to: via Limited Direct Execusion.

### What is LDE? LIMITED DIRECT EXECUTION
**Direct Execution:**
Run the user code directly on the processor. When OS wants to run a program it will load in memory from disk, setup stack and argc, argv and jump to main. once done will free memory and remove from process list.

**Limited:**
Q How does OS make sure the code running on processor does not access things it should not?
Q How does OS implement timesharing and context switching?

To fix the first issue OS has two processor mode: 
- user mode: cannot do any restricted action such as I/O
- kernal mode: mode in which OS runs, has all privilages to do anything

user programs run in user mode if they need to do a privilaged action such
as I/O memory allocation etc then they perform a **system call**

### System call
system calls allow the kernel to carefully expose certain key pieces of functionality to user programs, such as accessing the file system, creating and destroying processes, communicating with other processes, and allocating more. User program executes a trap instruction which:
- jumps to kernal code
- raises the mode to kernal mode
- kernal performs the privilaged action 
- then calls **return-from-trap** which restores user program specific stack and registers and reduces the mode to user mode.
The state of the user proccess is stored on the *kernal stack* and *trap table* is created by os at boot time to store the address of the trap instructions (trap message handle).


### How does OS switch betwen process
For this, the os needs to get contorl first. There have been two approches:
1. Wait for the process to send a trap -- this approch was common before and that is why computers would hang if a process caused an infinite loop
2. A timer calls initiates an interupt every few milliseconds which is handled by kernal trap-handler and gives control to the OS

Once the os regains control the scheduler decides which process to run next, and invokes a "context-swtich". 
context-switch is code in the os which load PC, stack registers for the process to be run and then calls return from trap

### Homework
- Compute time it takes for system call and context switch
