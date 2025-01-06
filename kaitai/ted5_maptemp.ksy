meta:
  id: ted5_maptemp
  title: TED5 MAPTEMP File
  application: TED5
  license: CC0-1.0
  endian: le

doc: |
  Part of the source maps format used by id Software's TED5 tilemap editor.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

doc-ref:
  - https://moddingwiki.shikadi.net/wiki/TED5
  - https://moddingwiki.shikadi.net/wiki/GameMaps_Format

seq:
  - id: magic
    contents: "TED5v1.0"
    doc: Magic identifier

types:
  map:
    seq:
      - id: ofs_planes
        type: s4
        repeat: expr
        repeat-expr: num_planes
        doc: Offsets to plane arrays
      - id: len_planes
        type: u2
        repeat: expr
        repeat-expr: num_planes
        doc: Sizes of plane arrays
      - id: width
        type: u2
        doc: Map width in tiles
      - id: height
        type: u2
        doc: Map height in tiles
      - id: name
        type: strz
        encoding: ascii
        size: 16
        doc: Map name
    instances:
      num_planes:
        value: 3
        doc: Number of planes per map
