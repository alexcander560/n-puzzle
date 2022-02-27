#include "../includes/Puzzle.hpp"

class Cmp {
	public:
		int first;
		Puzzle second;

		Cmp(int first, Puzzle &second): first (first), second (second) {}

		bool operator< (Cmp const& other) const { return (first > other.first); }
		bool operator> (Cmp const& other) const { return (first < other.first); }
};

// std::hash<int> hasher;
// class HashVectors {
// public:
// 	size_t operator() (vector< vector<int> > const &containers) const { return (std::hash<char *>{}((char *)&containers)); }
// };

//=================================================================================
// Метод, использующий эвристику
void	heuristics(Puzzle puzzle, int mod, int mod_print) {
	priority_queue<Cmp, vector<Cmp>, std::less<Cmp> >	q;			// очередь из вариантов головоломок, требующих рассмотрения
	set<vector<vector <int> > >							visited;		// множество уже рассмотренных вариантов
	bool												check, flag = true, lim = false;
	int													step = 0, size = puzzle.size - 1, max_size_q = 0;
	Puzzle												res = puzzle;
	Cmp													it(heuristics_count(puzzle.box, mod), puzzle);

	if (!puzzle.validity) {
		printf_("Головоломка не валидна", YELLOW);
		return ;
	}
	if (puzzle.answer) {
		printf_("Головоломка уже решена", YELLOW);
		return ;
	}

	q.push(Cmp(heuristics_count(puzzle.box, mod), puzzle));
	visited.insert(puzzle.box);

	while (flag) {
		it = q.top();
		q.pop();

		//cout << "step= " << step << endl;
		for (auto command : commands) {
			check = (get<2>(command) ? it.second.point.first : it.second.point.second) != (get<3>(command) ? size : 0);
			if (it.second.direction != get<0>(command) && check) {
				Puzzle	temp = it.second;

				step++;
				temp.swapBlock(get<1>(command));
				if (visited.insert(temp.box).second)
					q.push(Cmp(heuristics_count(temp.box, mod), temp));
				if (temp.answer) {
					res = temp;
					flag = false;
					break ;
				}
			}
		}

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
// Метод решения, когда все узлы имеют одинаковый вес и равноценны между собой
void	uniform_cost(Puzzle puzzle, int mod_print) {
	queue<Puzzle>					q;			// очередь из вариантов головоломок, требующих рассмотрения
	set<vector <vector <int> > >	visited;	// множество уже рассмотренных вариантов
	bool							check, flag = true, lim = false;
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
		for (auto command : commands) {
			check = (get<2>(command) ? q.front().point.first : q.front().point.second) != (get<3>(command) ? q.front().size - 1 : 0);
			if (q.front().direction != get<0>(command) && check) {
				Puzzle	temp = q.front();

				step++;
				temp.swapBlock(get<1>(command));
				if (visited.insert(temp.box).second)
					q.push(temp);
				if (temp.answer) {
					flag = false;
					break ;
				}
			}
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
