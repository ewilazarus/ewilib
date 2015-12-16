/******************************************************************************
 *
 * ewilib:tests.main (main.c)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *
 * :copyright: (c) 2015 - Gabriel Lima
 * :license: MIT, see LICENSE for more details
 *
 *****************************************************************************/
#include <stdlib.h>
#include <check.h>

#include "test_backbone.h"


/******************************************************************************
 ****************************** PUBLIC MEMBERS ********************************
 *****************************************************************************/

/******************************************************************************
 *
 * :function: main
 *
 * Test runner entry point
 *
 *****************************************************************************/
int main(void)
{
	SRunner *sr = srunner_create(TSuite_backbone());
	srunner_run_all(sr, CK_VERBOSE);
	srunner_free(sr);

	return 0;
}
