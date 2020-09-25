42 Paris project - minishell

Recoding a shell in C

Goals :

- introduce us to the processes through fork, wait, kill

- gain a deeper understanding of file descriptors

- step up in termes of parsing and error handling

Features : 

- Writes a prompt waiting for a new command

- Searches and launches the right executable (based on the PATH environment variable, or using a relative or absolute path)

- Builtins cmds :
	- echo

	- cd

	- pwd

	- export

	- unset

	- env

	- exit

- Handles ';', single and double quotes (except in multiline), and the use of '\'

- Redirections : '<', '>' and '>>'

- Pipes

- Environment variables

- Return values ("echo $?")

- Signals : ctrl-C, ctrl-D, ctrl-\
