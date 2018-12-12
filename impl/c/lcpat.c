#include "stdlib.h"
#include "string.h"
#include "lcpat.h"
#include "stdio.h"

/**
 * 
 */
Paths* lcpat
(
	int n_vertices,
	int start_vertex,
	double** edge_costs,
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
			edge_costs,
			step_cost,
			step_cost,
			memory
		);

		for (int i = 0; i < left_paths->count; i++) {
			Path left_path = left_paths->paths[i];
			int path_last_vertex = left_path.vertices[left_path.length - 1];
			for (int j = 0; j < n_vertices; j++) {
				if (edge_costs[path_last_vertex][j] < 0) continue;

				Paths* right_paths = lcpat (
					n_vertices,
					j,
					edge_costs,
					step_cost,
					threshold_cost - left_path.cost,
					memory
				);

				paths = lcpat_combine_paths (
					paths,
					lcpat_merge_paths (
						&left_path,
						edge_costs[path_last_vertex][j],
						right_paths
					)
				);
			}
		}

	} else {
		paths = lcpat_recall (
			start_vertex,
			threshold_cost,
			memory
		);

		if (paths == NULL) {
			paths = lcpat_backtrack (
				n_vertices,
				edge_costs,
				start_vertex,
				threshold_cost
			);

			lcpat_remember (
				start_vertex,
				threshold_cost,
				paths,
				memory
			);
		}
	}

	return paths;
}

Paths* lcpat_recall
(
	int start_vertex,
	double threshold_cost,
	BackTrackMemory* memory
)
{
	for (int i = 0; i < memory->count; i++) {
		BackTrackCallMemory callMemory = memory->callsMemory[i];
		if (callMemory.start_vertex == start_vertex && callMemory.threshold_cost == threshold_cost) {
			return callMemory.paths;
		}
	}

	return NULL;
}

void lcpat_remember
(
	int start_vertex,
	double threshold_cost,
	Paths* paths,
	BackTrackMemory* memory
)
{
	if (memory->count == memory->capacity - 1) {
		memory->capacity = memory->capacity + INITIAL_MEMORY_CAPACITY;
		BackTrackCallMemory* oldCallsMemory = memory->callsMemory;

		memory->callsMemory = calloc(memory->capacity, sizeof(BackTrackCallMemory));
		memcpy(memory->callsMemory, oldCallsMemory, sizeof(BackTrackCallMemory) * memory->count);
	}

	memory->callsMemory[memory->count] = (BackTrackCallMemory) { .start_vertex = start_vertex, .threshold_cost = threshold_cost, .paths = paths };
	memory->count += 1;
}

Paths* lcpat_backtrack
(
	int n_vertices,
	double** edge_costs,
	int start_vertex,
	double threshold_cost
)
{
	Path* currentVertexPath = calloc(1, sizeof(Path));
	currentVertexPath->length = 1;
	currentVertexPath->cost = 0;
	currentVertexPath->vertices = &(int) { start_vertex };

	Paths* paths = NULL;

	if (threshold_cost <= 0) {
		paths = calloc(1, sizeof(Paths));
		paths->count = 1;
		paths->paths = currentVertexPath;

		return paths;
	}

	for (int i = 0; i < n_vertices; i++) {
		if (edge_costs[start_vertex][i] <= 0) continue;

		Paths* right_paths = lcpat_backtrack (
			n_vertices,
			edge_costs,
			i,
			threshold_cost - edge_costs[start_vertex][i]
		);

		paths = lcpat_combine_paths (
			paths,
			lcpat_merge_paths (currentVertexPath, edge_costs[start_vertex][i], right_paths)
		);
	}

	return paths;
}

Paths* lcpat_merge_paths
(
	Path* left_path,
	double jump_cost,
	Paths* right_paths
)
{
	int count = right_paths->count;

	Path* paths = calloc(count, sizeof(Path));
	for (int i = 0; i < count; i++) {

		paths[i].cost = left_path->cost + jump_cost + right_paths->paths[i].cost;
		paths[i].length = left_path->length + right_paths->paths[i].length;
		paths[i].vertices = calloc(paths[i].length, sizeof(int));

		memcpy(
			paths[i].vertices,
			left_path->vertices,
			left_path->length * sizeof(int)
		);
		memcpy(
			paths[i].vertices + left_path->length,
			right_paths->paths[i].vertices,
			right_paths->paths[i].length * sizeof(int)
		);
	}

	Paths* result = calloc(1, sizeof(Paths));
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

	Path* paths = calloc(count, sizeof(Path));
	size_t copy_offset = 0;
	if (paths1 != NULL) {
		memcpy(paths + copy_offset, paths1->paths, sizeof(Path) * paths1->count);
		copy_offset = paths1->count;
	}
	if (paths2 != NULL) {
		memcpy(paths + copy_offset, paths2->paths, sizeof(Path) * paths2->count);
	}

	Paths* result = calloc(1, sizeof(Paths));
	result->count = count;
	result->paths = paths;

	return result;
}