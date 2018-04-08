#/usr/bin/python

def dijkstra_shortest_pathways(adjacency_matrix, number_of_nodes, start_node_number):
    """Find the shortest pathway to every node in the graph.

    Positional arguments:
    adjacency_matrix -- graph representation in two-dimensional array.
    e. g.           a  b  c
                a [[0, 3, I],
                b  [I, 0, 2],
                c  [6, 4, 0]].
    I stands for infinity: float('inf')."""

    unchecked = [True]*number_of_nodes
    distance = [float('inf')]*number_of_nodes

    distance[start_node_number] = 0
    for i in range(number_of_nodes):
        min_distance = float('inf')
        min_weight_index = -1
        for index, value in enumerate(distance):
            if unchecked[index] and value < min_distance:
                min_distance = value
                min_weight_index = index
        for node in range(number_of_nodes):
            if distance[min_weight_index] + adjacency_matrix[min_weight_index][node] < distance[node]:
                distance[node] = distance[min_weight_index] + adjacency_matrix[min_weight_index][node]
        unchecked[min_weight_index] = False
    return distance


def bellman_ford_shortest_pathways(number_of_nodes, edges, weight_matrix, start_node_number):
    """Find the shortest pathway to every node in the graph.

    Positional arguments:
    edges -- array of tuples representing edges.
    e. g. [(0, 1), (0, 2), (1, 2), (2, 0)].
    weight_matrix -- two-dimensional array of distances between nodes."""

    distance = [float('inf')]*number_of_nodes
    distance[start_node_number] = 0

    for i in range(number_of_nodes):
        for u, v in edges:
            if distance[v] > distance[u] + weight_matrix[u][v]:
                distance[v] = distance[u] + weight_matrix[u][v]

    return distance


def bellman_ford_shortest_pathways_bfs(number_of_nodes, adjacency_list, weight_matrix, start_node_number):
    """Find the shortest pathway to every node in the graph.
    Uses breadth-first search.

    Positional arguments:
    adjacency_list -- two-dimensinal array, represents adjacency of nodes.
    e. g. [[1, 2],
           [0, 3],
           [0, 3],
           [1, 2]].
    weight_matrix -- two-dimensional array, represents distance between nodes.
    e. g. [[0, 4, 8, float('inf')],
           [4, 0, float('inf'), 20],
           [8, float('inf'), 0, 4],
           [float('inf'), 20, 4, 0]]."""

    distance = [float('inf')]*number_of_nodes
    distance[start_node_number] = 0

    checked = set()
    queue = {start_node_number}

    while queue:
        node = queue.pop()
        checked.add(node)

        queue.update(adjacency_list[node])
        queue -= checked

        for next_node in adjacency_list[node]:
            if distance[node] > distance[next_node] + weight_matrix[next_node][node]:
                distance[node] = distance[next_node] + weight_matrix[next_node][node]

    return distance
