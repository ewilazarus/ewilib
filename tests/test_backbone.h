/******************************************************************************
 *
 * ewilib:tests.test_backbone (test_backbone.h)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * This module implement the backbone's test suite.
 *
 * TESTS: [NODE_CREATION]
 *        test_can_create_node
 *        test_can_correclty_init_node
 *
 *        [NODE_LINKING]
 *        test_can_link_two_nodes
 *        test_can_link_multiple_nodes
 *        test_can_link_node_to_itself
 *        test_cannot_link_node_more_than_once_same_target
 *        test_cannot_link_node_to_null_target
 *
 *        [NODE_UNLINKING]
 *        test_can_unlink_two_linked_nodes
 *        test_can_unlink_multiple_linked_nodes
 *        test_cannot_unlink_not_linked_nodes
 *
 *        [NODE_DESTRUCTION]
 *        test_can_destroy_node
 *
 *****************************************************************************/


/******************************************************************************
 *
 * :function: Suite_backbone
 *
 * Creates a test suite for the backbone module
 *
 * :returns: `Suite *` - test suite
 *
 *****************************************************************************/
Suite *TSuite_backbone(void);
