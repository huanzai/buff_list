#ifndef _BUFF_LIST_
#define _BUFF_LIST_

struct buff_list;

struct buff_list* buff_new();
void buff_delete(struct buff_list* B);
void buff_write(struct buff_list* B, const char* base, size_t len);
void buff_read(struct buff_list* B, size_t nread);
const char* buff_next(struct buff_list* B, size_t* nlen);

#endif