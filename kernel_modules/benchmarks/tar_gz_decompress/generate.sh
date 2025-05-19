rm -f testfile testfile.tar.gz
base64 /dev/urandom | head -c 10000000 > testfile
tar -czf testfile.tar.gz testfile
rm -f testfile