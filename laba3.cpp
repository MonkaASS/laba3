#include <iostream>

using namespace std;

// функция изменяет матрицу tmpMatrix понижая порядок матрицы на один относительно одного из элементов первой строки originalMatrixCol
void subMatrix(int** matrix, int** tmpMatrix, unsigned int size, int originalMatrixCol) {
	int tmpMatrixRow = 0;
	int tmpMatrixCol = 0;
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (row != 0 && col != originalMatrixCol) {
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
			// чередуем знаки по первому столбцу
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
	setlocale(LC_ALL, "Russian");
	cout << "Введите размерность матрицы n * n (n > 0):" << endl;
	// вводим длину
	unsigned int size;
	cin >> size;

	// дин матрица
	int** matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
	}
	cout << "Введите значения матрицы:" << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cin >> matrix[i][j];
		}
	}

	cout << "Определитель = " << matrixDeterminant(matrix, size);

	// и память очищаем
	for (int i = 0; i < size; ++i)
		delete[] matrix[i];
	delete[] matrix;

	return 0;
}
