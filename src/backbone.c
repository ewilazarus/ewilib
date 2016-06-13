/******************************************************************************
 *
 * ewilib:src.backbone (backbone.c)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *
 * :copyright: (c) 2015 - Gabriel Lima
 * :license: MIT, see LICENSE for more details
 *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "backbone.h"


/******************************************************************************
 ***************************** PRIVATE MEMBERS ********************************
 *****************************************************************************/
static fmeta fmeta_n;  // function used to free node's metadata
static fmeta fmeta_e;  // function used to free edge's metadata


/******************************************************************************
 *
 * :function: linked
 *
 * Resolves whether two nodes are linked. This resolution is *not*
 * bidirectional
 *
 * :param: orig - node to be checked
 * :param: dest - node to be checked
 * :returns: 1 if the nodes are linked or 0 otherwise
 *
 *****************************************************************************/
int linked(Node *orig, Node *dest)
{
	int i, rv;

	for (i = 0, rv = 0; i < orig->count_e; i++) {
		if (orig->edges[i]->to == dest) {
			rv = 1;
			break;
		}
	}
	return rv;
}


/******************************************************************************
 *
 * :function: nalloc
 *
 * Allocates memory for a graph node
 *
 * :except: fails allocating memory
 * :returns: `Node *` - pointer to node
 *
 *****************************************************************************/
Node *nalloc()
{
	Node *n = (Node *)malloc(sizeof(Node));
	if (!n) {
		printf("Error creating node.\n");
		exit(1);
	}
	return n;
}


/******************************************************************************
 *
 * :function: _ealloc
 *
 * (Helper function) Shrinks or expands the allocated memory for the array of
 * edges
 *
 * :param: edges - array of edges
 * :param: l - array of edges' *new* length
 * :except: fails allocating memory
 * :returns: `Edge **` - pointer to array of edges
 *
 *****************************************************************************/
Edge **_ealloc(Edge **edges, int l)
{
	if (l < 0) return NULL;

	Edge **e = (Edge **)realloc(edges, (l * sizeof(Edge *)));
	if (l && !e) {
		printf("Error modifying array of edges.\n");
		exit(1);
	}
	return e;
}


/******************************************************************************
 *
 * :function: ealloc
 *
 * Allocates memory for an array of edges. Note that this function is not
 * responsible for increasing or decreasing the node's edge count (n->count_e)
 *
 * :param: n - node that owns the array of edges referece
 * :param: w - an integer that sums to the node's edge count to increase or 
 *             decreased the needed amount of memory.
 * :except: fails allocating memory
 * :returns: `Edge **` - pointer to array of edges
 *
 *****************************************************************************/
Edge **ealloc(Node *n, int w)
{
	int i, range;
	Edge *e;
	
	range = (n->count_e + w) >= 0 ? n->count_e + w : 0;

	// free metas, free edges, shrink array
	if (w < 0) {
		for (i = n->count_e - 1; i >= range; i--) {
			fmeta_e(n->edges[i]->meta);
			free(n->edges[i]);
		}
		n->edges = _ealloc(n->edges, range);
	
	// expand array, malloc edges
	} else if (w > 0) {
		n->edges = _ealloc(n->edges, range);
		
		for (i = n->count_e; i < range; i++) {
			e = (Edge *)malloc(sizeof(Edge));
			if (!e) {
				printf("Error creating edge.\n");
				exit(1);
			}
			n->edges[i] = e;
		}
	}
	return n->edges;
}


/******************************************************************************
 ****************************** PUBLIC MEMBERS ********************************
 *****************************************************************************/

/******************************************************************************
 *
 * Backbone_register
 *
 *****************************************************************************/
void Backbone_register(fmeta fmetadata_n, fmeta fmetadata_e)
{
	fmeta_n = fmetadata_n;
	fmeta_e = fmetadata_e;
}


/******************************************************************************
 *
 * Backbone_create
 *
 *****************************************************************************/
Node *Backbone_create(void *meta_n)
{
	Node *node = nalloc();
	node->edges = NULL;
	node->count_e = 0;
	node->meta = meta_n;

	return node;
}


/******************************************************************************
 *
 * Backbone_link
 *
 *****************************************************************************/
void Backbone_link(Node *orig, Node *dest, void *meta_e)
{
	if (orig && dest && !linked(orig, dest)) {
		orig->edges = ealloc(orig, 1);
		orig->edges[orig->count_e]->from = orig;
		orig->edges[orig->count_e]->to = dest;
		orig->edges[orig->count_e]->meta = meta_e;
		orig->count_e++;
	}
}


/******************************************************************************
 *
 * Backbone_unlink
 *
 *****************************************************************************/
void Backbone_unlink(Node *orig, Node *dest)
{
	int i, offset;

	for (i = 0, offset = 0; i < orig->count_e; i++) {
		
		// clear edge if adjacent node is target
		if (orig->edges[i]->to == dest) {
			fmeta_e(orig->edges[i]->meta);
			offset++;
		}

		// copy [i + offset]th edge to ith position if not the last
		if (offset > 0 && (i + offset) < orig->count_e) {
			memcpy(orig->edges[i], orig->edges[i + offset], sizeof(Edge));
		}
	}

	// realloc memory if any edge has been cleared
	if (offset > 0) {
		orig->edges = ealloc(orig, (-1 * offset));
		orig->count_e -= offset;
	}
}


/******************************************************************************
 *
 * Backbone_destroy
 *
 *****************************************************************************/
void Backbone_destroy(Node **node)
{
	if (*node) {
		(*node)->edges = ealloc(*node, (-1 * (*node)->count_e));
		free((*node)->edges);
		fmeta_n((*node)->meta);
		free(*node);
		*node = NULL;
	}
}
