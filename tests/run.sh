#bin/bash
rm tests/bash.txt tests/us.txt tests/diff.txt
touch tests/bash.txt tests/us.txt

./minishell tests/test.sh >> tests/us.txt
bash tests/test.sh >> tests/bash.txt

diff tests/us.txt tests/bash.txt
diff tests/us.txt tests/bash.txt > tests/diff.txt
