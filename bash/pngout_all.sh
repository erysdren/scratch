#!/bin/bash

for FILE in ./*.png; do
	pngout "$FILE" -c2 -f3 -b128 -kbKGD -v
done
