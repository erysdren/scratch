meta:
  id: ted5
  title: TED5 Level Files
  application: TED5
  license: CC0-1.0
  endian: le

doc-ref:
  - https://moddingwiki.shikadi.net/wiki/TED5
  - https://moddingwiki.shikadi.net/wiki/GameMaps_Format
doc: |
  This specification was authored by erysdren (it/its).
  https://erysdren.me/

params:
  - id: maptemp
    type: io

seq:
  - id: tag
    type: u2
    valid: 0xABCD
  - id: ofs_maps
    type: s4
    repeat: expr
    repeat-expr: num_maps

instances:
  num_maps:
    value: 100
    doc: Standard number of maps per mapset
  maps:
    type: map(_index)
    repeat: expr
    repeat-expr: num_maps

types:

  plane:
    params:
      - id: index
        type: s4
    instances:
      body:
        pos: _parent.ofs_planes[index]
        size: _parent.len_planes[index]

  map_body:
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
      planes:
        type: plane(_index)
        repeat: expr
        repeat-expr: num_planes

  map:
    params:
      - id: index
        type: s4
    instances:
      offset:
        value: _root.ofs_maps[index]
      used:
        value: _root.ofs_maps[index] > 0
      body:
        io: _root.maptemp
        pos: offset
        type: map_body
        if: used
