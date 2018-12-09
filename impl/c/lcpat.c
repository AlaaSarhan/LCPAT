#include "stdlib.h"
#include "string.h"
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
	int count = right_paths->count;
	
	Path paths[count];
	for (int i = 0; i < count; i++) {
		Path path;
		Path right_path = right_paths->paths[i];

		path.cost = left_path.cost + right_path.cost;
		path.length = left_path.length = right_path.length;
		path.vertices = malloc(sizeof(int) * path.length);

		size_t left_path_vertices_size = sizeof(int) * left_path.length;
		memcpy(
			path.vertices,
			left_path.vertices,
			left_path_vertices_size
		);
		memcpy(
			path.vertices + left_path_vertices_size,
			right_path.vertices,
			sizeof(int) * right_path.length
		);
	}

	Paths* result = malloc(sizeof(Paths*));
	result->count = count;
	result->paths = paths;

	return result;
}

Paths* lcpat_combine_paths
(
	Paths* paths1,
	Paths* paths2
)
{
	int count = 0;
	if (paths1 != NULL) {
		count += paths1->count;
	}
	if (paths2 != NULL) {
		count += paths2->count;
	}

	Path paths[count];
	size_t copy_offset = 0;
	if (paths1 != NULL) {
		memcpy(paths + copy_offset, paths1->paths, sizeof(Path) * paths1->count);
		copy_offset = sizeof(Path) * paths1->count;
	}
	if (paths2 != NULL) {
		memcpy(paths + copy_offset, paths2->paths, sizeof(Path) * paths2->count);
	}

	Paths *result = malloc(sizeof(Path*));
	result->count = count;
	result->paths = paths;

	return result;
}