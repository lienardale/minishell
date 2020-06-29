echo "--- TESTS ECHO ---"
echo coucou
echo -n coucou
echo "coucou"
echo -n "coucou"
echo "coucou" "bonjour"
echo 'coucou' bonjour
echo "coucou
1
2
3
4
5
6
7
8
9
10
11
12"

echo

echo "--- TESTS LS ---"
ls
ls -la

echo

echo "--- TESTS PWD ---"
pwd
pwd salut

echo

echo "--- TESTS CAT ---"
cat Dockerfile
cat -e Dockerfile

echo

echo "--- TESTS ; ---"
ls ; ls ; ls
ls ; pwd
echo "coucou
1
2
3
4
5
6
7
8
9
10
11
12" ; ls ; pwd