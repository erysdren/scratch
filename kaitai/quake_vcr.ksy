meta:
  id: quake_vcr
  title: Quake VCR
  application: Quake
  file-extension: vcr
  license: CC0-1.0
  endian: le

doc: |
  Quake's "VCR" recording format, seemingly an unfinished predecessor to demos.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: magic
    contents: "1RCV"
  - id: num_args
    type: s4
  - id: args
    type: length_string
    repeat: expr
    repeat-expr: num_args
  - id: packets
    type: packet
    repeat: eos

types:
  length_string:
    seq:
      - id: length
        type: s4
      - id: buffer
        type: str
        encoding: ascii
        size: length

  packet_connect:
    seq:
      - id: address
        type: str
        encoding: ascii
        size: _parent.session == 0 ? 0 : 64

  packet_get_message:
    seq:
      - id: type
        type: s4
        enum: message_type
      - id: len_message
        type: s4
        if: type != message_type::none
      - id: message
        size: len_message
        if: type != message_type::none

  packet_send_message:
    seq:
      - id: value
        type: s4

  packet_can_send_message:
    seq:
      - id: value
        type: s4

  packet:
    seq:
      - id: time
        type: f8
      - id: operation
        type: s4
        enum: operation
      - id: session
        type: u4
      - id: operation_data
        type:
          switch-on: operation
          cases:
            'operation::connect': packet_connect
            'operation::get_message': packet_get_message
            'operation::send_message': packet_send_message
            'operation::can_send_message': packet_can_send_message

enums:
  message_type:
    0: none
    1: reliable
    2: unreliable

  operation:
    1: connect
    2: get_message
    3: send_message
    4: can_send_message
