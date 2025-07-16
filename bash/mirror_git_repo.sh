#!/bin/sh

git clone --mirror $1 $2/.git
cd $2
git config --bool core.bare false
git reset --hard HEAD
git clean -fd
git bundle create ../$2.bundle --all
cd ..
trash $2
