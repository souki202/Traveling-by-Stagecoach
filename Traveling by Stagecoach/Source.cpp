#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <cstring>
#include <numeric>
#include <algorithm>
#include <iomanip>

constexpr int NUM_TICKET = 8;
int n, m, p, a, b;
float costs[30][30] = {0};
std::array<int, NUM_TICKET> t;
float dp[1 << NUM_TICKET][30] = {0};

struct Node {
	float cost;
	int city;
	unsigned char tickets = 0b11111111;
};

int main() {
	while (std::cin >> n >> m >> p >> a >> b && (n || m || p || a || b)) {
		--a; --b;
		std::memset(dp, 0x7f, sizeof(float) * (1 << NUM_TICKET) * 30);
		std::memset(costs, 0, sizeof(float) * 30 * 30);
		for (int i = 0; i < n; i++) std::cin >> t[i];
		for (int i = 0; i < p; i++) {
			int x, y; float cost;
			std::cin >> x >> y >> cost;
			costs[--x][--y] = cost;
			costs[y][x] = cost;
		}

		//DFS
		std::stack<Node> s;
		s.push({ 0.f, a });
		bool isOk = false;
		float minCost = INFINITY;
		while (!s.empty()) {
			auto node = s.top(); s.pop();
			if (node.city == b) {
				minCost = std::min(minCost, node.cost);
				isOk = true;
				continue;
			}
			for (int i = 0; i < m; i++) { //éüÇÃìsés
				if (!costs[node.city][i]) continue;
				//ÇªÇÍÇºÇÍÇÃTICKETÇ≈ééÇ∑
				for (int j = 0; j < n; j++) {
					if (!((node.tickets >> j) & 1)) continue; //éùÇ¡ÇƒÇ¢Ç»Ç¢

					auto next = node;
					next.city = i;
					next.cost += costs[node.city][i] / t[j];
					next.tickets ^= (1 << j);
					if (dp[next.tickets][i] <= next.cost) continue;
					dp[next.tickets][i] = next.cost;
					s.push(next);
				}
			}
		}
		if (isOk) std::cout << std::fixed << std::setprecision(3) << minCost << std::endl;
		else std::cout << "Impossible" << std::endl;
	}
	return 0;
}