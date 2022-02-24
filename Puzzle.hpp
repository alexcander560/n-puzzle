#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
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

#define clear() printf("\033[H\033[J")

void	printf_(string str, string color) { cout << color + str + DEFAULT"\n"; }

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
		// Печать головоломки на экран (если 1 аргумент true - то выведется порядок движений для решения головоломкм)
		void			print(bool flag = false) const{
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
			if (flag)
				print_manual();
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
			int temp = sqrt(v.size()), ind = 0;

			validity = false;
			direction = NO;
			step = 0;
			if (v.size() > 100) {
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
					validity = check(v);
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
		bool			check(vector<int> v) const {
			int len = size * size, count = 0;

			for (int i = 0; i < len-1; i++)
				for (int j = i+1; j < len; j++)
					if (v[i] && v[j] && v[i] > v[j])
						count++;
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
		void			print_manual() const {
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
		}
};
