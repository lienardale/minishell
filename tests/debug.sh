# ls | ls | ls | cat -e

echo "11 : expected output :	bonjour
			coucou
			salut
			salut"
echo "salut
coucou
bonjour
salut" | sort
echo

echo "8 : expected output : sorted .sh files"
ls | grep .sh | sort
echo

# echo "expected output : coucou$"
# echo | echo coucou | cat -e
# echo




# echo test1\
# ; echo test2
# 

# echo -n 2 : \	\	coucou
# echo -n 2 : 		coucou

# export PATH= ;
# env | grep -v PATH
# echo

# export coucou=salut ;
# env | grep coucou
# echo

# echo
# echo 7
# echo
# echo coucou > 0test.log 1test.log 2test.log > 3test.log