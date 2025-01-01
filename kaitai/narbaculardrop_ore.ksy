meta:
  id: narbaculardrop_ore
  title: Narbacular Drop Archive
  application: Narbacular Drop
  file-extension: ore
  license: CC0-1.0
  endian: le

doc: |
  The archive format used by Narbacular Drop (2005). The format is made up of
  "directories" which contain named files and "loose files" which sit above the
  directories. The files contained are uncompressed. Only one layer of
  directories seems to be supported.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: header_size
    type: s4
  - id: num_directories
    type: s4
  - id: directories
    type: directory
    repeat: expr
    repeat-expr: num_directories
  - id: num_loose_files
    type: s4
  - id: loose_files
    type: loose_file
    repeat: expr
    repeat-expr: num_loose_files

types:

  file:
    seq:
      - id: name
        type: strz
        encoding: ascii
      - id: ofs_data
        type: s4
      - id: len_data
        type: s4
    instances:
      data:
        pos: _parent._parent.offset + ofs_data + 8
        size: len_data

  file_list:
    seq:
      - id: signature
        type: s8
        valid: 8
      - id: num_files
        type: s4
      - id: files
        type: file
        repeat: expr
        repeat-expr: num_files

  directory:
    seq:
      - id: name
        type: strz
        encoding: ascii
      - id: offset
        type: s4
    instances:
      file_list:
        type: file_list
        pos: offset

  loose_file:
    seq:
      - id: name
        type: strz
        encoding: ascii
      - id: ofs_data
        type: s4
      - id: len_data
        type: s4
    instances:
      data:
        pos: _root.header_size + ofs_data
        size: len_data
