#!/bin/env python3
# -*- coding: utf-8 -*-

import sys
from pathlib import Path
from scipy.spatial.transform import Rotation

from gta3_col import Gta3Col
from renderware_binary_stream import RenderwareBinaryStream

col = Gta3Col.from_file(sys.argv[1])

outpath = Path(Path(sys.argv[1]).stem)
outpath.mkdir(exist_ok=True)

globalscale = 8

# first write the models to iqe
for model in col.models:
	if not model.num_vertices or not model.num_faces:
		continue
	with open(outpath / Path(model.name).with_suffix(".iqe"), "w") as iqe:
		iqe.write("# Inter-Quake Export\n\n")
		iqe.write(f"mesh \"{model.name}\"\n\tmaterial \"{model.name}\"\n\n")
		for vertex in model.vertices:
			iqe.write(f"vp {vertex.x * globalscale} {vertex.y * globalscale} {vertex.z * globalscale}\n");
			iqe.write(f"\tvt {0} {0}\n");
		iqe.write("\n")
		for face in model.faces:
			iqe.write(f"fm {face.a} {face.b} {face.c}\n");

# then convert the item placement info to map
with open(outpath.with_suffix(".ipl"), "r") as ipl:

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

	with open(outpath / outpath.with_suffix(".map"), "w") as map:
		map.write(f"{{\n\"classname\" \"worldspawn\"\n}}\n")

		for entry in ipldata["inst"]:
			rot = Rotation.from_quat(entry.rotation)
			rot = rot.as_euler("ZYX", True)
			map.write(f"{{\n\"classname\" \"misc_model\"\n")
			map.write(f"\"origin\" \"{entry.origin[0] * globalscale} {entry.origin[1] * globalscale} {entry.origin[2] * globalscale}\"\n")
			map.write(f"\"angles\" \"{rot[0]} {rot[1]} {rot[2]}\"\n")
			map.write(f"\"model\" \"models/{outpath.stem}/{entry.model}.iqm\"\n")
			map.write(f"}}\n")
