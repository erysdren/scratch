meta:
  id: kaos_dlf
  title: Kaos Mapset
  application: Kaos
  file-extension: dlf
  license: CC0-1.0
  endian: le

doc: |
  Mapset format from the cancelled MS-DOS FPS game Kaos.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: magic
    contents: "NICdlf\x07\x1a"
  - id: num_maps
    type: u1
  - id: maps
    type: map
    repeat: expr
    repeat-expr: num_maps

types:

  map:
    seq:
      - id: index
        type: u1
      - id: name
        type: strz
        encoding: ascii
        size: 24
      - id: background
        type: u1
      - id: walls
        size: 0x2000
      - id: floors
        size: 0x1000
      - id: ceilings
        size: 0x1000
