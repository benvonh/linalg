#include "linalg/linalg.hpp"

#include <iostream>

using namespace linalg;

int main()
{
  Matrix<2, 2> a{ 1.5, 0, 0, 1 };
  Matrix<2, 2> b{ 1, 2.5, 3, 4 };

  auto c = a * b;

  std::cout << a << "x\n" << b << "=\n" << c << std::endl;
}