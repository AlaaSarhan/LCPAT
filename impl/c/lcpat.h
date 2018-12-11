#include "stdlib.h"

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
	int startVertex;
	int thresholdCost;
	Paths paths;
} BackTrackCallMemory;

typedef struct
{
	BackTrackCallMemory* callsMemory;
} BackTrackMemory;

Paths* lcpat
(
	int n_vertices,
	int startVertex,
	double** edgeCosts,
	double stepCost,
	double thresholdCost,
	BackTrackMemory* memory
);

Paths* lcpat_recall
(
	int startVertex,
	double thresholdCost,
	BackTrackMemory* memory
);

void lcpat_remember
(
	int startVertex,
	double thresholdCost,
	Paths* paths,
	BackTrackMemory* memory
);

Paths* lcpat_backtrack
(
	int n_vertices,
	double** edgeCosts,
	int startVertex,
	double thresholdCost
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