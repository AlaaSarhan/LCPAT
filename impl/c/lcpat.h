#include "stdlib.h"

#ifndef __LCPAT_H__
#define __LCPAT_H__ 1
#define INITIAL_MEMORY_CAPACITY 50

typedef struct
{
	int cost;
	int length;
	int* vertices;
} Path;

typedef struct
{
	int count;
	Path* paths;
} Paths;

typedef struct
{
	int start_vertex;
	int threshold_cost;
	Paths* paths;
} BackTrackCallMemory;

typedef struct
{
	size_t hits;
	size_t misses;
	size_t count;
	size_t capacity;
	BackTrackCallMemory* callsMemory;
} BackTrackMemory;

Paths* lcpat
(
	int n_vertices,
	int start_vertex,
	double** edgeCosts,
	double stepCost,
	double threshold_cost,
	BackTrackMemory* memory
);

Paths* lcpat_recall
(
	int start_vertex,
	double threshold_cost,
	BackTrackMemory* memory
);

void lcpat_remember
(
	int start_vertex,
	double threshold_cost,
	Paths* paths,
	BackTrackMemory* memory
);

Paths* lcpat_backtrack
(
	int n_vertices,
	double** edgeCosts,
	int start_vertex,
	double threshold_cost
);

Paths* lcpat_merge_paths
(
	Path* leftPath,
	double jump_cost,
	Paths* rightPaths
);

Paths* lcpat_combine_paths
(
	Paths* paths1,
	Paths* paths2
);
#endif