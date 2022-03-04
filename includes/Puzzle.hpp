#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <tuple>
#include <algorithm>
#include <fstream>

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

#define LIMIT		300000
#define BEST		15

#define clear() printf("\033[H\033[J")

class Puzzle;

void	printf_(string str, string color);
void	printf_noendl_(string str, string color);

void	uniform_cost(Puzzle puzzle, int mod_print = 0);
void	uniform_cost_depth(Puzzle puzzle, int mod_print = 0);
void	greedy_search(Puzzle puzzle, int mod_print = 0);
int		heuristics_count(vector <vector <int> > &v, int mod);
void	heuristics(Puzzle puzzle, int mod, int mod_print = 0);

set< tuple<int, int, bool, bool> > const commands
{
	make_tuple(DOWN, UP, true, false),
	make_tuple(UP, DOWN, true, true),
	make_tuple(LEFT, RIGHT, false, true),
	make_tuple(RIGHT, LEFT, false, false)
};

class Puzzle {
	public:
		bool					validity;	// является ли головоломка валидной
		int						size;		// кол-во рядов/столбцов в головоломке
		int						distance;	// необходимое расстояние между элементами для корректного отображения в консоли
		vector< vector<int> >	box;		// двумерный массив для размещения элементов головоломки
		bool					answer;		// собрана головоломка или нет
		int						direction;	// направление прошлого движения пустого блока
		pair<int, int>			point;		// координаты пустого блока
		int						step;		// сколько шагов было сделано, что бы придти к этому варианту
		vector<int>				manual;		// порядок движений для сборки

		// Конструктор (1 аргумент - список чисел справа налево и сверху вниз)
		Puzzle(vector<int> v) {
			init(v);
		}
		// Конструктор (1 аргумент - имя файла сгенерированного npuzzle-gen.py, только СГЕНЕРИРОВАННЫХ!!!!)
		Puzzle(string name_file) {
			ifstream	file(name_file);
			string		str;
			int			count, temp;
			vector<int>	v;

			if (file.is_open()) {
				getline(file, str);
				file >> count;
				count *= count;
				for (int i = 0; i < count; i++) {
					file >> temp;
					v.push_back(temp);
				}
				file.close();
				init(v);
			}
			else
				printf_("Не могу открыть файл", RED);
		}
		// Печать головоломки на экран (если 1 аргумент true - то выведется порядок движений для решения головоломкм)
		void			print(int mod_print = 0) const{
			if (!validity) {
				printf_("Головоломка не валидна", RED);
				return ;
			}
			cout << "Кол-во рядов/столбцов: " << size << endl;
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

			cout << "Всего передвижений: " << step << endl;
			print_manual(mod_print);
			answer ? printf_("Головоломка решена", GREEN) : printf_("Головоломка не решена", RED);
		}
		// Передвинуть пустой в нужном направлении (внимание, функция небезопасна, не всегда можно передвинуть!!!)
		void			swapBlock(int dir) {
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
			step++;
			manual.push_back(dir);
		}
	
	private:
		// Начальная проверка всех условий
		void			init(vector<int> v) {
			int	temp = sqrt(v.size()), ind = 0;

			validity = false;
			direction = NO;
			step = 0;
			if (v.size() > 49) {
				printf_("Головоломка слишком велика =(", RED);
				return ;
			}
			if (v.size() <= 1) {
				printf_("Головоломка слишком мала =(", RED);
				return ;
			}
			if (sqrt(v.size()) == temp) {	// опасное место, но в нашем случае должно быть всё хорошо(но это не точно)
				size = temp;
				distance = log10(v.size()) + 2;
				box.resize(size);
				for (int i = 0; i < size; i++)
					for (int j = 0; j < size; j++)
						box[i].push_back(v[ind++]);
				point = find();
				if (validity_numbers(v))
					validity = check_decision(v);
				answer = check();
			}
			else {
				printf_("Вы подали неверное кол-во элементов в векторе =(", RED);
				validity = false;
				size = -1;
				distance = -1;
				answer = false;
				point = make_pair(-1, -1);
			}
		}
		// Проверка валидности поданых чисел
		bool			validity_numbers(vector<int> v) const {
			int	count = 0, end = size * size;

			sort(v.begin(), v.end());
			for (int i = 0; i < end; i++)
				if (v[i] != count++)
					return (false);
			return (true);
		}
		// Проверка решена ли головоломка
		bool			check() const {
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
		// Проверка, можно ли сложить данную головоломку (от этот блок ещё стоит проверить, но вроед ок)
		bool			check_decision(vector<int> v) const {
			int				len = size * size, count = 0;

			for (int i = 0; i < len-1; i++)
				for (int j = i+1; j < len; j++)
					if (v[i] && v[j] && v[i] > v[j])
						count++;
			// Если головоломка чётная (https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/)
			if (size % 2 == 0) {
				for (int i = size - 1; i >= 0; i--)
					for (int j = size - 1; j >= 0; j--)
						if (box[i][j] == 0)
							return ((size - i) & 1 ? !(count & 1) : (count & 1));
			}
			return (count % 2 == 0);
		}
		// Поиск координат пустого блока
		pair<int, int>	find() const {
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					if (box[i][j] == 0)
						return (make_pair(i, j));
			return (make_pair(-1, -1));
		}
		// Печать ходов передвижения пустого блока
		void			print_manual(int mod_print) const {
			if (mod_print == 0)
				return ;
			if (mod_print == 1) {
				for (int i = 0; i < step; i++) {
					cout << setw(direction) << i+1 << ") ";
					if (manual[i] == UP)
						cout << "вверх" << endl;
					else if (manual[i] == DOWN)
						cout << "вниз" << endl;
					else if (manual[i] == RIGHT)
						cout << "вправо" << endl;
					else if (manual[i] == LEFT)
						cout << "влево" << endl;
					else
						cout << "нет" << endl;
				}
				//================== Здесь нужно восстановить всю последовательность решения головоломки ======================
				vector <vector< vector<int> > > mac;
				mac.resize(step);
				vector< vector<int> >	temp = box;
				pair<int, int>			point_temp = point;

				for (int i = step - 1; i>= 0; i--) {
					if (manual[i] == DOWN)
						swap(temp[point_temp.first][point_temp.second], temp[--point_temp.first][point_temp.second]);
					else if (manual[i] == UP)
						swap(temp[point_temp.first][point_temp.second], temp[++point_temp.first][point_temp.second]);
					else if (manual[i] == LEFT)
						swap(temp[point_temp.first][point_temp.second], temp[point_temp.first][++point_temp.second]);
					else if (manual[i] == RIGHT)
						swap(temp[point_temp.first][point_temp.second], temp[point_temp.first][--point_temp.second]);
					mac[i] = temp;
				}
				// напечатаем все шаги
				for (int k = 0; k < step; k++) {
					cout << "=========== " << setw(distance) << k << " ===========" << endl;
					for (int i = 0; i < size; i++) {
						for (int j = 0; j < size; j++)
							cout << setw(distance) << mac[k][i][j];
						cout << endl;
					}
				}
				// напечатаем решённую головоломку
				cout << "=========== " << setw(distance) << step << " ===========" << endl;
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < size; j++)
						cout << setw(distance) << box[i][j];
					cout << endl;
				}
			}
		}
};
