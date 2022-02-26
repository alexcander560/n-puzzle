#include "../includes/Puzzle.hpp"

//=================================================================================
// Метод, использующий эвристику
void	heuristics(Puzzle puzzle, int mod, int mod_print) {
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

	q.insert(make_pair(heuristics_count(puzzle.box, mod), puzzle));
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
void	uniform_cost(Puzzle puzzle, int mod_print) {
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
