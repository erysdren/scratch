#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from pathlib import Path
from kaitaistruct import KaitaiStream
from gta3_dir import Gta3Dir
from gta3_col import Gta3Col
from renderware_binary_stream import RenderwareBinaryStream

dirFile = open("gta3.dir", "rb")
imgFile = open("gta3.img", "rb")

outpath = Path("gta3")
outpath.mkdir(exist_ok=True)

dirStream = KaitaiStream(dirFile)
imgStream = KaitaiStream(imgFile)

gta3dir = Gta3Dir(imgStream, dirStream)

def convert_color(color):
	return f"{float(color.r) / 255} {float(color.g) / 255} {float(color.b) / 255} {float(color.a) / 255}"

# first write the models to iqe
for f in gta3dir.files:
	if f.name.endswith(".dff"):
		dff = RenderwareBinaryStream.from_bytes(f.data)
		for entry in dff.body.entries:
			if entry.code == dff.Sections.geometry_list and len(entry.body.entries) > 0:
				modelname = Path(f.name)
				iqepath = outpath / modelname.with_suffix(".iqe")
				with open(iqepath, "w") as iqe:
					print(f"writing \"{iqepath}\"")
					geometry = entry.body.entries[0]
					iqe.write("# Inter-Quake Export\n\n")
					iqe.write(f"mesh \"{modelname.stem}\"\n\tmaterial \"{modelname.stem}\"\n\n")
					morph_target = geometry.body.header.morph_targets[0]
					if geometry.body.header.is_textured:
						uv_layer = geometry.body.header.geometry.uv_layers[0]
					for i, vertex in enumerate(morph_target.vertices):
						iqe.write(f"vp {vertex.x} {vertex.y} {vertex.z}\n")
						if geometry.body.header.is_prelit:
							iqe.write(f"\tvc {convert_color(geometry.body.header.geometry.prelit_colors[i])}\n")
						if geometry.body.header.is_textured:
							iqe.write(f"\tvt {uv_layer.tex_coords[i].u} {uv_layer.tex_coords[i].v}\n")
						if morph_target.has_normals:
							iqe.write(f"vn {morph_target.normals[i].x} {morph_target.normals[i].y} {morph_target.normals[i].z}\n")
					iqe.write("\n")
					for triangle in geometry.body.header.geometry.triangles:
						iqe.write(f"fm {triangle.vertex3} {triangle.vertex2} {triangle.vertex1}\n")
	elif f.name.endswith(".txd"):
		txd = RenderwareBinaryStream.from_bytes(f.data)
		pass
	elif f.name.endswith(".col"):
		# TODO
		# col = Gta3Col.from_bytes(f.data)
		pass

dirFile.close()
imgFile.close()
