#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from kaitaistruct import KaitaiStream
from gta3_dir import Gta3Dir

dirFile = open("gta3.dir", "rb")
imgFile = open("gta3.img", "rb")

dirStream = KaitaiStream(dirFile)
imgStream = KaitaiStream(imgFile)

gta3dir = Gta3Dir(imgStream, dirStream)

for f in gta3dir.files:
	print(f"{f.name}: {f.len_data * gta3dir.sector_size} bytes at {f.ofs_data * gta3dir.sector_size}")

dirFile.close()
imgFile.close()
