#ifndef PAGING_H_UVXAEOK2
#define PAGING_H_UVXAEOK2


#define NUM_PAGE_TABLES 1024
#define NUM_PAGE_FRAMES 1024
#define PAGE_FRAME_SIZE 4096

/* page write attributes */
#define PAGE_READ_ONLY 0
#define PAGE_READ_WRITE 1

/* page access permissions */
#define PAGE_USER 1
#define PAGE_KERNEL 0

/* page size */
#define PAGE_SIZE_4KB 0
#define PAGE_SIZE_4MB 1

struct page_directory_entry {
    unsigned int present                        : 1;
    unsigned int read_write                     : 1;
    unsigned int permissions                    : 1;
    unsigned int write_through                  : 1;
    unsigned int cache_disabled                 : 1;
    unsigned int accessed                       : 1;
    unsigned int reserved_1                     : 1;
    unsigned int page_size                      : 1;
    unsigned int reserved_2                     : 3;
    unsigned int page_table_address             : 20;
};
typedef struct page_directory_entry page_directory_entry_t;


struct page_table_entry {
    unsigned int present                   : 1;
    unsigned int read_write                : 1;
    unsigned int permissions               : 1;
    unsigned int write_through             : 1;
    unsigned int cache_disabled            : 1;
    unsigned int accessed                  : 1;
    unsigned int dirty                     : 1;
    unsigned int reserved_1                : 1;
    unsigned int global                    : 1;
    unsigned int reserved_2                : 3;
    unsigned int physical_page             : 20;
};
typedef struct page_table_entry page_table_entry_t;



void init_identity_paging();

void page_fault();

extern void enable_paging(unsigned int pdt_address);
extern void enable_paging_identity(unsigned int pdt_address);

/*
 ; invalidate any TLB references to virtual address 0
    invlpg [0]
*/

#endif /* end of include guard: PAGING_H_UVXAEOK2 */
