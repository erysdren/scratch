meta:
  id: source2_dmx
  title: Source 2 Engine Binary DMX
  file-extension:
    - dmx
    - vmap
  license: CC0-1.0
  endian: le

doc: |
  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: identifier
    type: strz
    encoding: utf-8
  - id: has_prefixed_attributes
    type: s4
  - id: num_prefixed_attributes
    type: s4
    if: 'has_prefixed_attributes != 0'
  - id: prefixed_attributes
    type: prefixed_attribute
    repeat: expr
    repeat-expr: num_prefixed_attributes
    if: 'has_prefixed_attributes != 0'
  - id: num_strings
    type: s4
  - id: strings
    type: strz
    encoding: utf-8
    repeat: expr
    repeat-expr: num_strings
  - id: num_elements
    type: s4
  - id: element_headers
    type: element_header
    repeat: expr
    repeat-expr: num_elements
  - id: element_bodies
    type: element_body
    repeat: expr
    repeat-expr: num_elements

types:

  element_header:
    seq:
      - id: type
        type: s4
      - id: name_id
        type: s4
      - id: guid
        size: 16
    instances:
      name:
        value: _root.strings[name_id]

  element_body:
    seq:
      - id: num_attributes
        type: s4
      - id: attributes
        type: attribute
        repeat: expr
        repeat-expr: num_attributes

  prefixed_attribute:
    seq:
      - id: name
        type: strz
        encoding: utf-8
      - id: type
        type: u1
      - id: value
        type:
          switch-on: type
          cases:
            1: attribute_element
            2: attribute_int
            3: attribute_float
            4: attribute_bool
            5: attribute_string
            6: attribute_binary
            7: attribute_time
            8: attribute_color
            9: attribute_vec2
            10: attribute_vec3
            11: attribute_vec4
            12: attribute_angle
            13: attribute_quaternion
            14: attribute_matrix
            15: attribute_u64
            16: attribute_u8
            33: attribute_element_array
            34: attribute_int_array
            35: attribute_float_array
            36: attribute_bool_array
            37: attribute_string_array
            38: attribute_binary_array
            39: attribute_time_array
            40: attribute_color_array
            41: attribute_vec2_array
            42: attribute_vec3_array
            43: attribute_vec4_array
            44: attribute_angle_array
            45: attribute_quaternion_array
            46: attribute_matrix_array
            47: attribute_u64_array
            48: attribute_u8_array

  attribute:
    seq:
      - id: name_id
        type: s4
      - id: value
        type: attribute_value
    instances:
      name:
        value: _root.strings[name_id]

  attribute_value:
    seq:
      - id: type
        type: u1
      - id: data
        type:
          switch-on: type
          cases:
            1: attribute_element
            2: attribute_int
            3: attribute_float
            4: attribute_bool
            5: attribute_string_id
            6: attribute_binary
            7: attribute_time
            8: attribute_color
            9: attribute_vec2
            10: attribute_vec3
            11: attribute_vec4
            12: attribute_angle
            13: attribute_quaternion
            14: attribute_matrix
            15: attribute_u64
            16: attribute_u8
            33: attribute_element_array
            34: attribute_int_array
            35: attribute_float_array
            36: attribute_bool_array
            37: attribute_string_array
            38: attribute_binary_array
            39: attribute_time_array
            40: attribute_color_array
            41: attribute_vec2_array
            42: attribute_vec3_array
            43: attribute_vec4_array
            44: attribute_angle_array
            45: attribute_quaternion_array
            46: attribute_matrix_array
            47: attribute_u64_array
            48: attribute_u8_array

  # 1
  attribute_element:
    seq:
      - id: element_id
        type: s4

  # 2
  attribute_int:
    seq:
      - id: value
        type: s4

  # 3
  attribute_float:
    seq:
      - id: value
        type: f4

  # 4
  attribute_bool:
    seq:
      - id: value
        type: u1

  # 5
  attribute_string:
    seq:
      - id: string
        type: strz
        encoding: utf-8

  # 5
  attribute_string_id:
    seq:
      - id: string_id
        type: s4
    instances:
      string:
        value: _root.strings[string_id]

  # 6
  attribute_binary:
    seq:
      - id: len_data
        type: s4
      - id: data
        size: len_data

  # 7
  attribute_time:
    seq:
      - id: ms
        type: s4

  # 8
  attribute_color:
    seq:
      - id: r
        type: u1
      - id: g
        type: u1
      - id: b
        type: u1
      - id: a
        type: u1

  # 9
  attribute_vec2:
    seq:
      - id: x
        type: f4
      - id: y
        type: f4

  # 10
  attribute_vec3:
    seq:
      - id: x
        type: f4
      - id: y
        type: f4
      - id: z
        type: f4

  # 11
  attribute_vec4:
    seq:
      - id: x
        type: f4
      - id: y
        type: f4
      - id: z
        type: f4
      - id: w
        type: f4

  # 12
  attribute_angle:
    seq:
      - id: pitch
        type: f4
      - id: yaw
        type: f4
      - id: roll
        type: f4

  # 13
  attribute_quaternion:
    seq:
      - id: x
        type: f4
      - id: y
        type: f4
      - id: z
        type: f4
      - id: w
        type: f4

  # 13
  attribute_matrix:
    seq:
      - id: matrix
        type: f4
        repeat: expr
        repeat-expr: 16

  # 14
  attribute_u64:
    seq:
      - id: value
        type: u8

  # 15
  attribute_u8:
    seq:
      - id: value
        type: u1

  # 33
  attribute_element_array:
    seq:
      - id: num_elements
        type: s4
      - id: element_ids
        type: attribute_element
        repeat: expr
        repeat-expr: num_elements

  # 34
  attribute_int_array:
    seq:
      - id: num_ints
        type: s4
      - id: ints
        type: s4
        repeat: expr
        repeat-expr: num_ints

  # 35
  attribute_float_array:
    seq:
      - id: num_floats
        type: s4
      - id: floats
        type: f4
        repeat: expr
        repeat-expr: num_floats

  # 36
  attribute_bool_array:
    seq:
      - id: num_bools
        type: s4
      - id: bools
        type: u1
        repeat: expr
        repeat-expr: num_bools

  # 37
  attribute_string_array:
    seq:
      - id: num_strings
        type: s4
      - id: strings
        type: strz
        encoding: utf-8
        repeat: expr
        repeat-expr: num_strings

  # 38
  attribute_binary_array:
    seq:
      - id: num_binary_elements
        type: s4
      - id: binary_elements
        type: attribute_binary
        repeat: expr
        repeat-expr: num_binary_elements

  # 39
  attribute_time_array:
    seq:
      - id: num_time_elements
        type: s4
      - id: time_elements
        type: attribute_time
        repeat: expr
        repeat-expr: num_time_elements

  # 40
  attribute_color_array:
    seq:
      - id: num_colors
        type: s4
      - id: colors
        type: attribute_color
        repeat: expr
        repeat-expr: num_colors

  # 41
  attribute_vec2_array:
    seq:
      - id: num_vec2_elements
        type: s4
      - id: vec2_elements
        type: attribute_vec2
        repeat: expr
        repeat-expr: num_vec2_elements

  # 42
  attribute_vec3_array:
    seq:
      - id: num_vec3_elements
        type: s4
      - id: vec3_elements
        type: attribute_vec3
        repeat: expr
        repeat-expr: num_vec3_elements

  # 43
  attribute_vec4_array:
    seq:
      - id: num_vec4_elements
        type: s4
      - id: vec4_elements
        type: attribute_vec4
        repeat: expr
        repeat-expr: num_vec4_elements

  # 44
  attribute_angle_array:
    seq:
      - id: num_angles
        type: s4
      - id: angles
        type: attribute_angle
        repeat: expr
        repeat-expr: num_angles

  # 45
  attribute_quaternion_array:
    seq:
      - id: num_quaternions
        type: s4
      - id: quaternions
        type: attribute_quaternion
        repeat: expr
        repeat-expr: num_quaternions

  # 46
  attribute_matrix_array:
    seq:
      - id: num_matrices
        type: s4
      - id: matrices
        type: attribute_matrix
        repeat: expr
        repeat-expr: num_matrices

  # 47
  attribute_u64_array:
    seq:
      - id: num_u64_elements
        type: s4
      - id: u64_elements
        type: u8
        repeat: expr
        repeat-expr: num_u64_elements

  # 48
  attribute_u8_array:
    seq:
      - id: num_u8_elements
        type: s4
      - id: u8_elements
        type: u1
        repeat: expr
        repeat-expr: num_u8_elements
