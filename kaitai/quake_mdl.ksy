meta:
  id: quake_mdl
  title: Quake Model
  application: Quake
  file-extension: mdl
  license: CC0-1.0
  endian: le

doc: |
  Quake (1996)'s Model format, created by id Software. This specification also
  supports the pre-release "QTest" version of the format.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: magic
    contents: "IDPO"
  - id: version
    type: s4
    valid:
      any-of: [3, 6]
  - id: scale
    type: vec3f
  - id: translation
    type: vec3f
  - id: bounding_radius
    type: f4
  - id: eye_position
    type: vec3f
  - id: num_skins
    type: u4
  - id: skin_width
    type: u4
  - id: skin_height
    type: u4
  - id: num_vertices
    type: u4
  - id: num_faces
    type: u4
  - id: num_frames
    type: u4
  - id: sync_type
    type: u4
    enum: sync_type
  - id: flags
    type: u4
    if: not is_qtest
  - id: size
    type: f4
    if: not is_qtest
  - id: skins
    type: skin
    repeat: expr
    repeat-expr: num_skins
  - id: texcoords
    type: texcoord
    repeat: expr
    repeat-expr: num_vertices
  - id: faces
    type: face
    repeat: expr
    repeat-expr: num_faces
  - id: frames
    type: frame
    repeat: expr
    repeat-expr: num_frames

instances:
  is_qtest:
    value: version == 3

enums:
  sync_type:
    0: sync
    1: random

  skin_type:
    0: single
    1: group

  face_type:
    0: back
    1: front

  frame_type:
    0: single
    1: group

types:
  vec3ub:
    seq:
      - id: x
        type: u1
      - id: y
        type: u1
      - id: z
        type: u1
    instances:
      x_scaled:
        value: x * _root.scale.x
      y_scaled:
        value: y * _root.scale.y
      z_scaled:
        value: z * _root.scale.z

  vec3i:
    seq:
      - id: x
        type: s4
      - id: y
        type: s4
      - id: z
        type: s4

  vec3f:
    seq:
      - id: x
        type: f4
      - id: y
        type: f4
      - id: z
        type: f4

  skin_image:
    params:
      - id: width
        type: u4
      - id: height
        type: u4
    seq:
      - id: pixels
        size: width * height

  skin:
    seq:
      - id: skin_type
        type: u4
        enum: skin_type
      - id: num_frames
        type: u4
        if: skin_type == skin_type::group
      - id: durations
        type: f4
        repeat: expr
        repeat-expr: num_frames
        if: skin_type == skin_type::group
      - id: frames
        type: skin_image(_root.skin_width, _root.skin_height)
        repeat: expr
        repeat-expr: skin_type == skin_type::group ? num_frames : 1

  texcoord:
    seq:
      - id: onseam
        type: s4
      - id: s
        type: s4
      - id: t
        type: s4

  face:
    seq:
      - id: face_type
        type: u4
        enum: face_type
      - id: indices
        type: vec3i

  vertex:
    seq:
      - id: origin
        type: vec3ub
      - id: normal
        type: u1

  frame_data:
    seq:
      - id: min
        type: vertex
      - id: max
        type: vertex
      - id: name
        type: strz
        encoding: ascii
        size: 16
        if: not _root.is_qtest
      - id: vertices
        type: vertex
        repeat: expr
        repeat-expr: _root.num_vertices

  frame:
    seq:
      - id: frame_type
        type: u4
        enum: frame_type
      - id: num_frames
        type: u4
        if: is_group
      - id: min
        type: vertex
        if: is_group
      - id: max
        type: vertex
        if: is_group
      - id: durations
        type: f4
        repeat: expr
        repeat-expr: num_frames
        if: is_group
      - id: frames
        type: frame_data
        repeat: expr
        repeat-expr: is_group ? num_frames : 1
    instances:
      is_group:
        value: frame_type == frame_type::group
