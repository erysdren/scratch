meta:
  id: mact_rox
  title: MACT Library ROX
  file-extension: rox
  license: CC0-1.0
  endian: le

doc: |
  Customized id Software PAK format used by Apogee Software in their MACT
  library.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: magic
    contents: "ROX\0"
  - id: ofs_entries
    type: s4
  - id: len_entries
    type: s4

instances:
  len_entry:
    value: 64

  entries:
    pos: ofs_entries
    type: entry
    size: len_entry
    repeat: expr
    repeat-expr: len_entries / len_entry

types:
  entry:
    seq:
      - id: name
        type: strz
        encoding: ascii
        size: _root.len_entry - 8
      - id: ofs_data
        type: s4
      - id: len_data
        type: s4
    instances:
      data:
        io: _root._io
        pos: ofs_data
        size: len_data
