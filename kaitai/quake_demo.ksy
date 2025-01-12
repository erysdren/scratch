meta:
  id: quake_demo
  title: Quake Demo
  application: Quake
  file-extension: dem
  license: CC0-1.0
  endian: le

doc: |
  Quake's original demo format, for recording server-to-client messages to disk
  for playback later.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: cd_track_index
    type: str
    encoding: ascii
    terminator: 0x0a
  - id: packets
    type: packet
    repeat: eos

types:
  packet:
    seq:
      - id: len_message
        type: s4
      - id: angles
        type: vec3f
      - id: message
        size: len_message

  vec3f:
    seq:
      - id: x
        type: f4
      - id: y
        type: f4
      - id: z
        type: f4
