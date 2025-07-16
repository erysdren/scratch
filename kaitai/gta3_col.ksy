meta:
  id: gta3_col
  title: Grand Theft Auto 3 Collision Models
  file-extension: col
  license: CC0-1.0
  endian: le

doc: |
  Collision model collection used by GTA 3 and GTA: Vice City.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: models
    type: model
    repeat: eos

types:
  model:
    seq:
      - id: magic
        contents: "COLL"
      - id: size
        type: u4
      - id: name
        type: strz
        encoding: ascii
        size: 22
      - id: model_id
        type: u2
      - id: bounds
        type: bounds
      - id: num_spheres
        type: u4
      - id: spheres
        type: sphere
        repeat: expr
        repeat-expr: num_spheres
      - id: num_unknown
        type: u4
      - id: num_boxes
        type: u4
      - id: boxes
        type: box
        repeat: expr
        repeat-expr: num_boxes
      - id: num_vertices
        type: u4
      - id: vertices
        type: vec3
        repeat: expr
        repeat-expr: num_vertices
      - id: num_faces
        type: u4
      - id: faces
        type: face
        repeat: expr
        repeat-expr: num_faces

  vec3:
    seq:
      - id: x
        type: f4
      - id: y
        type: f4
      - id: z
        type: f4

  bounds:
    seq:
      - id: radius
        type: f4
      - id: center
        type: vec3
      - id: min
        type: vec3
      - id: max
        type: vec3

  surface:
    seq:
      - id: material
        type: u1
      - id: flags
        type: u1
      - id: brightness
        type: u1
      - id: light
        type: u1

  sphere:
    seq:
      - id: radius
        type: f4
      - id: center
        type: vec3
      - id: surface
        type: surface

  box:
    seq:
      - id: min
        type: vec3
      - id: max
        type: vec3
      - id: surface
        type: surface

  face:
    seq:
      - id: a
        type: u4
      - id: b
        type: u4
      - id: c
        type: u4
      - id: surface
        type: surface
