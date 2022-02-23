#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <cmath>
#include <tuple>

using namespace std;

#define DEFAULT		"\033[0m"
#define BOLD		"\033[1m"
#define UNDERLINE	"\033[4m"
#define REVERS		"\033[7m"
#define RED			"\033[31m"
#define GREEN		"\033[32m"
#define YELLOW		"\033[33m"
#define BLUE		"\033[34m"
#define	AQUA		"\033[36m"

#define NO			0
#define UP			1
#define DOWN		2
#define LEFT		3
#define RIGHT		4

#define clear() printf("\033[H\033[J")

void printf_(string str, string color) { cout << color + str + DEFAULT"\n"; }

class Puzzle {
	private:
		bool					validity;	// является ли головоломка валидной
		int						size;		// кол-во рядов/столбцов в головоломке
		int						distance;	// необходимое расстояние между элементами для корректного отображения в консоли
		vector< vector<int> >	box;		// двумерный массив для размещения элементов головоломки
		bool					answer;		// собрана головоломка или нет
		int						direction;	// направление прошлого движения пустого блока
		pair<int, int>			point;		// координаты пустого блока

	public:
		// Конструктор (1 аргумент - список чисел справа налевоб сверху вниз)
		Puzzle(vector<int> v) {
			int temp = sqrt(v.size()), ind = 0;

			if (v.size() > 100) {
				printf_("Головоломка слишком велика =(", RED);
				return ;
			}
			if (v.size() <= 1) {
				printf_("Головоломка слишком мала =(", RED);
				return ;
			}
			if (sqrt(v.size()) == temp) {	// опасное место, но в нашем случае должно быть всё хорошо(но это не точно)
				validity = true;
				size = temp;
				distance = log10(v.size()) + 2;
				box.resize(size);
				for (int i = 0; i < size; i++)
					for (int j = 0; j < size; j++)
						box[i].push_back(v[ind++]);
				answer = check();
			}
			else {
				printf_("Вы подали неверное кол-во элементов в векторе =(", RED);
				validity = false;
				size = -1;
				distance = -1;
				answer = false;
			}
			direction = NO;
			point = find();
		}
		// Печать головоломки на экран
		void print() {
			if (!validity) {
				printf_("Головоломка не валидна,не могу распечатать =(", RED);
				return ;
			}
			cout << "Кол-во рядов/столбцов: " << size << endl;
			cout << "Расстояние между элементами: " << distance << endl;
			cout << "Координаты пустого блока: (" << point.first << " " << point.second << ")" << endl;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++)
					cout << setw(distance) << box[i][j];
				cout << endl;
			}
			answer ? printf_("Головоломка решена", GREEN) : printf_("Головоломка не решена", RED);
		}
		// Проверка решена ли головоломка
		bool check() {
			int count = 1;
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (i != size-1 && j != size-1 && box[i][j] != count)
						return (false);
					if (i == size-1 && j == size-1 && box[i][j] != 0)
						return (false);
					count++;
				}
			}
			return (true);
		}
		// Поиск координат пустого блока
		pair<int, int> find() {
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					if (box[i][j] == 0)
						return (make_pair(i, j));
			return (make_pair(-1, -1));
		}
};

int main() {
	vector<int> numbers = {1, 2, 8, 3, 5, 6, 7, 4, 0};
	//vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 0};
	cout << numbers.size() << endl;
	//vector<int> numbers = {1, 2, 8, 3};
	Puzzle puzzle(numbers);
	puzzle.print();

	return (0);
}