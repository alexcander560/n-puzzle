#include "../includes/Puzzle.hpp"

void	printf_(string str, string color) { cout << color + str + DEFAULT"\n"; }
void	printf_noendl_(string str, string color) { cout << color + str + DEFAULT; }

void	timeSetting(unsigned int &time)
{
	time = clock() - time;
	cout << "Время: " << (double)time/1000000 << " c." << endl;
	time = clock();
}

// Запуск тестирование
template <typename T>
void	test_start(T numbers, int mod, int mod_print = 0) {
	Puzzle			puzzle(numbers);
	unsigned int	time;

	map<int, string> methods
	{
		{0, "-------------Все узлы равны-------------"},
		{1, "------Манхэттеновское расстояние-----"},
		{2, "----------Линейный конфликт----------"},
		{3, "------------Угловые элементы-------------"},
		{4, "------------Последний ход-------------"},
		{5, "Манхэттеновское расстояние + Линейный конфликт"},
		{6, "Манхэттеновское расстояние + Угловые элементы"},
		{7, "Манхэттеновское расстояние + Последний ход"},
		{8, "Линейный конфликт + Угловые элементы"},
		{9, "Линейный конфликт + Последний ход"},
		{10, "Угловые элементы + Последний ход"},
		{11, "Манхэттеновское расстояние + Линейный конфликт + Угловые элементы"},
		{12, "Манхэттеновское расстояние + Линейный конфликт + Последний ход"},
		{13, "Манхэттеновское расстояние + Угловые элементы + Последний ход"},
		{14, "Линейный конфликт + Угловые элементы + Последний ход"},
		{15, "Манхэттеновское расстояние + Линейный конфликт + Угловые элементы + Последний ход"}

	};

	cout << "=====================================" << endl;
	cout << "=------------Тестируем--------------=" << endl;
	cout << "=====================================" << endl;
	puzzle.print();
	time = clock();

	switch (mod) {
		case -1:
			for (int i = 1; i < 16; i++)
			{
				printf_(methods[i], BLUE);
				heuristics(puzzle, i, mod_print);
				timeSetting(time);
			}
		case 0:
			printf_(methods[0], BLUE);
			uniform_cost(puzzle, mod_print);
			timeSetting(time);
			break ;
		default:
			printf_(methods[mod], BLUE);
			heuristics(puzzle, mod, mod_print);
			timeSetting(time);
			break ;
	}

}
//=================================================================================
// Безопасно получить число из консоли
int	get_number(int min_num = INT_MIN, int max_num = INT_MAX) {
	int number;
	string line;

	getline(cin, line);
	if (cin.eof())
		exit(EXIT_FAILURE);
	try {
		number = stoi(line);
		if (number < min_num) {
			printf_("Значение слишком маленькое. Выход из программы = (", RED);
			exit(EXIT_FAILURE);
		}
		if (number > max_num) {
			printf_("Значение слишком большое. Выход из программы = (", RED);
			exit(EXIT_FAILURE);
		}
	} catch (exception &e) {
		printf_("Введено некорректное значение. Выход из программы = (", RED);
		exit(EXIT_FAILURE);
	}
	return (number);
}
//=================================================================================
// Безопасно получить строку из консоли
string	get_string(void) {
	string line;

	getline(cin, line);
	if (cin.eof())
		exit(EXIT_FAILURE);
	return (line);
}
// Проверить
bool	file_exists(const string &filename)
{
	bool	is_exists;

	ifstream	file(filename);
	is_exists = file.is_open();
	file.close();
	return (is_exists);
}
//=================================================================================
//=================================================================================
// Надо написать дружелюбный интерфейс для пользователя, что бы он мог запускать разные алгоритмы для решения задачи из файла
// ИЛИ мог ввести данные сам!!!
void	test_user() {
	int map_size, mode, mode_print;
	bool from_file;
	string line, filename;
	vector<int> numbers;

	printf_("Выбери режим для загрузки карты игры", YELLOW);
	printf_("'1' - чтение из файла", YELLOW);
	printf_("'2' - чтение из консоли", YELLOW);

	line = get_string();
	if (line == "1") {
		from_file = true;
		printf_("Введи путь до файла", YELLOW);
		filename = get_string();
		if (!file_exists(filename))
		{
			printf_("Невозможно открыть файл. Выход из программы = (", RED);
			exit(EXIT_FAILURE);
		}
	}
	else if (line == "2") {
		from_file = false;
		printf_("Введите размер карты", YELLOW);
		map_size = get_number(1, 10);
		numbers.resize(map_size * map_size);
		for (int i = 0; i < map_size * map_size; i++) {
			printf_noendl_("Введите число ", YELLOW);
			printf_noendl_(to_string(i + 1), YELLOW);
			printf_noendl_(" из ", YELLOW);
			printf_(to_string(map_size * map_size), YELLOW);
			numbers[i] = (get_number(0, 99));
		}
	}
	else {
		printf_("Введено некорректное значение. Выход из программы = (", RED);
		exit(EXIT_FAILURE);
	}

	printf_("Какую функцию вы хотите использовать?", YELLOW);
	printf_("'-1' - запустить все алгоритмы", YELLOW);
	printf_("'0' - узлы имеют одинаковый вес", YELLOW);
	printf_("'1' - манхэттеновское расстояние", YELLOW);
	printf_("'2' - линейный конфликт", YELLOW);
	printf_("'3' - угловые элементы", YELLOW);
	printf_("'4' - последний ход", YELLOW);
	printf_("'5' - манхэттеновское расстояние + линейный конфликт", YELLOW);
	printf_("'6' - манхэттеновское расстояние + угловые элементы", YELLOW);
	printf_("'7' - манхэттеновское расстояние + последний ход", YELLOW);
	printf_("'8' - линейный конфликт + угловые элементы", YELLOW);
	printf_("'9' - линейный конфликт + последний ход", YELLOW);
	printf_("'10' - угловые элементы + последний ход", YELLOW);
	printf_("'11' - манхэттеновское расстояние + линейный конфликт + угловые элементы", YELLOW);
	printf_("'12' - манхэттеновское расстояние + линейный конфликт + последний ход", YELLOW);
	printf_("'13' - манхэттеновское расстояние + угловые элементы + последний ход", YELLOW);
	printf_("'14' - линейный конфликт + угловые элементы + последний ход", YELLOW);
	printf_("'15' - манхэттеновское расстояние + линейный конфликт + угловые элементы + последний ход", YELLOW);
	mode = get_number(-1, 15);

	printf_("Хотите ли вы видеть процесс решения головоломки?", YELLOW);
	printf_("'0' - нет", YELLOW);
	printf_("'1' - да", YELLOW);
	mode_print = get_number(0, 1);

	if (from_file)
		test_start(filename, mode, mode_print);
	else
		test_start(numbers, mode, mode_print);

}
//=================================================================================
// https://metaschool.ru/pub/games/puzzle15/puzzle15.php	// отсюда можно взять головоломки
//=================================================================================
int		linear_conflicts(vector <vector <int> > &v);

int main() {
	test_user();			// тест дружелюбным интерфейсом

	// vector< vector <int> > v;
	// v.resize(3);
	// v[0].push_back(8); // 4
	// v[0].push_back(0);
	// v[0].push_back(0);

	// v[1].push_back(1);
	// v[1].push_back(0);
	// v[1].push_back(0);

	// v[2].push_back(0);
	// v[2].push_back(0);
	// v[2].push_back(0);

	// linear_conflicts(v);

	return (0);
}
