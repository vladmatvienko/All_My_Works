#include <iostream>
#include <vector>
#include <cmath>


class bin_code
{
private:
    std::vector <int> bin_number;
    std::vector <int> one;
    bool sign = true;
    int depth;

public:
    bin_code(int num, int Bit_depth) {
        depth = Bit_depth;
        bin_number.resize(depth);
        one.resize(depth);
        one[depth - 1] = 1;
        transf_bin(num);
    }
    bin_code(int Bit_depth) {
        depth = Bit_depth;
        bin_number.resize(depth);
        one.resize(depth);
        one[depth - 1] = 1;
    }
    void transf_bin(int num) {
        int k = depth - 1;
        if (num < 0) {
            sign = false;
            num = num * -1;
            while (num != 0) {
                if (num % 2 == 0) {
                    bin_number[k] = 0;
                    num = num / 2;
                    k--;
                }
                if (num % 2 == 1) {
                    bin_number[k] = 1;
                    num = num / 2;
                    k--;
                }
            }
            for (int i = 0; i < bin_number.size(); i++) {
                if (bin_number[i] == 1) {
                    bin_number[i] = 0;
                }
                else if (bin_number[i] == 0) {
                    bin_number[i] = 1;
                }
            }
            bin_number = sum_one(bin_number);
        }

        else {
            while (num != 0) {
                if (num % 2 == 0) {
                    bin_number[k] = 0;
                    num = num / 2;
                    k--;
                }
                if (num % 2 == 1) {
                    bin_number[k] = 1;
                    num = num / 2;
                    k--;
                }
            }
        }
    }
    void sum(bin_code* num1, bin_code* num2) {

        int k = 0;
        std::vector<int> bin_number_1 = num1->bin_number;
        std::vector<int> bin_number_2 = num2->bin_number;
        std::vector <int> summator;
        summator.resize(depth + 1);
        for (int i = depth - 1; i >= 0; i--) {
            k = bin_number_1[i] + bin_number_2[i];
            if (k == 2) {
                summator[i - 1] = 1;
            }
        }
        k = 0;
        for (int i = depth - 1; i >= 0; i--) {
            k = bin_number_1[i] + bin_number_2[i] + summator[i];
            if (k == 0) {
                bin_number[i] = 0;
            }
            else if (k == 1) {
                bin_number[i] = 1;
            }
            else if (k == 2 && summator[i] == 1 && i != 0) {
                summator[i - 1] = 1;
                bin_number[i] = 0;
            }
            else if (k == 2 && summator[i] == 0) {
                bin_number[i] = 0;
            }
            else if (k == 3) {
                bin_number[i] = 1;
            }
            else {
                bin_number[i] = 0;
            }
        }
        if (summator[0] == 1 && bin_number_2[0] == 0) {
            throw 1;
        }
        std::cout << "Bin_Number_1: ";
        for (int i = 0; i < num1->bin_number.size(); i++) {
            std::cout << num1->bin_number[i];
        }
        std::cout << "\n";
        std::cout << "Bin_Number_2: ";
        for (int i = 0; i < num2->bin_number.size(); i++) {
            std::cout << num2->bin_number[i];
        }
        std::cout << "\n";
    }
    void sum_for_min(bin_code* num1, std::vector<int> num2) {

        int k = 0;
        std::vector<int> bin_number_1 = num1->bin_number;
        std::vector<int> bin_number_2 = num2;
        std::vector <int> summator;
        summator.resize(depth + 1);
        for (int i = depth - 1; i >= 0; i--) {
            k = bin_number_1[i] + bin_number_2[i];
            if (k == 2) {
                summator[i - 1] = 1;
            }
        }
        k = 0;
        for (int i = depth - 1; i >= 0; i--) {
            k = bin_number_1[i] + bin_number_2[i] + summator[i];
            if (k == 0) {
                bin_number[i] = 0;
            }
            else if (k == 1) {
                bin_number[i] = 1;
            }
            else if (k == 2 && summator[i] == 1 && i != 0) {
                summator[i - 1] = 1;
                bin_number[i] = 0;
            }
            else if (k == 2 && summator[i] == 0) {
                bin_number[i] = 0;
            }
            else if (k == 3) {
                bin_number[i] = 1;
            }
            else {
                bin_number[i] = 0;
            }
        }

    }
    std::vector<int> sum_one(std::vector<int> number_1) {
        int k = 0;
        std::vector<int> bin_number_1 = number_1;
        std::vector<int> bin_number_2 = one;
        std::vector<int> bin_number_answ;
        bin_number_answ.resize(depth);
        std::vector <int> summator;
        summator.resize(depth + 1);
        for (int i = depth - 1; i >= 0; i--) {
            k = bin_number_1[i] + bin_number_2[i];
            if (k == 2) {
                summator[i - 1] = 1;
            }
        }
        k = 0;
        for (int i = depth - 1; i >= 0; i--) {
            k = bin_number_1[i] + bin_number_2[i] + summator[i];
            if (k == 0) {
                bin_number_answ[i] = 0;
            }
            else if (k == 1) {
                bin_number_answ[i] = 1;
            }
            else if (k == 2 && summator[i] == 1) {
                summator[i - 1] = 1;
                bin_number_answ[i] = 0;
            }
            else if (k == 2 && summator[i] == 0) {
                bin_number_answ[i] = 0;
            }
            else if (k == 2 && summator[i] == 0) {
                bin_number_answ[i] = 0;
            }
            else if (k == 3) {
                bin_number_answ[i] = 1;
            }
        }
        return bin_number_answ;
    }

    void min(bin_code* num1, bin_code* num2) {
        std::vector<int> bin_number_2 = num2->bin_number;
        for (int i = 0; i < bin_number_2.size(); i++) {
            if (bin_number_2[i] == 1) {
                bin_number_2[i] = 0;
            }
            else if (bin_number_2[i] == 0) {
                bin_number_2[i] = 1;
            }
        }

        bin_number_2 = sum_one(bin_number_2);
        if (bin_number_2[0] == 1) {
            throw 1;
        }
        sum_for_min(num1, bin_number_2);
        std::cout << "Bin_Number_1: ";
        for (int i = 0; i < num1->bin_number.size(); i++) {
            std::cout << num1->bin_number[i];
        }
        std::cout << "\n";
        std::cout << "Bin_Number_2: ";
        for (int i = 0; i < bin_number_2.size(); i++) {
            std::cout << bin_number_2[i];
        }
        std::cout << "\n";
    }
    //_______________________________________________________________________________________________________________________________________________________________________________________
    void mul(bin_code* num1, bin_code* num2) {
        std::cout << "Bin_Number_1: ";
        for (int i = 0; i < num1->bin_number.size(); i++) {
            std::cout << num1->bin_number[i];
        }
        std::cout << "\n";
        std::cout << "Bin_Number_2: ";
        for (int i = 0; i < num2->bin_number.size(); i++) {
            std::cout << num2->bin_number[i];
        }
        std::cout << "\n";

        std::vector<int> bin_number_1 = num1->bin_number;
        std::vector<int> bin_number_2 = num2->bin_number;
        int key = 0;
        if (bin_number_1[0] == 1) {
            for (int i = 0; i < bin_number_1.size(); i++) {
                if (bin_number_1[i] == 1) {
                    bin_number_1[i] = 0;
                }
                else if (bin_number_1[i] == 0) {
                    bin_number_1[i] = 1;
                }
            }
                bin_number_1 = sum_one(bin_number_1);
            key++;
        }
        if (bin_number_2[0] == 1) {
            for (int i = 0; i < bin_number_2.size(); i++) {
                if (bin_number_2[i] == 1) {
                    bin_number_2[i] = 0;
                }
                else if (bin_number_2[i] == 0) {
                    bin_number_2[i] = 1;
                }
            }
                bin_number_2 = sum_one(bin_number_2);
            key++;
        }
        
        std::vector<int> positions_1;
        std::vector<std::vector<int>> bin_summand;
        for (int i = bin_number_1.size() - 1; i >= 0; i--) {
            if (bin_number_1[i] == 1) {
                positions_1.push_back(depth - 1 - i);
            }
        }

        
        for (int i = 0; i < positions_1.size(); i++) {
            std::vector<int> bin_number_2_true;
            bin_number_2_true.resize(depth);
            for (int p = bin_number_2.size() - 1; p >= positions_1[i]; p--) {
                bin_number_2_true[p - positions_1[i]] = bin_number_2[p];
            }

            bin_summand.push_back(bin_number_2_true);
        }
        for (int i = 0; i < bin_summand.size(); i++) {
            bin_number = sum_for_mul(bin_number, bin_summand[i]);
        }
        if (key == 1) {
            for (int i = 0; i < bin_number.size(); i++) {
                if (bin_number[i] == 1) {
                    bin_number[i] = 0;
                }
                else if (bin_number[i] == 0) {
                    bin_number[i] = 1;
                }
            }
            bin_number = sum_one(bin_number);
        }
        else {
            if (bin_number[0] == 1) {
                throw 1;
            }
        }
    }
    std::vector<int> sum_for_mul(std::vector<int> num1, std::vector<int> num2) {
        int k = 0;
        std::vector<int> bin_number_1 = num1;
        std::vector<int> bin_number_2 = num2;
        std::vector<int> bin_number_answ;
        bin_number_answ.resize(depth);
        std::vector <int> summator;
        summator.resize(depth + 1);
        for (int i = depth - 1; i >= 0; i--) {
            k = bin_number_1[i] + bin_number_2[i];
            if (k == 2) {
                summator[i - 1] = 1;
            }
        }

        k = 0;
        for (int i = depth - 1; i >= 0; i--) {
            k = bin_number_1[i] + bin_number_2[i] + summator[i];
            if (k == 0) {
                bin_number_answ[i] = 0;
            }
            else if (k == 1) {
                bin_number_answ[i] = 1;
            }
            else if (k == 2 && summator[i] == 1) {
                summator[i - 1] = 1;
                bin_number_answ[i] = 0;
            }
            else if (k == 2 && summator[i] == 0) {
                bin_number_answ[i] = 0;
            }
            else if (k == 2 && summator[i] == 0) {
                bin_number_answ[i] = 0;
            }
            else if (k == 3) {
                bin_number_answ[i] = 1;
            }
        }
        if (summator[0] == 1) {
            throw 1;
        }
        return bin_number_answ;

    }
    //_______________________________________________________________________________________________________________________________________________________________________________________
    void print() {
        std::cout << "Bin_Answer: ";
        for (int i = 0; i < bin_number.size(); i++) {
            std::cout << bin_number[i];
        }
        std::cout << "\n";
        int answer = 0;
        if (bin_number[0] == 0) {
            for (int i = bin_number.size() - 1; i >= 0; i--) {
                if (bin_number[i] == 1) {
                    answer += pow(2, 7-i);
                }
            }
        }
        else {
            for (int i = 0; i < bin_number.size(); i++) {
                if (bin_number[i] == 1) {
                    bin_number[i] = 0;
                }
                else if (bin_number[i] == 0) {
                    bin_number[i] = 1;
                }
            }
            bin_number = sum_one(bin_number);
            for (int i = bin_number.size() - 1; i >= 0; i--) {
                if (bin_number[i] == 1) {
                    answer += pow(2, 7-i);
                }
            }
            answer = answer * -1;
        }
        std::cout << "Answer: " << answer;
    }
};
int write_Bit_depth() {
    int key = 0;
    int Bit_depth = 0;
    while (key == 0) {
        std::cout << "Write bit depth (8, 16, 32): ";
        std::cin >> Bit_depth;
        key = 1;
        if (Bit_depth != 8 && Bit_depth != 16 && Bit_depth != 32) {
            key = 0;
            std::cout << "Error" << "\n";
        }
    }
    return Bit_depth;
}
char write_sign() {
    int key = 0;
    char sign = 0;
    while (key == 0) {
        std::cout << "Write sign: ";
        std::cin >> sign;
        key = 1;
        if ((sign != '+' && sign != '*' && sign != '-')) {
            key = 0;
            std::cout << "Error" << "\n";
        }
    }
    return sign;
}
int write_number(int Bit_numbers) {
    int key = 0;
    int number = 0;
    while (key == 0) {
        std::cout << "Write number: ";
        std::cin >> number;
        key = 1;
        if (-Bit_numbers > number || number > Bit_numbers - 1) {
            key = 0;
            std::cout << "Error" << "\n";
        }

    }
    return number;
}
int main()
{
    int Bit_depth = write_Bit_depth();
    int Bit_numbers = pow(2, Bit_depth) / 2;
    bin_code num1 = bin_code(write_number(Bit_numbers), Bit_depth);
    char sign = write_sign();
    bin_code num2 = bin_code(write_number(Bit_numbers), Bit_depth);
    bin_code answer = bin_code(Bit_depth);
    try {
        if (sign == '+') {
            answer.sum(&num1, &num2);
        }
        else if (sign == '*') {
            answer.mul(&num1, &num2);
        }
        else if (sign == '-') {
            answer.min(&num1, &num2);
        }
        answer.print();
    }
    catch (int i) {
        std::cout << "Error";
    }
    return 0;
}
