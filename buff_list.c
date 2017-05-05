#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buff_list.h"

struct buf {
	struct buf* next;
	size_t nread;
	size_t nsize;
	char base[1];
};

struct buff_list {
	struct buf* head;
	struct buf* tail;
};

struct buf* malloc_buf(size_t len) {
	return malloc(sizeof(struct buf) + len);
}

void free_buf(struct buf * buf) {
	free(buf);
}

void add_tail(struct buff_list* B, struct buf* buf) {
	if (!B->head) {
		B->head = buf;
	}

	if (B->tail) {
		B->tail->next = buf;
	}
	B->tail = buf;
}

struct buf* del_head(struct buff_list* B) {
	struct buf* buf = B->head;
	if (buf) {
		if (B->head == B->tail) {
			B->head = NULL;
			B->tail = NULL;
		} else {
			B->head = buf->next;
		}
	}
	return buf;
}

struct buf* get_head(struct buff_list* B) {
	return B->head;
}

struct buff_list* 
buff_new() {
	struct buff_list* B = malloc(sizeof(struct buff_list));
	memset(B, 0, sizeof(struct buff_list));
	return B;
}

void
buff_delete(struct buff_list* B) {
	const char* buf;
	size_t nsize;
	while((buf = buff_next(B, &nsize))) {
		buff_read(B, nsize);
	}
	free(B);
}

void 
buff_write(struct buff_list* B, const char* base, size_t len) {
	struct buf* buf = malloc_buf(len);

	buf->next = NULL;
	buf->nread = 0;
	buf->nsize = len;

	memcpy(&buf->base, base, len);

	add_tail(B, buf);
}

void 
buff_read(struct buff_list* B, size_t nread) {
	struct buf* buf = get_head(B);
	if (!buf) return;

	if (nread == buf->nsize - buf->nread) {
		struct buf* buf = del_head(B);
		free_buf(buf);
		return;
	}

	buf->nread += nread;
}

const char* 
buff_next(struct buff_list* B, size_t* nlen) {
	struct buf* buf = get_head(B);
	if (!buf) return NULL;

	*nlen = buf->nsize - buf->nread;

	return buf->base + buf->nread;
}

