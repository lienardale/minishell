

# ours segfaults
# expected :
# "test1
# test2"
echo test1\
; echo test2

|
 ;

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

echo lol; echo test | | wc

# ours doesnt trim the isspaces
# echo -n 2 : \	\	coucou
# echo -n 2 : 		coucou

#rdir pb
# export > 0test.log
# cat nop.txt 2> error.txt
# cat Dockerfile 1> 0test.log
# echo coucou > ../tests/test.log
# echo coucou > 0test.log 1test.log 2test.log > 3test.log
# echo coucou > ../tests/test.log
# echo lol > srcs


#has to do with parsing of options -> ok in cdai
# echo -n -n One"argument"'lo'l; echo "n"''ee"d"more'?'''"'"
# echo -n -n return

# is ok I guess ?
# export PATH= ;
# ls
# echo

# export pouet="echo coucou" ; $pouet
# echo $RIP


# wrong error msg
# /bin/ls/lol
# ./srcs
# README.md


#one too many \ at the end
# echo '\\please\\' "\"fail\\"

# exits instead of not exiting
# echo test | exit
# is ok
# exit | echo test

# pb
# echo \
# echo "
# echo '

# cat run.sh | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat

# /!\ prompt must be in STDERR
