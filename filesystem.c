#include "filesys.h"
#include <string.h>
filesystem fs;
void in_fs(){
memset(&fs,0,sizeof(fs));
for (int i=0;i<MAX_BLOCKS;i++){
fs.free_blocks[i]=i;
}
fs.free_block_count=MAX_BLOCKS;
}
