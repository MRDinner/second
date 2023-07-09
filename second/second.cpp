#include <bitset>
#include <iostream>
#include <math.h>

using namespace std;
#define N 5

template <std::size_t size>
void reverse(std::bitset<size>& b) {
    for (std::size_t i = 0; i < size / 2; ++i) {
        bool temp = b[i];
        b[i] = b[size - i - 1];
        b[size - i - 1] = temp;
    }
}

template <std::size_t size>
class LinearShiftRegister {
private:
    std::bitset<size> register_;

public:
    LinearShiftRegister(std::bitset<size> init) : register_(init) {}

    void shift() {
        bool xor_result = register_[0] ^ register_[2] ^ register_[3] ^ register_[4];
        register_ >>= 1;
        register_.set(size - 1, xor_result);
    }

    std::bitset<size> getRegister() const {
        return register_;
    }
};

void getMinorMatrix(bitset<N> matrix[N], bitset<N> minor[N], int row, int col, int n) {
    int minorRow = 0, minorCol = 0;
    for (int r = 0; r < n; r++) {
        if (r != row) {
            for (int c = 0; c < n; c++) {
                if (c != col) {
                    minor[minorRow][minorCol++] = matrix[r][c];
                }
            }
            minorRow++;
            minorCol = 0;
        }
    }
}

int determinant(bitset<N> matrix[N], int n) {
    int det = 0;
    bitset<5> submatrix[N];
    if (n == 2)
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    else {
        for (int x = 0; x < n; x++) {
            int subMatrixRow = 0, subMatrixCol = 0;
            for (int r = 1; r < n; r++) {
                for (int c = 0; c < n; c++) {
                    if (c != x) {
                        submatrix[subMatrixRow][subMatrixCol++] = matrix[r][c];
                    }
                }
                subMatrixRow++;
                subMatrixCol = 0;
            }
            det = det + (pow(-1, x) * matrix[0][x] * determinant(submatrix, n - 1));
        }
    }
    return det;
}

void getAdjointMatrix(bitset<N> matrix[N], bitset<N> adjoint[N]) {
    if (N == 1) {
        adjoint[0][0] = 1;
        return;
    }
    int s = 1;
    bitset<N> minor[N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            getMinorMatrix(matrix, minor, i, j, N);
            s = ((i + j) % 2 == 0) ? 1 : -1;
            adjoint[j][i] = (s) * (determinant(minor, N - 1));
        }
    }
}

bool inverse(bitset<N> matrix[N], bitset<N> inversed[N]) {
    int det = determinant(matrix, N);
    if (det == 0) {
        cout << "Unable to find the inverse matrix";
        return false;
    }
    bitset<N> adjoint[N];
    getAdjointMatrix(matrix, adjoint);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inversed[i][j] = adjoint[i][j] / float(det);
    return true;
}

bitset<N + 1> multiplyMatrix(bitset<N> mat1[N], bitset<5> mat2) {
    bitset<N + 1> answer;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 1; j++) {
            int result = 0;
            for (int k = 0; k < N; k++) {
                result += mat1[i][k] * mat2[k];
            }
            result %= 2;
            if (result)
                answer.set(i);
        }
    }
    return answer;
}

template <class T>
void print(T A[N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
}

int main(int argc, char const* argv[]) {

    

    bitset<10> output(210);
    cout << output << endl;

    bitset<5> results[5];
    bitset<5> result;
    for (int i = 5; i < output.size(); i++) {
        result[i - 5] = output[i];
        int diff = i - 5;
        for (int j = i - 5; j < i; j++)
            if (output[j])
                results[i - 5].set(j - diff);

        cout << result[i - 5] << " | " << results[i - 5] << endl;
    }

    bitset<N> inversed[N];
    inverse(results, inversed);

    bitset<N + 1> answer = multiplyMatrix(inversed, result);
    answer.set(answer.size() - 1);
    cout << "answer: " << answer << endl;

    return 0;
}
