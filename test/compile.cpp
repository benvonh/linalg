#include "../include/linalg.hpp"

int main()
{
    Matrix<3, 3> A = Matrix<3, 3>::Eye();

    Matrix<3, 3> B{};
    B(1, 1) = 99;

    std::cout << A * B;
    std::cout << (A + B).GetRows() << '\n';

    A = B;
    std::cout << A * B;
    std::cout << (A + B).GetRows() << '\n';
}