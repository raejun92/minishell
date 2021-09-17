readline, rl_on_new_line, rl_replace_line,
rl_redisplay, add_history, printf, malloc, free,
write, open, read, close, fork, wait, waitpid,
wait3, wait4, signal, kill, exit, getcwd, chdir,
stat, lstat, fstat, unlink, execve, dup, dup2,
pipe, opendir, readdir, closedir, strerror, errno,
isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr,
tcgetattr, tgetent, tgetflag, tgetnum, tgetstr,
tgoto, tputs

# Shell Operation
1. Reads its input from a file (see Shell Scripts), from a string supplied as an argument to the -c invocation option (see Invoking Bash), or from the user’s terminal.
2. Breaks the input into words and operators, obeying the quoting rules described in Quoting. These tokens are separated by metacharacters. Alias expansion is performed by this step (see Aliases).
3. Parses the tokens into simple and compound commands (see Shell Commands).
4. Performs the various shell expansions (see Shell Expansions), breaking the expanded tokens into lists of filenames (see Filename Expansion) and commands and arguments.
5. Performs any necessary redirections (see Redirections) and removes the redirection operators and their operands from the argument list.
6. Executes the command (see Executing Commands).
7. Optionally waits for the command to complete and collects its exit status (see Exit Status).


# error
- bash: echo >>>>(3개 이상) -> bash: syntax error near unexpected token `>>'
- bash: echo >>> -> bash: syntax error near unexpected token `>'
- bash: abcd -> bash: abcd: command not found
- bash: echo > $CCC(존재하지 않는 환경변수) -> bash: $CCC: ambiguous redirect

# $?
- 0 -> 잘 처리 됐을 때
- 1 -> 커맨드 잘못된 옵션
- 127 -> command not found
- 258 -> syntax error