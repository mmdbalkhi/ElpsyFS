#include "elpsyfs.h"
#include <stdio.h>
#include <string.h>

void fs_format(const char *disk_path) {
  FILE *f = fopen(disk_path, "r+b");
  if (!f) {
    perror("fopen");
    return;
  }

  struct superblock sb;
  sb.magic = ELPSYFS_MAGIC;
  sb.total_blocks = MAX_BLOCKS;
  sb.free_blocks = MAX_BLOCKS - 10;
  sb.block_bitmap_start = 1;
  sb.inode_table_start = 2;
  sb.data_block_start = 10;

  fseek(f, 0, SEEK_SET);
  fwrite(&sb, sizeof(sb), 1, f);
  uint8_t bitmap[BITMAP_SIZE_BYTES];
  memset(bitmap, 0, sizeof(bitmap));

  for (int i = 0; i < 10; i++) {
    bitmap[i / 8] |= (1 << (i % 8));
  }

  fseek(f, BLOCK_SIZE * sb.block_bitmap_start, SEEK_SET);
  fwrite(bitmap, sizeof(bitmap), 1, f);
  fclose(f);
}

int fs_check(const char *disk_path) {
  FILE *f = fopen(disk_path, "rb");
  if (!f) {
    perror("fopen");
    return -1;
  }

  struct superblock sb;
  fread(&sb, sizeof(sb), 1, f);
  fclose(f);

  if (sb.magic != ELPSYFS_MAGIC) {
    fprintf(stderr, "Invalid filesystem: magic is 0x%x\n", sb.magic);
    return -1;
  }

  printf("Filesystem OK! Total blocks: %u, Free blocks: %u\n", sb.total_blocks,
         sb.free_blocks);
  return 0;
}

void create_disk(const char *path) {
  FILE *f = fopen(path, "wb");
  if (!f) {
    perror("fopen");
    return;
  }

  char zero[BLOCK_SIZE] = {0};
  for (int i = 0; i < MAX_BLOCKS; i++) {
    fwrite(zero, BLOCK_SIZE, 1, f);
  }

  fclose(f);
}

void fs_print_bitmap(const char *disk_path) {
  FILE *f = fopen(disk_path, "rb");
  if (!f) {
    perror("fopen");
    return;
  }

  uint8_t bitmap[BITMAP_SIZE_BYTES];
  fseek(f, BLOCK_SIZE * 1, SEEK_SET);
  fread(bitmap, sizeof(bitmap), 1, f);
  fclose(f);

  printf("Block bitmap:\n");
  for (int i = 0; i < MAX_BLOCKS; i++) {
    printf("%d", (bitmap[i / 8] >> (i % 8)) & 1);
    if ((i + 1) % 64 == 0)
      printf("\n");
  }
}

int main() {
  fs_format("disk.img");
  fs_check("disk.img");
  fs_print_bitmap("disk.img"); 
  return 0;
}
