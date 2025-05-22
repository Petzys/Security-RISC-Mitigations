#!/bin/bash
cd -- "$(dirname -- "${BASH_SOURCE:-$0}")"

echo "Running ffmpeg"
sudo perf stat -o ../ffmpeg.stat ffmpeg -loglevel error -c:v h264 -i test_video.mp4 -c:v libx264 -c:a mp3 test_video.avi # Using software encoder
rm -f test_video.avi
