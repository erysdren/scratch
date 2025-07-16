#!/bin/env python3
# -*- coding: utf-8 -*-

import sys
from pathlib import Path
from scipy.spatial.transform import Rotation

globalscale = 1

# then convert the item placement info to map
for arg in sys.argv[1:]:
	with open(arg, "r") as ipl:

		print(arg)

		class iplentry:
			def __init__(self):
				self.id = 0
				self.model = ""
				self.interior = 0
				self.origin = [0, 0, 0]
				self.unknown = [0, 0, 0]
				self.rotation = [0, 0, 0, 1]

		ipldata = {}

		recognizedsections = ["inst", "cull", "pick", "path"]

		iplsection = ""
		while line := ipl.readline().strip():
			if line.startswith("#"):
				continue
			if not iplsection:
				iplsection = line
				ipldata[iplsection] = []
			elif line == "end":
				iplsection = ""
			elif iplsection not in recognizedsections:
				print(f"error: unrecognized ipl section {iplsection}")
				sys.exit(1)
			else:
				tokens = line.split(", ")
				entry = iplentry()
				entry.id = int(tokens[0])
				entry.model = tokens[1]
				if len(tokens) == 13:
					entry.interior = int(tokens[2])
					entry.origin[0] = float(tokens[3])
					entry.origin[1] = float(tokens[4])
					entry.origin[2] = float(tokens[5])
					entry.unknown[0] = float(tokens[6])
					entry.unknown[1] = float(tokens[7])
					entry.unknown[2] = float(tokens[8])
					entry.rotation[0] = float(tokens[9])
					entry.rotation[1] = float(tokens[10])
					entry.rotation[2] = float(tokens[11])
					entry.rotation[3] = float(tokens[12])
				else:
					entry.origin[0] = float(tokens[2])
					entry.origin[1] = float(tokens[3])
					entry.origin[2] = float(tokens[4])
					entry.unknown[0] = float(tokens[5])
					entry.unknown[1] = float(tokens[6])
					entry.unknown[2] = float(tokens[7])
					entry.rotation[0] = float(tokens[8])
					entry.rotation[1] = float(tokens[9])
					entry.rotation[2] = float(tokens[10])
					entry.rotation[3] = float(tokens[11])
				ipldata[iplsection].append(entry)

		with open(Path(arg).with_suffix(".map"), "w") as map:
			map.write(f"{{\n\"classname\" \"worldspawn\"\n}}\n")

			for entry in ipldata["inst"]:
				print(f"placing \"models/gta3/{entry.model}.iqm\"")
				rot = Rotation.from_quat(entry.rotation)
				rot = rot.as_euler("XYZ", True)
				map.write(f"{{\n\"classname\" \"misc_model\"\n")
				map.write(f"\"origin\" \"{entry.origin[0] * globalscale} {entry.origin[1] * globalscale} {entry.origin[2] * globalscale}\"\n")
				map.write(f"\"angles\" \"{rot[0]} {rot[1]} {rot[2]}\"\n")
				map.write(f"\"model\" \"models/gta3/{entry.model}.iqm\"\n")
				map.write(f"}}\n")
