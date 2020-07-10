
echo
echo "--- TESTS unset ---"

export coucou=salut
env
unset coucou
env
unset PATH
env

echo