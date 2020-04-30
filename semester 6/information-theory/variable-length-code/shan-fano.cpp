#include <iostream>
#include <string>

struct Node {
	std::string sym;
	float pro;
	int arr[20];
	int top;
} p[1000];

void shannon(int l, int h, Node p[]) {
	float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
	int i, d, k, j;
	if ((l + 1) == h || l == h || l > h) {
		if (l == h || l > h)
			return;
		p[h].arr[++(p[h].top)] = 0;
		p[l].arr[++(p[l].top)] = 1;
		return;
	}
	else {
		for (i = l; i <= h - 1; i++)
			pack1 = pack1 + p[i].pro;
		pack2 = pack2 + p[h].pro;
		diff1 = pack1 - pack2;
		if (diff1 < 0)
			diff1 = diff1 * -1;
		j = 2;
		while (j != h - l + 1) {
			k = h - j;
			pack1 = pack2 = 0;
			for (i = l; i <= k; i++)
				pack1 = pack1 + p[i].pro;
			for (i = h; i > k; i--)
				pack2 = pack2 + p[i].pro;
			diff2 = pack1 - pack2;
			if (diff2 < 0)
				diff2 = diff2 * -1;
			if (diff2 >= diff1)
				break;
			diff1 = diff2;
			j++;
		}
		k++;
		for (i = l; i <= k; i++)
			p[i].arr[++(p[i].top)] = 1;
		for (i = k + 1; i <= h; i++)
			p[i].arr[++(p[i].top)] = 0;
		shannon(l, k, p);
		shannon(k + 1, h, p);
	}
}

void sortByProbability(int n, Node p[]) {
	int i, j;
	Node temp;
	for (j = 1; j <= n - 1; j++) {
		for (i = 0; i < n - 1; i++) {
			if ((p[i].pro) > (p[i + 1].pro)) {
				temp.pro = p[i].pro;
				temp.sym = p[i].sym;
				p[i].pro = p[i + 1].pro;
				p[i].sym = p[i + 1].sym;
				p[i + 1].pro = temp.pro;
				p[i + 1].sym = temp.sym;
			}
		}
	}
}

void display(int n, Node p[]) {
	int i, j;
	std::cout << "\tSymbol\tProbability\tCode";
	for (i = n - 1; i >= 0; i--) {
		std::cout << "\n\t" << p[i].sym << "\t\t" << p[i].pro << "\t";
		for (j = 0; j <= p[i].top; j++)
			std::cout << p[i].arr[j];
	}
	std::cout << std::endl;
}

int main() {
	int n, i, j;
	float x, total = 0;
	char ch;
	Node temp;
	std::cout << "Enter number of symbols\t: ";
	std::cin >> n;
	if (n < 1) {
		std::cout << "Wrong symbol count" << std::endl;
		return 0;
	}
	for (i = 0; i < n; i++) {
		std::cout << "Enter symbol " << i + 1 << " : ";
		std::cin >> ch;
		p[i].sym += ch;
	}
	for (i = 0; i < n; i++) {
		std::cout << "Enter probability of " << p[i].sym << " : ";
		std::cin >> x;
		p[i].pro = x;
		total += + p[i].pro;
	}
	if (total > 1.001 || total < 0.999) {
			std::cout << "Invalid." << std::endl;
			return 0;
	}
	p[i].pro = 1 - total;
	sortByProbability(n, p);
	for (i = 0; i < n; i++)
		p[i].top = -1;
	shannon(0, n - 1, p);
	display(n, p);
	return 0;
}
