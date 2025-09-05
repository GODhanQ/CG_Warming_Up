#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

class Node {
	tuple<int, int, int> point;
	Node* next;
	Node* prev;

public:
	Node(int x, int y, int z) : point(make_tuple(x, y, z)), next(nullptr), prev(nullptr) {}
	Node() : point(make_tuple(0, 0, 0)), next(nullptr), prev(nullptr) {}

	int get_x() {
		return get<0>(point);
	}
	int get_y() {
		return get<1>(point);
	}
	int get_z() {
		return get<2>(point);
	}
	
	void set_point(int x, int y, int z) {
		point = make_tuple(x, y, z);
	}
	bool is_empty() {
		return (get_x() == NULL && get_y() == NULL && get_z() == NULL);
	}

	friend class List;
};
class List {
	int data_size{};
	Node* head;
	Node* tail;

public:
	List() : data_size(0), head(nullptr), tail(nullptr) {
		init_list();
	}

	void init_list() {
		Node* head_node = new Node();
		head = head_node; tail = head_node;

		Node* current = head_node;
		int index{ 1 };
		for(int i = 0 ; i < 9; ++i) {
			Node* temp = new Node();
			current->next = temp;
			temp->prev = current;
			tail = tail->next;

			index++;
			current = current->next;
		}
		cout << "리스트 초기화 완료. 현재 리스트 크기: " << index << '\n';
	}

	void show() const {
		Node* current = tail;
		int index{ 10 };
		cout << "리스트에 저장된 점의 좌표:\n";
		while (current != nullptr) {
			int x{ current->get_x() }, y{ current->get_y() }, z{ current->get_z() };
			if (x == NULL && y == NULL && z == NULL) {
				cout << index << " : ( , , )\n";
				--index;
				current = current->prev;
				continue;
			}
			cout << index << " : (" << x << ", " << y << ", " << z << ")\n";
			current = current->prev;
			--index;
		}
	}

	void push_front(int x, int y, int z) {
		if (data_size > 10) {
			cout << "No more space to add new point at the front.\n";
			return;
		}
		else {
			Node* current = head;
			if (current->is_empty()) {
				current->set_point(x, y, z);
			}
			else {
				while (!(current->is_empty())) {
					current = current->next;
				}
				while (current != head) {
					current->point = current->prev->point;
					current = current->prev;
				}
				current->set_point(x, y, z);
			}
		}
		++data_size;
	}
	void push_back(int x, int y, int z) {
		if (data_size > 10) {
			cout << "No more space to add new point at the back.\n";
			return;
		}
		else {
			Node* current = head;
			if (current->is_empty()) {
				current->set_point(x, y, z);
			}
			else {
				while (current->next != nullptr && !(current->next->is_empty())) {
					current = current->next;
				}
				if (current->next == nullptr) {
					cout << "리스트가 가득 찼습니다. 뒤에 점을 추가할 수 없습니다.\n";
					return;
				}
				current->next->set_point(x, y, z);
			}
		}
		++data_size;
	}

	void pop_front() {
		if (data_size == 0) {
			cout << "리스트가 비어있습니다. 삭제할 점이 없습니다.\n";
			return;
		}
		else {
			Node* current = tail;
			while (current->prev != nullptr && current->is_empty()) {
				current = current->prev;
			}
			current->set_point(NULL, NULL, NULL);
			--data_size;
		}
	}
	void pop_back() {
		if (data_size == 0) {
			cout << "리스트가 비어있습니다. 삭제할 점이 없습니다.\n";
			return;
		}
		else {
			Node* current = head;
			while (current->next != nullptr && current->is_empty()) {
				current = current->next;
			}
			current->set_point(NULL, NULL, NULL);
			--data_size;
		}
	}

	void clear() {
		Node* current = head;
		while (current != nullptr) {
			current->set_point(NULL, NULL, NULL);
			current = current->next;
		}
		data_size = 0;
		cout << "리스트가 초기화되었습니다.\n";
	}

	void shift_data() {
		if (data_size == 0) {
			cout << "리스트가 비어있습니다. 이동할 점이 없습니다.\n";
			return;
		}
		else {
			Node* current = head;
			tuple<int, int, int> temp = current->point;
			while(current->next != nullptr) {
				current->point = current->next->point;
				current = current->next;
			}
			tail->point = temp;
		}
	}

	void sort_data() {
		if (data_size == 0) {
			cout << "리스트가 비어있습니다. 정렬할 점이 없습니다.\n";
			return;
		}
		else {
			vector<tuple<int, int, int>> points;
			Node* current = head;
			while (current != nullptr) {
				if (!current->is_empty()) {
					points.push_back(current->point);
				}
				current = current->next;
			}
			sort(points.begin(), points.end(), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
				return (get<0>(a) * get<0>(a) + get<1>(a) * get<1>(a) + get<2>(a) * get<2>(a)) < 
					(get<0>(b) * get<0>(b) + get<1>(b) * get<1>(b) + get<2>(b) * get<2>(b));
			});
			current = head;
			int count = 0;
			while(current != nullptr) {
				tuple<int, int, int> temp = points[count++];
				current->point = temp;
				current = current->next;
			}
		}
	}

	void get_data_size() const {
		cout << "리스트에 저장된 점의 개수: " << data_size << '\n';
	}
};

static int Command_Handler(char command, List& list) {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (command == '+') {
		int x, y, z;
		cout << "추가할 점의 좌표를 입력하세요 (x y z): ";
		if (!(cin >> x >> y >> z)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return 1;
		}
		list.push_back(x, y, z);
	}
	else if (command == '-') {
		list.pop_front();
	}
	else if (command == 'e') {
		int x, y, z;
		cout << "추가할 점의 좌표를 입력하세요 (x y z): ";
		if (!(cin >> x >> y >> z)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return 1;
		}
		list.push_front(x, y, z);
	}
	else if (command == 'd') {
		list.pop_back();
	}
	else if (command == 'a') {
		list.get_data_size();
	}
	else if (command == 'b') {
		list.shift_data();
	}
	else if (command == 'c') {
		list.clear();
	}
	else if (command == 'f') {
		list.sort_data();
	}
	else if (command == 'q') {
		return -1;
	}
	else {
		return 1;
	}
	return 0;
}

int main()
{
	char command;
	List list;
	while (true) {
		cout << "Input Command: ";
		if (!(cin >> command)) {
			cout << "잘못된 입력입니다. 다시 입력하세요.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		else {
			int Commnad_status = Command_Handler(command, list);
			if (1 == Commnad_status) {
				cout << "잘못된 입력입니다. 다시 입력하세요.\n";
				continue;
			}
			else if (-1 == Commnad_status) {
				cout << "프로그램을 종료합니다.\n";
				break;
			}
			else {
				list.show();
			}
		}
	}
}