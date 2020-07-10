#bin/bash
make
rm tests/bash.txt tests/us.txt tests/diff.txt
touch tests/bash.txt tests/us.txt

./minishell tests/echo.sh >> tests/us.txt
bash tests/echo.sh >> tests/bash.txt

./minishell tests/ls.sh >> tests/us.txt
bash tests/ls.sh >> tests/bash.txt

./minishell tests/pwd.sh >> tests/us.txt
bash tests/pwd.sh >> tests/bash.txt

./minishell tests/cat.sh >> tests/us.txt
bash tests/cat.sh >> tests/bash.txt

./minishell tests/semi_colon.sh >> tests/us.txt
bash tests/semi_colon.sh >> tests/bash.txt

./minishell tests/quote.sh >> tests/us.txt
bash tests/quote.sh >> tests/bash.txt

./minishell tests/backslash.sh >> tests/us.txt
bash tests/backslash.sh >> tests/bash.txt

# ./minishell tests/pipe.sh >> tests/us.txt
# bash tests/pipe.sh >> tests/bash.txt

# ./minishell tests/redir_in.sh >> tests/us.txt
# bash tests/redir_in.sh >> tests/bash.txt

# ./minishell tests/redir_out.sh >> tests/us.txt
# bash tests/redir_out.sh >> tests/bash.txt

# ./minishell tests/return.sh >> tests/us.txt
# bash tests/return.sh >> tests/bash.txt

./minishell tests/env.sh >> tests/us.txt
bash tests/env.sh >> tests/bash.txt

./minishell tests/export.sh >> tests/us.txt
bash tests/export.sh >> tests/bash.txt

./minishell tests/unset.sh >> tests/us.txt
bash tests/unset.sh >> tests/bash.txt

# ./minishell tests/exit.sh >> tests/us.txt
# bash tests/exit.sh >> tests/bash.txt

# ./minishell tests/signal.sh >> tests/us.txt
# bash tests/signal.sh >> tests/bash.txt

diff tests/us.txt tests/bash.txt
diff tests/us.txt tests/bash.txt > tests/diff.txt