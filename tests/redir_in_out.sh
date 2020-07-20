echo "--- TEST >< ---"

ls > test_file2
grep .sh < test_file2 > test_file1

cat Dockerfile > test_file1 < test_file2

