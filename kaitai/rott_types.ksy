meta:
  id: rott_types
  title: Rise of the Triad Common Types
  application: Rise of the Triad
  license: CC0-1.0
  endian: le

doc: |
  This specification was authored by erysdren (it/its).
  https://erysdren.me/

types:
  battle_options:
    seq:
      - id: gravity
        type: u4
      - id: speed
        type: u4
      - id: ammo
        type: u4
      - id: hitpoints
        type: u4
      - id: spawn_dangers
        type: u4
      - id: spawn_health
        type: u4
      - id: spawn_weapons
        type: u4
      - id: spawn_mines
        type: u4
      - id: respawn_items
        type: u4
      - id: weapon_persistence
        type: u4
      - id: random_weapons
        type: u4
      - id: friendly_fire
        type: u4
      - id: light_level
        type: u4
      - id: kills
        type: s4
      - id: danger_damage
        type: s4
      - id: time_limit
        type: u4
      - id: respawn_time
        type: u4

  specials:
    seq:
      - id: god_mode_time
        type: s4
      - id: dog_mode_time
        type: s4
      - id: shrooms_mode_time
        type: s4
      - id: elasto_mode_time
        type: s4
      - id: asbestos_vest_time
        type: s4
      - id: bulletproof_vest_time
        type: s4
      - id: gasmask_time
        type: s4
      - id: mercury_mode_time
        type: s4
      - id: god_mode_respawn_time
        type: s4
      - id: dog_mode_respawn_time
        type: s4
      - id: shrooms_mode_respawn_time
        type: s4
      - id: elasto_mode_respawn_time
        type: s4
      - id: asbestos_vest_respawn_time
        type: s4
      - id: bulletproof_vest_respawn_time
        type: s4
      - id: gasmask_respawn_time
        type: s4
      - id: mercury_mode_respawn_time
        type: s4

  player_description:
    seq:
      - id: character
        type: u1
      - id: color
        type: u1
      - id: name
        type: strz
        encoding: ascii
        size: 9
