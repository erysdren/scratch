#!/bin/env python3
# -*- coding: utf-8 -*-

from pathlib import Path
import sys
import math
from scipy.spatial.transform import Rotation

from cpj_utils import *

from formats.frm import Frm
from formats.geo import Geo
from formats.srf import Srf
from formats.skl import Skl
from formats.seq import Seq
from formats.mac import Mac

cpj_data = load_cpj_data(sys.argv[1])

outfilename = Path(sys.argv[1]).with_suffix(".iqe")
outfile = open(outfilename, "w")
outfile.write("# Inter-Quake Export\n\n")

class Bone():
	def __init__(self, name, index, parent, translate, rotate, scale):
		self.name = name
		self.index = index
		self.parent = parent
		self.translate = translate
		self.rotate = rotate
		self.scale = scale
		self.children = []

def resolve_bone_name(bones, index):
	for i,bone in enumerate(bones):
		if i == index:
			return bone.name
	return None

def sort_bones(inbones):
	bones = {}
	worklist = [inbones[key] for key in inbones if inbones[key].parent == None]
	for index, bone in enumerate(worklist):
		bones[bone.name] = Bone(bone.name, index, bone.parent, bone.translate, bone.rotate, bone.scale)
		for child in bone.children:
			if child not in worklist:
				worklist.append(child)
	return bones

# create bone tree
skl = Skl.from_bytes(cpj_data["SKLB"][-1])
bones = {}
for i,bone in enumerate(skl.data_block.bones):
	bones[bone.name] = Bone(bone.name, i, resolve_bone_name(skl.data_block.bones, bone.parent_index), bone.base_translate, bone.base_rotate, bone.base_scale)

# resolve parents and children
for key in bones:
	bone = bones[key]
	if bone.parent in bones:
		bones[bone.parent].children.append(bone)

# sort bones
bones = sort_bones(bones)
bonelist = sorted(bones.values(), key = lambda bone: bone.index)

def remap_bone_index(index):
	return bones[resolve_bone_name(skl.data_block.bones, index)]

# write bones
for bone in bonelist:
	if bone.parent == None:
		parent_index = -1
	else:
		parent_index = bones[bone.parent].index
	outfile.write(f"joint \"{bone.name}\" {parent_index}\n")
	outfile.write(f"\tpq {bone.translate.x} {bone.translate.y} {bone.translate.z}")
	outfile.write(f" {bone.rotate.v.x} {bone.rotate.v.y} {bone.rotate.v.y} {bone.rotate.s}")
	outfile.write(f" {bone.scale.x} {bone.scale.y} {bone.scale.z}\n")

# write sequences
for seq_byte_data in cpj_data["SEQB"]:
	seq = Seq.from_bytes(seq_byte_data)
	print(f"writing {seq.name}")
	outfile.write(f"\nanimation \"{seq.name}\"\n\tframerate {seq.play_rate}\n")
	# write frames
	for frame in seq.data_block.frames:
		# build translation array
		transform = [[0 for i in range(10)] for j in range(len(skl.data_block.bones))]
		# setup base
		for i in range(len(bonelist)):
			transform[i][0] = bonelist[i].translate.x
			transform[i][1] = bonelist[i].translate.y
			transform[i][2] = bonelist[i].translate.z
			transform[i][3] = bone.rotate.v.x
			transform[i][4] = bone.rotate.v.y
			transform[i][5] = bone.rotate.v.z
			transform[i][6] = bone.rotate.s
			transform[i][7] = bonelist[i].scale.x
			transform[i][8] = bonelist[i].scale.y
			transform[i][9] = bonelist[i].scale.z
		for i in range(frame.first_bone_translate, frame.first_bone_translate + frame.num_bone_translate):
			bone = remap_bone_index(seq.data_block.bone_translate[i].bone_index)
			transform[bone.index][0] = seq.data_block.bone_translate[i].translate.x
			transform[bone.index][1] = seq.data_block.bone_translate[i].translate.y
			transform[bone.index][2] = seq.data_block.bone_translate[i].translate.z
		for i in range(frame.first_bone_rotate, frame.first_bone_rotate + frame.num_bone_rotate):
			bone = remap_bone_index(seq.data_block.bone_rotate[i].bone_index)
			rot = Rotation.from_euler("zxy", [seq.data_block.bone_rotate[i].roll * math.pi / 32768, seq.data_block.bone_rotate[i].pitch * math.pi / 32768, seq.data_block.bone_rotate[i].yaw * math.pi / 32768], degrees=False)
			rot = rot.as_quat()
			transform[bone.index][3] = rot[0]
			transform[bone.index][4] = rot[1]
			transform[bone.index][5] = rot[2]
			transform[bone.index][6] = rot[3]
		for i in range(frame.first_bone_scale, frame.first_bone_scale + frame.num_bone_scale):
			bone = remap_bone_index(seq.data_block.bone_scale[i].bone_index)
			transform[bone.index][7] = seq.data_block.bone_scale[i].scale.x
			transform[bone.index][8] = seq.data_block.bone_scale[i].scale.y
			transform[bone.index][9] = seq.data_block.bone_scale[i].scale.z
		# write it
		outfile.write("\nframe\n")
		for t in transform:
			outfile.write(f"pq {t[0]} {t[1]} {t[2]} {t[3]} {t[4]} {t[5]} {t[6]} {t[7]} {t[8]} {t[9]}\n")

outfile.close()
