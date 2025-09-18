#include <iostream>
#include <set>

int main(){
    int n = 0;
    std::cin >> n;
    std::set <int> dif;
    if(n > 0){
        for(int i = 0; i < n; i++){
            int a = 0;
            std::cin >> a;
            dif.insert(a);
        }
        std::cout << dif.size() << std::endl;
    }else{
        std::cout << 0;
    }
}