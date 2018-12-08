#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "lcpat.h"

int suit_initialize ( void )
{
	return CUE_SUCCESS;
}

void test_thresholdCost_less_than_stepCost( void )
{
	CU_ASSERT(true);
}

void test_thresholdCost_more_than_stepCost ( void )
{
	CU_ASSERT(true);
}

int suit_cleanup ( void )
{
	return CUE_SUCCESS;
}

int main ( void )
{
	CU_initialize_registry();

	CU_pSuite lcpat_test_suit = CU_add_suite(
		"lcpat",
		&suit_initialize,
		&suit_cleanup
	);

	CU_add_test(
		lcpat_test_suit,
		"test thresholdCost < stepCost",
		&test_thresholdCost_less_than_stepCost
	);

	CU_add_test(
		lcpat_test_suit,
		"test threshold > stepCost",
		&test_thresholdCost_more_than_stepCost
	);

	CU_basic_run_tests();

	CU_cleanup_registry();
}