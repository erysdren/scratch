#!/bin/bash

for FILE in ./*.LBM; do
	lbmtool "$FILE" --png "${FILE%.*}.PNG"
done
