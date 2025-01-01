meta:
  id: build_map
  title: BUILD Engine Level
  application: BUILD Engine
  file-extension: map
  license: CC0-1.0
  endian: le

doc-ref: BUILDINF.TXT
doc: |
  BUILD engine MAP file. Used to store level geometry and
  entity position data for games like Duke Nukem 3D.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
      - id: version
        type: s4
      - id: start_position
        type: vec3l
      - id: start_angle
        type: s2
      - id: start_sector
        type: s2
  - id: num_sectors
    type: s2
  - id: sectors
    type: sector
    repeat: expr
    repeat-expr: num_sectors
  - id: num_walls
    type: s2
  - id: walls
    type: wall
    repeat: expr
    repeat-expr: num_walls
  - id: num_sprites
    type: s2
  - id: sprites
    type: sprite
    repeat: expr
    repeat-expr: num_sprites

types:
  sector:
    seq:
      - id: wall_pointer
        type: s2
      - id: wall_num
        type: s2
      - id: ceiling_z
        type: s4
      - id: floor_z
        type: s4
      - id: ceiling_stat
        type: s2
      - id: floor_stat
        type: s2
      - id: ceiling_texture_id
        type: s2
      - id: ceiling_hei_num
        type: s2
      - id: ceiling_shade
        type: s1
      - id: ceiling_pal
        type: u1
      - id: ceiling_x_panning
        type: u1
      - id: ceiling_y_panning
        type: u1
      - id: floor_texture_id
        type: s2
      - id: floor_hei_num
        type: s2
      - id: floor_shade
        type: s1
      - id: floor_pal
        type: u1
      - id: floor_x_panning
        type: u1
      - id: floor_y_panning
        type: u1
      - id: visibility
        type: u1
      - id: filler
        type: u1
      - id: lotag
        type: s2
      - id: hitag
        type: s2
      - id: extra
        type: s2

  wall:
    seq:
      - id: position
        type: vec2l
      - id: point2
        type: s2
      - id: nextwall
        type: s2
      - id: nextsector
        type: s2
      - id: cstat
        type: s2
      - id: texture_id
        type: s2
      - id: texture_id_overlay
        type: s2
      - id: shade
        type: s1
      - id: palette_table
        type: u1
      - id: repeat
        type: vec2ub
      - id: panning
        type: vec2ub
      - id: lotag
        type: s2
      - id: hitag
        type: s2
      - id: extra
        type: s2

  sprite:
    seq:
      - id: position
        type: vec3l
      - id: cstat
        type: s2
      - id: texture_id
        type: s2
      - id: shade
        type: s1
      - id: palette_table
        type: s1
      - id: clip_dist
        type: s1
      - id: filler
        type: s1
      - id: repeat
        type: vec2ub
      - id: offset
        type: vec2b
      - id: sector_id
        type: s2
      - id: stat_id
        type: s2
      - id: angle
        type: s2
      - id: owner
        type: s2
      - id: velocity
        type: vec3s
      - id: lotag
        type: s2
      - id: hitag
        type: s2
      - id: extra
        type: s2

  vec2b:
    seq:
      - id: x
        type: s1
      - id: y
        type: s1

  vec2ub:
    seq:
      - id: x
        type: u1
      - id: y
        type: u1

  vec2l:
    seq:
      - id: x
        type: s4
      - id: y
        type: s4

  vec3l:
    seq:
      - id: x
        type: s4
      - id: y
        type: s4
      - id: z
        type: s4

  vec3s:
    seq:
      - id: x
        type: s2
      - id: y
        type: s2
      - id: z
        type: s2
