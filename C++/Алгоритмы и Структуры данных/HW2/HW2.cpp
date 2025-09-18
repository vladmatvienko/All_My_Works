#include <iostream>
#include <vector>
#include <cmath>
#include <string>

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
            throw "Error 3: More than Bit_Depth (sum)";
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
        int k = 0;
        int p = 0;
        std::vector<int> bin_number_1 = num1->bin_number;
        std::vector<int> bin_number_2 = num2->bin_number;
        for (int i = 0; i < bin_number_1.size(); i++) {
            if (bin_number_1[i] == 1) {
                k++;
            }
        }
        for (int i = 0; i < bin_number_2.size(); i++) {
            if (bin_number_2[i] == 1) {
                p++;
            }
        }
        if (p == 0 || k == 0) {
            for (int i = 0; i < bin_number.size(); i++) {
                if (bin_number[i] == 1) {
                    bin_number[i] = 0;
                }
            }
        }
        else if(p == 8){
            bin_number = bin_number_1;
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
        else if (k == 8) {
            bin_number = bin_number_2;
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
        else{
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
                    throw "Error 5: More than Bit_Depth (mul)";
                }
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
            throw "Error 7: More than Bit_Depth (sum_one)";
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
                    answer += pow(2, 7 - i);
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
                    answer += pow(2, 7 - i);
                }
            }
            answer = answer * -1;
        }
        std::cout << "Answer: " << answer;
    }
    int get_answer() {
        std::vector<int> bin_number_1 = bin_number;
        int answer = 0;
        if (bin_number_1[0] == 0) {
            for (int i = bin_number_1.size() - 1; i >= 0; i--) {
                if (bin_number_1[i] == 1) {
                    answer += pow(2, 7 - i);
                }
            }
        }
        else {
            for (int i = 0; i < bin_number_1.size(); i++) {
                if (bin_number_1[i] == 1) {
                    bin_number_1[i] = 0;
                }
                else if (bin_number_1[i] == 0) {
                    bin_number_1[i] = 1;
                }
            }
            bin_number_1 = sum_one(bin_number_1);
            for (int i = bin_number_1.size() - 1; i >= 0; i--) {
                if (bin_number_1[i] == 1) {
                    answer += pow(2, 7 - i);
                }
            }
            answer = answer * -1;
        }
        return answer;
    }
};
template <class Data_Type>
class STACK {
private:
    struct node {
        Data_Type data_type;
        node* next;
        node(Data_Type x, node* t) {
            data_type = x;
            next = t;
        }
    };
    typedef node* link;
    link head;
public:
    STACK(int) { 
        head = 0;
    }
    int empty() const { 
        return head == 0;
    }
    void push(Data_Type x) { 
        head = new node(x, head);
    }
    Data_Type pop() {
        Data_Type v = head->data_type;
        link t = head->next;
        delete head;
        head = t;
        return v;
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
            throw "Error 6: You can not choose this number";
        }
    }
    return Bit_depth;
}

std::string write_expression(){
    std::string expression;
    std::cout << "Write expression (0123456789+-*_): ";
    std::cin >> expression;
    int num = 0;
    int sign = 0;
    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        char c_1 = expression[i+1];
        if ((c < '0' || c > '9') && c != '+' && c != '-' && c != '*' && c != '_') {
            throw "Error 0: Wrong expression";
        }
        if (c >= '0' && c <= '9' && c_1 == '_') {
            num++;
        }
        if (c == '+' || c == '-' || c == '*') {
            if (i + 1 == expression.length()) {
                sign++;
            }
            else {
                if (c_1 == '_') {
                    sign++;
                }
            }
        }
    }
    if (num - 1 != sign) {
        throw "Error 1: Wrong expression";
    }
    return expression;
}
int main()
{
    try {
        int Bit_depth = write_Bit_depth();
        int Bit_numbers = pow(2, Bit_depth) / 2;
        std::string expression = write_expression();
        bin_code answer = bin_code(Bit_depth);
        STACK<int> stack_expression(0);
        for (int i = 0; i < expression.length(); i++) {
            std::string s;
            char c = expression[i];
            s += expression[i];
            if (c >= '0' && c <= '9') {
                while (c != '_') {
                    i++;
                    c = expression[i];
                    s += expression[i];
                }
                stack_expression.push(std::stoi(s));
            }
            else if (c == '-') {
                if (expression[i + 1] == '_') {
                    bin_code num1 = bin_code(stack_expression.pop(), Bit_depth);
                    bin_code num2 = bin_code(stack_expression.pop(), Bit_depth);
                    answer.min(&num1, &num2);
                    stack_expression.push(answer.get_answer());
                }
                else {
                    while (c != '_') {
                        i++;
                        c = expression[i];
                        s += expression[i];
                    }
                    stack_expression.push(std::stoi(s));
                }
            }
            else if (c == '+') {
                bin_code num1 = bin_code(stack_expression.pop(), Bit_depth);
                bin_code num2 = bin_code(stack_expression.pop(), Bit_depth);
                answer.sum(&num1, &num2);
                stack_expression.push(answer.get_answer());
            }
            else if (c == '*') {
                bin_code num1 = bin_code(stack_expression.pop(), Bit_depth);
                bin_code num2 = bin_code(stack_expression.pop(), Bit_depth);
                answer.mul(&num1, &num2);
                stack_expression.push(answer.get_answer());
            }
        }
        answer.print();
    }
    catch (const char* error_code) {
        std::cout << error_code;
    }
    return 0;
}