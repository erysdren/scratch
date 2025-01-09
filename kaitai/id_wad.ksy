meta:
  id: id_wad
  title: id Software WAD
  file-extension:
    - wad
    - rts
  license: CC0-1.0
  endian: le

doc: |
  The WAD or "Where's All the Data" format, invented by id Software for
  DOOM (1993) and also used by Apogee Software and Valve Software for various
  titles.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: magic
    type: str
    size: 4
    encoding: ascii
    valid:
      any-of: ["'IWAD'", "'PWAD'", "'WAD2'", "'WAD3'", "'WAD4'", "'WAD5'"]
  - id: num_lumps
    type: u4
  - id: ofs_lumps
    type: u4

instances:

  is_doom:
    value: magic == "IWAD" or magic == "PWAD"

  is_quake:
    value: magic == "WAD2"

  is_halflife:
    value: magic == "WAD3"

  is_halflife2:
    value: magic == "WAD4" or magic == "WAD5"

  lumps:
    io: _root._io
    pos: ofs_lumps
    repeat: expr
    repeat-expr: num_lumps
    type:
      switch-on: magic
      cases:
        "'IWAD'": lump_v1
        "'PWAD'": lump_v1
        "'WAD2'": lump_v2
        "'WAD3'": lump_v2
        "'WAD4'": lump_v2
        "'WAD5'": lump_v2

types:

  color24:
    seq:
      - id: r
        type: u1
      - id: g
        type: u1
      - id: b
        type: u1

  lump_v1:
    seq:
      - id: ofs_data
        type: u4
      - id: len_data
        type: u4
      - id: name
        type: strz
        encoding: ascii
        size: 8

  lump_v2:
    seq:
      - id: ofs_data
        type: u4
      - id: len_data_compressed
        type: u4
      - id: len_data_uncompressed
        type: u4
      - id: type
        type: s1
      - id: compressed
        type: s1
      - id: padding
        size: 2
      - id: name
        type: strz
        encoding: ascii
        size: _root.is_halflife2 ? 128 : 16
    instances:
      len_data:
        value: compressed > 0 ? len_data_compressed : len_data_uncompressed
      data:
        pos: ofs_data
        size: len_data
        type:
          switch-on: type
          cases:
            0x40: palette(256)
            0x42: qpic
            0x43: miptex
            0x44: miptex
            0x45: conpic

  mip:
    params:
      - id: index
        type: u1
    instances:
      pixels:
        io: _parent._io
        pos: _parent.offsets[index]
        size: (_parent.width >> index) * (_parent.height >> index)

  miptex:
    seq:
      - id: name
        type: strz
        encoding: ascii
        size: _root.is_halflife2 ? 128 : 16
      - id: width
        type: u4
      - id: height
        type: u4
      - id: view_width
        type: u4
        if: _root.is_halflife2
      - id: view_height
        type: u4
        if: _root.is_halflife2
      - id: reflectivity
        type: f4
        if: _root.is_halflife2
        repeat: expr
        repeat-expr: 3
      - id: offsets
        type: u4
        repeat: expr
        repeat-expr: num_mips
    instances:
      num_mips:
        value: 4
      last_mip:
        value: num_mips - 1
      mips:
        type: mip(_index)
        repeat: expr
        repeat-expr: num_mips
      num_palette_entries:
        pos: offsets[last_mip] + (width >> last_mip) * (height >> last_mip)
        type: u2
        if: _root.is_halflife
      palette:
        pos: offsets[last_mip] + (width >> last_mip) * (height >> last_mip) + 2
        type: palette(num_palette_entries)
        if: _root.is_halflife

  conpic:
    seq:
      - id: pixels
        size: width * height
    instances:
      width:
        value: 320
      height:
        value: 200

  qpic:
    seq:
      - id: width
        type: u4
      - id: height
        type: u4
      - id: pixels
        size: width * height
    instances:
      num_palette_entries:
        pos: (width * height) + 8
        type: u2
        if: _root.is_halflife
      palette:
        pos: (width * height) + 8 + 2
        type: palette(num_palette_entries)
        if: _root.is_halflife

  palette:
    params:
      - id: num_entries
        type: u4
    seq:
      - id: entries
        type: color24
        repeat: expr
        repeat-expr: num_entries

enums:

  versions:
    0x44415749: iwad
    0x44415750: pwad
    0x32444157: wad2
    0x33444157: wad3
    0x34444157: wad4
    0x35444157: wad5
