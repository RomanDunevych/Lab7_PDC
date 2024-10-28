#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Функція для зчитування графу з файлу
void readGraph(const string& filename, int& n, int& m, vector<pair<int, int>>& edges) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Помилка при відкриттi файлу" << endl;
        return;
    }

    inputFile >> n >> m;

    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        inputFile >> edges[i].first >> edges[i].second;
    }

    inputFile.close();
}

// Функція для створення матриці суміжності
vector<vector<int>> createAdjacencyMatrix(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> adjacencyMatrix(n, vector<int>(n, 0));

    for (const auto& edge : edges) {
        int v = edge.first - 1;
        int u = edge.second - 1;
        adjacencyMatrix[v][u] = 1;
        adjacencyMatrix[u][v] = 1;  // Якщо граф неорієнтований
    }

    return adjacencyMatrix;
}

// Функція для обчислення степенів вершин
void calculateDegrees(const vector<vector<int>>& adjacencyMatrix, int n, vector<int>& degrees) {
    for (int i = 0; i < n; ++i) {
        degrees[i] = 0;
        for (int j = 0; j < n; ++j) {
            degrees[i] += adjacencyMatrix[i][j];
        }
    }
}

// Перевірка однорідності графу
bool isHomogeneous(const vector<int>& degrees) {
    int degree = degrees[0];
    for (int i = 1; i < degrees.size(); ++i) {
        if (degrees[i] != degree) {
            return false;
        }
    }
    return true;
}

// Пошук ізольованих та висячих вершин
void findIsolatedAndHangingVertices(const vector<int>& degrees, vector<int>& isolated, vector<int>& hanging) {
    for (int i = 0; i < degrees.size(); ++i) {
        if (degrees[i] == 0) {
            isolated.push_back(i + 1);
        }
        else if (degrees[i] == 1) {
            hanging.push_back(i + 1);
        }
    }
}

// Вивід інформації про степені вершин
void printDegrees(const vector<int>& degrees) {
    cout << "Степенi вершин:\n";
    for (int i = 0; i < degrees.size(); ++i) {
        cout << "Вершина " << i + 1 << ": Степiнь = " << degrees[i] << endl;
    }
}

// Вивід ізольованих та висячих вершин
void printIsolatedAndHangingVertices(const vector<int>& isolated, const vector<int>& hanging) {
    cout << "Iзольованi вершини: ";
    for (int v : isolated) {
        cout << v << " ";
    }
    cout << endl;

    cout << "Висячi вершини: ";
    for (int v : hanging) {
        cout << v << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "UKR");

    int n, m;
    string inputFile;

    cout << "Введiть iм'я вхiдного файлу: ";
    cin >> inputFile;

    vector<pair<int, int>> edges;
    readGraph(inputFile, n, m, edges);

    vector<vector<int>> adjacencyMatrix = createAdjacencyMatrix(n, edges);

    vector<int> degrees(n);
    calculateDegrees(adjacencyMatrix, n, degrees);
    printDegrees(degrees);

    if (isHomogeneous(degrees)) {
        cout << "Граф є однорiдним. Степiнь однорiдностi: " << degrees[0] << endl;
    }
    else {
        cout << "Граф не є однорiдним." << endl;
    }

    vector<int> isolated, hanging;
    findIsolatedAndHangingVertices(degrees, isolated, hanging);
    printIsolatedAndHangingVertices(isolated, hanging);

    return 0;
}
