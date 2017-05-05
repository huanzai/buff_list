all : buff_list

buff_list : buff_list.c buff_list_test.c
	gcc -g -Wall -o $@ $^ 

clean :
	rm buff_list