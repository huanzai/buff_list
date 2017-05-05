#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buff_list.h"

int main(void)
{
	struct buff_list* B = buff_new();

	const char* msg1 = "hello world";
	const char* msg2 = "Iam Roy";
	const char* msg3 = "China is my country";
	const char* msg4 = "where are you come from";

	size_t len;
	const char* buf;

	buff_write(B, msg1, strlen(msg1) + 1);
	buf = buff_next(B, &len);
	printf("%s\n", buf);
	buff_read(B, len);

	buff_write(B, msg2, strlen(msg2) + 1);
	buf = buff_next(B, &len);
	printf("%s\n", buf);
	buff_read(B, len);

	buff_write(B, msg3, strlen(msg3) + 1);
	buf = buff_next(B, &len);
	printf("%s\n", buf);
	buff_read(B, len);

	buff_write(B, msg4, strlen(msg4) + 1);
	buf = buff_next(B, &len);
	printf("%s\n", buf);
	buff_read(B, len);

	buff_write(B, msg1, strlen(msg1));
	buff_write(B, msg2, strlen(msg2));
	buff_write(B, msg3, strlen(msg3));
	buff_write(B, msg4, strlen(msg4));

	char tmp[1024];

	size_t nread;
	while((buf = buff_next(B, &len))) {
		nread = 5;
		if (len < nread) {
			nread = len;
		}

		memset(tmp, 0, 1024);
		memcpy(tmp, buf, nread);
		printf("%s\n", tmp);

		buff_read(B, nread);
	}

	buff_delete(B);
	return 0;
}