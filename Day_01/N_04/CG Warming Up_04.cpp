#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include <thread>
#include <iomanip>
#define NOMINMAX
#include <Windows.h>
#define DEFAULT_COLOR 7
using namespace std;

random_device rd;
default_random_engine dre(rd());
uniform_int_distribution<int> uid(97, 122);
uniform_int_distribution<int> uid_color(1, 14);

int err_flag{};

void Set_Corsour_color(int color);
class Board {
	static const int SIZE = 5;
	char board[SIZE][SIZE];
	bool revealed[SIZE][SIZE];
	int score;
	int alphabet_color_index[26]{};
	int max_attempts;

public:
	Board() : max_attempts(20), score(0) {
		init_board();
	}

	void init_board() {
		vector<char> cards;
		bool used[26] = { 0, };
		for (int i = 0; i < 12; ++i) {
			char c = static_cast<char>(uid(dre));
			if (used[c - 'a']) {
				--i;
				continue;
			}
			else {
				used[c - 'a'] = true;
			}
			cards.push_back(c);
			cards.push_back(c);
		}
		cards.push_back('@'); // Joker

		shuffle(cards.begin(), cards.end(), dre);
		int idx = 0;
		for (int i = 0; i < SIZE; ++i) {
			for (int j = 0; j < SIZE; ++j) {
				board[i][j] = cards[idx++];
				revealed[i][j] = false;
			}
		}
		for (int i = 0; i < 26; ++i) {
			alphabet_color_index[i] = uid_color(dre);
		}
	}

	void hint() const {
		system("cls");
		cout << "  a b c d e\n";
		for (int i = 0; i < SIZE; ++i) {
			cout << i + 1 << ' ';
			for (int j = 0; j < SIZE; ++j) {
				Set_Corsour_color(DEFAULT_COLOR);
				cout << board[i][j] << ' ';
			}
			cout << '\n';
		}
		cout << "Attempts left: " << max_attempts << ", Score: " << score << '\n';
	}

	void display_board() const {
		system("cls");
		cout << "  a b c d e\n";
		for (int i = 0; i < SIZE; ++i) {
			cout << i + 1 << ' ';
			for (int j = 0; j < SIZE; ++j) {
				if (revealed[i][j]) {
					Set_Corsour_color(alphabet_color_index[board[i][j] - 'a']);
					cout << static_cast<char>(toupper(board[i][j])) << ' ';
					Set_Corsour_color(DEFAULT_COLOR);
				}
				else {
					cout << "* ";
				}
			}
			cout << '\n';
		}
		cout << "Attempts left: " << max_attempts << ", Score: " << score << '\n';
	}

	void choose_location(string command) {
		// location format: "a1 b2"
		string location{ command };
		int row_num[2]{}, col_char[2]{};

		if (location.length() != 5) {
			err_flag = 1;
			return;
		}

		string loc_1 = location.substr(0, 2);
		string loc_2 = location.substr(3, 4);

		if (loc_1.length() != 2 || loc_2.length() != 2) {
			return;
		}
		if (loc_1[0] < 'a' || loc_1[0] > 'e' || loc_2[0] < 'a' || loc_2[0] > 'e' ||
			loc_1[1] < '1' || loc_1[1] > '5' || loc_2[1] < '1' || loc_2[1] > '5') {
			cout << "Invalid input format!\n";
			return;
		}
		if (loc_1 == loc_2) {
			cout << "You must choose two different locations!\n";
			return;
		}
		if (revealed[loc_1[1] - '1'][loc_1[0] - 'a'] || revealed[loc_2[1] - '1'][loc_2[0] - 'a']) {
			cout << "One of the chosen cards is already revealed!\n";
			return;
		}

		row_num[0] = loc_1[1] - '1';
		col_char[0] = loc_1[0] - 'a';
		row_num[1] = loc_2[1] - '1';
		col_char[1] = loc_2[0] - 'a';

		cout << "  a b c d e\n";
		for (int i = 0 ; i < SIZE; ++i) {
			cout << i + 1 << ' ';
			for (int j = 0 ; j < SIZE; ++j) {
				if ((i == row_num[0] && j == col_char[0]) || (i == row_num[1] && j == col_char[1])) {
					Set_Corsour_color(alphabet_color_index[board[i][j] - 'a']);
					cout << board[i][j] << ' ';
					Set_Corsour_color(DEFAULT_COLOR);
				}
				else if (revealed[i][j]) {
					Set_Corsour_color(alphabet_color_index[board[i][j] - 'a']);
					cout << static_cast<char>(toupper(board[i][j])) << ' ';
					Set_Corsour_color(DEFAULT_COLOR);
				}
				else {
					cout << "* ";
				}
			}
			cout << '\n';
		}
		cout << "Attempts left: " << max_attempts - 1 << ", Score: " << score << '\n';

		if (board[row_num[0]][col_char[0]] == board[row_num[1]][col_char[1]] ||
			board[row_num[0]][col_char[0]] == '@' || board[row_num[1]][col_char[1]] == '@') {
			reveal(row_num[0], col_char[0]);
			reveal(row_num[1], col_char[1]);
			score += 1;
			--max_attempts;
		}
		else {
			--max_attempts;
		}
	}

	void reveal(int row, int col) {
		if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
			cout << "Invalid position!\n";
			return;
		}
		if (revealed[row][col]) {
			cout << "Card already revealed!\n";
			return;
		}
		revealed[row][col] = true;
	}

	void show_ans() const {
		system("cls");
		cout << "Answer Board:\n";
		cout << "  a b c d e\n";
		for (int i = 0; i < SIZE; ++i) {
			cout << i + 1 << ' ';
			for (int j = 0; j < SIZE; ++j) {
				Set_Corsour_color(alphabet_color_index[board[i][j] - 'a']);
				cout << static_cast<char>(toupper(board[i][j])) << ' ';
				Set_Corsour_color(DEFAULT_COLOR);
			}
			cout << '\n';
		}
		cout << "Attempts left: " << max_attempts << ", Score: " << score << '\n';
	}

	void reset() {
		init_board();
		max_attempts = 20;
		score = 0;
	}

	int get_score() const {
		return score;
	}
	int get_attempts() const {
		return max_attempts;
	}
};

void ExcuteCommand(const string& command, Board& board);
void Error_Message(int err_flag);

int main()
{
	Board board;
	string command;

	while (true) {
		if (board.get_attempts() <= 0) {
			board.display_board();
			cout << "Game Over! You've used all your attempts.\n";
			cout << "Your final score is: " << board.get_score() << '\n';
			cout << "Resetting the game...\n";
			this_thread::sleep_for(chrono::seconds(3));
			board.reset();
		}

		board.display_board();
		cout << "last command : " << command << '\n';
		Error_Message(err_flag);

		cout << "\nInput format: 'a1 b2' to select two cards. or Commands\n";
		cout << "r : reset, h : hint, q : quit, A : answer\n";
		cout << "Input location : ";
		getline(cin, command);

		command.erase(command.find_last_not_of(" \n\r\t") + 1);
		ExcuteCommand(command, board);
	}
}

void ExcuteCommand(const string& command, Board& board) {
	if (command == "r") {
		cout << "resetting the game...\n";
		board.reset();
	}
	else if (command == "A") {
		cout << "Here is the answer board for 10 seconds...\n";
		board.show_ans();
		auto start = std::chrono::steady_clock::now();
		const double timer_duration = 5.0;
		double elapsed_seconds = 0.0;
		while (elapsed_seconds < timer_duration) {
			auto now = std::chrono::steady_clock::now();
			elapsed_seconds = std::chrono::duration<double>(now - start).count();
			double remaining_seconds = timer_duration - elapsed_seconds;
			if (remaining_seconds < 0) {
				remaining_seconds = 0;
			}
			std::cout << "\r남은 시간: " << std::fixed << std::setprecision(1) << remaining_seconds << "초  " << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
	else if (command == "h") {
		cout << "Here is the hint for 5 seconds...\n";
		board.hint();
		
		auto start = std::chrono::steady_clock::now();
		const double timer_duration = 5.0;
		double elapsed_seconds = 0.0;
		while (elapsed_seconds < timer_duration) {
			auto now = std::chrono::steady_clock::now();

			elapsed_seconds = std::chrono::duration<double>(now - start).count();

			double remaining_seconds = timer_duration - elapsed_seconds;
			if (remaining_seconds < 0) {
				remaining_seconds = 0;
			}

			std::cout << "\r남은 시간: " << std::fixed << std::setprecision(1) << remaining_seconds << "초  " << std::flush;

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
	else if (command == "q") {
		cout << "Exiting the game. Goodbye!\n";
		exit(0);
	}
	else {
		system("cls");
		cout << "You chose locations: " << command << '\n';
		cout << "Returning to the game in 3 seconds...\n";
		board.choose_location(command);
		if (err_flag != 0) {
			return;
		}

		auto start = std::chrono::steady_clock::now();
		const double timer_duration = 3.0;
		double elapsed_seconds = 0.0;
		while (elapsed_seconds < timer_duration) {
			auto now = std::chrono::steady_clock::now();

			elapsed_seconds = std::chrono::duration<double>(now - start).count();

			double remaining_seconds = timer_duration - elapsed_seconds;
			if (remaining_seconds < 0) {
				remaining_seconds = 0;
			}

			std::cout << "\r남은 시간: " << std::fixed << std::setprecision(1) << remaining_seconds << "초  " << std::flush;

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
}
static void Set_Corsour_color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void Error_Message(int err_flag) {
	// 1. command format error
	// 2. location input format error
	// 3. location range error
	// 4. same location error
	// 5. already revealed error
	Set_Corsour_color(12);
	if (err_flag == 1) {
		cout << "Invalid Command input format!\n";
	}
	else if (err_flag == 2) {
		cout << "Invalid Location input format!\n";
	}
	else if (err_flag == 3) {
		cout << "Input out of range! Please enter a letter from 'a' to 'e' and a number from '1' to '5'.\n";
	}
	else if (err_flag == 4) {
		cout << "You must choose two different locations!\n";
	}
	else if (err_flag == 5) {
		cout << "One of the chosen cards is already revealed!\n";
	}
	err_flag = 0;
	Set_Corsour_color(DEFAULT_COLOR);
}