meta:
  id: intel_dvi
  title: Intel DVI Video
  file-extension: dvs
  license: CC0-1.0
  endian: le

doc-ref:
  - https://ardent-tool.com/video/ActionMedia.html
  - https://www.fileformat.info/format/dvi/egff.htm
  - https://resources.oreilly.com/examples/9781565920583/-/tree/master/CDROM/GFF/VENDSPEC/INTDVI
doc: |
  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: file_header
    type: file_header
  - id: avl_header
    type: avl_header

instances:
  streams:
    type: avl_stream
    pos: avl_header.ofs_streams
    repeat: expr
    repeat-expr: avl_header.num_streams

  annotations:
    type: strz
    encoding: ascii
    if: file_header.ofs_annotations > 0

types:

  file_header:
    seq:
      - id: magic
        contents: "IVDV"
      - id: header_size
        type: s2
        valid: 12
      - id: header_version
        type: s2
        valid: 1
      - id: ofs_annotations
        type: u4

  avl_header:
    seq:
      - id: magic
        contents: "SSVA"
      - id: header_size
        type: s2
        valid: 120
      - id: header_version
        type: s2
        valid: 3
      - id: num_stream_groups
        type: s2
      - id: len_stream_groups
        type: s2
      - id: ofs_stream_groups
        type: u4
      - id: stream_group_version
        type: s2
        valid: 3
      - id: len_stream
        type: s2
        valid: 44
      - id: stream_version
        type: s2
        valid: 3
      - id: num_streams
        type: s2
      - id: ofs_streams
        type: u4
      - id: ofs_substreams
        type: u4
      - id: num_labels
        type: s4
      - id: ofs_labels
        type: u4
      - id: len_label
        type: s2
        valid: 20
      - id: label_version
        type: s2
        valid: 3
      - id: ofs_vsh
        type: u4
      - id: len_vsh
        type: u2
      - id: frame_version
        type: s2
        valid: 3
      - id: num_frames
        type: s4
      - id: len_frame
        type: s4
      - id: ofs_frames
        type: u4
      - id: ofs_frames_end
        type: u4
      - id: len_frame_header
        type: s2
      - id: len_frame_directory
        type: s2
        valid: 4
      - id: ofs_frame_directory
        type: u4
      - id: frame_directory_version
        type: s2
        valid: 3
      - id: fps
        type: s2
      - id: flag
        type: u4
      - id: ofs_free_block
        type: u4
      - id: padding
        size: 32

  avl_stream:
    seq:
      - id: magic
        contents: "MRTS"
      - id: type
        type: u2
        enum: avl_type
      - id: subtype
        type: u2
      - id: num_headers
        type: s2
        valid: 1
      - id: next_stream_num
        type: s2
      - id: stream_group_num
        type: s2
      - id: padding
        size: 2
      - id: flag
        type: u4
      - id: len_frame
        type: s4
      - id: ofs_headers
        type: s4
      - id: name
        type: strz
        encoding: ascii
        size: 16
    instances:
      substreams:
        pos: ofs_headers
        repeat: expr
        repeat-expr: num_headers
        type:
          switch-on: type
          cases:
            'avl_type::compressed_audio_stream': compressed_audio_stream
            'avl_type::compressed_image_stream': compressed_image_stream

  compressed_audio_stream:
    seq:
      - id: magic
        contents: "IDUA"
      - id: header_size
        type: s2
        valid: 168
      - id: header_version
        type: s2
        valid: 5
      - id: original_file
        type: strz
        encoding: ascii
        size: 80
      - id: original_frame
        type: s4
      - id: original_stream
        type: s2
      - id: padding
        size: 2
      - id: num_frames
        type: s4
      - id: ofs_next_header
        type: u4
      - id: library
        type: strz
        encoding: ascii
        size: 16
      - id: algorithm
        type: strz
        encoding: ascii
        size: 16
      - id: parm1
        type: s4
      - id: parm2
        type: s2
      - id: parm3
        type: s2
      - id: left_volume
        type: s2
      - id: right_volume
        type: s2
      - id: loop_offset
        type: s4
      - id: start_frame
        type: s4
      - id: flag
        type: u4
      - id: parm4
        type: s2
      - id: padding2
        size: 2
      - id: dfc_id
        type: s4

  compressed_image_stream:
    seq:
      - id: magic
        contents: "GMIC"
      - id: header_size
        type: s2
        valid: 136
      - id: header_version
        type: s2
        valid: 4
      - id: original_file
        type: strz
        encoding: ascii
        size: 80
      - id: original_frame
        type: s4
      - id: original_stream
        type: s2
      - id: padding
        size: 2
      - id: num_frames
        type: s4
      - id: ofs_next_header
        type: u4
      - id: origin_x
        type: s2
      - id: origin_y
        type: s2
      - id: width
        type: s2
      - id: height
        type: s2
      - id: crop_x
        type: s2
      - id: crop_y
        type: s2
      - id: drop_frame
        type: s2
      - id: drop_phase
        type: s2
      - id: still_period
        type: s4
      - id: bufs_min
        type: s2
      - id: bufs_max
        type: s2
      - id: decode_algorithm
        type: s2
      - id: padding2
        size: 2
      - id: dfc_id
        type: s4

enums:

  avl_type:
    2: compressed_audio_stream
    3: compressed_image_stream
    5: per_frame_data
    6: uncompressed_image_stream
    7: pad_stream
