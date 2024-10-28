#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// ������� ��� ���������� ����� � �����
void readGraph(const string& filename, int& n, int& m, vector<pair<int, int>>& edges) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "������� ��� �������i �����" << endl;
        return;
    }

    inputFile >> n >> m;

    edges.resize(m);
    for (int i = 0; i < m; ++i) {
        inputFile >> edges[i].first >> edges[i].second;
    }

    inputFile.close();
}

// ������� ��� ��������� ������� ��������
vector<vector<int>> createAdjacencyMatrix(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> adjacencyMatrix(n, vector<int>(n, 0));

    for (const auto& edge : edges) {
        int v = edge.first - 1;
        int u = edge.second - 1;
        adjacencyMatrix[v][u] = 1;
        adjacencyMatrix[u][v] = 1;  // ���� ���� ������������
    }

    return adjacencyMatrix;
}

// ������� ��� ���������� ������� ������
void calculateDegrees(const vector<vector<int>>& adjacencyMatrix, int n, vector<int>& degrees) {
    for (int i = 0; i < n; ++i) {
        degrees[i] = 0;
        for (int j = 0; j < n; ++j) {
            degrees[i] += adjacencyMatrix[i][j];
        }
    }
}

// �������� ���������� �����
bool isHomogeneous(const vector<int>& degrees) {
    int degree = degrees[0];
    for (int i = 1; i < degrees.size(); ++i) {
        if (degrees[i] != degree) {
            return false;
        }
    }
    return true;
}

// ����� ����������� �� ������� ������
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

// ���� ���������� ��� ������ ������
void printDegrees(const vector<int>& degrees) {
    cout << "������i ������:\n";
    for (int i = 0; i < degrees.size(); ++i) {
        cout << "������� " << i + 1 << ": ����i�� = " << degrees[i] << endl;
    }
}

// ���� ����������� �� ������� ������
void printIsolatedAndHangingVertices(const vector<int>& isolated, const vector<int>& hanging) {
    cout << "I��������i �������: ";
    for (int v : isolated) {
        cout << v << " ";
    }
    cout << endl;

    cout << "�����i �������: ";
    for (int v : hanging) {
        cout << v << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "UKR");

    int n, m;
    string inputFile;

    cout << "����i�� i�'� ��i����� �����: ";
    cin >> inputFile;

    vector<pair<int, int>> edges;
    readGraph(inputFile, n, m, edges);

    vector<vector<int>> adjacencyMatrix = createAdjacencyMatrix(n, edges);

    vector<int> degrees(n);
    calculateDegrees(adjacencyMatrix, n, degrees);
    printDegrees(degrees);

    if (isHomogeneous(degrees)) {
        cout << "���� � �����i����. ����i�� �����i�����i: " << degrees[0] << endl;
    }
    else {
        cout << "���� �� � �����i����." << endl;
    }

    vector<int> isolated, hanging;
    findIsolatedAndHangingVertices(degrees, isolated, hanging);
    printIsolatedAndHangingVertices(isolated, hanging);

    return 0;
}
