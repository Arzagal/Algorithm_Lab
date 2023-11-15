#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <limits>
#include <cstring>
#include <cerrno>
#include <algorithm>

std::vector<std::vector<int>> adj;
std::vector<int> distance;
std::vector<int> prev;
int n, m, start, end;

void addEdge(int x, int y, int weight) {
    adj[x - 1][y - 1] = weight;

    adj[y - 1][x - 1] = weight;
}

void initMatrix(std::vector<std::vector<int>> &matrix, int size) {
    matrix.resize(size, std::vector<int>(size, std::numeric_limits<int>::max()));
}

void spanningTree(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file '" << filename << "': "
                  << strerror(errno) << std::endl;
        return;
    }

    file >> n >> m >> start >> end;
    initMatrix(adj, n);

    int x, y, weight;
    while (m-- && file >> x >> y >> weight) {
        addEdge(x, y, weight);
    }

    file.close();
}

void dijkstra() {
    distance = std::vector<int>(n, std::numeric_limits<int>::max());
    prev = std::vector<int>(n, -1);
    distance[start - 1] = 0;

    std::set<std::pair<int, int>> toVisit;
    toVisit.insert({0, start - 1});

    while (!toVisit.empty()) {
        int current = toVisit.begin()->second;
        toVisit.erase(toVisit.begin());

        for (int k = 0; k < n; k++) {
            if (adj[current][k] != std::numeric_limits<int>::max()) {
                int dist = distance[current] + adj[current][k];
                if (dist < distance[k]) {
                    toVisit.erase({distance[k], k});
                    distance[k] = dist;
                    prev[k] = current;
                    toVisit.insert({dist, k});
                }
            }
        }
    }
}

void writePath(const std::string &pathName) {
    std::ofstream file(pathName);
    if (!file.is_open()) {
        std::cerr << "Error opening file '" << pathName << "': "
                  << strerror(errno) << std::endl;
        return;
    }


    std::vector<int> path;
    for (int at = end - 1; at != -1; at = prev[at]) {
        path.push_back(at + 1);
    }
    std::reverse(path.begin(), path.end());

    for (int v : path) {
        file << v << " ";
    }
    file << std::endl;
    file.close();
}

void exo6matrice(){
    spanningTree("../INPDIJGRAPH.TXT ");
    dijkstra();
    writePath("../OUTDIJGRAPH.TXT");
}

