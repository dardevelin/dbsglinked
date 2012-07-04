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
	libglinked_list_t list;
	libglinked_node_t *node;
	char *str  = "Hello World";
	char *str2 = "World Hello";

	libglinked_init_list(&list, NULL, NULL);
	
	node = libglinked_create_node(&list, (void*) sstrdup(str), delete_data);
	
	libglinked_show_node(node, printstr);

	libglinked_enqueue_node(&list, node);
	

	node = libglinked_create_node(&list,(void*) sstrdup(str2), delete_data);
	
	libglinked_show_node(node, printstr);

	libglinked_enqueue_node(&list, node);

	puts("\nshowing complete list\n");
	
	libglinked_show_list(&list, printstr);

	libglinked_reverse_list(&list);

	puts("\nshowing reversed list\n");
	libglinked_show_list(&list, printstr);

	libglinked_delete_list(&list);

	

	printf("Worked\n");
	return 0;
}
