#!/bin/env python3
# -*- coding: utf-8 -*-

import sys
from pathlib import Path
from scipy.spatial.transform import Rotation
import struct

outpath = Path("maps")
outpath.mkdir(exist_ok=True)

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

		with open(outpath / Path(arg).with_suffix(".hmp"), "w") as hmp:
			hmp.write(
f"""{{
"classname" "worldspawn"
"message" "{Path(arg).stem}"
"_sky" "vert_sky01a"
"_fog" "0.01"
"_maxdrawdist" "0"
"_segmentsize" "1024"
"_minxsegment" "0"
"_minysegment" "0"
"_maxxsegment" "16"
"_maxysegment" "16"
"_seed" "{arg}"
"_generator" "ipl2hmp.py"
"_exterior" "solid"
"_defaultgroundtexture" "ground"
"_defaultgroundheight" "0"
"_defaultwatertexture" "water"
"_defaultwaterheight" "-512"
}}
{{
"classname" "info_player_start"
"origin" "0 0 0"
}}
""")
		basepath = outpath / Path(arg).stem
		basepath.mkdir(exist_ok=True)

		with open(basepath / "block_00_00.hms", "wb") as hms:
			# magic
			hms.write(b"HMMS")
			# version
			hms.write(struct.pack("<L", 2))
			# flags
			hms.write(struct.pack("<L", 0))
			# height placeholder
			hms.write(struct.pack("<f", 0))
			# holes
			for i in range(8):
				hms.write(struct.pack("<B", 0))
			# water
			hms.write(struct.pack("<L", 0))
			# textures
			for i in range(4):
				hms.write(struct.pack("32s", "".encode("ascii")))
			# static ents
			hms.write(struct.pack("<L", len(ipldata["inst"])))
			for entry in ipldata["inst"]:
				print(f"placing \"models/gta3/{entry.model}.iqm\"")
				modelname = f"models/gta3/{entry.model}.iqm\0"
				hms.write(struct.pack("<L", 1))
				hms.write(struct.pack(f"<{len(modelname)}s", modelname.encode("ascii")))
				hms.write(struct.pack("<fff", entry.origin[0], entry.origin[1], entry.origin[2]))
				rot = Rotation.from_quat(entry.rotation)
				rot = rot.as_matrix()
				hms.write(struct.pack("<fffffffff", rot[0][0], rot[0][1], rot[0][2], rot[1][0], rot[1][1], rot[1][2], rot[2][0], rot[2][1], rot[2][2]))
				hms.write(struct.pack("<f", 1))
