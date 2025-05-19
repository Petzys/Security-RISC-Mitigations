base64 /dev/urandom | head -c 10000000 > testfile
sudo perf stat tar -czf testfile.tar.gz testfile
rm -f testfile.tar.gz