#include "stdlib.h"
#include "lcpat.h"

/**
 * 
 */
Paths* lcpat
(
	int n_vertices,
	int start_vertex,
	double** edgeCosts,
	double step_cost,
	double threshold_cost,
	BackTrackMemory* memory
)
{
	Paths* paths = NULL;

	if (threshold_cost > step_cost) {
		Paths* left_paths = lcpat (
					n_vertices,
					start_vertex,
					edgeCosts,
					step_cost,
					step_cost,
					memory
				);

		for (int i = 0; i < left_paths->count; i++) {
			Path left_path = left_paths->paths[i];
			int path_last_vertex = left_path.vertices[left_path.length - 1];
			for (int j = 0; j < n_vertices; j++) {
				if (
					j == path_last_vertex
					|| edgeCosts[path_last_vertex][j] < 0
				) continue;

				Paths* right_paths = lcpat (
					n_vertices,
					j,
					edgeCosts,
					step_cost,
					threshold_cost - left_path.cost,
					memory
				);

				paths = lcpat_combine_paths (
					paths,
					lcpat_merge_paths (left_path, right_paths)
				);
			}
		}

	} else {
		paths = lcpat_backtrack_recall (
			start_vertex,
			threshold_cost,
			memory
		);

		if (paths == NULL) {
			paths = lcpat_backtrack (
				n_vertices,
				edgeCosts,
				start_vertex,
				threshold_cost
			);

			lcpat_backtrack_remember (
				start_vertex,
				threshold_cost,
				paths,
				memory
			);
		}
	}

	return paths;
}

Paths* lcpat_backtrack_recall
(
	int start_vertex,
	double threshold_cost,
	BackTrackMemory* memory
)
{

}

void lcpat_backtrack_remember
(
	int start_vertex,
	double threshold_cost,
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
	int start_vertex,
	double threshold_cost
)
{

}

Paths* lcpat_merge_paths
(
	Path left_path,
	Paths* right_paths
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