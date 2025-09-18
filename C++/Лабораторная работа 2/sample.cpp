#include <iostream>
#include <list>
#include <string>

int main(){
    std::list <std::string> sample;
    std::string put;
    while(std::cin >> put){
        sample.push_back(put);
    }
    for(auto i = sample.begin(); i != sample.end(); i++){
        int a = 0;
        int b = 0;
        std::string c;
        if(*i == "+"){
            a = stoi(*(std::prev(i, 2)));
            b = stoi(*(std::prev(i, 1)));
            c = std::to_string(a + b);
            i = std::prev(i, 1);
            sample.erase(std::next(i, 1));
            i = std::prev(i, 1);
            sample.erase(std::next(i, 1));
            *i = c;
        }else if(*i == "-"){
            a = stoi(*(std::prev(i, 2)));
            b = stoi(*(std::prev(i, 1)));
            c = std::to_string(a - b);
            i = std::prev(i, 1);
            sample.erase(std::next(i, 1));
            i = std::prev(i, 1);
            sample.erase(std::next(i, 1));
            *i = c;
        }else if(*i == "*"){
            a = stoi(*(std::prev(i, 2)));
            b = stoi(*(std::prev(i, 1)));
            c = std::to_string(a * b);
            i = std::prev(i, 1);
            sample.erase(std::next(i, 1));
            i = std::prev(i, 1);
            sample.erase(std::next(i, 1));
            *i = c;
        }
    }
    std::cout << *(sample.begin()) << std::endl; 
}