#!/bin/bash

for VTT in ./*.vtt; do
	ffmpeg -i "$VTT" -vn -an -scodec srt "${VTT%.*}.srt"
done
