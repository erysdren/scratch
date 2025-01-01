meta:
  id: hrot_pak
  title: HROT Archive
  application: HROT
  file-extension: pak
  license: CC0-1.0
  endian: le

doc: |
  HROT Archive file, seemingly inspired by Quake (1996)'s PAK format.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: magic
    contents: "HROT"
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
        size: 120
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
    size: 128
    repeat: expr
    repeat-expr: len_entries / 128
