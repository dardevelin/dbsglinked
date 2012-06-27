/*
 * glinked_list.c
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

void libglinked_init_list(libglinked_list_t *list)
{
	list->count = 0;
	list->head = NULL;
	return;
}

libglinked_node_t *libglinked_create_node(void *data)
{
	libglinked_node_t *ptrnode;
	
	if (data == NULL )
		return NULL;
	
	if( (ptrnode = malloc( sizeof(libglinked_node_t)))==NULL )
	{
		fprintf(stderr,"libglinked_create_node malloc failed to alloc node_t\n");
		return NULL;
	}

	ptrnode->data = data;
	ptrnode->next = NULL;

	return ptrnode;
}

void libglinked_delete_node(libglinked_node_t *node, void(*f)(void*))
{
	if( node != NULL )
	{
		if( node->data != NULL && f != NULL )
			f(node->data);
				
		free(node);
		return;
	}
}

libglinked_node_t *libglinked_push_node(libglinked_list_t *list,
										libglinked_node_t *node)
{
	libglinked_node_t *ptrnode = list->head;
	
	if( node == NULL )
		return NULL; // nothing to push
	
	if( list->head == NULL )
	{
		list->head = node;
		list->count++;
		return node;
	}

	while(ptrnode->next != NULL )
		ptrnode = ptrnode->next;

	ptrnode->next = node;
	list->count++;
	return ptrnode;
}

libglinked_node_t *libglinked_pop_node(libglinked_list_t *list)
{
	libglinked_node_t *ptrnode = list->head;
	
	if( list->head == NULL )
		return NULL; // nothing to pop

	list->head = list->head->next;
	list->count--;
	return ptrnode;
}

void libglinked_delete_list(libglinked_list_t *list, void(*f)(void*))
{
	while(list->head != NULL )
	{
		libglinked_delete_node(libglinked_pop_node(list), f);
	}
	
}

size_t libglinked_get_num_items(libglinked_list_t *list)
{
	return list->count;
}

void libglinked_show_node(libglinked_node_t *node, void(*f)(void*))
{
	f(node->data);
}

void libglinked_show_list(libglinked_list_t *list, void(*f)(void*))
{
	libglinked_node_t *ptrnode = list->head;

	while(ptrnode != NULL )
	{
		libglinked_show_node(ptrnode,f);
		ptrnode = ptrnode->next;
	}
}

void libglinked_reverse_list(libglinked_list_t *list)
{
	libglinked_node_t *head = list->head,
		              *prev = NULL, 
		              *next = NULL;

    while( head )
    {
        //set head as last node
        list->head = head;
        //save the next ptr in PtrNext
        next = head->next;
        //change next to previous
        head->next = prev;
        //set current as previous
        prev = head;
        //set current as Next
        head = next;
    }
    
    next = list->head;
    list->head = next;


}










