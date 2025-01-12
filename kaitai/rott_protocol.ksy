meta:
  id: rott_protocol
  title: Rise of the Triad Network Protocol
  application: Rise of the Triad
  license: CC0-1.0
  endian: le
  imports:
    - rott_types

doc: |
  This specification was authored by erysdren (it/its).
  https://erysdren.me/

types:
  packet:
    seq:
      - id: type
        type: u1
      - id: payload
        type:
          switch-on: type
          cases:
            1: packet_delta
            2: packet_request
            3: packet_fixup
            4: packet_text
            5: packet_pause
            6: packet_quit
            7: packet_sync
            8: packet_remote_ridicule
            10: packet_respawn
            11: packet_unpause
            12: packet_server
            15: packet_game_desc
            16: packet_game_play
            17: packet_game_master
            18: packet_game_ack
            19: packet_end_game
            20: packet_sync_time
            22: packet_delta_sound
            23: packet_exit
            24: packet_game_end
            25: packet_delta_null

  packet_delta:
    seq:
      - id: time
        type: s4
      - id: x
        type: s2
      - id: y
        type: s2
      - id: z
        type: u2
      - id: buttons
        type: u2

  packet_request:
    seq:
      - id: time
        type: s4
      - id: num_packets
        type: u1

  packet_fixup:
    seq:
      - id: time
        type: s4
      - id: num_packets
        type: u1
      - id: packets
        type: packet
        repeat: expr
        repeat-expr: num_packets

  packet_text:
    seq:
      - id: time
        type: s4
      - id: player
        type: u1
      - id: text
        type: strz
        encoding: ascii
        size: 33

  packet_pause:
    seq:
      - id: time
        type: s4

  packet_quit:
    seq:
      - id: time
        type: s4

  packet_sync:
    seq:
      - id: time
        type: s4

  packet_remote_ridicule:
    seq:
      - id: time
        type: s4
      - id: source_player
        type: u1
      - id: sound_num
        type: u1
      - id: dest_player
        type: u1

  packet_respawn:
    seq:
      - id: time
        type: s4

  packet_unpause:
    seq:
      - id: time
        type: s4

  packet_server:
    seq:
      - id: player
        type: u1
      - id: num_packets
        type: u1
      - id: packets
        type: packet
        repeat: expr
        repeat-expr: num_packets

  packet_game_desc:
    seq:
      - id: player
        type: u1
      - id: violence
        type: u1
      - id: product
        type: u1
      - id: version
        type: s4
      - id: player_description
        type: rott_types::player_description

  packet_game_master:
    seq:
      - id: map
        type: u1
      - id: map_crc
        type: u2
      - id: violence
        type: u1
      - id: product
        type: u1
      - id: mode
        type: u1
      - id: version
        type: u4
      - id: teamplay
        type: u1
      - id: specials
        type: rott_types::specials
      - id: battle_options
        type: rott_types::battle_options
      - id: mapset
        type: strz
        encoding: ascii
        size: 20
      - id: random_seed
        type: s4
      - id: ludicrous_gibs
        type: u1
      - id: player_descriptions
        type: rott_types::player_description
        repeat: expr
        repeat-expr: 11

  packet_game_ack:
    seq:
      - id: player
        type: u1

  packet_game_end:
    seq:
      - id: time
        type: s4

  packet_end_game:
    seq:
      - id: time
        type: s4

  packet_sync_time:
    seq:
      - id: time
        type: s4

  packet_exit:
    seq:
      - id: time
        type: s4

  packet_delta_null:
    seq:
      - id: time
        type: s4

  packet_game_play:
    seq:
      - id: dummy
        size: 20

  packet_delta_sound:
    seq:
      - id: time
        type: s4
      - id: x
        type: s2
      - id: y
        type: s2
      - id: z
        type: u2
      - id: buttons
        type: u2
      - id: sound_type
        type: u1
      - id: sound_data
        size: 256
