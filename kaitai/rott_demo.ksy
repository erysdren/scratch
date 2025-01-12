meta:
  id: rott_demo
  title: Rise of the Triad Demo
  application: Rise of the Triad
  file-extension: dmo
  license: CC0-1.0
  endian: le

doc: |
  The on-disk demo format used by Rise of the Triad (1994). It's just a direct
  dump of some game-state structures, padding and all. It only tracks the
  primary player's inputs and position at somewhat-fixed intervals. When
  playing back a demo, the world is simulated as normal while the player's
  recorded inputs are played back.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: version
    type: u4
    valid:
      any-of: [12, 13]
  - id: product
    type: u4
    enum: product
  - id: time
    type: s4
  - id: frame
    type: s4
  - id: total_secrets
    type: s4
  - id: total_treasure
    type: s4
  - id: total_kills
    type: s4
  - id: num_secrets
    type: s4
  - id: num_treasure
    type: s4
  - id: num_kills
    type: s4
  - id: total_supers
    type: s4
  - id: total_health
    type: s4
  - id: total_missiles
    type: s4
  - id: num_supers
    type: s4
  - id: num_health
    type: s4
  - id: num_missiles
    type: s4
  - id: total_democratic
    type: s4
  - id: total_plants
    type: s4
  - id: num_democratic
    type: s4
  - id: num_plants
    type: s4
  - id: num_dipballs
    type: s4
  - id: difficulty
    type: s4
  - id: violence
    type: s4
  - id: map
    type: s4
  - id: score
    type: s4
  - id: episode
    type: s4
  - id: battle_mode
    type: s4
  - id: battle_option
    type: s4
  - id: random_seed
    type: s4
  - id: teamplay
    type: u1
  - id: democratic_bonus
    type: u1
  - id: ground_zero_bonus
    type: u1
  - id: padding0
    size: 1
  - id: autorun
    type: s4
  - id: battle_options
    type: battle_options
  - id: spawn_collect_items
    type: u1
  - id: spawn_eluder
    type: u1
  - id: spawn_deluder
    type: u1
  - id: show_scores
    type: u1
  - id: player_has_gun
    type: u1
    repeat: expr
    repeat-expr: num_players
  - id: padding1
    size: num_players == 11 ? 1 : 3
  - id: specials
    type: specials
  - id: packets
    type: packet
    repeat: eos

enums:
  product:
    0: shareware
    1: registered
    2: super_cd
    3: site_license

instances:
  num_players:
    value: product == product::shareware ? 5 : 11

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

  packet:
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