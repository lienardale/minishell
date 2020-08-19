

# ours segfaults
# echo test1\
# ; echo test2
# echo ;;;;
# echo test | | wc; echo lol
# echo lol; echo test | | wc 
# |
#  

# ours doesnt trim the isspaces
# echo -n 2 : \	\	coucou
# echo -n 2 : 		coucou

# is ok I guess ?
# export PATH= ;
# ls
# echo

# echo $RIP

# echo
# echo 7
# echo
# echo coucou > 0test.log 1test.log 2test.log > 3test.log
# echo coucou > ../tests/test.log

# wrong error msg
# /bin/ls/lol
# ./srcs
# README.md
# echo lol > output

#has to do with parsing of options
# echo -n -n One"argument"'lo'l; echo "n"''ee"d"more'?'''"'"
# echo -n -n return

#one too many \ at the end
# echo '\\please\\' "\"fail\\"

# exits instead of not exiting
# echo test | exit
# cat run.sh | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat

# pb
# echo \
# echo "
# echo '