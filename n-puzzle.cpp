#include "Puzzle.hpp"

// Метод решения перебором
void	brute_force(Puzzle puzzle) {
	queue<Puzzle>					q;			// очередь из вариантов головоломок, требующих рассмотрения
	set<vector <vector <int> > >	visited;	// множество уже рассмотренных вариантов
	bool							flag = true;
	int								step = 0;

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
		if (q.size() == 0)
			flag = false;
	}
	if (!flag)
		printf_("Перебраны все варианты, но головоломка не решена", YELLOW);
	if (q.size() != 0)
		q.back().print();	// должна быть решённая головоломка
	cout << "Элементов в очереди: " << q.size() - (q.size() ? 1 : 0) << endl;
	cout << "Рассмотренных головоломок: " << visited.size() << endl;
	cout << "Шагов: " << step << endl;
}

// Тестирование методом перебора (данные берутся из вектора)
void	test(vector<int> numbers) {
	Puzzle			puzzle(numbers);
	unsigned int	time;

	cout << "=====================================" << endl;
	cout << "=------------Тестируем--------------=" << endl;
	cout << "=====================================" << endl;
	puzzle.print();
	time = clock();
	brute_force(puzzle);
	time = clock() - time;
	cout << "Время: " << (double)time/1000000 << " c." << endl;
}

// Тестирование методом перебора (данные берутся из файла)
void	test(string name_file) {
	Puzzle			puzzle(name_file);
	unsigned int	time;

	cout << "=====================================" << endl;
	cout << "=------------Тестируем--------------=" << endl;
	cout << "=====================================" << endl;
	puzzle.print();
	time = clock();
	brute_force(puzzle);
	time = clock() - time;
	cout << "Время: " << (double)time/1000000 << " c." << endl;
}

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
	vector<int> numbers11 = {7, 4, 0, 8, 6, 2, 1, 5, 3};	// 109406 шагов
	vector<int> numbers12 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

	// test(numbers1);
	// test(numbers2);
	// test(numbers3);
	// test(numbers4);
	// test(numbers5);
	// test(numbers6);
	// test(numbers7);
	// test(numbers8);
	// test(numbers9);
	// test(numbers10);
	// test(numbers11);
	// test(numbers12);

	test("test.txt");

	return (0);
}
