#ifndef LIBOTI_H
#define LIBOTI_H

#define OTI_ERROR_BANNER "[OTI_ERROR] "


#define LOG_BLOCKSIZE 3
#define BLOCKSIZE 8  // == LOG_BLOCKSIZE

/* 
 * Given a pointer under protection, it will refer to 
   +-----16-----+------22-------+------23-------+--3--+
   | unused     | top-level idx | bot-level idx |  *  |
   |  bits      | 1st-level idx | 2nd-level idx |     |
   +------------+---------------+---------------+-----+
   
*/

// num entries
#define NUM_FIRST_LVL_ENTRY (1 << 22)
#define NUM_SECOND_LVL_ENTRY (1 << 23)

// mapped size (== num_entries * BLOCKSIZE)
#define FIRST_LVL_SIZE NUM_FIRST_LVL_ENTRY << LOG_BLOCKSIZE  
#define SECOND_LVL_SIZE NUM_SECOND_LVL_ENTRY << LOG_BLOCKSIZE
int __attribute((constructor)) oti_init(void);

void oti_vptr_store(void**);
void oti_vptr_check(void**);


#endif  // LIBOTI_H
