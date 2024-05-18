#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Matrix {
private:
    vector<vector<int>> data;
    int rows;
    int cols;

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        data.resize(rows, std::vector<int>(cols));
    }

    void setElement(int row, int col, int value) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            data[row][col] = value;
        }
    }

    int getElement(int row, int col) const {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return data[row][col];
        }
        return -1; 
    }

    int countColumnsWithZeros() const {
        int count = 0;
        for (int j = 0; j < cols; ++j) {
            for (int i = 0; i < rows; ++i) {
                if (data[i][j] == 0) {
                    ++count;
                    break;
                }
            }
        }
        return count;
    }

    int findRowWithLongestSeries() const {
        int maxRow = -1;
        int maxLength = 0;

        for (int i = 0; i < rows; ++i) {
            int currentLength = 1;
            int maxLengthForRow = 1;
            for (int j = 1; j < cols; ++j) {
                if (data[i][j] == data[i][j - 1]) {
                    ++currentLength;
                } else {
                    currentLength = 1;
                }
                if (currentLength > maxLengthForRow) {
                    maxLengthForRow = currentLength;
                }
            }
            if (maxLengthForRow > maxLength) {
                maxLength = maxLengthForRow;
                maxRow = i;
            }
        }
        return maxRow;
    }

    void sortMatrix() {
        for (int i = 0; i < rows; ++i) {
            vector<int> sameSeries;
            vector<int> differentSeries;
            map<int, int> frequency;
            for (int j = 0; j < cols; ++j) {
                ++frequency[data[i][j]];
            }
            for (const auto& elem : frequency) {
                if (elem.second > 1) {
                    for (int k = 0; k < elem.second; ++k) {
                        sameSeries.push_back(elem.first);
                    }
                } else {
                    differentSeries.push_back(elem.first);
                }
            }
            sameSeries.insert(sameSeries.end(), differentSeries.begin(), differentSeries.end());
            data[i] = sameSeries;
        }
    }

    void printMatrix() const {
        for (const auto& row : data) {
            for (const auto& elem : row) {
               cout << elem << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int rows = 4;
    int cols = 5;
    Matrix matrix(rows, cols);

    int values[4][5] = {
        {1, 2, 0, 4, 5},
        {6, 7, 8, 9, 10},
        {0, 0, 0, 0, 0},
        {11, 12, 13, 14, 15}
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix.setElement(i, j, values[i][j]);
        }
    }

    cout << "Matrix:" << endl;
    matrix.printMatrix();

    int columnsWithZeros = matrix.countColumnsWithZeros();
    cout << "Number of columns with at least one zero: " << columnsWithZeros << endl;

    int rowWithLongestSeries = matrix.findRowWithLongestSeries();
    cout << "Row with the longest series of identical elements: " << rowWithLongestSeries << endl;

    matrix.sortMatrix();
    cout << "Sorted Matrix:" << endl;
    matrix.printMatrix();

    return 0;
}
