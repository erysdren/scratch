#!/bin/bash

mkdir -p ./transcoded

for input in "$@"; do
	ffmpeg -i "$input" -c:v libx264 -crf 20 -preset slow -vf "yadif,scale=640:480,setsar=1:1" -b:a 320k "${input%.*}_transcoded.mp4"
done
