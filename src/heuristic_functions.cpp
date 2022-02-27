#include "../includes/Puzzle.hpp"

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
				//if (((v[j][i] - 1) % size == i) && ((v[k][i]- 1) % size == i)) {
					if (v[j][i] > v[k][i]) {
						//cout << v[j][i] << " ? " << v[k][i] << endl;
						res += 2;
					}
				//}
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
				if (((v[i][j] - 1) / size == i) && ((v[i][k]- 1) / size == i)) {
					if (v[i][j] > v[i][k]) {
						if (i == 0 && j == 0)
							up_left = true;
						if (i == 0 && k == size-1)
							up_right = true;
						if (i == size-1 && j == 0)
							down_left = true;
						res += 2;
					}
				}
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
//=================================================================================

vector< vector< function<int (vector <vector <int> > &v)> > > const functions
{
	{manhattan_distance},
	{linear_conflicts},
	{corner_tiles},
	{last_move},
	{manhattan_distance, linear_conflicts},
	{manhattan_distance, corner_tiles},
	{manhattan_distance, last_move},
	{manhattan_distance, corner_tiles},
	{linear_conflicts_and_corner_tiles},
	{corner_tiles, last_move},
	{manhattan_distance, linear_conflicts_and_corner_tiles},
	{manhattan_distance, linear_conflicts, last_move},
	{manhattan_distance, corner_tiles, last_move},
	{linear_conflicts_and_corner_tiles, last_move},
	{manhattan_distance, linear_conflicts_and_corner_tiles, last_move}
};

int		heuristics_count(vector <vector <int> > &v, int mod) {
	int	res = 0;

	for (auto functions_current : functions[mod - 1])
		res += functions_current(v);
	return (res);
}
//=================================================================================
