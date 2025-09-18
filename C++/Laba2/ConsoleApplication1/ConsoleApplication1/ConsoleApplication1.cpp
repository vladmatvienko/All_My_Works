
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> signs;
    std::vector<std::string> words;
    std::string str1;
    std::string str2;
    std::string k = " ";
    while (k != "#") {
        std::cin >> str1;
        if (str1 == "#") {
            k = str1;
            break;
        }
        std::cin >> str2;
        signs.push_back(str1);
        words.push_back(str2);
    }
    std::vector<std::string> onlywords;
    int key = 0;
    for (int i = cache.begin(); pos != cache.end(); ++pos) {
        if (pos->first == "+") {
            words.push_back(pos->second);
        }
        else if (pos->first == "-") {
            for (auto i = 0; i < words.size(); i++) {
                if (pos->second == words[i]) {
                    auto iter = words.cbegin();
                    words.erase(iter + i);
                    break;
                }
            }
        }
        else if (pos->first == "?") {
            key = 0;
            for (int i = 0; i < words.size(); i++) {
                if (pos->second == words[i]) {
                        std::cout << "YES" << std::endl;
                        key = 1;
                        break;
                }
                }
                if (key == 0) {
                    std::cout << "NO" << std::endl;
                }
        }
    }
}
