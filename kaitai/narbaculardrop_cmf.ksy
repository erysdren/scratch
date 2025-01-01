meta:
  id: narbaculardrop_cmf
  title: Narbacular Drop Level
  application: Narbacular Drop
  file-extension: cmf
  license: CC0-1.0
  endian: le

doc: |
  The level format used by Narbacular Drop (2005). The format was originally
  created by Stefan Hajnoczi in 2001 as part of an online tutorial for parsing
  Quake MAP file in C++. Version 2 of the format added a preview bitmap in the
  header.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: magic
    contents: "CMF"
  - id: version
    type: s1
  - id: preview_width
    type: u4
    if: version > 2
  - id: preview_height
    type: u4
    if: version > 2
  - id: preview_data
    size: preview_width * preview_height * 4
    if: version > 2
  - id: num_wads
    type: u4
  - id: num_entities
    type: u4
  - id: num_textures
    type: u4
  - id: wads
    type: strz
    encoding: ascii
    repeat: expr
    repeat-expr: num_wads
  - id: textures
    type: strz
    encoding: ascii
    repeat: expr
    repeat-expr: num_textures
  - id: entities
    type: entity
    repeat: expr
    repeat-expr: num_entities

types:

  property:
    seq:
      - id: name
        type: strz
        encoding: ascii
      - id: value
        type: strz
        encoding: ascii

  vec2:
    seq:
      - id: x
        type: f8
      - id: y
        type: f8

  vec3:
    seq:
      - id: x
        type: f8
      - id: y
        type: f8
      - id: z
        type: f8

  vec4:
    seq:
      - id: x
        type: f8
      - id: y
        type: f8
      - id: z
        type: f8
      - id: w
        type: f8

  vertex:
    seq:
      - id: origin
        type: vec3
      - id: uv
        type: vec2

  polygon:
    seq:
      - id: texture
        type: u4
      - id: plane
        type: vec4
      - id: num_vertices
        type: u4
      - id: vertices
        type: vertex
        repeat: expr
        repeat-expr: num_vertices

  entity:
    seq:
      - id: classname
        type: strz
        encoding: ascii
      - id: num_properties
        type: u4
      - id: properties
        type: property
        repeat: expr
        repeat-expr: num_properties
      - id: num_polygons
        type: u4
      - id: polygons
        type: polygon
        repeat: expr
        repeat-expr: num_polygons
