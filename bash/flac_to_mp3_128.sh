#!/bin/bash

for FILE in ./*.flac; do
	ffmpeg -i "$FILE" -ab 128k "${FILE%.*}.mp3"
done
