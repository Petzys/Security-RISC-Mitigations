sudo perf stat ffmpeg -loglevel error -c:v h264 -i test_video.mp4 -c:v libx264 -c:a mp3 test_video.avi # Using software encoder
rm -f test_video.avi