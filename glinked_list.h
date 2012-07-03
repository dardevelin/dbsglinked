/*
 * glinked_list.h
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


#ifndef LIBGLINKED_LIST_H_
#define LIBGLINKED_LIST_H_

#include <stdlib.h>
#define LIBGLINKED_DEFAULT_ALLOCATOR malloc;
#define LIBGLINKED_DEFAULT_DEALLOCATOR free;

typedef struct sGlinkedNode {
	void *data;
	void(*data_deallocator)(void *);
	struct sGlinkedNode *next;
} libglinked_node_t;

typedef struct sGlinkedList {
	size_t count;
	void *(*node_allocator)(void *);
	void (*node_deallocator)(void *);
	libglinked_node_t *head;
} libglinked_list_t;
//interface
void libglinked_init_list(libglinked_list_t *, 
  void *(*allocator)(void*), void(*deallocator)(void*));

libglinked_node_t *libglinked_create_node(libglinked_list_t *,
  void *, void(*dalloc)(void*));

void libglinked_delete_node(libglinked_list_t *, libglinked_node_t *);

libglinked_node_t *libglinked_push_node(libglinked_list_t *,
  libglinked_node_t *);

libglinked_node_t *libglinked_pop_node(libglinked_list_t *);

void libglinked_delete_list(libglinked_list_t * );

size_t libglinked_get_num_items(libglinked_list_t *);

void libglinked_show_node(libglinked_node_t *, void(*f)(void*));

void libglinked_show_list(libglinked_list_t *, void(*f)(void*));

void libglinked_reverse_list(libglinked_list_t*);
#endif
