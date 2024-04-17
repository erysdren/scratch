#!/bin/bash

mkdir -p ./transcoded

for input in "$@"; do
	ffmpeg -i "$input" -c:v libx264 -crf 20 -vf "scale=640:480,setsar=1:1" -c:a copy -c:s copy "./transcoded/$input"
done
