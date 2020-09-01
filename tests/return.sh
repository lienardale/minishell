echo
echo "--- TESTS return value ---"
echo

rm -f temp
echo $?

echo coucou
echo $?

echo exit > temp
$SHELL temp
# exit
echo $?

ls lishdzfgl
echo $?

# exit 1 2
# echo $?

sdffs
echo $?

echo exit 1 2 > temp
$SHELL < temp
# check in VM if exits or no (exits in 3.2, does not in 5.0)
echo $?

echo ls pouet > temp


rm -f temp
