meta:
  id: build_grp
  title: BUILD Engine Archive
  application: BUILD Engine
  file-extension: grp
  license: CC0-1.0
  endian: le

doc-ref: https://moddingwiki.shikadi.net/wiki/GRP_Format
doc: |
  BUILD engine GRP file. A basic uncompressed storage format that can store any
  kind of file with an 8.3 filename or less.

  This specification was authored by erysdren (it/its).
  https://erysdren.me/

seq:
  - id: magic
    contents: "KenSilverman"
  - id: num_files
    type: u4
  - id: entries
    type: entry
    repeat: expr
    repeat-expr: num_files

types:
  entry:
    seq:
      - id: filename
        type: strz
        encoding: ascii
        size: 12
      - id: len_file
        type: u4
