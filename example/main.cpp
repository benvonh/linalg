#include "../linalg/linalg.hpp"

using namespace linalg;

int main()
{
    Matrix<3, 3, long> A
    {
        1, 2, 3,
        4, 5, 6,
        7, 8, 0
    };

    auto lu = A.LU_Decomposition();
    std::cout << A << '\n';
    std::cout << lu.first << '\n';
    std::cout << lu.second << '\n';

    std::cout << "Soooo det: " << A.Determinant() << '\n';

    // std::cout << "Determinant of:\n" << A << " is " << A.LU_Decomposition().first << '\n';
    
    return 0;
}
