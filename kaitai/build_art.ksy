meta:
  id: build_art
  title: BUILD Engine Texture Archive
  application: BUILD Engine
  file-extension: art
  license: CC0-1.0
  endian: le

doc-ref: BUILDINF.TXT
doc: |
  BUILD engine ART file. Contains textures and texture attribute information
  for the engine. This file still needs information on how to directly access
  textures at specific offsets.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: version
    type: s4
    valid: 1
  - id: num_tiles
    type: s4
  - id: tile_id_start
    type: s4
  - id: tile_id_end
    type: s4
  - id: tile_sizes_x
    type: u2
    repeat: expr
    repeat-expr: tile_id_start + tile_id_end + 1
  - id: tile_sizes_y
    type: u2
    repeat: expr
    repeat-expr: tile_id_start + tile_id_end + 1
  - id: tile_attributes
    type: tile_attribute
    repeat: expr
    repeat-expr: tile_id_start + tile_id_end + 1

types:
  tile_attribute:
    seq:
      - id: unused
        type: b4
      - id: animation_speed
        type: b4
      - id: offset_y
        type: b8
      - id: offset_x
        type: b8
      - id: animation_type
        type: b2
      - id: num_frames
        type: b6
