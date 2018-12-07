#include "stdlib.h"
#include "lcpat.h"

/**
 * 
 */
Paths* lcpat
(
	int n_vertices,
	int startVertex,
	double** edgeCosts,
	double stepCost,
	double thresholdCost,
	BackTrackMemory* memory
)
{
	Paths* paths = NULL;

	if (thresholdCost > stepCost) {
		Paths* leftPaths = lcpat (
					n_vertices,
					startVertex,
					edgeCosts,
					stepCost,
					stepCost,
					memory
				);

		for (int i = 0; i < leftPaths->count; i++) {
			Path leftPath = leftPaths->paths[i];
			int pathLastVertex = leftPath.vertices[leftPath.length - 1];
			for (int j = 0; j < n_vertices; j++) {
				if (
					j == pathLastVertex
					|| edgeCosts[pathLastVertex][j] < 0
				) continue;

				Paths* rightPaths = lcpat (
					n_vertices,
					j,
					edgeCosts,
					stepCost,
					thresholdCost - leftPath.cost,
					memory
				);

				paths = lcpat_combine_paths (
					paths,
					lcpat_merge_paths (leftPath, rightPaths)
				);
			}
		}

	} else {
		paths = lcpat_backtrack_recall (
			startVertex,
			thresholdCost,
			memory
		);

		if (paths == NULL) {
			paths = lcpat_backtrack (
				n_vertices,
				edgeCosts,
				startVertex,
				thresholdCost
			);

			lcpat_backtrack_remember (
				startVertex,
				thresholdCost,
				paths,
				memory
			);
		}
	}

	return paths;
}

Paths* lcpat_backtrack_recall
(
	int startVertex,
	double thresholdCost,
	BackTrackMemory* memory
)
{

}

void lcpat_backtrack_remember
(
	int startVertex,
	double thresholdCost,
	Paths* paths,
	BackTrackMemory* memory
)
{

}

/**
 * 
 */
Paths* lcpat_backtrack
(
	int n_vertices,
	double** edgeCosts,
	int startVertex,
	double thresholdCost
)
{

}

Paths* lcpat_merge_paths
(
	Path leftPath,
	Paths* rightPaths
)
{

}

Paths* lcpat_combine_paths
(
	Paths* paths1,
	Paths* paths2
)
{

}