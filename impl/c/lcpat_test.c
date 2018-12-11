#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "lcpat.h"

int n_vertices = 10;
double** edgeCosts;


int suit_initialize ( void )
{
	edgeCosts = malloc(sizeof(double**) * n_vertices);
	for (int i = 0; i < n_vertices; i++) {
		edgeCosts[i] = malloc(sizeof(double**) * n_vertices);
		for (int j = 0; j < n_vertices; j++) {
			edgeCosts[i][j] = 0;
		}
	}
	edgeCosts[0][8] = 1.0;
	edgeCosts[1][2] = 1.0;
	edgeCosts[1][4] = 1.0;
	edgeCosts[2][1] = 1.0;
	edgeCosts[2][3] = 1.0;
	edgeCosts[2][5] = 1.0;
	edgeCosts[3][2] = 1.0;
	edgeCosts[3][6] = 1.0;
	edgeCosts[4][1] = 1.0;
	edgeCosts[4][5] = 1.0;
	edgeCosts[4][7] = 1.0;
	edgeCosts[5][4] = 1.0;
	edgeCosts[5][2] = 1.0;
	edgeCosts[5][6] = 1.0;
	edgeCosts[5][8] = 1.0;
	edgeCosts[6][5] = 1.0;
	edgeCosts[6][3] = 1.0;
	edgeCosts[6][9] = 1.0;
	edgeCosts[7][4] = 1.0;
	edgeCosts[7][8] = 1.0;
	edgeCosts[8][7] = 1.0;
	edgeCosts[8][5] = 1.0;
	edgeCosts[8][9] = 1.0;
	edgeCosts[8][0] = 1.0;
	edgeCosts[9][8] = 1.0;
	edgeCosts[9][6] = 1.0;

	return CUE_SUCCESS;
}

void test_thresholdCost_less_than_stepCost( void )
{
	BackTrackMemory memory;
	Paths* result = lcpat(n_vertices, 5, edgeCosts, 3, 1, &memory);
		
	CU_ASSERT_EQUAL(result->count, 4);

	CU_ASSERT_EQUAL(result->paths[0].vertices[0], 5);
	CU_ASSERT_EQUAL(result->paths[0].vertices[1], 2);

	CU_ASSERT_EQUAL(result->paths[1].vertices[0], 5);
	CU_ASSERT_EQUAL(result->paths[1].vertices[1], 4);

	CU_ASSERT_EQUAL(result->paths[2].vertices[0], 5);
	CU_ASSERT_EQUAL(result->paths[2].vertices[1], 6);

	CU_ASSERT_EQUAL(result->paths[3].vertices[0], 5);
	CU_ASSERT_EQUAL(result->paths[3].vertices[1], 8);
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