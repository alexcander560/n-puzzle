#include "../includes/Puzzle.hpp"

// Запуск тестирование
template <typename T>
void	test_start(T numbers, int mod, int mod_print = 0) {
	Puzzle			puzzle(numbers);
	unsigned int	time;

	cout << "=====================================" << endl;
	cout << "=------------Тестируем--------------=" << endl;
	cout << "=====================================" << endl;
	puzzle.print();
	time = clock();
	//========================================================================================================
	if (mod == 0 || mod == -1) {
		printf_("-------------Обход в ширину(все узлы равны)-------------", BLUE);
		uniform_cost(puzzle, mod_print);
	} //============================Основные================================================================
	if (mod == 1 || mod == -1) {
		printf_("------Манхэттеновское расстояние-----", BLUE);
		heuristics(puzzle, 1, mod_print);
	}
	if (mod == 2 || mod == -1) {
		printf_("----------Линейный конфликт----------", BLUE);
		heuristics(puzzle, 2, mod_print);
	}
	if (mod == 3 || mod == -1) {
		printf_("------------Угловые элементы-------------", BLUE);
		heuristics(puzzle, 3, mod_print);
	}
	if (mod == 4 || mod == -1) {
		printf_("------------Последний ход-------------", BLUE);
		heuristics(puzzle, 4, mod_print);
	} //============================Манхэттеновское расстояние + ?================================================================
	if (mod == 5 || mod == -1) {
		printf_("Манхэттеновское расстояние + Линейный конфликт", BLUE);
		heuristics(puzzle, 5, mod_print);
	}
	if (mod == 6 || mod == -1) {
		printf_("Манхэттеновское расстояние + Угловые элементы", BLUE);
		heuristics(puzzle, 6, mod_print);
	}
	if (mod == 7 || mod == -1) {
		printf_("Манхэттеновское расстояние + Последний ход", BLUE);
		heuristics(puzzle, 7, mod_print);
	} //============================Линейный конфликт + ?================================================================
	if (mod == 8 || mod == -1) {
		printf_("Линейный конфликт + Угловые элементы", BLUE);
		heuristics(puzzle, 8, mod_print);
	}
	if (mod == 9 || mod == -1) {
		printf_("Линейный конфликт + Последний ход", BLUE);
		heuristics(puzzle, 9, mod_print);
	}
	if (mod == 10 || mod == -1) {
		printf_("Угловые элементы + Последний ход", BLUE);
		heuristics(puzzle, 10, mod_print);
	} //========================================================================================================
	if (mod == 11 || mod == -1) {
		printf_("Манхэттеновское расстояние + Линейный конфликт + Угловые элементы", BLUE);
		heuristics(puzzle, 11, mod_print);
	}
	if (mod == 12 || mod == -1) {
		printf_("Манхэттеновское расстояние + Линейный конфликт + Последний ход", BLUE);
		heuristics(puzzle, 12, mod_print);
	}
	if (mod == 13 || mod == -1) {
		printf_("Манхэттеновское расстояние + Угловые элементы + Последний ход", BLUE);
		heuristics(puzzle, 13, mod_print);
	} //========================================================================================================
	if (mod == 14 || mod == -1) {
		printf_("Линейный конфликт + Угловые элементы + Последний ход", BLUE);
		heuristics(puzzle, 14, mod_print);
	} //========================================================================================================
	if (mod == 15 || mod == -1) {
		printf_("Манхэттеновское расстояние + Линейный конфликт + Угловые элементы + Последний ход", BLUE);
		heuristics(puzzle, 15, mod_print);
	} //========================================================================================================
	time = clock() - time;
	cout << "Время: " << (double)time/1000000 << " c." << endl;
}
//=================================================================================
// Безопасно получить число из консоли
int get_number(int min_num = INT_MIN, int max_num = INT_MAX) {
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
string get_string(void) {
	string line;

	getline(cin, line);
	if (cin.eof())
		exit(EXIT_FAILURE);
	return (line);
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
	printf_("'0' - обход в ширину (все узлы равны)", YELLOW);
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
	mode = get_number();

	printf_("Хотите ли вы видеть процесс решения головоломки?", YELLOW);
	printf_("'0' - нет", YELLOW);
	printf_("'1' - да", YELLOW);
	mode_print = get_number();

	if (from_file)
		test_start(filename, mode, mode_print);
	else
		test_start(numbers, mode, mode_print);

}
//=================================================================================
// https://metaschool.ru/pub/games/puzzle15/puzzle15.php	// отсюда можно взять головоломки
//=================================================================================
int main() {
	test_user();			// тест дружелюбным интерфейсом

	return (0);
}
