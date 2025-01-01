meta:
  id: vtmb_tth
  title: Troika Texture Header
  application: Vampire: The Masquerade – Bloodlines
  file-extension: tth
  license: CC0-1.0
  endian: le

doc: |
  Troika Texture Header.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: magic
    contents: "TTH\0"
  - id: version
    type: u1
    repeat: expr
    repeat-expr: 2
  - id: num_mipmaps
    type: u1
  - id: aspect
    type: u1
  - id: len_vtf_chunk
    type: s4
  - id: mipmap_flags
    type: u8
    repeat: expr
    repeat-expr: num_mipmaps
  - id: len_vtf_file
    type: s4
  - id: len_ttz_tail
    type: s4
  - id: vtf_chunk
    size: len_vtf_chunk
