#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from kaitaistruct import KaitaiStream
from ted5 import Ted5

maptempFile = open("MAPTEMP.WL1", "rb")
mapheadFile = open("MAPHEAD.WL1", "rb")

maptemp = KaitaiStream(maptempFile)
maphead = KaitaiStream(mapheadFile)

ted5 = Ted5(maptemp, maphead)

for m in ted5.maps:
	if m.used:
		print(m.body.name)

maptempFile.close()
mapheadFile.close()
