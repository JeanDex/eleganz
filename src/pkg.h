/*
 * Copyright (C) Youness Alaoui (KaKaRoTo)
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 3, as published by the Free Software Foundation.
 *
 */

#ifndef __PKG_H__
#define __PKG_H__

#include "tools.h"
#include "types.h"
#include "common.h"
#include "paged_file.h"

typedef struct {
  u32 magic;
  u32 pkg_type;
  u32 pkg_info_offset;
  u32 unknown3;
  u32 header_size;
  u32 item_count;
  u64 total_size;
  u64 data_offset;
  u64 data_size;
  char contentid[0x30];
  u8 digest[0x10];
  u8 k_licensee[0x10];
} PKG_HEADER;

#define PKG_HEADER_FROM_BE(x)                                   \
  (x).magic = FROM_BE (32, (x).magic);                          \
     (x).pkg_type = FROM_BE (32, (x).pkg_type);                 \
     (x).pkg_info_offset = FROM_BE (32, (x).pkg_info_offset);   \
     (x).unknown3 = FROM_BE (32, (x).unknown3);                 \
     (x).header_size = FROM_BE (32, (x).header_size);           \
     (x).item_count = FROM_BE (32, (x).item_count);             \
     (x).total_size = FROM_BE (64, (x).total_size);             \
     (x).data_offset = FROM_BE (64, (x).data_offset);           \
     (x).data_size = FROM_BE (64, (x).data_size);
#define PKG_HEADER_TO_BE(x) PKG_HEADER_FROM_BE (x)

typedef struct {
  u32 filename_offset;
  u32 filename_size;
  u64 data_offset;
  u64 data_size;
  u32 flags;
  u32 padding;
} PKG_FILE_HEADER;

#define PKG_FILE_HEADER_FROM_BE(x)                                     \
  (x).filename_offset = FROM_BE (32, (x).filename_offset);             \
     (x).filename_size = FROM_BE (32, (x).filename_size);              \
     (x).data_offset = FROM_BE (64, (x).data_offset);                  \
     (x).data_size = FROM_BE (64, (x).data_size);                      \
     (x).flags = FROM_BE (32, (x).flags);
#define PKG_HEADER_TO_BE(x) PKG_HEADER_FROM_BE (x)

int pkg_open (const char *filename, PagedFile *in,
    PKG_HEADER *header, PKG_FILE_HEADER **files);
int pkg_list (const char *filename);
int pkg_unpack (const char *filename, const char *destination);

#endif /* __PKG_H__ */
