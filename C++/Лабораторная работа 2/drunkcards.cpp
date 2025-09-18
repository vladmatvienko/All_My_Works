#include <iostream>
#include <deque>

int main(){
    std::deque <int> first(5);
    std::deque <int> second(5);
    for(int i = 0; i < first.size(); i++){
        std::cin >> first[i];
    }
    for(int i = 0; i < second.size(); i++){
        std::cin >> second[i];
    }
    int count = 0;
    while(true){
        if(first[0] > second[0]){
            if(second[0] == 0 && first[0] == 9){
                second.push_back(first[0]);
                second.push_back(second[0]);
                first.pop_front();
                second.pop_front();
            }else{
                first.push_back(first[0]);
                first.push_back(second[0]);
                first.pop_front();
                second.pop_front();
            }
        }else{
            if(first[0] == 0 && second[0] == 9){
                first.push_back(first[0]);
                first.push_back(second[0]);
                first.pop_front();
                second.pop_front();
            }else{
                second.push_back(first[0]);
                second.push_back(second[0]);
                first.pop_front();
                second.pop_front();
            }
        }
        count++;
        if(first.size() == 0 || second.size() == 0){
            break;
        }
        if(count == 1000000){
            std::cout << "botva";
            break;
        }
    }
    if(first.size() == 0){
        std::cout << "second " << count;
    }else if(second.size() == 0){
        std::cout << "first " << count;
    }
}
