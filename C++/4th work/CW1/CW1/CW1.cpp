//std::getline(std::cin, s);
//1111111111111111
/*std::string s;
    std::getline(std::cin; s)
    int heigh = 0;
    int low = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            low = low + 1;
        }
        if (s[i] >= 'A' && s[i] <= 'Z') {
            heigh = heigh + 1;
        }
    }
    std::cout << heigh << " " << low;
    return 0;*/
#include <iostream>
#include <string>
int main()
{
    std::string s;
    getline(std::cin, s);
    std::string w;
    int ls = s.size();
    int lw = 0;
    int i = 0;
    int j = 0;
    int let = 0;
    for (int i = 0; i <= 5; i++) {
        int lw = 2 + rand() % (7 - 2 + 1);
        j = 0;
        w = "";
        while (j < lw) {
            let = 0 + rand() % (ls - 0 + 1);
            w = s[let];
            if (w != " ") {

            }
            else {

            }
          
        }
        
    }
    return 0; 
}