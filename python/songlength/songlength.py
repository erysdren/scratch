#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from pathlib import Path
import librosa
import statistics
import datetime

extensions = [
	".mp3", ".ogg", ".flac", ".wav", ".wma"
]
durations = []

if __name__ == "__main__":
	if len(sys.argv) != 2:
		print("usage: python3 songlength.py <DIRECTORY>")
		sys.exit(0)

	p = Path(sys.argv[1])
	for f in p.rglob("*"):
		if (f.is_file()):
			if f.suffixes[0] not in extensions:
				continue
			dur = librosa.get_duration(path=f.as_posix())
			durations.append(dur)
			print(dur)

	print("=============================")
	print(f"parsed {len(durations)} files")
	print("=============================")
	print(f"mean:   {datetime.timedelta(seconds=statistics.mean(durations))}")
	print(f"median: {datetime.timedelta(seconds=statistics.median(durations))}")
	print("=============================")
