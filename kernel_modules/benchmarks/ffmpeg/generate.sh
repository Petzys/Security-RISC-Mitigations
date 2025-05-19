rm -f test_video.mp4 
ffmpeg -loglevel error -f lavfi -i testsrc=duration=15:size=1280x720:rate=30 \
       -f lavfi -i sine=frequency=1000:duration=15 \
       -c:v libx264 -preset veryfast -c:a aac -b:a 128k \
       -pix_fmt yuv420p -shortest test_video.mp4
       