#include <iostream>
enum Mark
{
    BMW,
    Lada,
    Toyota,
    UAZ,
    GAZ
};
enum Colour
{
    White,
    Black,
    Red,
    Blue
};
struct Car 
{
    Mark C_Mark;
    Colour C_Colour;
    int Amount;
    double Price;
    bool Existence;
    bool Sale;
};

int main() {
    Car carlist[10] = {
        {BMW, Black, 100, 10000.0, true, false },
        {Lada, White, 500, 50000.0, false, false },
        {Toyota, Red, 600, 60000.0, true, true },
        {UAZ, Blue, 300, 70000.0, true, false },
        {GAZ, Black, 400, 80000.0, true, true },
        {BMW, Red, 700, 90000.0, false, false },
        {Lada, Blue, 800, 98000.0, true, false },
        {Toyota, Red, 500, 67000.0, true, true },
        {UAZ, Red, 100, 56000.0, true, false },
        {GAZ, Blue, 100, 45000.0, true, false },
    };
    Mark mark1;
    Colour colour1;
    std::cin >> mark1;
    std::cin >> colour1;
    std::cout << "Mark - " << mark1 << " Colour - " << colour1;
    return 0;
}
