#include <iostream>
#include <map>
#include <string>

int main(){
    std::multimap <int, std::string> classes;
    int classNum = 0;
    std::string surname;
    while(std::cin >> classNum >> surname){
        if(classNum == -1){
            break;
        }
        classes.insert(std::pair<int, std::string>(classNum, surname));
    }
    for(auto i = classes.begin(); i != classes.end(); i++){
        std::cout << i->first << " " << i->second << std::endl;
    }
}