meta:
  id: quake_pak
  title: Quake PAK
  application: Quake
  file-extension: pak
  license: CC0-1.0
  endian: le

doc: |
  Quake PAK archive format. A simple table of filenames and offsets, stored
  uncompressed.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: magic
    contents: "PACK"
  - id: ofs_entries
    type: s4
  - id: len_entries
    type: s4

types:
  entry:
    seq:
      - id: name
        type: strz
        encoding: ascii
        size: 56
      - id: ofs_data
        type: s4
      - id: len_data
        type: s4
    instances:
      data:
        io: _root._io
        pos: ofs_data
        size: len_data

instances:
  entries:
    pos: ofs_entries
    type: entry
    size: 64
    repeat: expr
    repeat-expr: len_entries / 64
