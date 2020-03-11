#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <vector>

struct huffman_node {
	char c;
	unsigned frequency;
	huffman_node *left, *right;
	huffman_node(char c, unsigned frequency) {
		left = nullptr;
		right = nullptr;
		this->c = c;
		this->frequency = frequency;
	}
};

struct huffman_compare {
	bool operator() (huffman_node *left, huffman_node *right) {
		return left->frequency > right->frequency;
	}
};

void print_codes(huffman_node* node, std::string str) {
	if (!node) return;
	if (node->c != '\0') std::cout << '\'' << node->c << "' : " << str << std::endl;
	print_codes(node->left, str + '0');
	print_codes(node->right, str + '1');
}

void huffman_codes(std::map<char, unsigned> &stat) {
	huffman_node *left, *right, *top;
	std::priority_queue<huffman_node*, std::vector<huffman_node*>, huffman_compare> heap;
	for (auto i : stat) heap.push(new huffman_node(i.first, i.second));
	while (heap.size() != 1) {
		left = heap.top();
		heap.pop();
		right = heap.top();
		heap.pop();
		top = new huffman_node('\0', left->frequency + right->frequency);
		top->left = left;
		top->right = right;
		heap.push(top);
	}
	print_codes(heap.top(), "");
}

int main(void) {
	std::map<char, unsigned> stat;
	unsigned fixed_length_bits = 0;
	std::string input;
	std::cout << "Enter input line: ";
	std::getline(std::cin, input);
	for (char c : input) ++stat[c];
	huffman_codes(stat);
}
