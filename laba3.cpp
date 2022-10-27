#include <iostream>

using namespace std;

// ôóíêöèÿ èçìåíÿåò ìàòðèöó tmpMatrix ïîíèæàÿ ïîðÿäîê ìàòðèöû íà îäèí îòíîñèòåëüíî îäíîãî èç ýëåìåíòîâ ïåðâîé ñòðîêè originalMatrixRow
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

// Ôóíêöèÿ íåïîñðåäñòâåííî ïîäñ÷èòûâàåò îïðåäåëèòåëü ìàòðèöû n-ãî ïîðÿäêà
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
			// ñîçäàåì ìàòðèöó, â êîòîðîé áóäåò ñîäåðàæòüñÿ ìàòðèöà íà ïîðÿäîê íèæå
            int** tmpMatrix = new int* [size - 1];
            for (int r = 0; r < size - 1; r++) {
                tmpMatrix[r] = new int[size - 1];
            }

			
			subMatrix(matrix, tmpMatrix, size, i);

			// âîò òóò ðåêóðñèÿ 
            determinant += sign * matrix[0][i] * matrixDeterminant(tmpMatrix, size - 1);
            sign = -sign;

			// íó è ïàìÿòü íå çàáûâàåì î÷èùàòü
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
	// ââîäèì äëèíó
	unsigned int size;
	cin >> size;

	// äèí ìàòðèöà
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

	// è ïàìÿòü î÷èùàåì
	for (int i = 0; i < size; ++i)
		delete[] matrix[i];
	delete[] matrix;

	return 0;
}
