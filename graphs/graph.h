#pragma once
#include <vector>
#include <iostream>

namespace graphs
{
    using vertex_id = int;

    struct edge
    {
        vertex_id from;
        vertex_id to;
        float weight;
    };

    struct vertex
    {
        char label;
        std::vector<edge> edges;
    };

    struct visit_times
    {
        int pre;
        int post;

        friend std::ostream &operator<<(std::ostream &os, const visit_times &vt);
    };

    struct dfs_results
    {
        std::vector<int> component_numbers;
        std::vector<vertex_id> prev;
    };

    struct bfs_results
    {
        std::vector<float> dist;
        std::vector<vertex_id> prev;
    };

    struct scc_results
    {
        std::vector<int> component_numbers;
        adjacency_list metagraph;
    };

    using adjacency_list = std::vector<vertex>;

    void swap_vertices(adjacency_list &graph, vertex_id a, vertex_id b);

    namespace undirected
    {
        void explore(adjacency_list &graph,
                     vertex_id vert,
                     std::vector<bool> &visited,
                     int component_number,
                     std::vector<int> &component_numbers,
                     std::vector<vertex_id> & prev);
        dfs_results dfs(adjacency_list &graph);
        bfs_results bfs(adjacency_list &graph, vertex_id start);
    }

    namespace directed
    {
        void explore(adjacency_list &graph,
                     vertex_id vert,
                     std::vector<bool> &visited,
                     std::vector<visit_times> &timestamps,
                     int &clock);
        std::vector<visit_times> dfs(adjacency_list &graph);
        bfs_results bfs(adjacency_list &graph, vertex_id start);

        scc_results scc(adjacency_list &graph);
    }
}
