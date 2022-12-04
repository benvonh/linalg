#include "../include/linalg.hpp"

int main()
{
    Matrix<2, 2, float> A{}, B{};

    A[0] = 2;
    A[2] = 3;

    std::cout << A << '\n';

    B = A;

    std::cout << B << '\n';

    auto C = B.Transpose();

    std::cout << C << '\n';

    auto D = A * C;

    std::cout << D << '\n';
}