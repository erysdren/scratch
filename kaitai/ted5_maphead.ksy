meta:
  id: ted5_maphead
  title: TED5 MAPHEAD File
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
  - id: rle_tag
    type: str
    valid: 0xABCD
    doc: RLE compression tag (also serves as magic identifier)
  - id: map_offsets
    type: s4
    repeat: expr
    repeat-expr: 100
    doc: Byte offsets to the level data in the associated MAPTEMP file
