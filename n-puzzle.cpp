#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <cmath>
#include <set>

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
	public:
		bool					validity;	// является ли головоломка валидной
		int						size;		// кол-во рядов/столбцов в головоломке
		int						distance;	// необходимое расстояние между элементами для корректного отображения в консоли
		vector< vector<int> >	box;		// двумерный массив для размещения элементов головоломки
		bool					answer;		// собрана головоломка или нет
		int						direction;	// направление прошлого движения пустого блока
		pair<int, int>			point;		// координаты пустого блока

		// Конструктор (1 аргумент - список чисел справа налево и сверху вниз)
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
				point = find();
				//===========================================
				// вот этот блок ещё стоит проверить, но вроед ок
				int len = size * size, count = point.second;

				for (int i = 0; i < len-1; i++)
					for (int j = i+1; j < len; j++)
						if (v[i] > v[j])
							count++;
				validity = count % 2 == 0;
				//===========================================
			}
			else {
				printf_("Вы подали неверное кол-во элементов в векторе =(", RED);
				validity = false;
				size = -1;
				distance = -1;
				answer = false;
			}
			
			direction = NO;
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
			cout << "Последнее движение: ";
			if (direction == UP)
				cout << "вверх" << endl;
			else if (direction == DOWN)
				cout << "вниз" << endl;
			else if (direction == RIGHT)
				cout << "вправо" << endl;
			else if (direction == LEFT)
				cout << "влево" << endl;
			else
				cout << "нет" << endl;

			answer ? printf_("Головоломка решена", GREEN) : printf_("Головоломка не решена", RED);
		}
		// Передвинуть пустой в нужном направлении (внимание, функция небезопасна, не всегда можно передвинуть!!!)
		void	swapBlock(int dir) {
			direction = dir;
			if (dir == UP)
				swap(box[point.first][point.second], box[--point.first][point.second]);
			else if (dir == DOWN)
				swap(box[point.first][point.second], box[++point.first][point.second]);
			else if (dir == RIGHT)
				swap(box[point.first][point.second], box[point.first][++point.second]);
			else if (dir == LEFT)
				swap(box[point.first][point.second], box[point.first][--point.second]);
			answer = check();
		}
	
	private:
		// Проверка решена ли головоломка
		bool check() {
			int count = 1, end = size * size;

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					if (box[i][j] != count)
						return (false);
					count++;
					if (count == end)
						break ;
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

// Метод решения перебором
void	brute_force(Puzzle puzzle) {
	if (!puzzle.validity) {
		printf_("Головоломка не валидна", YELLOW);
		return ;
	}

	queue<Puzzle>	q;			// очередь из вариантов головоломок, требующих рассмотрения
	set<vector <vector <int> > >	visited;	// множество уже рассмотренных вариантов
	bool			flag = true;
	int				step = 0;

	q.push(puzzle);
	visited.insert(puzzle.box);

	if (q.front().answer == true) {
		printf_("Головоломка уже решена", YELLOW);
		return ;
	}

	while (flag) {
		// cout << "Элементов в очереди: " << q.size() << endl;
		// cout << "Рассмотренных головоломок: " << visited.size() << endl;

		if (q.front().direction != DOWN && q.front().point.first != 0) {
			Puzzle	temp = q.front();

			step++;
			temp.swapBlock(UP);
			if (visited.insert(temp.box).second)
				q.push(temp);
			if (temp.answer)
				break ;
		}
		if (q.front().direction != UP && q.front().point.first != q.front().size - 1) {
			Puzzle	temp = q.front();

			step++;
			temp.swapBlock(DOWN);
			if (visited.insert(temp.box).second)
				q.push(temp);
			if (temp.answer)
				break ;
		}
		if (q.front().direction != LEFT && q.front().point.second != q.front().size - 1) {
			Puzzle	temp = q.front();

			step++;
			temp.swapBlock(RIGHT);
			if (visited.insert(temp.box).second)
				q.push(temp);
			if (temp.answer)
				break ;
		}
		if (q.front().direction != RIGHT && q.front().point.second != 0) {
			Puzzle	temp = q.front();

			step++;
			temp.swapBlock(LEFT);
			if (visited.insert(temp.box).second)
				q.push(temp);
			if (temp.answer)
				break ;
		}
		q.pop();
	}
	q.back().print();	// должна быть решённая головоломка
	cout << "Элементов в очереди: " << q.size()-1 << endl;
	cout << "Рассмотренных головоломок: " << visited.size() << endl;
	cout << "Шагов: " << step << endl;
}

int main() {
	// https://metaschool.ru/pub/games/puzzle15/puzzle15.php
	// vector<int> numbers1 = {3, 8, 5, 2, 7, 6, 4, 1};		// не валидна
	// vector<int> numbers2 = {3, 8, 5, 2, 7, 6, 4, 1, 0};	// 102.851 шагов
	// vector<int> numbers3 = {8, 2, 6, 7, 4, 5, 1, 3, 0};	// 234.069 шагов
	// vector<int> numbers4 = {2, 1, 8, 5, 3, 6, 7, 4, 0};	// 102.552 шагов
	// vector<int> numbers5 = {1, 2, 3, 4, 5, 6, 0, 7, 8};	// 6 шагов
	// vector<int> numbers6 = {1, 2, 3, 4, 5, 6, 7, 0, 8};	// 2 шага
	// vector<int> numbers7 = {1, 2, 3, 4, 5, 6, 7, 8, 0};	// уже решена
	// vector<int> numbers8 = {1, 2, 3, 4, 5, 6, 8, 7, 0};	// нельзя решить
	vector<int> numbers9 = {7, 0, 5, 8, 6, 3, 2, 1, 4};	// 232.918 шагов

	// Puzzle puzzle1(numbers1);
	// Puzzle puzzle2(numbers2);
	// Puzzle puzzle3(numbers3);
	// Puzzle puzzle4(numbers4);
	// Puzzle puzzle5(numbers5);
	// Puzzle puzzle6(numbers6);
	// Puzzle puzzle7(numbers7);
	// Puzzle puzzle8(numbers8);
	Puzzle puzzle9(numbers9);

	// puzzle1.print();
	// puzzle2.print();
	// puzzle3.print();
	// puzzle4.print();
	// puzzle5.print();
	// puzzle6.print();
	// puzzle7.print();
	// puzzle8.print();
	puzzle9.print();
	cout << "-----------" << endl;


	unsigned int time = clock();
	brute_force(puzzle9);
	time = clock() - time;
	cout << "Время: " << (double)time/1000000 << " c." << endl;

	return (0);
}