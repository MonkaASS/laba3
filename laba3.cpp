/* Тема: Функции

Вопросы:
1.	Функция.Функции в C++
2.	Процедура
3.	Подпрограмма
4.	Концептуализация кода и интерфейс функции
5.	Декомпозиция
6.	Сигнатура и прототип
7.	Вызов функции и оператор return
8.	Аргументы и параметры
9.	Аргументы по умолчанию
10.	Перегрузка функций
11.	Правила вызова перегруженной функции
12.	Рекурсия
13.	Область видимости переменной
14.	Время жизни переменной
15.	Static - переменная функции
16.	Препроцессор и директивы препроцессора*/

#include <iostream>

using namespace std;

// Определитель вычисляется рекурсией по первой строке следующим образом:
/*
| 1 2 3 |       | 5 6 |       | 4 6 |       | 4 5 |
| 4 5 6 | = 1 * | 8 9 | - 2 * | 7 9 | + 3 * | 7 8 |
| 7 8 9 |
*/
// и так матрица при порядке n > 2 с помощью рекурсии приходит к виду матрицы 2-ого порядка, где определитель
// вычисляется как произведение элементов главной диагонали минус произведение элементов побочной.

// функция изменяет матрицу tmpMatrix понижая порядок матрицы на один относительно одного из элементов первой строки originalMatrixRow
void subMatrix(int** matrix, int** tmpMatrix, unsigned int size, int originalMatrixRow) {
	int tmpMatrixRow = 0;
	int tmpMatrixCol = 0;
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (row != 0 && col != originalMatrixRow) {
				tmpMatrix[tmpMatrixRow][tmpMatrixCol] = matrix[row][col];
				tmpMatrixCol++;
			}
		}
		if (row != 0) {
			tmpMatrixRow++;
			tmpMatrixCol = 0;
		}
	}
}

// Функция непосредственно подсчитывает определитель матрицы n-го порядка
int matrixDeterminant(int** matrix, unsigned int size) {
    int determinant = 0;
    if (size == 1) {
        return matrix[0][0];
    }
	else if (size == 2) {
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	else if (size > 2) {
        int sign = 1;
        for (int i = 0; i < size; i++) {
			// создаем матрицу, в которой будет содеражться матрица на порядок ниже
            int** tmpMatrix = new int* [size - 1];
            for (int r = 0; r < size - 1; r++) {
                tmpMatrix[r] = new int[size - 1];
            }

			
			subMatrix(matrix, tmpMatrix, size, i);

			// вот тут рекурсия 
            determinant += sign * matrix[0][i] * matrixDeterminant(tmpMatrix, size - 1);
            sign = -sign;

			// ну и память не забываем очищать
			for (int r = 0; r < size - 1; r++) {
				delete[] tmpMatrix[r];
			}
			delete[] tmpMatrix;
        }
	}

    return determinant;
}

int main()
{
	// вводим длину
	unsigned int size;
	cin >> size;

	// дин матрица
	int** matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cin >> matrix[i][j];
		}
	}

	cout << matrixDeterminant(matrix, size);

	// и память очищаем
	for (int i = 0; i < size; ++i)
		delete[] matrix[i];
	delete[] matrix;

	return 0;
}
