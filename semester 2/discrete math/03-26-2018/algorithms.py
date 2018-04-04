#/usr/bin/python

def dijkstra_shortest_pathways(adjacency_matrix, number_of_nodes, start_node_number):
    """Find the shortest pathway to every node in the graph.

    Positional arguments:
    adjacency_matrix -- graph representation in two-dimensional array.
    e. g.           a  b  c
                a [[0, 3, I],
                b  [I, 0, 2],
                c  [6, 4, I]].
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
