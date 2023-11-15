#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>


std::vector<int> find(int start, int end, std::unordered_map<int, std::vector<int>> &ways, std::vector<int> visited) {
    auto result = std::vector<int>();

    if (start == end)
        return visited;

    for (int value : ways[start]) {
        if (std::find(visited.begin(), visited.end(), value) != visited.end()) continue;
        auto newVisited = std::vector<int>(visited.begin(), visited.end());
        newVisited.push_back(value);

        auto data = find(value, end, ways, newVisited);

        if ((!data.empty()) && (result.empty() || data.size() > result.size()))
            result = data;
    }

    return result;
}


void run() {
    std::unordered_map<int, std::vector<int>> ways;

    std::string filename;
    std::cout << "Enter filename:\n";
    std::cin >> filename;

    std::ifstream file(filename);

    if (!file.is_open()) throw std::runtime_error("file " + filename + " not found");

    int V, s, t, K;
    file >> V >> s >> t >> K;

    auto add = [&ways](int first, int second) {
        if (!ways.contains(first))
            ways[first] = std::vector<int>();
        ways[first].push_back(second);
    };

    for (int _ = 0; _ < V; _++) {
        int first, second;
        file >> first >> second;

        add(first, second);
        add(second, first);
    }

    file.close();

    auto data = std::vector<int>();
    data.push_back(s);
    auto result = find(s, t, ways, data);

    std::string outputName;
    std::cout << "Enter output filename:\n";
    std::cin >> outputName;
    std::ofstream output("../files/" + outputName);

    if (result.empty()) {
        output << -1;
    } else {
        for (int value : result) {
            output << value << ' ';
        }
    }

    output.close();
}


int main() {
    run();

    return 0;
}
