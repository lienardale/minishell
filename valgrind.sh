#bin/bash

make
read -p 'Which test ?: ' test
valgrind --leak-check=full --show-leak-kinds=all ./minishell $test.sh 2> leaks.log
tail leaks.log