#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

vector<vector<int>> readGraph(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> graph;

    if (!file.is_open()) {
        cerr << "Помилка: Не вдалося відкрити файл " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        vector<int> row;
        int value;
        while (ss >> value) {
            row.push_back(value);
        }

        if (!graph.empty() && row.size() != graph[0].size()) {
            cerr << "Помилка: Некоректний формат графу. Кількість елементів в рядках не співпадає." << endl;
            exit(EXIT_FAILURE);
        }
        graph.push_back(row);
    }

    file.close();
    return graph;
}

void breadthFirstSearch(const vector<vector<int>>& graph, int startVertex) {
    int vertices = graph.size();
    vector<bool> visited(vertices, false);
    queue<int> q;
    vector<int> bfsNumbers(vertices, 0);

    q.push(startVertex);
    visited[startVertex] = true;
    int bfsCounter = 1;

    cout << "Поточна вершина | BFS-номер | Стан черги\n";
    cout << "------------------------------------------\n";

    while (!q.empty()) {
        int currentVertex = q.front();
        q.pop();
        bfsNumbers[currentVertex] = bfsCounter++;

        cout << currentVertex + 1 << "              | " << bfsNumbers[currentVertex]
            << "         | ";

        queue<int> tempQueue = q;
        vector<int> queueContent;
        while (!tempQueue.empty()) {
            queueContent.push_back(tempQueue.front() + 1);
            tempQueue.pop();
        }
        for (int v : queueContent) {
            cout << v << " ";
        }

        cout << "\n";

        for (int i = 0; i < vertices; ++i) {
            if (graph[currentVertex][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

int main() {
    string filename;
    cout << "Введіть назву вхідного файлу з описом графу: ";
    cin >> filename;

    vector<vector<int>> graph = readGraph(filename);

    int startVertex;
    cout << "Введіть початкову вершину (1-" << graph.size() << "): ";
    cin >> startVertex;
    startVertex--;

    if (startVertex < 0 || startVertex >= graph.size()) {
        cerr << "Помилка: Некоректна початкова вершина." << endl;
        return EXIT_FAILURE;
    }

    cout << "\nЗавдання: Обхід графу пошуком вшир.\n";
    breadthFirstSearch(graph, startVertex);

    return 0;
}
