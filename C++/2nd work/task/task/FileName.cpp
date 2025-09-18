#include <iostream>
#include <vector>
int main() {
    std::cout << "Write coordinats\n";
    std::cout << "Triangle N1:\n";
    std::vector<double> triangleN1;
    int a = 0;
    triangleN1.reserve(6);
    std::cout << "X1:";
    std::cin >> a;
    triangleN1.push_back(a);
    std::cout << "Y1:";
    std::cin >> a;
    triangleN1.push_back(a);
    std::cout << "X2:";
    std::cin >> a;
    triangleN1.push_back(a);
    std::cout << "Y2:";
    std::cin >> a;
    triangleN1.push_back(a);
    std::cout << "X3:";
    std::cin >> a;
    triangleN1.push_back(a);
    std::cout << "Y3:";
    std::cin >> a;
    triangleN1.push_back(a);
    for (auto i : triangleN1) {
        std::cout << i << " ";
    }
    return 0;
}