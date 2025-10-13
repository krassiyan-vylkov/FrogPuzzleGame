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

bool searchSolution(std::string& game, int n, int empty, std::stack<std::string>& moves) {

	if (checkIfSolved(game, n)) {
		moves.push(game);
		return true;
	}
	int gameSize = game.size();

	if (empty - 1 >= 0 && game[empty - 1] == '>') {
		std::swap(game[empty], game[empty - 1]);
		if (searchSolution(game, n, empty - 1, moves)) {
			std::swap(game[empty], game[empty - 1]);
			moves.push(game);
			return true;
		}
		std::swap(game[empty], game[empty - 1]);
	}
	if (empty - 2 >= 0 && game[empty - 2] == '>') {
		std::swap(game[empty], game[empty - 2]);
		if (searchSolution(game, n, empty - 2, moves)) {
			std::swap(game[empty], game[empty - 2]);
			moves.push(game);
			return true;
		}
		std::swap(game[empty], game[empty - 2]);
	}
	if (empty + 1 < gameSize && game[empty + 1] == '<') {
		std::swap(game[empty], game[empty + 1]);
		if (searchSolution(game, n, empty + 1, moves)) {
			std::swap(game[empty], game[empty + 1]);
			moves.push(game);
			return true;
		}
		std::swap(game[empty], game[empty + 1]);
	}
	if (empty + 2 < gameSize && game[empty + 2] == '<') {
		std::swap(game[empty], game[empty + 2]);
		if (searchSolution(game, n, empty + 2, moves)) {
			std::swap(game[empty], game[empty + 2]);
			moves.push(game);
			return true;
		}
		std::swap(game[empty], game[empty + 2]);
	}

	return false;
}

void frogGameSolver(int n) {
	std::string game = generateGame(n);
	std::stack<std::string> moves;
	const auto startTime = std::chrono::high_resolution_clock::now();
	searchSolution(game, n, n, moves);
	const auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> executionTime = endTime - startTime;
	while (!moves.empty()) {
		std::cout << moves.top() << std::endl;
		moves.pop();
	}

	std::cout << "Exectuion time of algorithm: " << executionTime.count() << " seconds." << std::endl;
}

int main() {

	int n;
	std::cout << "Please enter number: ";
	std::cin >> n;

	frogGameSolver(n);

	return 0;
}