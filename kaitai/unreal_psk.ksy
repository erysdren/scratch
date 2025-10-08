meta:
  id: unreal_psk
  title: Unreal Engine PSK
  file-extension:
    - psk
    - psa
  license: CC0-1.0
  endian: le

doc: |
  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: chunks
    type: chunk
    repeat: eos

types:

  chunk:
    seq:
      - id: name
        type: strz
        encoding: ascii
        size: 20
      - id: flags
        type: u4
      - id: len_entry
        type: u4
      - id: num_entries
        type: u4
      - id: entries
        repeat: expr
        repeat-expr: num_entries
        size: len_entry
        type:
          switch-on: name
          cases:
            "'PNTS0000'": vec3
            "'VTXW0000'": vertex
            "'FACE0000'": face
            "'MATT0000'": material
            "'REFSKELT'": bone
            "'BONENAMES'": bone
            "'RAWWEIGHTS'": weight
            "'ANIMINFO'": animation
            "'ANIMKEYS'": animation_key
            "'SCALEKEYS'": animation_scale_key

  vec3:
    seq:
      - id: x
        type: f4
      - id: y
        type: f4
      - id: z
        type: f4

  quat:
    seq:
      - id: x
        type: f4
      - id: y
        type: f4
      - id: z
        type: f4
      - id: w
        type: f4

  vertex:
    seq:
      - id: point
        type: u4
      - id: u
        type: f4
      - id: v
        type: f4
      - id: material
        type: u4

  face:
    seq:
      - id: x
        type: u2
      - id: y
        type: u2
      - id: z
        type: u2
      - id: material
        type: u1
      - id: aux_material
        type: u1
      - id: smoothing_groups
        type: u4

  material:
    seq:
      - id: name
        type: strz
        encoding: ascii
        size: 64
      - id: texture
        type: u4
      - id: flags
        type: u4
      - id: aux_material
        type: u4
      - id: aux_flags
        type: u4
      - id: lod_bias
        type: u4
      - id: lod_style
        type: u4

  bone_transform:
    seq:
      - id: orientation
        type: quat
      - id: position
        type: vec3
      - id: length
        type: f4
      - id: scale
        type: vec3

  bone:
    seq:
      - id: name
        type: strz
        encoding: ascii
        size: 64
      - id: flags
        type: u4
      - id: num_children
        type: u4
      - id: parent_index
        type: u4
      - id: transform
        type: bone_transform

  weight:
    seq:
      - id: weight
        type: f4
      - id: point_index
        type: u4
      - id: bone_index
        type: u4

  animation_key:
    seq:
      - id: position
        type: vec3
      - id: orientation
        type: quat
      - id: time
        type: f4

  animation_scale_key:
    seq:
      - id: position
        type: vec3
      - id: time
        type: f4

  animation:
    seq:
      - id: name
        type: strz
        encoding: ascii
        size: 64
      - id: group
        type: strz
        encoding: ascii
        size: 64
      - id: total_bones
        type: u4
      - id: root_includes
        type: u4
      - id: key_compression_style
        type: u4
      - id: key_quotum
        type: u4
      - id: key_reduction
        type: f4
      - id: track_time
        type: f4
      - id: rate
        type: f4
      - id: start_bone
        type: u4
      - id: first_raw_frame
        type: u4
      - id: num_raw_frames
        type: u4
