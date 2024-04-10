# minishell
minishell is a group project (2 members) that aims to recreate my own bash.

We had to manage the parsing of user input, the execution of commands (with management of pipes, redirections, heredoc...), signals (``CTRL + C``, ``CTRL + D``, ``CTRL + \``) and the creation of several builtins (exit, echo, env, export, unset, cd & pwd).

This project is made in C for 42School.

## Usage
**1. Clone the repository**
```
git clone https://github.com/alones-dev/minishell.git
```
**2. Compile the project**
```
make
```
**3. Enjoy**
```
./minishell
```
