#!/bin/bash

for FILE in ./*.flac; do
	ffmpeg -i "$FILE" -ab 320k "${FILE%.*}.mp3"
done
