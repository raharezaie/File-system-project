#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <time.h>
#include <stdint.h>
#define MAX_FILES 100
#define BLOCK_SIZE 4096
#define MAX_BLOCKS 1024
typedef struct{
 char name[32]; 
    uint32_t size; 
    uint32_t blocks[MAX_BLOCKS]; 
    uint32_t block_count; 
    uint32_t creation_time; 
    uint32_t modification_time; 
} inode;

typedef struct{
uint8_t data[BLOCK_SIZE];
}block;

typedef struct{
inode nodes[MAX_FILES];
block blocks[MAX_BLOCKS];
uint32_t free_blocks[MAX_BLOCKS]; 
uint32_t free_block_count;}filesystem;
extern filesystem fs;
void in_fs();
uint32_t get_current_time();
int create_file(const char *name);
int delete_file(const char *name);
int read_file(const char *name, char *buffer, uint32_t size);
int write_file(const char *name, char *buffer, uint32_t size);
void save_fs(const char *name);
void load_fs(const char *name);
#endif
