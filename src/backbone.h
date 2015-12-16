/******************************************************************************
 *
 * ewilib:src.backbone (backbone.h)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * This module implements the barebone functionality of a graph
 *
 * Note that this module is intended to be generic and reusable, therefore,
 * it does not assume a specific usage for the graph. It should *not* be used
 * directly in application code, but, instead, extended to suit the client's
 * needs
 *
 * IMPORTANT: It is the *client's responsability* to manage a proper and
 *            memory safe node destruction
 *
 *
 * :copyright: (c) 2015 - Gabriel Lima
 * :license: MIT, see LICENSE for more details
 *
 *****************************************************************************/
#ifndef _backbone_h_
#define _backbone_h_


/******************************************************************************
 *
 * :datatype: Node
 *
 * Representation of a node in a graph
 *
 * :member: edges - array of ptrs to directed edges related to this node
 * :member: count_e - count of number of edges related to this node
 * :member: meta - metadata associated with this node (e.g.: label, value)
 *
 *****************************************************************************/
struct Edge;

typedef struct Node {
	struct Edge **edges;
	int count_e;
	void *meta;
} Node;


/******************************************************************************
 *
 * :datatype: Edge
 *
 * Representation of an edge in a graph
 *
 * :member: from - node *from* where this edge points
 * :member: to - node where this edge points *to*
 * :member: meta - metadata associated with this edge (e.g.: weight, visited)
 *
 *****************************************************************************/
typedef struct Edge {
	Node *from;
	Node *to;
	void *meta;
} Edge;


/******************************************************************************
 *
 * :datatype: fmeta
 *
 * Pointer to function responsible for freeing memory of either node's and 
 * edge's metadata
 *
 * :param: meta - metadata to be freed
 *
 *****************************************************************************/
typedef void (*fmeta)(void *meta);


/******************************************************************************
 *
 * :function: Backbone_register
 *
 * Registration entry point for the functions responsible for freeing the 
 * nodes' and the edges' metadata.
 *
 * IMPORTANT: This function should be invoked once in the beginning of the
 *            workflow
 *
 * :param: fmeta_n - function responsible for freeing the metadata associated
 *                   with the nodes
 * :param: fmeta_e - function responsible for freeing the metadata associated
 *                   with the edges
 *
 *****************************************************************************/
void Backbone_register(fmeta fmeta_n, fmeta fmeta_e);


/******************************************************************************
 *
 * :function: Backbone_create
 *
 * Creates a graph node
 *
 * :param: meta_n - metadata associated with this node
 * :returns: `Node *` - pointer to created node
 *
 *****************************************************************************/
Node *Backbone_create(void *meta_n);


/******************************************************************************
 *
 * :function: Backbone_link
 *
 * Links two graph nodes. This linkage is *not* bidirectional
 *
 * :param: orig - node to be linked
 * :param: dest - node to be linked
 * :param: meta_e - metadata associated with the edge linking the nodes
 *
 *****************************************************************************/
void Backbone_link(Node *orig, Node *dest, void *meta_e);


/******************************************************************************
 *
 * :function: Backbone_unlink
 *
 * Unlinks two graph nodes. This unlinkage is *not* bidirectional
 *
 * :param: orig - node to be unlinked
 * :param: dest - node to be unlinked
 *
 *****************************************************************************/
void Backbone_unlink(Node *orig, Node *dest);


/******************************************************************************
 *
 * :function: Backbone_destroy
 *
 * Destroys a graph node. This destruction is *not* memory safe
 *
 * :param: node - pointer to the  node to be destroyed
 *
 *****************************************************************************/
void Backbone_destroy(Node **node);

#endif
