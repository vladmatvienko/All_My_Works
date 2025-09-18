#include <iostream>
#include <string>
#include <set>
#include <vector>

int main(){
    std::set <std::string> words;
    std::vector <std::string> answer;
    while(true){
        char sign;
        std::string sub;
        std::cin >> sign;
        if(sign == '#'){
            break;
        }
        std::cin >> sub;
        if(sign == '+'){
            words.insert(sub);
        }else if(sign == '-'){
            if(words.count(sub) > 0){
                words.erase(sub);
            }
        }else if(sign == '?'){
            if(words.count(sub) > 0){
                answer.push_back("YES");
            }else{
                answer.push_back("NO");
            }
        }
    }
    for(int i = 0; i < answer.size(); i++){
        std::cout << answer[i] << std::endl;
    }
}