#bin/bash

make
read -p 'Which test ?: ' test

if [ -n "$test" ] ; then
	valgrind --leak-check=full --show-leak-kinds=all ./minishell alientest_minishell/$test.sh 2> leaks.log
else
	valgrind --leak-check=full --show-leak-kinds=all ./minishell 2> leaks.log
fi
tail leaks.log