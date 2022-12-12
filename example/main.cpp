#include "../linalg/linalg.hpp"

using namespace linalg;

int main()
{
    Matrix<2, 2> A;
    A[0] = 1;
    A[1] = 2;
    A[2] = 3;
    A[3] = 4;
    std::cout << A.Determinant() << '\n';
}
