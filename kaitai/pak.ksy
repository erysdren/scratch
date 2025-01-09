meta:
  id: quake_pak
  title: Quake PAK
  application: Quake
  file-extension: pak
  license: CC0-1.0
  endian: le

doc: |
  The PAK or "PACK" format, invented by id Software for Quake (1996) and also
  used by Valve Software for various titles. A modified version of the format
  was used for HROT (2023).

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: magic
    type: str
    size: 4
    encoding: ascii
    valid:
      any-of: ["'PACK'", "'HROT'"]
  - id: ofs_entries
    type: s4
  - id: len_entries
    type: s4

instances:
  is_hrot:
    value: magic == "HROT"

  len_entry:
    value: is_hrot ? 128 : 64

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
