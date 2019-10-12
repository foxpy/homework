#include <iostream>
#include <vector>
#include <algorithm>

int main(void)
{
	int n, m, buf;
	std::cin >> n >> m;
	std::vector<int> a1(n), a2(m);

	for (int i = 0; i < n; ++i) {
		std::cin >> buf;
		a1[i] = buf;
	}
	for (int i = 0; i < m; ++i) {
		std::cin >> buf;
		a2[i] = buf;
	}

	std::pair<std::vector<int>::iterator, std::vector<int>::iterator> rc;
	for (std::vector<int>::iterator i = a2.begin(); i != a2.end(); ++i) {
		if (!std::binary_search(a1.begin(), a1.end(), *i)) {
			std::cout << 0 << std::endl;
			continue;
		}
		rc = std::equal_range(a1.begin(), a1.end(), *i);
		std::cout << rc.first - a1.begin() + 1 << " " << rc.second - a1.begin() << std::endl;
	}
}
