
# ours segfaults
# expected :
# "test1
# test2"
# echo test1\
# ; echo test2

# |
 
# ecjo ;;;


# expected :
# stdin_mode : "bash: syntax error near unexpected token `;;'"
# in_file_mode :
# "tests/debug.sh: line 6: syntax error near unexpected token `;;'
# tests/debug.sh: line 6: `echo ;;;;'"
# ->doesn't read the .sh further
# echo ;;;;

# expected :
# stdin_mode : "bash: syntax error near unexpected token `;'"
# in_file_mode :
# "tests/debug.sh: line 6: syntax error near unexpected token `;'
# tests/debug.sh: line 6: `echo ; ; ; ;'"
# ->doesn't read the .sh further
# echo ; ; ; ;

# expected :
# stdin_mode : "bash: syntax error near unexpected token `|'"
# in_file_mode :
# "tests/debug.sh: line 7: syntax error near unexpected token `|'
# tests/debug.sh: line 7: `echo test | | wc; echo lol'"
# ->doesn't read the .sh further
# echo test | | wc; echo lol


# ALL ABOVE THIS IS OK

ls |
ls >

#rdir pb
# export > 0test.log
# cat nop.txt 2> error.txt
# cat Dockerfile 1> 0test.log
# echo coucou > ../tests/test.log
# echo coucou > 0test.log 1test.log 2test.log > 3test.log
# echo coucou > ../tests/test.log
# echo lol > srcs


# malloc errors
# export PATH= ;
# cat Dockerfile
# ls
# echo

# wrong error msg
# /bin/ls/lol
# ./srcs
# README.md

# exits instead of not exiting
# echo test | exit
# exit | echo test

# pb prompt
# echo \
# echo "
# echo '

# /!\ prompt must be in STDERR

# see how vm behaves for this one
# exit 1 2
# echo $?

# ps -ef | grep "minishell" | grep -v 'grep' | awk '{print $2}' | xargs kill
# ps -ef | grep ./minishell | grep -v 'grep' | awk '{print $2}' | xargs kill
# ps -ef | grep ./minishell | grep -v 'grep' | cut -b 7,8,9,10,11 | xargs kill

# echo lol; echo test | | wc

