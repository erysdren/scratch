#!/bin/bash

for FILE in ./*.mp4; do
	ffmpeg -i "$FILE" -ab 320k "${FILE%.*}.mp3"
done
