#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "lcpat.h"

int n_vertices = 10;
double** edge_costs;

int suit_initialize ( void )
{
	edge_costs = calloc(n_vertices, sizeof(double*));
	for (int i = 0; i < n_vertices; i++) {
		edge_costs[i] = calloc(n_vertices, sizeof(double));
	}

	edge_costs[0][8] = 1.0;
	edge_costs[1][2] = 1.0;
	edge_costs[1][4] = 1.0;
	edge_costs[2][1] = 1.0;
	edge_costs[2][3] = 1.0;
	edge_costs[2][5] = 1.0;
	edge_costs[3][2] = 1.0;
	edge_costs[3][6] = 1.0;
	edge_costs[4][1] = 1.0;
	edge_costs[4][5] = 1.0;
	edge_costs[4][7] = 1.0;
	edge_costs[5][4] = 1.0;
	edge_costs[5][2] = 1.0;
	edge_costs[5][6] = 1.0;
	edge_costs[5][8] = 1.0;
	edge_costs[6][5] = 1.0;
	edge_costs[6][3] = 1.0;
	edge_costs[6][9] = 1.0;
	edge_costs[7][4] = 1.0;
	edge_costs[7][8] = 1.0;
	edge_costs[8][7] = 1.0;
	edge_costs[8][5] = 1.0;
	edge_costs[8][9] = 1.0;
	edge_costs[8][0] = 1.0;
	edge_costs[9][8] = 1.0;
	edge_costs[9][6] = 1.0;

	return CUE_SUCCESS;
}

void test_thresholdCost_less_than_stepCost( void )
{
	BackTrackMemory memory = { .capacity = INITIAL_MEMORY_CAPACITY, .callsMemory = calloc(INITIAL_MEMORY_CAPACITY, sizeof(BackTrackCallMemory)) };
	Paths* result = lcpat(n_vertices, 5, edge_costs, 3, 1, &memory);

	CU_ASSERT_EQUAL(result->count, 4);

	CU_ASSERT_EQUAL(result->paths[0].vertices[0], 5);
	CU_ASSERT_EQUAL(result->paths[0].vertices[1], 2);

	CU_ASSERT_EQUAL(result->paths[1].vertices[0], 5);
	CU_ASSERT_EQUAL(result->paths[1].vertices[1], 4);

	CU_ASSERT_EQUAL(result->paths[2].vertices[0], 5);
	CU_ASSERT_EQUAL(result->paths[2].vertices[1], 6);

	CU_ASSERT_EQUAL(result->paths[3].vertices[0], 5);
	CU_ASSERT_EQUAL(result->paths[3].vertices[1], 8);

	free(result);
}

void test_thresholdCost_more_than_stepCost ( void )
{
	BackTrackMemory memory = { .capacity = INITIAL_MEMORY_CAPACITY, .callsMemory = calloc(INITIAL_MEMORY_CAPACITY, sizeof(BackTrackCallMemory)) };
	Paths* result = lcpat(n_vertices, 5, edge_costs, 3, 13, &memory);

	printf("DP Memory Hits  : %d\n", memory.hits);
	printf("DP Memory Misses: %d\n", memory.misses);
	printf("Paths count     : %d", result->count);

	free(result);
}

int suit_cleanup ( void )
{
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