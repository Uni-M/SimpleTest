#include "task_6.h"

Figure current;

/*
* ������ 6
* �������� �������� ����, �������������� ���� ��� ���� � ������ ��������� 20 �� 10 ����� ���������� ����.
* ��� ���������� � ��������� ������, �������� � �������� � ������, ����������� ������� � �����������,
* ����� ������ ��������������� �� ������� ����.
*/
int main()
{
	srand(time(NULL));
	hidecursor();

	int score = 0;
	bool in_game = true;
	bool** field = InitField();

	const Figure FIGURES[] = {
		{ initFigure((int*)g0, 2, 4), 2, 4},
		{ initFigure((int*)g1, 2, 4), 2, 4},
		{ initFigure((int*)g2, 2, 4), 2, 4},
		{ initFigure((int*)g3, 2, 4), 2, 4},
		{ initFigure((int*)g4, 2, 4), 2, 4},
		{ initFigure((int*)g5, 2, 4), 2, 4},
		{ initFigure((int*)g6, 2, 4), 2, 4}
	};

	GenerateRandomFigure(FIGURES);


	while (in_game)
	{
		printf("=========================================\n");
		printf("                  TETRIS                 \n");
		printf("             SCORE........%d\n", score);
		printf("=========================================\n");

		PrintField(field);

		char c = (_kbhit()) ? _getch() : -1;
		switch (c)
		{
		case KEY_MOVE_LEFT:			ShiftLeft(field);		break;
		case KEY_MOVE_RIGHT:		ShiftRight(field);		break;
		case KEY_MOVE_DOWN:			ShiftDown(field);		break;
		case KEY_ROTATE:			Rotate(field);			break;
		case KEY_QUIT:				in_game = false;		break;
		default:					ShiftDown(field);		break;
		}

		if (IsFixed(field) == 0)
		{
			score += CheckLine(field);
			GenerateRandomFigure(FIGURES);

			if (GameOver(field) == 1) {
				in_game = false;
				DeleteFigures(FIGURES);
			}
		}

		Sleep(500);
		setcur(0, 0);
	}
}



int** initFigure(int* arr, size_t columns_count, size_t rows_count)
{
	{
		int** a = (int**)malloc(rows_count * sizeof(int*));
		for (int i = 0; i < rows_count; ++i)
		{
			a[i] = (int*)malloc(columns_count * sizeof(int));
			for (int j = 0; j < columns_count; ++j)
			{
				a[i][j] = *(arr + i * columns_count + j);
			}
		}
		return a;
	}

}

bool** InitField()
{
	bool** field = (bool**)calloc(FIELD_ROWS, sizeof(bool*));

	for (int i = 0; i < FIELD_ROWS; ++i)
	{
		field[i] = (bool*)calloc(FIELD_COLUMNS, sizeof(bool));
	}
	return field;
}

void GenerateRandomFigure(Figure FIGURES[])
{
	Figure random_figure = FIGURES[rand() % amount_of_figures];
	Figure new_figure = random_figure;
	int k = ((FIELD_COLUMNS - 1) / 2);

	new_figure.data = (int**)malloc(new_figure.rows_count * sizeof(int*));
	for (int i = 0; i < new_figure.rows_count; ++i) {

		new_figure.data[i] = (int*)malloc(new_figure.columns_count * sizeof(int));

		new_figure.data[i][0] = random_figure.data[i][0] + k;
		new_figure.data[i][1] = random_figure.data[i][1];

	}

	DeleteFigure(current);
	current = new_figure;
}

void PrintField(bool** field)
{
	int** arr = current.data;
	size_t h = current.rows_count;

	for (int i = 0, n = 0; i < FIELD_ROWS; ++i)
	{
		for (int j = 0; j < FIELD_COLUMNS; ++j)
		{
			int fig = 0;
			for (int k = 0; k < h; k++)
			{
				if (arr[k][1] == i && arr[k][0] == j)
				{
					fig = 1;
				}
			}

			if (fig == 1 || field[i][j] != 0)
			{
				printf("# ");
			}
			else
			{
				printf("- ");
			}
		}

		AddInfo(i);
		printf("\n");
	}

}

void AddInfo(int i)
{
	switch (i)
	{
	case 0:		printf("\tcontrol keys:");							break;

	case 2:		printf("\tmove left.......%c", KEY_MOVE_LEFT);		break;
	case 3:		printf("\tmove right......%c", KEY_MOVE_RIGHT);		break;
	case 4:		printf("\tmove down.......%c", KEY_MOVE_DOWN);		break;
	case 5:		printf("\trotate..........%c", KEY_ROTATE);			break;
	case 6:		printf("\tquit............%c", KEY_QUIT);			break;
	}
}

Figure CopyFigure(Figure figure) {

	Figure new_figure = figure;

	new_figure.data = (int**)malloc(new_figure.rows_count * sizeof(int*));
	for (int i = 0; i < new_figure.rows_count; ++i) {
		new_figure.data[i] = (int*)malloc(new_figure.columns_count * sizeof(int));
		for (int j = 0; j < new_figure.columns_count; j++) {
			new_figure.data[i][j] = figure.data[i][j];
		}
	}
	return new_figure;
}

void DeleteFigure(Figure f) {

	for (int i = 0; i < f.rows_count; ++i) {
		free(f.data[i]);
	}
	free(f.data);
}

void Rotate(bool** field)
{
	Figure current_copy = CopyFigure(current);

	double angle = 90;
	const double g2r = M_PI / 180.;
	angle *= g2r;

	int k_x = 0, k_y = 0;
	for (int i = 0; i < current.rows_count; ++i)
	{
		double x_shifted = (double)current_copy.data[i][0] - current_copy.data[1][0];
		double y_shifted = (double)current_copy.data[i][1] - current_copy.data[1][1];

		int x = current_copy.data[1][0] + rint(x_shifted * cos(angle) - y_shifted * sin(angle));
		int y = current_copy.data[1][1] + rint(x_shifted * sin(angle) + y_shifted * cos(angle));

		if (x < 0 && k_x > x) k_x = -x;
		if (y < 0 && k_y > y) k_y = -y;
		if (x >= FIELD_COLUMNS && k_x < x)  k_x = x - FIELD_COLUMNS - 1;
		if (y >= FIELD_ROWS && k_y < y)  k_y = x - FIELD_ROWS - 1;

		current.data[i][0] = x;
		current.data[i][1] = y;
	}

	for (int i = 0; i < current.rows_count; i++)
	{
		current.data[i][0] += k_x;
		current.data[i][1] += k_y;
	}

	DeleteFigure(current_copy);
}

void ShiftLeft(bool** field)
{
	for (int i = 0; i < current.rows_count; ++i)
	{
		if (current.data[i][0] == 0 || field[current.data[i][1]][current.data[i][0] - 1] == 1) return;
	}

	for (int i = 0; i < current.rows_count; ++i)
	{
		--current.data[i][0];
	}
}

void ShiftRight(bool** field)
{
	for (int i = 0; i < current.rows_count; ++i)
	{
		if (current.data[i][0] == FIELD_COLUMNS - 1 || field[current.data[i][1]][current.data[i][0] + 1] == 1) return;
	}

	for (int i = 0; i < current.rows_count; ++i)
	{
		++current.data[i][0];
	}
}

void ShiftDown(bool** field)
{
	for (int i = 0; i < current.rows_count; ++i)
	{
		if (current.data[i][1] == FIELD_ROWS - 1 || field[current.data[i][1] + 1][current.data[i][0]] == 1) return;
	}

	for (int i = 0; i < current.rows_count; ++i)
	{
		++current.data[i][1];
	}

}

int IsFixed(bool** field)
{
	for (int i = 0; i < current.rows_count; ++i)
	{
		if (current.data[i][1] == FIELD_ROWS - 1 || field[current.data[i][1] + 1][current.data[i][0]] == 1)
		{
			for (int i = 0; i < current.rows_count; ++i)
			{
				field[current.data[i][1]][current.data[i][0]] = 1;
			}
			return 0;
		}
	}
	return 1;
}

int CheckLine(bool** field)
{
	int count_lines = 0;

	for (int i = 0; i < FIELD_ROWS; ++i)
	{
		int sumCells = 0;

		for (int j = 0; j < FIELD_COLUMNS; ++j)
		{
			if (field[i][j] == 1) ++sumCells;
		}

		if (sumCells == FIELD_COLUMNS)
		{
			ShiftDownLine(i, field);
			++count_lines;
		}

	}
	return CountScore(count_lines);
}

int CountScore(int count_lines)
{
	switch (count_lines)
	{
	case 1:			return 10;
	case 2:			return 25;
	case 3:			return 100;
	case 4:			return 250;
	}
}

void ShiftDownLine(int line, bool** field)
{
	for (int i = line; i > 0; --i)
	{
		for (int j = 0; j < FIELD_COLUMNS; ++j)
		{
			field[i][j] = field[i - 1][j];
		}
	}

	for (int l = 0; l < FIELD_COLUMNS; ++l)
	{
		field[0][l] = 0;
	}
}

int GameOver(bool** field)
{
	for (int i = 0; i < FIELD_COLUMNS; ++i)
	{
		for (int j = 0; j < current.columns_count; ++j)
		{
			if (field[0][i] == 1 && current.data[j][0] == i)
			{
				printf("=========================================\n");
				printf("=============== Game Over ===============\n");
				printf("=========================================\n");
				return 1;
			}
		}
	}
	return 0;
}

void DeleteFigures(Figure FIGURES[])
{
	for (int i = 0; i < amount_of_figures; i++)
	{
		DeleteFigure(FIGURES[i]);
	}
}

void setcur(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}