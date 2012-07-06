# DBSGLINKED version 0.0.19

This is a small C implementation of a generic linked list, to avoid having to
create the same code all the time. 
		
## LICENSE - GPLv3
See COPYING to get the license or go to
http://www.gnu.org/licenses/gpl-3.0.txt

## Lib Interface - quick docs
### Usage:
	A complete use of libraries function can be found in main.c
	main.c is not required to use the library.
#### libglinked_init_list(libglinked_list_t * list, void * (*node_allocator)(void * ), void(*node_deallocator)(void * )); 
	Prepares the list so it can be used.

#### libglinked_node_t *libglinked_create_node(libglinked_list_t *list, void *data, void(*dalloc)(void * ));
     checks if data is null, if it is, returns null
     if data is not null, creates a ligblinked_node_t using list->node_allocator and points
     node->data to data;
     sets node->data_deallocator to dalloc; the user may use null to not deallocate
     the data. Useful for things like literals and constanst
     sets node->next to null
     returns the newly created node

#### void libglinked_delete_node(libglinked_list_t *list, libglinked_node_t *node )
	checks if node is null, if it is, returns null
	checks if node->data and node->data_deallocator aren't set
        to null, if not, then calls node->data_deallocator(node->data);
	else if node->data or node->data_deallocator are set to null
	the call will be ignored, however the node_t structure will be deallocated using
	list->node_deallocator that was set using libglinked_init_list
	
#### libglinked_node_t *libglinked_enqueue_node(libglinked_list_t *list,linglinked_node_t *node);
	Increments the list items count;
	Appends node to the end of list (fifo)
	Returns the enqueued node, this is useful for a combined call of
	libglinked_enqueue_node with libglinked_create_node;
	Like so:
	libglinked_node_t * catch;
	catch = libglinked_enqueue_node(&list, libglinked_create_node(data));

#### libglinked_node_t * libglinked_push_node(libglinked_list_t * list, libglinked_node_t * node);
        Increments the list items count
	Appends node to the start of the list (lifo)
	returns the pushed node, this is useful for a combined call
	of libglinked_push_node with libglinked_create_node;
	like so:
	catch = libglinked_push_node(libglinked_list_t * list, libglinked_node_t * node);

#### libglinked_node_t * libglinked_dequeue_node(libglinked_list_t * list);
	Decrements the list items count (fifo)
	Removes a node from the head of the list and returns it
	Returns NULL if the list is empty

#### libglinked_node_t * libglinked_pop_node(libglinked_list_t * list);
        Decrements the list items count (lifo)
	Removes a node from the head of the list and returns it
	Returns NULL if the list is empty     

#### void libglinked_delete_list(libglinked_list_t *list );
	dequeues all nodes from the list and deletes them using 
	libglinked_delete_node(libglinked_node_t *node );

#### size_t libglinked_get_num_items(libglinked_list_t *list);
	Gets the count of the current amount of items in the list;

#### void libglinked_show_node(libglinked_node_t *node, void(*f)(void * ));
	Shows the data stored in the node, using the function passed
	By parameter to it. 

#### void libglinked_show_list(libglinked_list_t *list, void(*f)(void * ));
	Shows the full list nodes using the f function passed by parameter
	to it

#### void * libglinked_foreach_node(libglinked_list_t * list,void * state, void * ( *action)(void * , void * , void * ), void * param);
        iterates through each node triggering action function.
	like so:
	catch = action(state, node->data, param);
	this way catch will always contain the result of the last 
	operation.
	and state can be used to travel data through node calls.
	data, is the node data to be processed/analised
	param is so the user can carry any data into the function needed
	for whatever the process is. 
	if action is NULL, the function fails and returns NULL;

#### libglinked_node_t * libglinked_find_node(libglinked_list_t * list, void * key, bool (*cmp)(void * , void * ));
        This function receives a list where it uses cmp function to determine
        if node->data and key are equal, if so cmp must return true and
        returns the node that was found
	in case of failure returns null
	if cmp is null, fail and return null

#### libglinked_node_t * libglinked_remove_node(libglinked_list_t * list, void * key, bool (*cmp)(void * , void * ));
     	This function receives a list where it uses cmp function to determine
	if node->next->data and key are equal, if so cmp must return true and
        the node which data and key are equal is removed from the list
	in case of failure returns null

#### libglinked_list_t *libglinked_split_list(libglinked_list_t * list, libglinked_list_t * nlist, void * key, bool(*cmp)(void * , void * ));
        This function receives a list where it uses cmp function to determine
        the split location. stores half of the list into nlist, returns
        a pointer to nlist.
        in case of failure returns null

#### void libglinked_reverse_list(libglinked_list_t *list)
	Reverses the linked list and sets list as the head;
	
## TODO
	A complete todo list can be found in TODO file
	This file also contains information of which version received
	a specific feature
