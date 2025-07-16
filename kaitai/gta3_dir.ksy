meta:
  id: gta3_dir
  title: Grand Theft Auto 3 Directory
  file-extension: dir
  license: CC0-1.0
  endian: le

doc: |
  File directory image used by GTA 3 and GTA: Vice City.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

params:
  - id: img
    type: io

seq:
  - id: files
    type: file
    repeat: eos

instances:
  sector_size:
    value: 2048

types:
  file:
    seq:
      - id: ofs_data
        type: u4
      - id: len_data
        type: u4
      - id: name
        type: strz
        encoding: ascii
        size: 24
    instances:
      data:
        io: _root.img
        pos: ofs_data * _root.sector_size
        size: len_data * _root.sector_size
