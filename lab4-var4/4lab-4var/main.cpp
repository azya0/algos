#include <iostream>
#include <vector>
#include <fstream>


#define N 5


class Tree {
public:
	std::pair<Tree*, Tree*> *subtree = new std::pair<Tree*, Tree*>;
	std::string data;
	int length;

	Tree(const std::string &str) {
		data = str;
	}

	Tree*& left() {
		return subtree->first;
	}

	Tree*& right() {
		return subtree->second;
	}
};

void fillTree(const std::vector<Tree*> trees, const std::string filename) {
	std::ifstream file(filename);

	for (int tree_index = 0; tree_index < N; tree_index++) {
		for (int index = 0; index < N; index++) {
			int val;
			file >> val;

			if (val == 0)
				continue;

			auto tree = trees[tree_index];

			if (tree->left() == nullptr)
				tree->left() = trees[index];
			else
				tree->right() = trees[index];
		}
	}
}

int calculate(Tree* tree) {
	if (tree == nullptr)
		return 0;

	tree->length = calculate(tree->left()) + calculate(tree->right()) + tree->data.size();

	return tree->length;
}

void print(const std::vector<Tree*> trees) {
	for (int tree_index = 0; tree_index < N; tree_index++) {
		auto tree = trees[tree_index];
		for (int index = 0; index < N; index++) {
			if (trees[index] == tree->left() || trees[index] == tree->right())
				std::cout << trees[index]->length << ' ';
			else
				std::cout << "0 ";
		}
		std::cout << "\tSelf-length: " << tree->data.size() << "\tTotal: " << tree->length << '\n';
	}
}

int main() {
	std::vector<Tree*> trees;

	for (int index = 0; index < N; index++) {
		std::string str = "";

		for (int _ = 0; _ < index + 1; _++)
			str += "a";

		trees.push_back(new Tree(str));
	}

	fillTree(trees, "input.txt");
	auto head = trees[4];
	head->length = calculate(head);

	print(trees);

	return 0;
}