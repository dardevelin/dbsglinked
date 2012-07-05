/*
 * main.c
 * This file is part of dbsglinked
 *
 * Copyright (C) 2012 - Darcy Brás da Silva
 *
 * dbsglinked is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * dbsglinked is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dbsglinked. If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "glinked_list.h"

char *sstrdup(const char * str)
{
	size_t l = strlen(str);
	char *new;
	if( (new = malloc(l+1))== NULL)
	{
		fprintf(stderr,"sstrdup malloc failed\n");
		return NULL;
	}
	memcpy(new,str,l); new[l] ='\0';
	return new;
}

void delete_data(void *data)
{
	free(data);
}

void printstr(void *data)
{
	char *str = (char*) data;
	printf("%s\n", str);
}

int main(int argc, char **argv)
{		
	char *str  = "Hello World";
	char *str2 = "World Hello";

	libglinked_node_t *node;
	//handle fifo list sample

	libglinked_list_t list_fifo;

	libglinked_init_list(&list_fifo, NULL, NULL);
	
	node = libglinked_create_node(&list_fifo,
								  (void*) sstrdup(str),
								  delete_data);
	
	if(node == NULL )
		fprintf(stderr,"failed to create node %d\n", __LINE__);
		
	
	if(NULL == libglinked_enqueue_node(&list_fifo, node) )
		fprintf(stderr,"failed to enqueue node %d\n", __LINE__);

	node = libglinked_create_node(&list_fifo,
								  (void *)sstrdup(str2),
								  delete_data);

	if(node == NULL)
		fprintf(stderr,"failed to create node %d\n", __LINE__);

	if(NULL == libglinked_enqueue_node(&list_fifo, node) )
		fprintf(stderr,"failed to enqueue node %d\n", __LINE__);

	puts("show fifo results");
	libglinked_show_list(&list_fifo, printstr);
	puts("the reverse list");
	libglinked_reverse_list(&list_fifo);
	libglinked_show_list(&list_fifo, printstr);
	puts("\n");

	
	//clean the node just to make sure
	node = NULL;

	libglinked_list_t list_lifo;

	//hanlde lifo sample
	libglinked_init_list(&list_lifo, NULL, NULL);
	
	node = libglinked_create_node(&list_lifo, 
								  (void*) sstrdup(str),
								  delete_data);

	if(node == NULL)
		fprintf(stderr,"failed to create node %d\n", __LINE__);

	if( NULL == libglinked_push_node(&list_lifo, node) )
		fprintf(stderr,"failed to push node %d\n", __LINE__);

   
	node = libglinked_create_node(&list_lifo, 
								  (void *) sstrdup(str2),
								  delete_data);

	if(node == NULL)
		fprintf(stderr,"failed create node %d\n", __LINE__);

	if( NULL == libglinked_push_node(&list_lifo, node) )
		fprintf(stderr,"failed to push node %d\n", __LINE__);

	puts("show lifo results");
	libglinked_show_list(&list_lifo, printstr);
	puts("show reverse list");
	libglinked_reverse_list(&list_lifo);
	libglinked_show_list(&list_lifo, printstr);
	puts("\n");
	
	//erase both lists

	libglinked_delete_list(&list_fifo);
	libglinked_delete_list(&list_lifo);
	
  	return 0;
}
