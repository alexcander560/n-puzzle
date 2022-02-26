#include "Puzzle.hpp"

//=================================================================================
// Считает значение для эвристика "Манхэттеновское расстояние"
int		manhattan_distance(vector <vector <int> > &v) {
	int res = 0, size = v.size();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (v[i][j] != 0) {
				//cout << v[i][j] << " ( " << (v[i][j]-1)/size << " " << (v[i][j]-1)%size << " ) ";
				//cout << abs(i - ((v[i][j]-1)/size)) + abs(j - ((v[i][j]-1)%size)) << endl;
				res += abs(i - ((v[i][j]-1)/size)) + abs(j - ((v[i][j]-1)%size));
			}
		}
	}
	//cout << res << endl;
	return (res);
}
//=================================================================================
//=================================================================================
// Считает значение для эвристика "Линейные конфликты" (возможно здесь есть двойной счёт, но ёто не точно)
int		linear_conflicts(vector <vector <int> > &v) {
	int res = 0, size = v.size();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (v[i][j] == 0)
				continue ;

			for (int k = j + 1; k < size; k++) {
				if ((i == 2 && k == 2) || v[i][k] == 0)
					continue ;
				//cout << v[i][j] << " ? " << v[i][k] << endl;
				// Нужно проверить находятся ли они в своих строках
				if (((v[i][j] - 1) / size == i) && ((v[i][k]- 1) / size == i)) {
					if (v[i][j] > v[i][k])
						res += 2;
				}
			}
		}
	}
	//cout << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (v[i][j] == 0)
				continue ;
			
			for (int k = j + 1; k < size; k++) {
				if ((j == 2 && k == 2) || v[k][i] == 0)
					continue ;
				//cout << v[j][i] << " ? " << v[k][i] << endl;
				if (v[j][i] > v[k][i])
					res += 2;
			}
		}
	}
	
	return (res);
}
//=================================================================================
//=================================================================================
// Считает значение для эвристика "Угловые элементы"
int		corner_tiles(vector <vector <int> > &v) {
	int res = 0, size = v.size();

	if (v[0][0] != 0) {
		if ((0 != ((v[0][0]-1)/size)) || (0 != ((v[0][0]-1)%size))) {
			//cout << "Верхний левый угол" << endl;
			if (((0 == ((v[0][1]-1)/size)) && (1 == ((v[0][1]-1)%size))) || ((1 == ((v[1][0]-1)/size)) && (0 == ((v[1][0]-1)%size)))) {
				//cout << "Так: " << v[0][0] << endl;
				res += 2;
			}
		}
	}
	if (v[0][size-1] != 0) {
		if ((0 != ((v[0][size-1]-1)/size)) || (size-1 != ((v[0][size-1]-1)%size))) {
			//cout << "Верхний правый угол" << endl;
			if (((0 == ((v[0][size-2]-1)/size)) && (size-2 == ((v[0][size-2]-1)%size))) || ((1 == ((v[1][size-1]-1)/size)) && (size-1 == ((v[1][size-1]-1)%size)))) {
				//cout << "Так: " << v[0][size-1] << endl;
				res += 2;
			}
		}
	}
	if (v[size-1][0] != 0) {
		if ((size-1 != ((v[size-1][0]-1)/size)) || (0 != ((v[size-1][0]-1)%size))) {
			//cout << "Нижний левый угол" << endl;
			if (((size-1 == ((v[size-1][1]-1)/size)) && (1 == ((v[size-1][1]-1)%size))) || ((size-2 == ((v[size-2][0]-1)/size)) && (0 == ((v[size-2][0]-1)%size)))) {
				//cout << "Так: " << v[size-1][0] << endl;
				res += 2;
			}
		}
		
	}
	//cout << "res= " << res << endl;
	return (res);
}
//=================================================================================
//=================================================================================
// При использовании "Линейные конфликты" и "Угловые элементы" вместе происходит двойной счёт, поэтму надо пиcать отдельную функцию
int		linear_conflicts_and_corner_tiles(vector <vector <int> > &v) {
	int		res = 0, size = v.size();
	bool	up_left = false, up_right = false, down_left = false;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (v[i][j] == 0)
				continue ;

			for (int k = j + 1; k < size; k++) {
				if ((i == 2 && k == 2) || v[i][k] == 0)
					continue ;
				//cout << v[i][j] << " ? " << v[i][k] << endl;
				//if (((v[i][j] - 1) / size == i) && ((v[i][k]- 1) / size == i)) {
					if (v[i][j] > v[i][k]) {
						if (i == 0 && j == 0)
							up_left = true;
						if (i == 0 && k == size-1)
							up_right = true;
						if (i == size-1 && j == 0)
							down_left = true;
						res += 2;
					}
				//}
			}
		}
	}
	//cout << "-------------" << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (v[i][j] == 0)
				continue ;
			
			for (int k = j + 1; k < size; k++) {
				if ((j == 2 && k == 2) || v[k][i] == 0)
					continue ;
				//cout << v[j][i] << " ? " << v[k][i] /*<< " j= " << j << " i= " << i << " k= " << k */ << endl;
				if (v[j][i] > v[k][i]) {
					//cout << "Hello\n";
					if (i == 0 && j == 0)
						up_left = true;
					if (i == size - 1 && j == 0)
						up_right = true;
					if (k == size - 1 && i == 0)
						down_left = true;
					res += 2;
				}
			}
		}
	}
	// cout << "up_left= " << up_left << endl;
	// cout << "up_right= " << up_right << endl;
	// cout << "down_left= " << down_left << endl;
	//=========================================================================================
	if (up_left && v[0][0] != 0) {
		if ((0 != ((v[0][0]-1)/size)) || (0 != ((v[0][0]-1)%size))) {
			//cout << "Верхний левый угол" << endl;
			if (((0 == ((v[0][1]-1)/size)) && (1 == ((v[0][1]-1)%size))) || ((1 == ((v[1][0]-1)/size)) && (0 == ((v[1][0]-1)%size)))) {
				//cout << "Так: " << v[0][0] << endl;
				res += 2;
			}
		}
	}
	if (up_right && v[0][size-1] != 0) {
		if ((0 != ((v[0][size-1]-1)/size)) || (size-1 != ((v[0][size-1]-1)%size))) {
			//cout << "Верхний правый угол" << endl;
			if (((0 == ((v[0][size-2]-1)/size)) && (size-2 == ((v[0][size-2]-1)%size))) || ((1 == ((v[1][size-1]-1)/size)) && (size-1 == ((v[1][size-1]-1)%size)))) {
				//cout << "Так: " << v[0][size-1] << endl;
				res += 2;
			}
		}
	}
	if (down_left && v[size-1][0] != 0) {
		if ((size-1 != ((v[size-1][0]-1)/size)) || (0 != ((v[size-1][0]-1)%size))) {
			//cout << "Нижний левый угол" << endl;
			if (((size-1 == ((v[size-1][1]-1)/size)) && (1 == ((v[size-1][1]-1)%size))) || ((size-2 == ((v[size-2][0]-1)/size)) && (0 == ((v[size-2][0]-1)%size)))) {
				//cout << "Так: " << v[size-1][0] << endl;
				res += 2;
			}
		}
		
	}
	//cout << "res= " << res << endl;
	return (res);
}
//=================================================================================
//=================================================================================
// Считает значение для эвристика "Последний ход"
int		last_move(vector <vector <int> > &v) {
	int res = 0, size = v.size(), a = size * size - 1, b = size * (size - 1), count = 0;

	if (v[size - 1][size - 1] != a && v[size - 1][size - 1] != b)
		res += 2;

	//cout << res << endl;
	return (res);
}
//=================================================================================
// Считает вес для головоломки с помощью эвристичесих функций
// 1 - "Манхэттеновское расстояние"
// 2 - "Линейные конфликты"
// 3 - "Угловые элементы"
// 4 - "Последнее перемещение"
// 5 - "Манхэттеновское расстояние" + "Линейные конфликты"
// 6 - "Манхэттеновское расстояние" + "Линейные конфликты" + "Угловые элементы"
// 7 - "Манхэттеновское расстояние" + "Линейные конфликты" + "Угловые элементы" + "Последнее перемещение"
int		heuristics_count(vector <vector <int> > &v, int mod) {
	int	res = 0;

	if (mod == 1)
		res = manhattan_distance(v);
	else if (mod == 2)
		res = linear_conflicts(v);
	else if (mod == 3)
		res = corner_tiles(v);
	else if (mod == 4)
		res = last_move(v);
	else if (mod == 5)
		res = manhattan_distance(v) + linear_conflicts(v);
	else if (mod == 6)
		res = manhattan_distance(v) + corner_tiles(v);
	else if (mod == 7)
		res = manhattan_distance(v) + last_move(v);
	else if (mod == 8)
		res = manhattan_distance(v) + corner_tiles(v);
	else if (mod == 9)
		res = linear_conflicts_and_corner_tiles(v);
	else if (mod == 10)
		res = corner_tiles(v) + last_move(v);
	else if (mod == 11)
		res = manhattan_distance(v) + linear_conflicts_and_corner_tiles(v);
	else if (mod == 12)
		res = manhattan_distance(v) + linear_conflicts(v) + last_move(v);
	else if (mod == 13)
		res = manhattan_distance(v) + corner_tiles(v) + last_move(v);
	else if (mod == 14)
		res = linear_conflicts_and_corner_tiles(v) + last_move(v);
	else if (mod == 15)
		res = manhattan_distance(v) + linear_conflicts_and_corner_tiles(v) + last_move(v);

	return (res);
}
//=================================================================================
//=================================================================================
// Метод, использующий эвристику
void	heuristics(Puzzle puzzle, int mod, int mod_print = 0) {
	multimap<int, Puzzle>			q;			// очередь из вариантов головоломок, требующих рассмотрения
	set<vector<vector <int> > >	visited;		// множество уже рассмотренных вариантов
	bool							flag = true, lim = false;
	int								step = 0, size = puzzle.size - 1, max_size_q = 0;
	Puzzle							res = puzzle;

	if (!puzzle.validity) {
		printf_("Головоломка не валидна", YELLOW);
		return ;
	}
	if (puzzle.answer) {
		printf_("Головоломка уже решена", YELLOW);
		return ;
	}

	q.insert(make_pair(linear_conflicts(puzzle.box), puzzle));
	visited.insert(puzzle.box);

	while (flag) {
		multimap<int, Puzzle>::iterator it = q.begin();

		//cout << "step= " << step << endl;
		if (it->second.direction != DOWN && it->second.point.first != 0) {
			Puzzle	temp = it->second;

			step++;
			temp.swapBlock(UP);
			if (visited.insert(temp.box).second)
				q.insert(make_pair(heuristics_count(temp.box, mod), temp));
			if (temp.answer) {
				res = temp;
				break ;
			}
		}
		if (it->second.direction != UP && it->second.point.first != size) {
			Puzzle	temp = it->second;

			step++;
			temp.swapBlock(DOWN);
			if (visited.insert(temp.box).second)
				q.insert(make_pair(heuristics_count(temp.box, mod), temp));
			if (temp.answer) {
				res = temp;
				break ;
			}
		}
		if (it->second.direction != LEFT && it->second.point.second != size) {
			Puzzle	temp = it->second;

			step++;
			temp.swapBlock(RIGHT);
			if (visited.insert(temp.box).second)
				q.insert(make_pair(heuristics_count(temp.box, mod), temp));
			if (temp.answer) {
				res = temp;
				break ;
			}
		}
		if (it->second.direction != RIGHT && it->second.point.second != 0) {
			Puzzle	temp = it->second;

			step++;
			temp.swapBlock(LEFT);
			if (visited.insert(temp.box).second)
				q.insert(make_pair(heuristics_count(temp.box, mod), temp));
			if (temp.answer) {
				res = temp;
				break ;
			}
		}
		q.erase(it);
		if (q.size() == 0)
			flag = false;
		if (step >= LIMIT) {
			lim = true;
			break ;
		}
		if (q.size() > max_size_q)
			max_size_q = q.size();
	}
	int	count_elem = q.size() - (q.size() ? 1 : 0);

	if (!flag)
		printf_("Перебраны все варианты, но головоломка не решена", YELLOW);
	if (lim)
		printf_("Алгоритм сделал " + to_string(LIMIT) + " шагов, но не пришёл к решению, стоит выбрать другой метод =(", YELLOW);
	if (q.size() != 0)
		res.print(mod_print);	// должна быть решённая головоломка
	cout << "Элементов в очереди: " << count_elem << endl;
	cout << "Максимальное кол-во элементов в очереди: " << ((max_size_q > count_elem) ? max_size_q : count_elem) << endl;
	cout << "Рассмотренных головоломок: " << visited.size() << endl;
	cout << "Шагов: " << step << endl;
}
//=================================================================================
//=================================================================================
// Метод решения обходом в ширину (все узлы имеют одинаковый вес и равноценны между собой)
void	uniform_cost(Puzzle puzzle, int mod_print = 0) {
	queue<Puzzle>					q;			// очередь из вариантов головоломок, требующих рассмотрения
	set<vector <vector <int> > >	visited;	// множество уже рассмотренных вариантов
	bool							flag = true, lim = false;
	int								step = 0, max_size_q = 0;

	if (!puzzle.validity) {
		printf_("Головоломка не валидна", YELLOW);
		return ;
	}
	if (puzzle.answer) {
		printf_("Головоломка уже решена", YELLOW);
		return ;
	}

	q.push(puzzle);
	visited.insert(puzzle.box);

	while (flag) {
		//cout << "step= " << step << endl;
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
		if (q.size() == 0)
			flag = false;
		if (step >= LIMIT) {
			lim = true;
			break ;
		}
	}
	int	count_elem = q.size() - (q.size() ? 1 : 0);
	
	if (!flag)
		printf_("Перебраны все варианты, но головоломка не решена", YELLOW);
	if (lim)
		printf_("Алгоритм сделал " + to_string(LIMIT) + " шагов, но не пришёл к решению, стоит выбрать другой метод =(", YELLOW);
	if (q.size() != 0)
		q.back().print(mod_print);	// должна быть решённая головоломка
	cout << "Элементов в очереди: " << count_elem << endl;
	cout << "Максимальное кол-во элементов в очереди: " << ((max_size_q > count_elem) ? max_size_q : count_elem) << endl;
	cout << "Рассмотренных головоломок: " << visited.size() << endl;
	cout << "Шагов: " << step << endl;
}
//=================================================================================
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
		if (number < min_num)
		{
			printf_("Значение слишком маленькое. Выход из программы = (", RED);
			exit(EXIT_FAILURE);
		}
		if (number > max_num)
		{
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
	int map_size;
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
	else
	{
		printf_("Введено некорректное значение. Выход из программы = (", RED);
		exit(EXIT_FAILURE);
	}

//	for (int i : numbers)
//		cout << i << " ";
//	cout << endl;


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


	if (from_file)
		test_start(filename, get_number());
	else
		test_start(numbers, get_number());

}
//=================================================================================
//=================================================================================
int main() {
	// https://metaschool.ru/pub/games/puzzle15/puzzle15.php	// отсюда можно взять головоломки
	vector<int> numbers1 = {3, 8, 5, 2, 7, 6, 4, 1};		// не валидна
	vector<int> numbers2 = {3, 8, 5, 2, 7, 6, 4, 1, 0};	// 102.851 шагов
	vector<int> numbers3 = {8, 2, 6, 7, 4, 5, 1, 3, 0};	// 234.069 шагов
	vector<int> numbers4 = {2, 1, 8, 5, 3, 6, 7, 4, 0};	// 102.552 шагов
	vector<int> numbers5 = {1, 2, 3, 4, 5, 6, 0, 7, 8};	// 6 шагов
	vector<int> numbers6 = {1, 2, 3, 4, 5, 6, 7, 0, 8};	// 2 шага
	vector<int> numbers7 = {1, 2, 3, 4, 5, 6, 7, 8, 0};	// уже решена
	vector<int> numbers8 = {1, 2, 3, 4, 5, 6, 8, 7, 0};	// нельзя решить
	vector<int> numbers9 = {7, 0, 5, 8, 6, 3, 2, 1, 4};	// 232.918 шагов
	vector<int> numbers10 = {7, 0, 5, 8, 6, 3, 2, 1, 100};	// не валидна (не все числа нужные)
	vector<int> numbers11 = {4, 6, 8, 2, 7, 5, 1, 3, 0};	// 168.748 шагов
	vector<int> numbers12 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
	vector<int> numbers13 = {12, 5, 15, 11, 6, 14, 10, 13, 4, 9, 8, 3, 2, 1, 7, 0};
	vector<int> numbers14 = {3, 7, 11, 15, 2, 13, 9, 4, 5, 14, 6, 0, 8, 1, 10, 12}; // не валидна
	vector<int> numbers15 = {1, 4, 15, 5, 11, 8, 12, 6, 14, 2, 10, 7, 13, 9, 3, 0};

	// test(numbers1);
	// test(numbers2);
	// test(numbers3);
	// test(numbers4);
	// test(numbers5);
	// test(numbers6);
	// test(numbers7);
	// test(numbers8);
	 //test(numbers9);
	// test(numbers10);
	//test_start(numbers11, -1);   //======================

	// test(numbers12);
	// test(numbers13);
	//test(numbers14);
	//test(numbers15);

	//test("test.txt");		// тест из файла
	test_user();			// тест дружелюбным интерфейсом
	//heuristics(numbers6, 7);

	//=========================================================================
	// Тесты для проверки корректного просчёта эвристической функции (удалить в конце)
	//=========================================================================
	// vector< vector <int> > v;
	// v.resize(3);
	// v[0].push_back(1);
	// v[0].push_back(2);
	// v[0].push_back(3);
	// v[1].push_back(4);
	// v[1].push_back(5);
	// v[1].push_back(6);
	// v[2].push_back(7);
	// v[2].push_back(8);
	// v[2].push_back(0);
	// linear_conflicts_and_corner_tiles(v);
	// linear_conflicts(v);
	//last_move(v);

	return (0);
}
