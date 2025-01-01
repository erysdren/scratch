meta:
  id: rott_mapset
  title: Rise of the Triad Mapset
  application: Rise of the Triad
  file-extension:
    - rtl
    - rtc
    - rtlx
    - rtcx
    - rtr
  license: CC0-1.0
  endian: le

doc: |
  The level format used by Rise of the Triad (1994). The format is extended
  from the source format of the tile editor they used, TED5. Each mapset
  contains exactly 100 levels, though they must be marked as "used" to be
  considered valid.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: magic
    type: u4
    enum: magics
  - id: version
    type: u4
    enum: versions
  - id: ofs_info_headers
    type: u8
    if: is_ludicrous
  - id: num_info_headers
    type: u8
    if: is_ludicrous
  - id: maps
    type: map
    repeat: expr
    repeat-expr: 100

instances:

  is_ludicrous:
    value: version == versions::ludicrous or magic == magics::rxl or magic == magics::rxc

  info_headers:
    pos: ofs_info_headers
    type: info_header
    repeat: expr
    repeat-expr: num_info_headers
    if: is_ludicrous

types:

  map:
    seq:
      - id: used
        type: u4
      - id: crc
        type: u4
      - id: tag
        type: u4
        enum: tags
      - id: flags
        type: u4
      - id: ofs_walls
        type: u4
      - id: ofs_sprites
        type: u4
      - id: ofs_infos
        type: u4
      - id: len_walls
        type: u4
      - id: len_sprites
        type: u4
      - id: len_infos
        type: u4
      - id: name
        type: strz
        encoding: ascii
        size: 24
    instances:
      walls:
        pos: ofs_walls
        size: len_walls
      sprites:
        pos: ofs_sprites
        size: len_sprites
      infos:
        pos: ofs_infos
        size: len_infos
      open_pushwalls_in_commbat:
        value: flags & 1

  info_header:
    seq:
      - id: identifier
        type: strz
        encoding: ascii
        size: 16
      - id: ofs_data
        type: u8
      - id: len_data
        type: u8
    instances:
      data:
        pos: ofs_data
        size: len_data

enums:

  magics:
    0x004C5452: rtl
    0x00435452: rtc
    0x00525452: rtr
    0x004C5852: rxl
    0x00435852: rxc

  versions:
    0x0101: rott
    0x0200: ludicrous

  tags:
    0x4344: registered
    0x4d4b: shareware
