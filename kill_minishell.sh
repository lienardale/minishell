ps aux | grep minishell | grep -v grep | cut -b 10,11,12,13,14,15 | xargs kill
