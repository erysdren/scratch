#!/bin/bash

for DIR in */ ; do
	if [ -d "$DIR/.git" ]; then
		BUNDLE=$(basename $DIR).bundle
		echo "creating $BUNDLE"
		cd "$DIR"
		git bundle create "../$BUNDLE" --all --quiet
		cd ".."
		mv "$DIR" "DONE/"
	fi
done
