# 🖥️ minishell
## 🎯 **Introduction**

Welcome to **minishell**! 🚀  
This is a fun and challenging **group project** where we recreated our very own version of **bash**. In this project, we worked on parsing user input, executing commands (with pipes, redirections, heredoc handling), managing signals (like `CTRL + C`, `CTRL + D`, `CTRL + \`), and implementing a variety of **builtins** (such as `exit`, `echo`, `env`, `export`, `unset`, `cd`, and `pwd`).

This project was developed in **C** for **42School**, and it’s a great way to practice system programming and get a deeper understanding of how shells work!

## 🛠️ **Features**

**minishell** allows you to interact with the shell in a way that mimics the behavior of a standard bash shell. Some of the key features include:

- 📝 **User Input Parsing**: Handle the parsing of commands and arguments in user input.
- 🔄 **Command Execution**: Execute commands with support for **pipes**, **redirections**, and **heredoc**.
- ⚡ **Signal Management**: Manage signals like `CTRL + C`, `CTRL + D`, and `CTRL + \` gracefully.
- 🧑‍💻 **Builtins**: Implement several built-in commands like:
  - `exit`
  - `echo`
  - `env`
  - `export`
  - `unset`
  - `cd`
  - `pwd`

It’s like having your very own bash shell at your fingertips!

## 🛠️ Usage
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
