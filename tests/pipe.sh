echo
echo "--- TESTS | ---"
echo

echo "expected output : coucou"
echo "coucou
bonjour
salut" | grep coucou
echo

echo "expected output : coucou"
echo | echo coucou
echo

# echo "expected output : coucou$"
# echo | echo coucou | cat -e
# echo

echo "expected output : coucou"
ls | echo coucou
echo

echo "expected output : ls output"
echo coucou | ls
echo

echo "expected output : ls output with $"
ls | cat -e
echo

echo "expected output : ls sorted output"
ls | sort
echo

echo "expected output : .sh files"
ls | grep .sh
echo

echo "expected output : sorted .sh files"
ls | grep .sh | sort
echo

# echo "expected output : sorted .sh files with $"
# ls | grep .sh | sort | cat -e
# echo

# echo "expected output : one ls output"
# ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls | ls 
# echo 