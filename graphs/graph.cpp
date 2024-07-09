#include <vector>
#include <queue>
#include "graph.h"
#include <limits>

constexpr float infty = std::numeric_limits<float>::infinity();

namespace graphs
{
    namespace undirected
    {
        void explore(adjacency_list &graph,
                vertex_id vert,
                std::vector<bool> &visited,
                int component_number)
        {
            graph[vert].component_number = component_number;
            visited[vert] = true;
            for (int j = 0; j < graph[vert].edges.size(); j++)
            {
                if (graph[vert].edges[j].to != vert
                        && !visited[graph[vert].edges[j].to])
                {
                    explore(graph,
                            graph[vert].edges[j].to,
                            visited,
                            component_number);
                }
                else if (graph[vert].edges[j].from != vert
                        && !visited[graph[vert].edges[j].from])
                {
                    explore(graph,
                            graph[vert].edges[j].from,
                            visited,
                            component_number);
                }
            }
        }

        void dfs(adjacency_list &graph)
        {
            std::vector<bool> visited(graph.size(), false);
            int component_number = 0;
            for (int i = 0; i < graph.size(); i++)
            {
                if (!visited[i])
                {
                    explore(graph,
                            i,
                            visited,
                            component_number);
                    component_number++;
                }
            }
        }

        void bfs(adjacency_list &graph, vertex_id start)
        {
            std::vector<float> dist(graph.size(), infty);
            std::queue<vertex_id> queue;
            dist[start] = 0;
            queue.push(start);
            while (!queue.empty())
            {
                vertex_id u = queue.front();
                queue.pop();
                for (int i = 0; i < graph[u].edges.size(); i++)
                {
                    vertex_id v = graph[u].edges[i].from;
                    if (graph[u].edges[i].from == u)
                    {
                        v = graph[u].edges[i].to;
                    }
                    if (dist[v] == infty)
                    {
                        queue.push(v);
                        dist[v] = dist[u] + 1;
                    }
                }
            }
        }
    }
}

int main()
{

}