#include "../linalg/linalg.hpp"

using namespace linalg;

int main()
{
    Matrix<4, 4> A
    {
        2, 4, 3, 5,
        -4, -7, -5, -8,
        6, 8, 2, 9,
        4, 9, -2, 14
    };

    auto lu = A.LU_Decomposition();
    std::cout << A << '\n';
    std::cout << lu.first << '\n';
    std::cout << lu.second << '\n';

    // std::cout << "Determinant of:\n" << A << " is " << A.LU_Decomposition().first << '\n';
    
    return 0;
}
