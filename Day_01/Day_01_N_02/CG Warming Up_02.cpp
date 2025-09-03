#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include <algorithm>
using namespace std;

int Input_Command(char a);
void Show_File();
void F_toUpper();
void F_CountWords();
void F_ChColorUpperWords();
void F_ReverseLine();
void F_AddSlash();
void F_SlashReverse();
void F_ChangeChar();
void F_NewLineAfterNumber();
void F_SortByAlphaCount();
void F_FindWord(const string& word);

static void SetColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

bool Upper_Flag{ false }, Color_Flag{ false }, Reverse_Flag{ false }, AddSlash_Flag{ false }, RevWSlash_Flag{ false },
	ChChar_Flag{ false }, NewLine_Flag{ false }, FindWord_Flag{ false };
short int Sort_State{ 1 }; // 0 : None, 1 : Asc, 2 : Desc

int main()
{
	char Command;

	Show_File();

	while (true) {
		cout << "\n\nInput Command : ";
		if (!(cin >> Command)) {
			cout << "잘못된 입력입니다. 다시 입력하세요.\n";
			continue;
		}
		int Command_Flag = Input_Command(Command);
		if (Command_Flag == 1) {
			cout << "잘못된 입력입니다. 다시 입력하세요.\n";
			continue;
		}
		else if (Command_Flag == -1) {
			cout << "프로그램을 종료합니다.\n";
			break;
		}
	}

	return 0;
}

int Input_Command(char a) {
	if (a == 'a') {
		if (Upper_Flag) {
			Show_File();
			Upper_Flag = false;
		}
		else {
			F_toUpper();
			Upper_Flag = true;
		}
	}
	else if (a == 'b') {
		F_CountWords();
	}
	else if (a == 'c') {
		if (Color_Flag) {
			Show_File();
			Color_Flag = false;
		}
		else {
			F_ChColorUpperWords();
			Color_Flag = true;
		}
	}
	else if (a == 'd') {
		if (Reverse_Flag) {
			Show_File();
			Reverse_Flag = false;
		}
		else {
			F_ReverseLine();
			Reverse_Flag = true;
		}
	}
	else if (a == 'e') {
		if (AddSlash_Flag) {
			Show_File();
			AddSlash_Flag = false;
		}
		else {
			F_AddSlash();
			AddSlash_Flag = true;
		}
	}
	else if (a == 'f') {
		if (RevWSlash_Flag) {
			Show_File();
			RevWSlash_Flag = false;
		}
		else {
			F_SlashReverse();
			RevWSlash_Flag = true;
		}
	}
	else if (a == 'g') {
		if (ChChar_Flag) {
			Show_File();
			ChChar_Flag = false;
		}
		else {
			F_ChangeChar();
			ChChar_Flag = true;
		}
	}
	else if (a == 'h') {
		if (NewLine_Flag) {
			Show_File();
			NewLine_Flag = false;
		}
		else {
			F_NewLineAfterNumber();
			NewLine_Flag = true;
		}
	}
	else if (a == 'i') {
		if (Sort_State % 3 == 0) {
			Show_File();
			Sort_State++;
		}
		else {
			F_SortByAlphaCount();
		}
	}
	else if (a == 'j') {
		string word;
		cout << "찾을 단어를 입력하세요 : ";
		cin >> word;
		F_FindWord(word);
	}
	else if (a == 'q') {
		return -1;
	}
	else return 1;
	return 0;
}

void Show_File() {
	constexpr int word_size{ 128 };
	constexpr int buffer_size{ 1024 };
	ifstream in("Data_01.txt");
	if (!in) {
		cerr << "파일 열기 실패\n";
		exit(1);
	}

	int Word_Num{}, UpperWord_Num{};
	char buffer[buffer_size];
	int index{}, CountN{};
	vector<string> total_words;

	while (in.getline(buffer, buffer_size)) {
		vector<string> line_words;
		char* context = nullptr;
		char* token = strtok_s(buffer, " ", &context);
		while (token != nullptr) {
			line_words.push_back(token);
			token = strtok_s(nullptr, " ", &context);
			Word_Num++;
		}

		line_words.push_back("\n");
		CountN++;

		for (const string& temp : line_words) {
			cout << temp;
			if (temp != "\n") cout << ' ';
			if (isupper(temp[0])) UpperWord_Num++;
			total_words.push_back(temp);
		}
		memset(buffer, 0, sizeof(buffer));
	}

	Word_Num = total_words.size() - CountN;
	cout << "\n\n단어의 개수 : " << Word_Num << "\n대문자로 시작하는 단어의 개수 : " << UpperWord_Num << '\n';

	in.close();
}
void F_toUpper() {
	constexpr int word_size{ 128 };
	ifstream in("Data_01.txt");
	if (!in) {
		cerr << "파일 열기 실패\n";
		exit(1);
	}

	string buffer;
	vector<string> words;
	int index{};
	while (getline(in, buffer)) {
		while (buffer.size() > 0) {
			size_t pos = buffer.find(' ');
			if (pos == string::npos) {
				words[0] = buffer;
				break;
			}
			words.push_back(buffer.substr(0, pos));
			buffer = buffer.substr(pos + 1);
		}
		words.push_back("\n");
	}
	for (const auto& word : words) {
		string temp = word;
		for (auto& ch : temp) {
			ch = toupper(ch);
		}
		cout << temp;
		if (temp != "\n") cout << ' ';
	}

	in.close();
}
void F_CountWords() {
	constexpr int word_size{ 128 };
	constexpr int buffer_size{ 1024 };
	ifstream in("Data_01.txt");
	if (!in) {
		cerr << "파일 열기 실패\n";
		exit(1);
	}

	char buffer[buffer_size];
	int index{}, CountN{}, Word_Num{}, UpperWord_Num{};
	vector<string> total_words;
	while (in.getline(buffer, buffer_size)) {
		vector<string> line_words;
		char* context = nullptr;
		char* token = strtok_s(buffer, " ", &context);
		int line_word_count = 0;
		while (token != nullptr) {
			line_words.push_back(token);
			token = strtok_s(nullptr, " ", &context);
			line_word_count++;
		}

		for (const string& temp : line_words) {
			cout << temp << ' ';
			total_words.push_back(temp);
		}
		cout << "[단어 개수: " << line_word_count << "]\n";
		line_words.push_back("\n");
	}

	in.close();
}
void F_ChColorUpperWords() {
	constexpr int word_size{ 128 };
	constexpr int buffer_size{ 1024 };
	ifstream in("Data_01.txt");
	if (!in) {
		cerr << "파일 열기 실패\n";
		exit(1);
	}
	char buffer[buffer_size];
	int index{}, CountN{}, UpperWord_Num{};
	vector<string> total_words;
	while (in.getline(buffer, buffer_size)) {
		vector<string> line_words;
		char* context = nullptr;
		char* token = strtok_s(buffer, " ", &context);
		while (token != nullptr) {
			line_words.push_back(token);
			token = strtok_s(nullptr, " ", &context);
		}
		line_words.push_back("\n");
		CountN++;
		for (const string& temp : line_words) {
			if (isupper(temp[0])) {
				SetColor(12); // Red
				cout << temp << ' ';
				SetColor(7); // Default
				UpperWord_Num++;
			}
			else {
				cout << temp << ' ';
			}
			total_words.push_back(temp);
		}
		memset(buffer, 0, sizeof(buffer));
	}

	cout << "\n\n대문자로 시작하는 단어의 개수 : " << UpperWord_Num << '\n';
	in.close();
}
void F_ReverseLine() {
	constexpr int word_size{ 128 };
	constexpr int buffer_size{ 1024 };
	ifstream in("Data_01.txt");
	if (!in) {
		cerr << "파일 열기 실패\n";
		exit(1);
	}

	char buffer[buffer_size];
	int index{}, CountN{};
	vector<string> total_words;
	while (in.getline(buffer, buffer_size)) {
		vector<string> line_words;
		char* context = nullptr;
		char* token = strtok_s(buffer, " ", &context);
		while (token != nullptr) {
			line_words.push_back(token);
			token = strtok_s(nullptr, " ", &context);
		}

		line_words.push_back("\n");
		CountN++;

		for (int i = line_words.size() - 1; i >= 0; --i) {
			const string& temp = line_words[i];
			cout << temp;
			if (temp != "\n") cout << ' ';
			total_words.push_back(temp);
		}

		memset(buffer, 0, sizeof(buffer));
	}

	in.close();
}
void F_AddSlash() {
	constexpr int word_size{ 128 };
	constexpr int buffer_size{ 1024 };
	ifstream in("Data_01.txt");
	if (!in) {
		cerr << "파일 열기 실패\n";
		exit(1);
	}
	char buffer[buffer_size];
	int index{}, CountN{};
	vector<string> total_words;
	while (in.getline(buffer, buffer_size)) {
		vector<string> line_words;
		char* context = nullptr;
		char* token = strtok_s(buffer, " ", &context);
		while (token != nullptr) {
			line_words.push_back(token);
			token = strtok_s(nullptr, " ", &context);
		}
		line_words.push_back("\n");
		CountN++;
		for (const string& temp : line_words) {
			cout << temp;
			if (temp != "\n") cout << " / ";
			total_words.push_back(temp);
		}
		memset(buffer, 0, sizeof(buffer));
	}
	in.close();
}
void F_SlashReverse() {
	constexpr int word_size{ 128 };
	constexpr int buffer_size{ 1024 };
	ifstream in("Data_01.txt");
	if (!in) {
		cerr << "파일 열기 실패\n";
		exit(1);
	}

	cout << "RevWSlash_Flag : ";
	if (AddSlash_Flag) cout << "True\n";
	else cout << "False\n";

	char buffer[buffer_size];
	int index{}, CountN{};
	while (in.getline(buffer, buffer_size)) {
		vector<string> line_words;
		char* context = nullptr;
		char* token = strtok_s(buffer, " ", &context);
		while (token != nullptr) {
			line_words.push_back(token);
			token = strtok_s(nullptr, " ", &context);
		}
		line_words.push_back("\n");
		CountN++;
		for (int i = line_words.size() - 1; i >= 0; --i) {
			const string& temp = line_words[i];
			cout << temp;
			if (temp != "\n") {
				if (AddSlash_Flag) cout << " / ";
				else cout << " ";
			}
		}

		memset(buffer, 0, sizeof(buffer));
	}

	in.close();
}
void F_ChangeChar() {
	constexpr int word_size{ 128 };
	constexpr int buffer_size{ 1024 };
	ifstream in("Data_01.txt");
	if (!in) {
		cerr << "파일 열기 실패\n";
		exit(1);
	}
	char buffer[buffer_size];
	int index{}, CountN{};
	vector<string> total_words;
	char oldChar, newChar;
	cout << "바꿀 문자 입력 : ";
	cin >> oldChar;
	cout << "새로운 문자 입력 : ";
	cin >> newChar;
	while (in.getline(buffer, buffer_size)) {
		vector<string> line_words;
		char* context = nullptr;
		char* token = strtok_s(buffer, " ", &context);
		while (token != nullptr) {
			line_words.push_back(token);
			token = strtok_s(nullptr, " ", &context);
		}
		line_words.push_back("\n");
		CountN++;
		for (const string& temp : line_words) {
			string modified = temp;
			for (auto& ch : modified) {
				if (ch == oldChar) {
					ch = newChar;
				}
			}
			cout << modified;
			if (modified != "\n") cout << ' ';
			total_words.push_back(modified);
		}
		memset(buffer, 0, sizeof(buffer));
	}
	in.close();
}
void F_NewLineAfterNumber() {
	constexpr int word_size{ 128 };
	constexpr int buffer_size{ 1024 };
	ifstream in("Data_01.txt");
	if (!in) {
		cerr << "파일 열기 실패\n";
		exit(1);
	}
	char buffer[buffer_size];
	int index{}, CountN{};
	vector<string> total_words;
	while (in.getline(buffer, buffer_size)) {
		vector<string> line_words;
		char* context = nullptr;
		char* token = strtok_s(buffer, " ", &context);
		while (token != nullptr) {
			line_words.push_back(token);
			token = strtok_s(nullptr, " ", &context);
		}
		line_words.push_back("\n");
		CountN++;
		for (const string& temp : line_words) {
			cout << temp;
			if (temp != "\n") {
				if (isdigit(temp.back())) {
					cout << '\n';
				}
				else {
					cout << ' ';
				}
			}
			total_words.push_back(temp);
		}
		memset(buffer, 0, sizeof(buffer));
	}
	in.close();
}
void F_SortByAlphaCount() {
	constexpr int word_size{ 128 };
	constexpr int buffer_size{ 1024 };
	ifstream in("Data_01.txt");
	if (!in) {
		cerr << "파일 열기 실패\n";
		exit(1);
	}

	cout << "Sort_State : ";
	if (Sort_State % 3 == 1) cout << "Asc\n";
	else if (Sort_State % 3 == 2) cout << "Desc\n";
	else cout << "None\n";

	char buffer[buffer_size];
	int index{}, CountN{};
	while (in.getline(buffer, buffer_size)) {
		char* current = buffer;
		int lower_alphabet[26]{ 0, }, upper_alphabet[26]{ 0, };
		while (*current) {
			if (isalpha(*current)) {
				if (isupper(*current)) upper_alphabet[toupper(*current) - 'A']++;
				else lower_alphabet[tolower(*current) - 'a']++;
			}
			current++;
		}
		if (Sort_State % 3 == 1) {
			sort(lower_alphabet, lower_alphabet + 26);
			sort(upper_alphabet, upper_alphabet + 26);
		}
		else if (Sort_State % 3 == 2) {
			sort(lower_alphabet, lower_alphabet + 26, greater<int>());
			sort(upper_alphabet, upper_alphabet + 26, greater<int>());
		}
		
		for(int i = 0; i < 26; ++i) {
			int count = upper_alphabet[i];
			if (count > 0) {
				char ch = 'A' + i;
				for (int j = 0; j < count; ++j) {
					cout << ch;
				}
			}
			count = lower_alphabet[i];
			if (count > 0) {
				char ch = 'a' + i;
				for (int j = 0; j < count; ++j) {
					cout << ch;
				}
			}
		}
		cout << '\n';
		memset(buffer, 0, sizeof(buffer));
	}

	Sort_State++;
	in.close();
}
void F_FindWord(const string& word) {
	constexpr int word_size{ 128 };
	constexpr int buffer_size{ 1024 };
	ifstream in("Data_01.txt");
	if (!in) {
		cerr << "파일 열기 실패\n";
		exit(1);
	}
	char buffer[buffer_size];
	int index{}, CountN{}, FoundCount{};
	vector<string> total_words;
	string lower_word = word;
	transform(lower_word.begin(), lower_word.end(), lower_word.begin(), ::tolower);
	while (in.getline(buffer, buffer_size)) {
		vector<string> line_words;
		char* context = nullptr;
		char* token = strtok_s(buffer, " ", &context);
		while (token != nullptr) {
			line_words.push_back(token);
			token = strtok_s(nullptr, " ", &context);
		}
		line_words.push_back("\n");
		CountN++;
		for (const string& temp : line_words) {
			string lower_temp = temp;
			transform(lower_temp.begin(), lower_temp.end(), lower_temp.begin(), ::tolower);
			if (lower_temp == lower_word) {
				SetColor(12); // Red
				cout << temp << ' ';
				SetColor(7); // Default
				FoundCount++;
			}
			else {
				cout << temp << ' ';
			}
			total_words.push_back(temp);
		}
		memset(buffer, 0, sizeof(buffer));
	}
	cout << "\n\n찾은 단어의 개수 : " << FoundCount << '\n';
	in.close();
}