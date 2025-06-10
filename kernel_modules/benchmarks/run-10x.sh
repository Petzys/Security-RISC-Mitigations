#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

if [[ $EUID -ne 0 ]]; then
    echo "This script must be run as root (use sudo)" 
    exit 1
fi

echo "Running tests 10 times"
sleep 10 # time to disconnect from tmux/ssh

./run-all.sh
sudo mv -f "results/" "results0/"
./run-all.sh
sudo mv -f "results/" "results1/"
./run-all.sh nomake
sudo mv -f "results/" "results2/"
./run-all.sh nomake
sudo mv -f "results/" "results3/"
./run-all.sh nomake
sudo mv -f "results/" "results4/"
./run-all.sh nomake
sudo mv -f "results/" "results5/"
./run-all.sh nomake
sudo mv -f "results/" "results6/"
./run-all.sh nomake
sudo mv -f "results/" "results7/"
./run-all.sh nomake
sudo mv -f "results/" "results8/"
./run-all.sh nomake
sudo mv -f "results/" "results9/"
