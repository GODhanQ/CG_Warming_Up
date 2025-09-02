#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <Eigen/Dense>
using namespace std;

default_random_engine dre;
uniform_int_distribution<int> uid{1,9};

class Matrix {

public:
	int matrix[4][4];
	Matrix() {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				matrix[i][j] = uid(dre);
			}
		}
	}

	void show() const {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				cout << matrix[i][j] << ' ';
			}
			cout << '\n';
		}
	}

	void reset() {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				matrix[i][j] = uid(dre);
			}
		}
	}
};

Matrix Matrix_1;
Matrix Matrix_2;
bool sub_flag{ false };
bool add_flag{ false };

void M_multifly();
void M_add();
void M_sub();
void M_T();
void M_minsub();
void M_maxadd();
void M_det();

int Input_Command(char a) {
	if (a == 'm') {
		M_multifly();
		return 0;
	}
	else if (a == 'a') {
		M_add();
		return 0;
	}
	else if (a == 'd') {
		M_sub();
		return 0;
	}
	else if (a == 'r') {
		M_det();
		return 0;
	}
	else if (a == 't') {
		M_T();
		return 0;
	}
	else if (a == 'e') {
		if (sub_flag) {
			cout << "Matrix_1 : \n";
			Matrix_1.show();
			cout << "\nMatrix_2 : \n";
			Matrix_2.show();

			sub_flag = false;
		}
		M_minsub();
		sub_flag = true;
		return 0;
	}
	else if (a == 'f') {
		if (add_flag) {
			cout << "Matrix_1 : \n";
			Matrix_1.show();
			cout << "\nMatrix_2 : \n";
			Matrix_2.show();

			sub_flag = false;
		}
		M_maxadd();
		add_flag = true;
		return 0;
	}
	else if (a == 's') {
		Matrix_1.reset();
		Matrix_2.reset();

		cout << "New Matrix_1 : \n";
		Matrix_1.show();
		cout << "\nNew Matrix_2 : \n";
		Matrix_2.show();

		return 0;
	}
	else if (a == 'q') {
		return 1;
	}
	else return -1;
}

int main()
{
	char Command;

	cout << "Initialize Matrix... \n";
	cout << "Matrix_1 : \n";
	Matrix_1.show();
	cout << "\nMatrix_2 : \n";
	Matrix_2.show();

	while (true) {
		cout << "\n\n문자 한개만 입력하세요.\nCommand : ";
		if (!(cin >> Command)) {
			cout << "잘못된 입력입니다. 다시 입력하세요.\n";
			continue;
		}
		int Flag = Input_Command(Command);
		if (Flag == -1) {
			cout << "잘못된 입력입니다. 다시 입력하세요.\n";
			continue;
		}
		else if (Flag == 1) {
			return 0;
		}
	}
}

void M_multifly() {
	Matrix temp;
	// 1의 n번째 행 x 2의 n번째 열
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			int temp_sum{};
			for (int k = 0; k < 4; ++k) {
				temp_sum += Matrix_1.matrix[i][k] * Matrix_2.matrix[k][j];
			}
			temp.matrix[i][j] = temp_sum;
		}
	}
	cout << "\n RESULT \n";
	temp.show();
}
void M_add() {
	Matrix temp;
	// 1의 n번째 행 x 2의 n번째 열
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			temp.matrix[i][j] = Matrix_1.matrix[i][j] + Matrix_2.matrix[i][j];
		}
	}
	cout << "\n RESULT \n";
	temp.show();
}
void M_sub() {
	Matrix temp;
	// 1의 n번째 행 x 2의 n번째 열
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			temp.matrix[i][j] = Matrix_1.matrix[i][j] - Matrix_2.matrix[i][j];
		}
	}
	cout << "\n RESULT \n";
	temp.show();
}
void M_T() {
	Matrix temp_1, temp_2;
	int k{ 3 };
	for (int i = 0; i < 4; ++i) {
		int l{ 3 };
		for (int j = 0; j < 4; ++j) {
			temp_1.matrix[k][l] = Matrix_1.matrix[i][j];
			temp_2.matrix[k][l] = Matrix_2.matrix[i][j];
			l--;
		}
		k--;
	}
	cout << "\n RESULT \nMatrix_1 : \n";
	temp_1.show();
	cout << "\nMatrix_2 : \n";
	temp_2.show();
}
void M_minsub() {
	Matrix temp_1, temp_2;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			temp_1.matrix[i][j] = Matrix_1.matrix[i][j]; temp_2.matrix[i][j] = Matrix_1.matrix[i][j];
		}
	}
	int min_1{ numeric_limits<int>::max() }, min_2{ numeric_limits<int>::max() };
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (min_1 > Matrix_1.matrix[i][j]) min_1 = Matrix_1.matrix[i][j];
			if (min_2 > Matrix_2.matrix[i][j]) min_2 = Matrix_2.matrix[i][j];
		}
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			temp_1.matrix[i][j] -= min_1;
			temp_2.matrix[i][j] -= min_2;
		}
	}

	cout << "\n RESULT \nMatrix_1 : \n";
	temp_1.show();
	cout << "\nMatrix_2 : \n";
	temp_2.show();
}
void M_maxadd() {
	Matrix temp_1, temp_2;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			temp_1.matrix[i][j] = Matrix_1.matrix[i][j]; temp_2.matrix[i][j] = Matrix_1.matrix[i][j];
		}
	}
	int max_1{ numeric_limits<int>::min() }, max_2{ numeric_limits<int>::min() };
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (max_1 < Matrix_1.matrix[i][j]) max_1 = Matrix_1.matrix[i][j];
			if (max_2 < Matrix_2.matrix[i][j]) max_2 = Matrix_2.matrix[i][j];
		}
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			temp_1.matrix[i][j] += max_1;
			temp_2.matrix[i][j] += max_2;
		}
	}

	cout << "\n RESULT \nMatrix_1 : \n";
	temp_1.show();
	cout << "\nMatrix_2 : \n";
	temp_2.show();
}
void M_det() {
	Eigen::Matrix4d em1, em2;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			em1(i, j) = Matrix_1.matrix[i][j];
			em2(i, j) = Matrix_2.matrix[i][j];
		}
	}

	cout << "\n RESULT \nMatrix_1 determinant : " << em1.determinant();
	cout << "\nMatrix_2 determinant : " << em2.determinant();
}