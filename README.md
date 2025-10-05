<h1 align="center">&lt;/&gt; cmpsh</h1>
<div align="center">cmpsh is a minimal shell program in C that supports both interactive and non-interactive modes</div>


## Features

Interactive Mode
- Execute built-in commands:
  - `pwd` : prints the current working directory  
  - `cd <dir>` : changes the current working directory  
  - `paths` : overwrites the list of program search paths  
  - `exit` : exits the shell  
- Support for multi-process pipelines  
- Run external commands


Non-Interactive Mode
- Executing script files


# Architecture

- **cmpsh:** main module that runs the continuous shell loop  
- **utils:** contains helper functions
- **commands** handles command execution logic
- **shared:** stores shared data across modules

## Flow
1. **Input Parsing**  
2. **Command Execution & Classification**  
   - **Internal commands:** handled directly by the shell
   - **External commands:** executed by searching through program paths
   - **Pipeline commands:** each command is parsed separately, then connected for input/output flow via pipes



## How to run 

After cloning the repo

```bash
cd src
make
./cmpsh
```

---

This project was written as part of an **Operating Systems course** in my **second year**.  here are some other resources I found useful for understanding how shells and processes work:

- [Write a simple shell in c](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [Implementing multi-process pipe-lining](https://cs162.org/static/hw/hw-shell/docs/pipes/)
- [Jacob Sorber channel (processes and IPC)](https://www.youtube.com/@JacobSorber/playlists)
