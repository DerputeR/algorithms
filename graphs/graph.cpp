#include <vector>
#include <queue>
#include "graph.h"
#include <limits>
#include <iostream>
#include "../common.h"

constexpr float infty = std::numeric_limits<float>::infinity();

namespace graphs
{
    std::ostream& operator<<(std::ostream& os, const visit_times& vt)
    {
        os << "(" << vt.pre << ", " << vt.post << ")";
        return os;
    }

    void swap_vertices(adjacency_list &graph, vertex_id a, vertex_id b)
    {
        vertex temp = graph[a];
        graph[a] = graph[b];
        graph[b] = temp;
        for (int i = 0; i < graph.size(); i++)
        {
            for (int j = 0; j < graph[i].edges.size(); j++)
            {
                if (graph[i].edges[j].from == a)
                {
                    graph[i].edges[j].from = b;
                }
                else if (graph[i].edges[j].from == b)
                {
                    graph[i].edges[j].from = a;
                }

                if (graph[i].edges[j].to == a)
                {
                    graph[i].edges[j].to = b;
                }
                else if (graph[i].edges[j].to == b)
                {
                    graph[i].edges[j].to = a;
                }
            }
        }
    }

    namespace undirected
    {
        void explore(adjacency_list &graph,
                     vertex_id vert,
                     std::vector<bool> &visited,
                     int component_number,
                     std::vector<int> &component_numbers,
                     std::vector<vertex_id> &prev)
        {
            component_numbers[vert] = component_number;
            visited[vert] = true;
            for (int j = 0; j < graph[vert].edges.size(); j++)
            {
                vertex_id other = graph[vert].edges[j].to;
                if (graph[vert].edges[j].from == vert)
                if (!visited[other])
                {
                    explore(graph,
                            other,
                            visited,
                            component_number,
                            component_numbers,
                            prev);
                    prev[other] = vert;
                }
            }
        }

        std::vector<vertex_id> dfs(adjacency_list &graph)
        {
            std::vector<vertex_id> prev(graph.size(), -1);
            std::vector<bool> visited(graph.size(), false);
            std::vector<int> component_numbers(graph.size(), 0);
            int component_number = 0;
            for (int i = 0; i < graph.size(); i++)
            {
                if (!visited[i])
                {
                    explore(graph,
                            i,
                            visited,
                            component_number,
                            component_numbers,
                            prev);
                    component_number++;
                }
            }
            return prev;
        }

        std::vector<traversal> bfs(adjacency_list &graph, vertex_id start)
        {
            std::queue<vertex_id> queue;
            std::vector<traversal> traversed(graph.size(), {-1, infty});
            traversed[start].dist = 0;
            queue.push(start);
            while (!queue.empty())
            {
                vertex_id u = queue.front();
                queue.pop();
                for (int i = 0; i < graph[u].edges.size(); i++)
                {
                    vertex_id v = graph[u].edges[i].to;
                    if (traversed[v].dist == infty)
                    {
                        queue.push(v);
                        traversed[v].prev = u;
                        traversed[v].dist = traversed[u].dist + 1;
                    }
                }
            }
        }
    }

    namespace directed
    {
        void explore(adjacency_list &graph,
                     vertex_id vert,
                     std::vector<bool> &visited,
                     std::vector<visit_times> &timestamps,
                     int &clock)
        {
            timestamps[vert].pre = clock++;
            visited[vert] = true;
            for (int j = 0; j < graph[vert].edges.size(); j++)
            {
                vertex_id other = graph[vert].edges[j].to;
                if (graph[vert].edges[j].from == vert)
                if (!visited[other])
                {
                    explore(graph,
                            other,
                            visited,
                            timestamps,
                            clock);
                }
            }
            timestamps[vert].post = clock++;
        }

        std::vector<visit_times> dfs(adjacency_list &graph)
        {
            int clock = 1;
            std::vector<visit_times> timestamps(graph.size(), visit_times{});
            std::vector<bool> visited(graph.size(), false);
            for (int i = 0; i < graph.size(); i++)
            {
                if (!visited[i])
                {
                    explore(graph,
                            i,
                            visited,
                            timestamps,
                            clock);
                }
            }
            return timestamps;
        }

        std::vector<traversal> bfs(adjacency_list &graph, vertex_id start)
        {
            return undirected::bfs(graph, start);
        }
    }
}

int main()
{
    using namespace graphs;

    adjacency_list graph {
        vertex {'a', std::vector<edge>{}}, // 0
        vertex {'b', std::vector<edge>{}}, // 1
        vertex {'c', std::vector<edge>{}}, // 2
        vertex {'d', std::vector<edge>{}}, // 3
        vertex {'e', std::vector<edge>{}}, // 4
        vertex {'f', std::vector<edge>{}}, // 5
        vertex {'g', std::vector<edge>{}}, // 6
        vertex {'h', std::vector<edge>{}} // 7
    };

    graph[0].edges.push_back(edge{0, 3, 0});
    graph[1].edges.push_back(edge{1, 0, 0});
    graph[1].edges.push_back(edge{1, 2, 0});
    graph[1].edges.push_back(edge{1, 4, 0});
    graph[2].edges.push_back(edge{2, 5, 0});
    graph[3].edges.push_back(edge{3, 4, 0});
    graph[3].edges.push_back(edge{3, 6, 0});
    graph[3].edges.push_back(edge{3, 7, 0});
    graph[4].edges.push_back(edge{4, 6, 0});
    graph[5].edges.push_back(edge{5, 7, 0});
    graph[7].edges.push_back(edge{7, 6, 0});

    swap_vertices(graph, 0, 1);

    std::vector<char> vert_letters{};
    for (auto v: graph)
    {
        vert_letters.push_back(v.label);
    }
    std::vector<visit_times> times = directed::dfs(graph);
    print_vec<char>(vert_letters);
    print_vec<visit_times>(times);
}