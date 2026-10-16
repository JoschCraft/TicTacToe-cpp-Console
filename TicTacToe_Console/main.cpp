#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

int games = 0;
int winsX = 0;
int winsO = 0;
int draws = 0;
int preventedForks = 0;
int createdForks = 0;

char gameBoard[3][3] = {
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	{' ', ' ', ' '}
};

// Generate random Numbers for row and column
int genRandomNumber(int min, int max) {
	random_device rd;
	mt19937 gen(rd());
	static uniform_int_distribution<int> distrib;
	return distrib(gen, uniform_int_distribution<int>::param_type{ min, max });
}


struct Point
{
	int row;
	int col;
};

void clearScreen() {
	// Clear the console screen
	// This is platform dependent. For Windows, you can use system("cls");
	// For Unix/Linux, you can use system("clear");
	// And when you not shure use the last option

	system("cls");  // Uncomment this line if you're on Windows

	//system("clear"); // Uncomment this line if you're on Unix/Linux
	
	// Here, we'll just print newlines to simulate clearing the screen.
	/*
	for (int i = 0; i < 100; i++) {
		cout << endl;
	}*/
}

void printBoard() {
	/*
	| X | O | O |
	-------------
	| O | X | X |
	-------------
	| O | O | X |
	*/

	cout << endl;
	cout << "| " << gameBoard[0][0] << " | " << gameBoard[0][1] << " | " << gameBoard[0][2] << " |" << endl;
	cout << "-------------" << endl;
	cout << "| " << gameBoard[1][0] << " | " << gameBoard[1][1] << " | " << gameBoard[1][2] << " |" << endl;
	cout << "-------------" << endl;
	cout << "| " << gameBoard[2][0] << " | " << gameBoard[2][1] << " | " << gameBoard[2][2] << " |" << endl;
	cout << endl;
}

void resetBoard() {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			gameBoard[row][col] = ' ';
		}
	}
}

void playerPlay(char player) {
	bool validMove = false;
	int row = -1, col = -1;

	while (!validMove) {

		cout << "Player " << player << " enter your coordinates (row column): ";
		cin >> row >> col;
		if (!(row < 1 || row > 3 || col < 1 || col > 3) && (gameBoard[row - 1][col - 1] == ' ')) {
			gameBoard[row - 1][col - 1] = player;
			validMove = true;
		} 
		else {
			cout << "Invalid move! Please enter Numbers between 1 and 3 and enter an free field!" << endl;
		}
	}
}

char checkWinner() {
	// Check rows
	for (int row = 0; row < 3; row++) {
		if (gameBoard[row][0] == gameBoard[row][1] && gameBoard[row][1] == gameBoard[row][2] && gameBoard[row][0] != ' ') {
			return gameBoard[row][0];
		}
	}

	// Check columns
	for (int col = 0; col < 3; col++) {
		if (gameBoard[0][col] == gameBoard[1][col] && gameBoard[1][col] == gameBoard[2][col] && gameBoard[0][col] != ' ') {
			return gameBoard[0][col];
		}
	}

	// Check diagonals
	if (gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2] && gameBoard[0][0] != ' ') {
		return gameBoard[0][0];
	}
	else if (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0] && gameBoard[0][2] != ' ') {
		return gameBoard[0][2];
	}

	return ' '; // No winner yet
}

bool checkFork(char player) {
	int winThreads = 0;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			
			if (gameBoard[row][col] == ' ') {
				gameBoard[row][col] = player;
				if (checkWinner() == player) {
					winThreads++;
				}
				gameBoard[row][col] = ' ';
			}
		}
	}
	return winThreads > 1;
}

bool isDraw() {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (gameBoard[row][col] == ' ') {
				return false;
			}
		}
	}
	return true;
}

void printScoreboard() {
	cout << "\nScoreboard: " << endl;
	cout << "	Rounds: " << games<< endl;
	cout << "	Player X Wins: " << winsX << endl;
	cout << "	Player O Wins: " << winsO << endl;
	cout << "	Draws: " << draws << "\n\n";
	cout << "	Prevented forks by AI: " << preventedForks << endl;
	cout << "	Created forks by AI: " << createdForks << endl;

	cout << "For Continuy press any key";
	char waiting = ' ';
	cin >> waiting;
}

void AIPlay(char player) {
	char opponent = (player == 'X') ? 'O' : 'X';

	// Check whether AI can win in the next move
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (gameBoard[row][col] == ' ') {

				gameBoard[row][col] = player;

				if (checkWinner() == player) {
					return; // AI wins
				}
				gameBoard[row][col] = ' '; // Undo move
			}
		}
	}

	// Check whether the player can win in the next move and block them
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (gameBoard[row][col] == ' ') {
				gameBoard[row][col] = opponent; // Assume the player is the opposite of AI

				if (checkWinner() == opponent) {
					gameBoard[row][col] = player; // Block the player
					return;
				}
				gameBoard[row][col] = ' '; // Undo move
			}
		}
	}

	// Check whether the AI can make a fork
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (gameBoard[row][col] == ' ') {
				gameBoard[row][col] = player;

				if (checkFork(player)) {
					createdForks++;
					return;
				}

				gameBoard[row][col] = ' ';
			}
		}
	}

	
	// Check whether the AI can prevent a fork and prevent it
	vector<Point> forks;
	//Check for forks
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (gameBoard[row][col] == ' ') {
				gameBoard[row][col] = opponent;
				if (checkFork(opponent)) {
					forks.push_back({ row,col });
				}
				gameBoard[row][col] = ' ';
			}
		}
	}
	// Check how to prevent the forks
	bool forkPrevented = true;
	if (!forks.empty()) {
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				if (gameBoard[row][col] == ' ') {
					gameBoard[row][col] = player;
					forkPrevented = true;
					for (int fork = 0; fork < forks.size(); fork++) {
						if (gameBoard[forks[fork].row][forks[fork].col] == ' ') {
							gameBoard[forks[fork].row][forks[fork].col] = opponent;
							if (checkFork(opponent)) { forkPrevented = false; }
							gameBoard[forks[fork].row][forks[fork].col] = ' ';
						}
					}
					if (forkPrevented) {
						preventedForks++;
						return;
					}
					gameBoard[row][col] = ' ';
				}
			}
		}
	}
	
	// Otherwise, make a random move 
	// 44,4% Center if its free
	// 33,3% Corner if its free
	// 22,2% Edge if its free
	while (true) {
		int randomNumber = genRandomNumber(1, 9);
		if ((randomNumber <= 4) && gameBoard[1][1] == ' ') {
			gameBoard[1][1] = player;
			return;
		}
		else if (randomNumber >= 7 && (gameBoard[0][0] == ' ' || gameBoard[0][2] == ' ' || gameBoard[2][0] == ' ' || gameBoard[2][2] == ' ')) {
			while (true) {
				switch (genRandomNumber(0, 3)) {
				case 0:
					if (gameBoard[0][0] == ' ') { gameBoard[0][0] = player; return; }
					break;
				case 1:
					if (gameBoard[0][2] == ' ') { gameBoard[0][2] = player; return; }
					break;
				case 2:
					if (gameBoard[2][0] == ' ') { gameBoard[2][0] = player; return; }
					break;
				case 3:
					if (gameBoard[2][2] == ' ') { gameBoard[2][2] = player; return; }
					break;
				}
			}
		}
		else if (gameBoard[0][1] == ' ' || gameBoard[1][0] == ' ' || gameBoard[1][2] == ' ' || gameBoard[2][1] == ' ') {
			while (true) {
				switch (genRandomNumber(0, 3)) {
				case 0:
					if (gameBoard[0][1] == ' ') { gameBoard[0][1] = player; return; }
					break;
				case 1:
					if (gameBoard[1][0] == ' ') { gameBoard[1][0] = player; return; }
					break;
				case 2:
					if (gameBoard[1][2] == ' ') { gameBoard[1][2] = player; return; }
					break;
				case 3:
					if (gameBoard[2][1] == ' ') { gameBoard[2][1] = player; return; }
					break;
				}
			}
		}
	}
}

void multiPlayer() {
	clearScreen();
	
	games++;
	resetBoard();
	printBoard();

	while (true) {
		playerPlay('X');
		clearScreen();
		printBoard();
		if (checkWinner() == 'X') { cout << "Player X wins!" << endl; winsX++; break; }
		if (isDraw()) { cout << "Its a Draw!" << endl; draws++; break; }

		playerPlay('O');
		clearScreen();
		printBoard();
		if (checkWinner() == 'O') { cout << "Player O wins!" << endl; winsO++; break; }
		if (isDraw()) { cout << "Its a Draw!" << endl; draws++; break; }
	}
	clearScreen();
	printScoreboard();
}

void singlePlayer() {
	clearScreen();
	
	games++;
	resetBoard();
	printBoard();

	while (true) {

		this_thread::sleep_for(chrono::milliseconds(1000)); // Pause for half a second before AI plays
		AIPlay('X');
		clearScreen();
		printBoard();
		if (checkWinner() == 'X') { cout << "Player X wins!" << endl; winsX++; break; }
		if (isDraw()) { cout << "Its a Draw!" << endl; draws++; break; }

		playerPlay('O');
		clearScreen();
		printBoard();
		if (checkWinner() == 'O') { cout << "Player O wins!" << endl; winsO++; break; }
		if (isDraw()) { cout << "Its a Draw!" << endl; draws++; break; }

	}
	printScoreboard();
}

void simulateAI() {
	int amountOfGames = 0;
	cout << "How many Rounds do you want to simulate: ";
	cin >> amountOfGames;
	
	for (int game = 0; game < amountOfGames; game++) {
		resetBoard();
		games++;
		while (true) {

			AIPlay('O');
			if (checkWinner() == 'O') { winsO++; break; }
			if (isDraw()) { draws++; break; }

			AIPlay('X');
			if (checkWinner() == 'X') { winsX++; break; }
			if (isDraw()) { draws++; break; }
		}
	}
	printScoreboard();
}

void gameMenu() {
	int choice = 0;
	while (true) {
		clearScreen();
		cout << "Select Game Mode:\n";
		cout << "1. Single Player (You vs AI)\n";
		cout << "2. Multiplayer (Player X vs Player O)\n";
		cout << "3. Simulate AI (AI vs AI)\n";
		cout << "4. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			singlePlayer();
			break;
		case 2:
			multiPlayer();
			break;
		case 3:
			simulateAI();
			break;
		case 4:
			cout << "Exiting the game. Goodbye!" << endl;
			return;
		default:
			cout << "Invalid choice! Please try again." << endl;
		}
	}
	clearScreen();
}

int main() {
	cout << "Welcome to Tic Tac Toe!\n" << endl;
	cout << "Game is starting..." << endl;
	this_thread::sleep_for(chrono::milliseconds(500));

	gameMenu();

	return 0;
}