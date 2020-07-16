echo "--- TEST > ---"

echo coucou > test.log
ls
cat test.log
rm test.log

echo coucou > test.log\ coucou
ls
cat test.log\ coucou
rm cat test.log\ coucou

echo coucou > 0test.log > 1test.log
ls
cat 0test.log
cat 1test.log
rm 0test.log 1test.log