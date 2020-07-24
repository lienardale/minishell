echo
echo "--- TESTS export ---"
echo

export coucou=salut ;
env | grep coucou
echo

export cou=ec
export bon=ho
$cou$bon salut
echo

# export PATH= ;
# env | grep -v PATH
# echo
