meta:
  id: portal2d_map
  title: Portal2D Engine Level
  application: Portal2D Engine
  file-extension: map
  license: CC0-1.0
  endian: le

doc-ref: https://sourceforge.net/p/portal2d/code/HEAD/tree/Source/level.c
doc: |
  This is the basic level format used by the Portal2D Engine, created by Derek
  John Evans over the summer of 1999.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: chunks
    type: chunk
    repeat: eos

types:
  chunk:
    seq:
      - id: type
        type: str
        encoding: ascii
        size: 4
      - id: id
        type: s4
      - id: flags
        type: s4
      - id: len_data
        type: s4
      - id: data
        size: len_data
        type:
          switch-on: type
          cases:
            "'LLAW'": wall
            "'TCES'": sector

  surface:
    seq:
      - id: texture_id
        type: u1
      - id: overlay_id
        type: u1
      - id: flags
        type: u2
      - id: light_level
        type: u1
      - id: color_r
        type: u1
      - id: color_g
        type: u1
      - id: color_b
        type: u1
      - id: slope_x
        type: s4
      - id: slope_y
        type: s4
      - id: slope_z
        type: s4
      - id: repeat_x
        type: u1
      - id: padding_1
        size: 3
      - id: repeat_y
        type: u1
      - id: padding_2
        size: 3
      - id: uv_x
        type: s4
      - id: uv_y
        type: s4
      - id: reserved
        size: 4

  wall:
    seq:
      - id: side_id
        type: u2
      - id: padding_1
        type: u2
      - id: next_wall_id
        type: u2
      - id: padding_2
        type: u2
      - id: portal_id
        type: u2
      - id: padding_3
        type: u2
      - id: x
        type: s4
      - id: y
        type: s4
      - id: surface
        type: surface

  sector:
    seq:
      - id: lid
        type: u2
      - id: padding
        type: u2
      - id: first_wall_id
        type: u2
      - id: flags
        type: u2
      - id: top_surface
        type: surface
      - id: bottom_surface
        type: surface
      - id: middle_surface
        type: surface
