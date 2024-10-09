#!/bin/bash

for FILE in *.odt; do
	echo "${FILE} >> ${FILE%.*}.md"
	pandoc -f odt -t gfm --ascii=true --columns 79 -i ${FILE} >> ${FILE%.*}.md
done
