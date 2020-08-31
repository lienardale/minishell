
# $tmp 
# tmp = ps | grep minishell 
# if [[tmp != NULL]]; then
	ps | grep minishell | cut -b 1,2,3,4,5 | xargs kill
# fi
# if [[tmp == NULL]]; then
	ps | grep bash | grep -v 'grep' | cut -b 1,2,3,4,5 | xargs kill
# fi
