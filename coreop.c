#include "filesys.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

filesystem fs;

int create_file(const char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs.nodes[i].name[0] == '\0') {
            strncpy(fs.nodes[i].name, name, sizeof(fs.nodes[i].name) - 1);
            fs.nodes[i].size = 0;
            fs.nodes[i].block_count = 0;
            fs.nodes[i].creation_time = get_current_time();
            fs.nodes[i].modification_time = fs.nodes[i].creation_time;
            return i;
        }
    }
    return -1;
}

int delete_file(const char *name) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(fs.nodes[i].name, name) == 0) {
            for (int j = 0; j < fs.nodes[i].block_count; j++) {
                fs.free_blocks[fs.free_block_count++] = fs.nodes[i].blocks[j];
            }
            memset(&fs.nodes[i], 0, sizeof(inode));
            return 0;
        }
    }
    return -1;
}

int write_file(const char *name, char *buffer, uint32_t size) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(fs.nodes[i].name, name) == 0) {
            uint32_t rem = size;
            fs.nodes[i].size = size;
            fs.nodes[i].block_count = 0;
            fs.nodes[i].modification_time = get_current_time();

            for (int j = 0; j < MAX_BLOCKS && rem > 0; j++) {
                if (fs.free_block_count == 0) return -1;

                int block = fs.free_blocks[--fs.free_block_count];
printf("Before write: Block %d contains: %s\n", block, fs.blocks[block].data);
                memset(fs.blocks[block].data, 0, BLOCK_SIZE);
		uint32_t to_write = (rem > BLOCK_SIZE) ? BLOCK_SIZE : rem;

                printf("Writing %u bytes to block %d\n", to_write, block);
                memcpy(fs.blocks[block].data, buffer, to_write);
 printf("After write: Block %d contains: %s\n", block, fs.blocks[block].data);                
fs.nodes[i].blocks[fs.nodes[i].block_count++] = block;

                buffer += to_write;
                rem -= to_write;
            }
            return size - rem;
        }
    }
    return -1;
}

int read_file(const char *name, char *buffer, uint32_t size) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(fs.nodes[i].name, name) == 0) { 
            uint32_t remaining = size > fs.nodes[i].size ? fs.nodes[i].size : size;
            char *original_buffer = buffer; 

            for (uint32_t j = 0; j < fs.nodes[i].block_count && remaining > 0; j++) {
                uint32_t block = fs.nodes[i].blocks[j]; 

               
                printf("Before read: Block %d contains: %s\n", block, fs.blocks[block].data);

                uint32_t to_read = (remaining > BLOCK_SIZE) ? BLOCK_SIZE : remaining; 
                printf("Reading %u bytes from block %d\n", to_read, block);
                memcpy(buffer, fs.blocks[block].data, to_read); 

                buffer += to_read; 
                remaining -= to_read; 
            }

            *buffer = '\0'; 

            
            printf("After read: Buffer contains: %s\n", original_buffer);

            return size - remaining; 
        }
    }
    return -1; 
}
uint32_t get_current_time() {
    return (uint32_t)time(NULL);
}

void save_fs(const char *name){
FILE *file=fopen(name,"wb");
if (file!=NULL){
fwrite(&fs,sizeof(fs),1,file);}
else{  printf("Error saving file system to disk.\n");}}

void load_fs(const char *name){
FILE *file=fopen(name,"rb");
if (file!=NULL){
fread(&fs,sizeof(fs),1,file);
fclose(file);}
else{printf("Error loading file system from disk, initializing new file system.\n");
in_fs();}}
