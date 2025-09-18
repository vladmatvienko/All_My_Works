#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int compare(std::string a, std::string b, int &zn){
    int num = 0;
    for(int i = 0; i < a.size(); i++){
        if(num != 0){
            break;
        }
        for(int j = 0; i + j < a.size(); j++){
            if(a[i + j] == b[j]){
                num++;
                if(num == b.size()){
                    break;
                }
            }else{
                num = 0;
                break;
            }
        }
    }
    if(num == 0){
        for(int i = 0; i < b.size(); i++){
            if(num != 0){
                break;
            }
            for(int j = 0; num < b.size(); j++){
                if(b[i + j] == a[j]){
                    num++;
                    if(num == a.size()){
                        break;
                    }
                }else{
                    num = 0;
                    break;
                }
            }
        }
        if(num != 0){
            zn = -1;
        }
    }else{
        zn = 1;
    }
    return num;
}

std::string word(std::string a, std::string b, int num, int zn){
    std::string x;
    if(zn == 1){
        x = a + b.substr(num, b.size() - num);
    }else if(zn == -1){
        x = b + a.substr(num, a.size() - num);
    }else{
        x = a + b;
    }
    return x;
}
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int n;
    cin >> n;
    string subseq[n];
    for (int i = 0; i < n; i++) {
        cin >> subseq[i];
    }

    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    std::string answer;
    bool check = false;

    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            int zn = 0;
            if(i == 0 && j < 1){
                answer = subseq[i];
            }
            if(subseq[i] != subseq[j] && compare(subseq[i], subseq[j], zn) != 0){
                answer = word(answer, subseq[j], compare(answer, subseq[j], zn), zn);
                check = true;
            }
            if(j + 1 == n && compare(subseq[i], subseq[j], zn) == 0 && check == false){
                answer = word(answer, subseq[j], compare(answer, subseq[j], zn), zn);
            }
        }
    }

    std::cout << answer.size() << endl;
}