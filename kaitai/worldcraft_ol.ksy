meta:
  id: worldcraft_ol
  title: Worldcraft Object Library
  application: Worldcraft
  file-extension: ol
  license: CC0-1.0
  endian: le

doc: |
  Worldcraft Object Library. A simple collection of Worldcraft RMF and Quake
  MAP files with some metadata.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: magic
    contents: "Worldcraft Prefab Library\x0d\x0a\x1a"
  - id: version
    type: f4
  - id: ofs_entries
    type: u4
  - id: num_entries
    type: u4
  - id: notes
    type: strz
    encoding: ascii
    size: 501

types:

  entry:
    seq:
      - id: ofs_data
        type: u4
      - id: len_data
        type: u4
      - id: name
        type: strz
        encoding: ascii
        size: 31
      - id: notes
        type: strz
        encoding: ascii
        size: 501
      - id: type
        type: u4
        enum: entry_type
    instances:
      data:
        pos: ofs_data
        size: len_data

instances:
  entries:
    pos: ofs_entries
    type: entry
    repeat: expr
    repeat-expr: num_entries

enums:
  entry_type:
    0: rmf
    1: map
