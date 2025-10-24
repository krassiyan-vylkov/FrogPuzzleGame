#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <chrono>

std::string generateGame(int n) {
	std::string gameMap(2 * n + 1, '_');
	for (int i = 0; i < n; i++) {
		gameMap[i] = '>';
		gameMap[n + i + 1] = '<';
	}
	return gameMap;
}

bool checkIfSolved(const std::string& game, int n) {
	if (game[n] != '_') {
		return false;
	}
	for (int i = 0; i < n; i++) {
		if (game[i] != '<' || game[n + i + 1] != '>') {
			return false;
		}
	}
	return true;
}

bool searchSolution(std::string& game, int n, int emptyStone, std::stack<std::string>& moves) {
	if (checkIfSolved(game, n)) {
		moves.push(game);
		return true;
	}
	int gameSize = game.size();

	if (emptyStone - 1 >= 0 && game[emptyStone - 1] == '>') {
		std::swap(game[emptyStone], game[emptyStone - 1]);
		if (searchSolution(game, n, emptyStone - 1, moves)) {
			std::swap(game[emptyStone], game[emptyStone - 1]);
			moves.push(game);
			return true;
		}
		std::swap(game[emptyStone], game[emptyStone - 1]);
	}
	if (emptyStone - 2 >= 0 && game[emptyStone - 2] == '>') {
		std::swap(game[emptyStone], game[emptyStone - 2]);
		if (searchSolution(game, n, emptyStone - 2, moves)) {
			std::swap(game[emptyStone], game[emptyStone - 2]);
			moves.push(game);
			return true;
		}
		std::swap(game[emptyStone], game[emptyStone - 2]);
	}
	if (emptyStone + 1 < gameSize && game[emptyStone + 1] == '<') {
		std::swap(game[emptyStone], game[emptyStone + 1]);
		if (searchSolution(game, n, emptyStone + 1, moves)) {
			std::swap(game[emptyStone], game[emptyStone + 1]);
			moves.push(game);
			return true;
		}
		std::swap(game[emptyStone], game[emptyStone + 1]);
	}
	if (emptyStone + 2 < gameSize && game[emptyStone + 2] == '<') {
		std::swap(game[emptyStone], game[emptyStone + 2]);
		if (searchSolution(game, n, emptyStone + 2, moves)) {
			std::swap(game[emptyStone], game[emptyStone + 2]);
			moves.push(game);
			return true;
		}
		std::swap(game[emptyStone], game[emptyStone + 2]);
	}

	return false;
}

void frogGameSolver(int n) {
	std::string game = generateGame(n);
	std::stack<std::string> moves;

	const auto startTime = std::chrono::high_resolution_clock::now();
	searchSolution(game, n, n, moves);
	const auto endTime = std::chrono::high_resolution_clock::now();
	auto executionTime = std::chrono::duration<double, std::milli>(endTime - startTime);

	std::cout << "# TIMES_MS: alg= " << executionTime.count() << '\n';
	while (!moves.empty()) {
		std::cout << moves.top() << '\n';
		moves.pop();
	}
}

int main() {
	int n;
	std::cin >> n;

	frogGameSolver(n);

	return 0;
}