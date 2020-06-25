#bin/bash
rm bash.txt us.txt
./minishell test.sh >> us.txt
bash test.sh >> bash.txt
diff us.txt bash.txt
diff us.txt bash.txt > diff.txt
