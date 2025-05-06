#pragma once
#include <stdint.h>

#define ELPSYFS_MAGIC 0x3D289 // 250505
#define BLOCK_SIZE 4096
#define MAX_BLOCKS 1024

#define BITMAP_SIZE_BYTES (MAX_BLOCKS / 8)

struct superblock {
  uint32_t magic;
  uint32_t total_blocks;
  uint32_t free_blocks;
  uint32_t block_bitmap_start;
  uint32_t inode_table_start;
  uint32_t data_block_start;
};
