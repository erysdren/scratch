meta:
  id: mact_wad
  title: MACT Library WAD
  file-extension: wad
  license: CC0-1.0
  endian: le

doc: |
  Customized id Software WAD format used by Apogee Software in their MACT
  library.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: magic
    contents: "IWAD"
  - id: num_lumps
    type: u4
  - id: ofs_lumps
    type: u4

types:
  lump:
    seq:
      - id: ofs_data
        type: u4
      - id: len_data
        type: u4
      - id: type
        type: s4
      - id: name
        type: strz
        encoding: ascii
        size: 8
    instances:
      data:
        pos: ofs_data
        size: len_data
        type:
          switch-on: type
          cases:
            1: pic
            2: lpic
            3: post
            8: palette
            11: miptex
            17: colormap

  pic:
    seq:
      - id: width
        type: s2
      - id: height
        type: s2
      - id: pixels
        size: width * height

  lpic:
    seq:
      - id: width
        type: s2
      - id: height
        type: s2
      - id: origin_x
        type: s2
      - id: origin_y
        type: s2
      - id: pixels
        size: width * height

  post:
    seq:
      - id: width
        type: s2
      - id: height
        type: s2
      - id: pixels
        size: width * height

  palette:
    seq:
      - id: entries
        type: rgb24
        repeat: expr
        repeat-expr: 256

  rgb24:
    seq:
      - id: r
        type: u1
      - id: g
        type: u1
      - id: b
        type: u1

  miptex:
    seq:
    - id: width
      type: u1
    - id: height
      type: u1
    - id: num_mips
      type: u1
    - id: reserved
      type: u1
    - id: offsets
      type: u2
      repeat: expr
      repeat-expr: num_mips
    - id: pixels
      repeat: expr
      repeat-expr: num_mips
      size: (width >> _index) * (height >> _index)

  colormap:
    seq:
      - id: reverse
        type: s4
      - id: num_levels
        type: u1
      - id: num_dark
        type: u1
      - id: data
        size: 256 * num_levels

instances:
  lumps:
    pos: ofs_lumps
    type: lump
    repeat: expr
    repeat-expr: num_lumps
