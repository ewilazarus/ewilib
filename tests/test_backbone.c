/******************************************************************************
 *
 * ewilib:tests.test_backbone (test_backbone.c)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *
 * :copyright: (c) 2015 - Gabriel Lima
 * :license: MIT, see LICENSE for more details
 *
 *****************************************************************************/
#include <stdlib.h>
#include <check.h>

#include "../src/backbone.h"
#include "test_backbone.h"


/******************************************************************************
 ***************************** PRIVATE MEMBERS ********************************
 *****************************************************************************/
void free_meta(void *meta)
{
	return;
}


/********************************** TESTS ************************************/
void setup(void)
{
	Backbone_register(free_meta, free_meta);
}


START_TEST(test_can_create_node)
{
	Node *n = Backbone_create(NULL);

	ck_assert_ptr_ne(n, NULL);

	Backbone_destroy(&n);
}
END_TEST


START_TEST(test_can_correctly_init_node)
{
	char *meta = "META";
	Node *n = Backbone_create(meta);

	ck_assert_int_eq(n->count_e, 0);
	ck_assert_ptr_eq(n->edges, NULL);
	ck_assert_ptr_eq(n->meta, meta);

	Backbone_destroy(&n);
}
END_TEST


START_TEST(test_can_link_two_nodes)
{
	Node *n1 = Backbone_create(NULL);
	Node *n2 = Backbone_create(NULL);

	Backbone_link(n1, n2, NULL);
	Backbone_link(n2, n1, NULL);
	
	ck_assert_int_eq(1, n1->count_e);
	ck_assert_int_eq(1, n2->count_e);
	
	ck_assert_ptr_eq(n1->edges[0]->to, n2);
	ck_assert_ptr_eq(n2->edges[0]->to, n1);

	Backbone_unlink(n1, n2);
	Backbone_unlink(n2, n1);

	Backbone_destroy(&n1);
	Backbone_destroy(&n2);
}
END_TEST


START_TEST(test_can_link_multiple_nodes)
{
	Node *n1 = Backbone_create(NULL);
	Node *n2 = Backbone_create(NULL);
	Node *n3 = Backbone_create(NULL);

	Backbone_link(n1, n2, NULL);
	Backbone_link(n1, n3, NULL);
	Backbone_link(n2, n1, NULL);
	Backbone_link(n2, n3, NULL);
	Backbone_link(n3, n1, NULL);
	Backbone_link(n3, n2, NULL);
	
	ck_assert_int_eq(2, n1->count_e);
	ck_assert_int_eq(2, n2->count_e);
	ck_assert_int_eq(2, n3->count_e);

	ck_assert_ptr_eq(n1->edges[0]->to, n2);
	ck_assert_ptr_eq(n1->edges[1]->to, n3);
	ck_assert_ptr_eq(n2->edges[0]->to, n1);
	ck_assert_ptr_eq(n2->edges[1]->to, n3);
	ck_assert_ptr_eq(n3->edges[0]->to, n1);
	ck_assert_ptr_eq(n3->edges[1]->to, n2);

	Backbone_unlink(n1, n2);  // unlink in the same order
	Backbone_unlink(n1, n3);
	Backbone_unlink(n2, n1);
	Backbone_unlink(n2, n3);
	Backbone_unlink(n3, n2);  // unlink in the opposite order
	Backbone_unlink(n3, n1);

	Backbone_destroy(&n1);
	Backbone_destroy(&n2);
	Backbone_destroy(&n3);
}
END_TEST


START_TEST(test_can_link_node_to_itself)
{
	Node *n = Backbone_create(NULL);

	Backbone_link(n, n, NULL);

	ck_assert_int_eq(n->count_e, 1);
	ck_assert_ptr_eq(n->edges[0]->to, n);

	Backbone_unlink(n, n);
	
	Backbone_destroy(&n);
}
END_TEST


START_TEST(test_cannot_link_node_more_than_once_same_target)
{
	Node *n1 = Backbone_create(NULL);
	Node *n2 = Backbone_create(NULL);

	Backbone_link(n1, n2, NULL);
	Backbone_link(n1, n2, NULL);

	ck_assert_int_eq(n1->count_e, 1);
	
	Backbone_unlink(n1, n2);

	Backbone_destroy(&n1);
	Backbone_destroy(&n2);
}
END_TEST


START_TEST(test_can_unlink_two_linked_nodes)
{
	Node *n1 = Backbone_create(NULL);
	Node *n2 = Backbone_create(NULL);
	
	Backbone_link(n1, n2, NULL);
	Backbone_link(n1, n2, NULL);

	Backbone_unlink(n1, n2);
	Backbone_unlink(n2, n1);

	ck_assert_int_eq(n1->count_e, 0);
	ck_assert_int_eq(n2->count_e, 0);

	Backbone_destroy(&n1);
	Backbone_destroy(&n2);
}
END_TEST


START_TEST(test_can_unlink_multiple_linked_nodes)
{
	Node *n1 = Backbone_create(NULL);
	Node *n2 = Backbone_create(NULL);
	Node *n3 = Backbone_create(NULL);
	
	Backbone_link(n1, n2, NULL);
	Backbone_link(n1, n3, NULL);

	Backbone_unlink(n1, n2);
	ck_assert_int_eq(n1->count_e, 1);

	Backbone_unlink(n1, n3);
	ck_assert_int_eq(n1->count_e, 0);

	Backbone_destroy(&n1);
	Backbone_destroy(&n2);
	Backbone_destroy(&n3);
}
END_TEST


START_TEST(test_cannot_unlink_not_linked_nodes)
{
	Node *n1 = Backbone_create(NULL);
	Node *n2 = Backbone_create(NULL);

	ck_assert_int_eq(n1->count_e, 0);
	ck_assert_int_eq(n2->count_e, 0);

	Backbone_unlink(n1, n2);

	ck_assert_int_eq(n2->count_e, 0);
	ck_assert_int_eq(n2->count_e, 0);

	Backbone_destroy(&n1);
	Backbone_destroy(&n2);
}
END_TEST


START_TEST(test_can_destroy_node)
{
	Node *n = Backbone_create(NULL);

	Backbone_destroy(&n);
	
	ck_assert_ptr_eq(n, NULL);
}
END_TEST


/******************************************************************************
 ****************************** PUBLIC MEMBERS ********************************
 *****************************************************************************/

/******************************************************************************
 *
 * Suite_backbone
 *
 *****************************************************************************/
Suite *TSuite_backbone(void)
{
	Suite *s;
	TCase *tc;

	s = suite_create("Backbone");

	tc = tcase_create("NODE_CREATION");
	tcase_add_unchecked_fixture(tc, setup, NULL);
	tcase_add_test(tc, test_can_create_node);
	tcase_add_test(tc, test_can_correctly_init_node);
	suite_add_tcase(s, tc);

	tc = tcase_create("NODE_LINKING");
	tcase_add_unchecked_fixture(tc, setup, NULL);
	tcase_add_test(tc, test_can_link_two_nodes);
	tcase_add_test(tc, test_can_link_multiple_nodes);
	tcase_add_test(tc, test_can_link_node_to_itself);
	tcase_add_test(tc, test_cannot_link_node_more_than_once_same_target);
	suite_add_tcase(s, tc);

	tc = tcase_create("NODE_UNLINKING");
	tcase_add_unchecked_fixture(tc, setup, NULL);
	tcase_add_test(tc, test_can_unlink_two_linked_nodes);
	tcase_add_test(tc, test_can_unlink_multiple_linked_nodes);
	tcase_add_test(tc, test_cannot_unlink_not_linked_nodes);
	suite_add_tcase(s, tc);

	tc = tcase_create("NODE_DESTRUCTION");
	tcase_add_unchecked_fixture(tc, setup, NULL);
	tcase_add_test(tc, test_can_destroy_node);
	suite_add_tcase(s, tc);

	return s;
}
