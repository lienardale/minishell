echo
echo "--- TESTS export ---"
echo

# export coucou=salut ;
# env | grep coucou
# echo

export cou=ec ; export bon=ho ; $cou$bon salut

# $coucou salut

# av[0] = |$coucou|
# av[1] = |salut|

# ->

# av[0] = |salut|

echo

# export PATH= ;
# env | grep -v PATH
# echo
