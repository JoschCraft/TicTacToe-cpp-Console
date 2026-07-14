#include <iostream>
#include <random>
#include <thread>

using namespace std;

int rounds = 0;
int winsX = 0;
int winsO = 0;
int draws = 0;

char gameBoard[3][3] = {
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	{' ', ' ', ' '}
};

void clearScreen() {
	// Clear the console screen
	// This is platform dependent. For Windows, you can use system("cls");
	// For Unix/Linux, you can use system("clear");

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

void playerPLay(char player) {
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
	cout << "	Rounds: " << rounds << endl;
	cout << "	Player X Wins: " << winsX << endl;
	cout << "	Player O Wins: " << winsO << endl;
	cout << "	Draws: " << draws << "\n\n";
}

void AIPlay(char player) {
	// Check if AI can win in the next move
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

	// Check if the player can win in the next move and block them
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (gameBoard[row][col] == ' ') {
				gameBoard[row][col] = (player == 'X') ? 'O' : 'X'; // Assume the player is the opposite of AI

				if (checkWinner() == ((player == 'X') ? 'O' : 'X')) {
					gameBoard[row][col] = player; // Block the player
					return;
				}
				gameBoard[row][col] = ' '; // Undo move
			}
		}
	}

	// Otherwise, make a random move
	// Generate random Numbers for row and column
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distribution(0, 2);

	int row = -1, col = -1;
	do {
		row = distribution(gen);
		col = distribution(gen);

	} while (gameBoard[row][col] != ' ');
	gameBoard[row][col] = player;
}

void multiPlayer() {
	clearScreen();
	
	rounds++;

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			gameBoard[row][col] = ' ';
		}
	}

	printBoard();

	while (true) {
		playerPLay('X');
		clearScreen();
		printBoard();
		if (checkWinner() == 'X') { cout << "Player X wins!" << endl; winsX++; break; }
		if (isDraw()) { cout << "Its a Draw!" << endl; draws++; break; }

		playerPLay('O');
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
	
	rounds++;

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			gameBoard[row][col] = ' ';
		}
	}

	printBoard();

	while (true) {
		playerPLay('X');
		clearScreen();
		printBoard();
		if (checkWinner() == 'X') { cout << "Player X wins!" << endl; winsX++; break; }
		if (isDraw()) { cout << "Its a Draw!" << endl; draws++; break; }

		this_thread::sleep_for(chrono::milliseconds(1000)); // Pause for half a second before AI plays
		AIPlay('O');
		clearScreen();
		printBoard();
		if (checkWinner() == 'O') { cout << "Player O wins!" << endl; winsO++; break; }
		if (isDraw()) { cout << "Its a Draw!" << endl; draws++; break; }
	}
	printScoreboard();
}

void gameMenu() {
	int choice = 0;
	while (true) {
		char waitingForContinue = ' ';
		cout << "Press any key to continue..." << endl;
		cin >> waitingForContinue;
		clearScreen();
		cout << "Select Game Mode:\n";
		cout << "1. Single Player (You vs AI)\n";
		cout << "2. Multiplayer (Player X vs Player O)\n";
		cout << "3. Exit\n";
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

	gameMenu();

	return 0;
}