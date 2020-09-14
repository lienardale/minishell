#bin/bash

make
read -p 'Which test ?: ' test

if [ "$test" = "all" ] ; then
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/cat.sh 2> leak.log ; echo ; echo CAT ; echo > leaks.log ; tail leak.log >> leaks.log

	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/ls.sh 2>> leak.log ; echo \nLS\n > leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/echo.sh 2>> leak.log ; echo \nECHO\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/pwd.sh 2>> leak.log ; echo \nPWD\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/cd.sh 2>> leak.log ; echo \nCD\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/env.sh 2>> leak.log ; echo \nENV\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/export.sh 2>> leak.log ; echo \nEXPORT\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/unset.sh 2>> leak.log ; echo \nUNSET\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/exit.sh 2>> leak.log ; echo \nEXIT\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/semi_colon.sh 2>> leak.log ; echo \nSEMICOLON\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/quote.sh 2>> leak.log ; echo \nQUOTE\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/backslash.sh 2>> leak.log ; echo \nBKSLH\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/pipe.sh 2>> leak.log ; echo \nPIPE\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/redir_in.sh 2>> leak.log ; echo \nREDIN\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/redir_out.sh 2>> leak.log ; echo \nREDOUT\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/append.sh 2>> leak.log ; echo \nAPPEND\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/redir_nb.sh 2>> leak.log ; echo \nREDNB\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/parsing.sh 2>> leak.log ; echo \nPARSING\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/return.sh 2>> leak.log ; echo \nRETURN\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/roalvalre.sh 2>> leak.log ; echo \nROALVARE\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell < alientest_minishell/echo.sh 2>> leak.log ; echo \nSTDIN1\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell < alientest_minishell/ls.sh 2>> leak.log ; echo \nSTDIN2\n >> leaks.log ; tail leak.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell test/backslash.sh 2>> leak.log ; tail leak.log ; echo \nERROR1\n >> leaks.log >> leaks.log
	echo\n----- -----\n >> leaks.log
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/error.sh 2>> leak.log ; echo \nERROR2\n >> leaks.log ; tail leak.log >> leaks.log
elif [ -n "$test" ] ; then
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/$test.sh 2> leaks.log
else
	valgrind --leak-check=full --show-leak-kinds=all ./minishell 2> leaks.log
fi
tail leaks.log