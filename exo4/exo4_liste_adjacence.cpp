#include <iostream>
#include <vector>
#include <fstream>




struct Node {
    int vertex;
    Node* next;

    Node(int v) : vertex(v), next(nullptr) {}
};

struct AdjList {
    Node* head;

    AdjList() : head(nullptr) {}
    void addEdge2(int v) {
        Node* newNode = new Node(v);
        newNode->next = head;
        head = newNode;
    }
};

std::vector<AdjList> listAdj;

void spanningTree2(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    int n, m;
    file >> n >> m;

    listAdj.resize(n);

    int x, y;
    while (m-- && file >> x >> y) {
        listAdj[x - 1].addEdge2(y - 1); // Adjust for 0-based indexing
        listAdj[y - 1].addEdge2(x - 1);
    }

    file.close();
}

void dfs2(int start, std::vector<bool>& visited, std::vector<AdjList>& myAdj) {
    visited[start] = true;
    for (Node* curr = listAdj[start].head; curr != nullptr; curr = curr->next) {
        if (!visited[curr->vertex]) {
            myAdj[start].addEdge2(curr->vertex);
            dfs2(curr->vertex, visited, myAdj);
        }
    }
}

void writeSpanningTree2(const std::string& filename, const std::vector<AdjList>& myAdj) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    for (int i = 0; i < myAdj.size(); ++i) {
        for (Node* curr = myAdj[i].head; curr != nullptr; curr = curr->next) {
            file << i + 1 << " " << curr->vertex + 1 << std::endl;
        }
    }

    file.close();
}

/*
int main() {


    spanningTree2("../INPARBGRAPH.TXT");
    std::vector<bool> visited2(listAdj.size(), false);
    std::vector<AdjList> myAdjList(listAdj.size());
    dfs2(1, visited2, myAdjList);
    writeSpanningTree2("../OUTARBGRAPH.TXT", myAdjList);

    return 0;
}
*/
