#!/bin/bash

for FILE in ./*.wav; do
	ffmpeg -i "$FILE" -ab 320k "${FILE%.*}.mp3"
done
