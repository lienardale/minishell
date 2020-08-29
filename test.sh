#bin/bash

make
rm tests/bash.txt tests/us.txt tests/diff.txt tests/us_errors.txt tests/bash_errors.txt tests/diff_errors.txt

read -p 'Which test ?: ' test
./minishell tests/$test.sh 1>> tests/us.txt 2>> tests/us_errors.txt
bash tests/$test.sh 1>> tests/bash.txt 2>> tests/bash_errors.txt

diff tests/us.txt tests/bash.txt
diff tests/us.txt tests/bash.txt > tests/diff.txt

diff tests/us_errors.txt tests/bash_errors.txt
diff tests/us_errors.txt tests/bash_errors.txt > tests/diff_errors.txt