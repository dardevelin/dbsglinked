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

/*
  returns a copy of a string, can be 
  considered as node->data allocator
  this is a user defined function.
*/
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
/*
  the node->data deallocator, 
  for node->data created by sstrdup
  used along with libglinked_create_node
  this is a user defined function
*/
void delete_data(void *data)
{
	free(data);
}

/*
  shows node->data when data is
  a string.
  used along show_node and show_list
  functions.
  this is a user defined function
*/
void printstr(void *data)
{
	printf("%s\n", (char *)data);
}

/*
  shows node->data when data is an
  int.
  used along with show_node and show_list
  functions.
  this is a user defined function.
*/
void printint(void *data)
{
	printf("%d\n", *(int*)data);
}

/*
  returns a copy of a int, can be 
  considered as node->data allocator
  this is a user defined function.
*/
int *icopy(int data)
{
	int *new;
	size_t sz = sizeof(int);
	if( (new = malloc( sz )) == NULL )
	{
		fprintf(stderr,"icopy malloc failed\n");
		return NULL;
	}
	
	memcpy(new, &data, sz);
	return new;
}

/*
  frees node->data allocated by
  icopy.
  used along with libglinked_create_node
  function, as the deallocator parameter
  this is a user defined function.
*/
void ideallocator(void *data)
{
	free(data);
}
/*
  this is the function that is triggered for each item
  of the linked list.
  for more info check the readme file, but in short, 
  the return of this function is usually to remark the last
  operation made.
  state to go accross calls between elements, 
  data is the node->data
  param is for/if you need to pass something else.
  used with the libglinked_foreach_node function.
  this is a user defined function.
*/
void *sum_int_list(void *state, void *data, void *param)
{
	//return value. this can be used to return the last
	void *ret = NULL;
	
	(*(int*)state) += ( (*(int*)data) * (*(int*)param) );

	(*(int*)data) *= (*(int*)param);

	return ret = data;
	
}

/*
  this is a user defined function, however it
  needs to respect the given prototype
  bool (void*, void *); and needs to return true,
  when both are equal.
  this is for sample the use of
  libglinked_find_node function
*/
bool int_compare(void *data, void *key)
{
	return (*(int*)data) == (*(int*)key);
}

int main(int argc, char **argv)
{
	//our sample constants
	char *str  = "Hello World";
	char *str2 = "World Hello";

	libglinked_node_t *node;
	//handle fifo list sample

	//the list used to sample a fifo implementation
	libglinked_list_t list_fifo;

	/*iniciate the list, NULL will set the 
	  default allocator and default deallocator for
	  libglinked_node_t structures.
	  default ones are malloc and free.
	  you can set you own allocators by passing a allocator
	  of void *(*allocator)(void *)
	  and a deallocator of void (*deallocator)(void *);
	*/
	libglinked_init_list(&list_fifo, NULL, NULL);

	
	/*create the node and put it in a temporary node, 
	  the list is used because of the libglinked_node_t
	  structures allocators
	  returns null in failure
	 */
	node = libglinked_create_node(&list_fifo,
    (void*) sstrdup(str), delete_data);
	
	//check for failure
	if(node == NULL ) 
		fprintf(stderr,"failed to create node %d\n", __LINE__);
		
	//check for failure while trying to add to the fifo list
	if(NULL == libglinked_enqueue_node(&list_fifo, node) )
		fprintf(stderr,"failed to enqueue node %d\n", __LINE__);

	node = libglinked_create_node(&list_fifo,
	    (void *)sstrdup(str2), delete_data);

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
	    (void*) sstrdup(str), delete_data);

	if(node == NULL)
		fprintf(stderr,"failed to create node %d\n", __LINE__);

	if( NULL == libglinked_push_node(&list_lifo, node) )
		fprintf(stderr,"failed to push node %d\n", __LINE__);

   
	node = libglinked_create_node(&list_lifo, 
        (void *) sstrdup(str2), delete_data);

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

	//handle sample int list
	libglinked_list_t list_int;
	
	libglinked_init_list(&list_int, NULL, NULL);
	
	//clean node just to make sure
	node = NULL;

	node = libglinked_create_node(&list_int, 
       (void *)icopy(15), ideallocator);

	if( node == NULL )
		fprintf(stderr,"failed to create list_int node %d\n", __LINE__);

	if(NULL == libglinked_enqueue_node(&list_int, node) )
		fprintf(stderr,"failed to enqueue node %d\n", __LINE__);

	node = libglinked_create_node(&list_fifo, 
       (void*)icopy(30), ideallocator);

	if(node == NULL)
		fprintf(stderr,"failed to create node %d\n", __LINE__);

	if(NULL == libglinked_enqueue_node(&list_int, node) )
		fprintf(stderr,"failed to enqueue node %d\n", __LINE__);

	
	node = libglinked_create_node(&list_int, 
       (void *)icopy(45), ideallocator);

	if(node == NULL )
		fprintf(stderr,"failed to create node %d\n", __LINE__);

	if(NULL == libglinked_enqueue_node(&list_int, node) )
		fprintf(stderr,"failed to enqueue node %d\n", __LINE__);


	puts("show int list");
	libglinked_show_list(&list_int, printint);
	puts("reverse list");
	libglinked_reverse_list(&list_int);
	libglinked_show_list(&list_int, printint);
	
	//foreach user input
	int n = 10, 
		res=0; // result

	//returns of libglinked_foreach_node
	void *ret      = NULL; //return 
	void *stateh   = &res; //state handler

	
	ret = libglinked_foreach_node(&list_int, stateh, sum_int_list, &n);
	
	puts("showing ret value and state handler value");
	printf("ret    = %d\n", *(int*)ret);
	printf("stateh = %d\n", *(int*)stateh);

	puts("\nshowing processed list");
	libglinked_show_list(&list_int, printint);

	//the value we are looking for in the list
	int key = 300;
	printf("trying to find node :\n\t");
	node = libglinked_find_node(&list_int, (void*)&key, int_compare);

	//check if we found the node or not
	if(node == NULL )
		printf("couldn't find node\n");
	else
	{
		printf("found: ");
		libglinked_show_node(node, printint);
	}

	puts("\ntrying to remove node");
	node = libglinked_remove_node(&list_int, (void*)&key, int_compare);

	if(node == NULL)
		puts("\tfailed to remove");
	else
	{
		printf("found: ");
		libglinked_show_node(node, printint);
		printf("deleting node - - - -");
		libglinked_delete_node(&list_int, node);
		printf("DONE\n");
		puts("\nshow list after removal");
		libglinked_show_list(&list_int, printint);
	}

	//create some more nodes to sample split list function

	node = libglinked_create_node(&list_int, (void*)icopy(500),ideallocator);
	if(node == NULL)
		fprintf(stderr,"\nfailed to create node %d\n", __LINE__);

	libglinked_enqueue_node(&list_int, node);

	node = libglinked_create_node(&list_int, (void*)icopy(600),ideallocator);
	if(node == NULL)
		fprintf(stderr,"\nfailed to create node %d\n", __LINE__);

	libglinked_enqueue_node(&list_int, node);

	node = libglinked_create_node(&list_int, (void*)icopy(700),ideallocator);
	if(node == NULL)
		fprintf(stderr,"\nfailed to create node %d\n", __LINE__);

	libglinked_enqueue_node(&list_int, node);

	node = libglinked_create_node(&list_int, (void*)icopy(800),ideallocator);
	if(node == NULL)
		fprintf(stderr,"\nfailed to create node %d\n", __LINE__);

	libglinked_enqueue_node(&list_int, node);

	node = libglinked_create_node(&list_int, (void*)icopy(900),ideallocator);
	if(node == NULL)
		fprintf(stderr,"\nfailed to create node %d\n", __LINE__);

	libglinked_enqueue_node(&list_int, node);
	
	puts("\nshow the current list before the split");
	libglinked_show_list(&list_int, printint);
	printf("has %zu items\n", libglinked_get_num_items(&list_int));
	
	libglinked_list_t new_list;
	puts("\nmaking split at 600");
	key = 600;
	if(libglinked_split_list(&list_int, &new_list, (void*)&key, int_compare) == NULL)
		fprintf(stderr,"split failed %d\n", __LINE__);
	
	puts("\nshow list after split");

	libglinked_show_list(&list_int, printint);
	printf("has %zu items\n", libglinked_get_num_items(&list_int));

	puts("\nshow new list, from split");
	
	libglinked_show_list(&new_list, printint);
	printf("has %zu items\n", libglinked_get_num_items(&new_list));

    //clean the new list
	libglinked_delete_list(&new_list);
	
	//clean all allocated memory
	libglinked_delete_list(&list_int);	

  	return 0;
}
