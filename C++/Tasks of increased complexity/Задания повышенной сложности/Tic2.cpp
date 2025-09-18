#include <iostream>
#include <cmath>
#include <vector>
double find_tAB(double XA, double YA, double XB, double YB, double XC, double YC, double XD, double YD) {
    double tAB = 0;
    
        tAB = ((YA - YC) * (XD + XC) + (XC - XA) * (YD - YC))
                                     /
              ((YD - YC) * (XB - XA) + (XC - XD) * (YB - YA));

    return tAB;
}
double find_tCD(double XA, double YA, double XB, double YB, double XC, double YC, double XD, double YD) {
    double tAB = ((YA - YC) * (XD + XC) + (XC - XA) * (YD - YC))
                                      /
                 ((YD - YC) * (XB - XA) + (XC - XD) * (YB - YA));
    double tCD = (XA-XC+(XB-XA)*tAB)
                        /
                     (XD-XC);
    return tCD;
}
double Area_3_Dot(double x1, double y1, double x2, double y2, double x3, double y3) {
    double S = 0.5 * std::fabs((x1 - x2) * (y1 - y2) - (x2 - x3) * (y2 - y3)); //формула Гаусса для 3 точек

    return S;
}
double Area_4_Dot(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    double S = 0.5 * std::fabs(x1 * y2 + x2 * y3 + x3 * y4 + (x4 * y1) - x2 * y1 - x3 * y2 - x4 * y3 - (x1 * y4)); //формула Гаусса для 4 точек

    return S;
}
double Area_5_Dot(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5) {
    double S = 0.5 * std::fabs(x1 * y2 + x2 * y3 + x3 * y4 + x4 * y5 + (x5 * y1) - x2 * y1 - x3 * y2 - x4 * y3 - x5 * y4 - (x1 * y5)); //формула Гаусса для 5 точек

    return S;
}double Area_6_Dot(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5, double x6, double y6) {
    double S = 0.5 * std::fabs(x1 * y2 + x2 * y3 + x3 * y4 + x4 * y5 + x5 * y6 + (x6 * y1) - x2 * y1 - x3 * y2 - x4 * y3 - x5 * y4 - x6 * y5 - (x1 * y6)); //формула Гаусса для 6 точек

    return S;
}


int main()
{
    std::cout << "Write coordinats\n";
    std::cout << "Triangle N1:\n";
    std::vector<double> triangleN1;
    double a = 0;
    triangleN1.reserve(6);
    std::cout << "X1:";
    std::cin >> a;
    triangleN1.push_back(a);
    std::cout << "Y1:";
    std::cin >> a;
    triangleN1.push_back(a);
    std::cout << "X2:";
    std::cin >> a;
    triangleN1.push_back(a);
    std::cout << "Y2:";
    std::cin >> a;
    triangleN1.push_back(a);
    std::cout << "X3:";
    std::cin >> a;
    triangleN1.push_back(a);
    std::cout << "Y3:";
    std::cin >> a;
    triangleN1.push_back(a);
    std::cout << "Triangle N2:\n";
    std::vector<double> triangleN2;
    triangleN2.reserve(6);
    std::cout << "X1:";
    std::cin >> a;
    triangleN2.push_back(a);
    std::cout << "Y1:";
    std::cin >> a;
    triangleN2.push_back(a);
    std::cout << "X2:";
    std::cin >> a;
    triangleN2.push_back(a);
    std::cout << "Y2:";
    std::cin >> a;
    triangleN2.push_back(a);
    std::cout << "X3:";
    std::cin >> a;
    triangleN2.push_back(a);
    std::cout << "Y3:";
    std::cin >> a;
    triangleN2.push_back(a);
    std::vector<double> CP; //Crossing points - точка пересечения
    CP.reserve(12);
    std::vector<double> IP; //Inner points - внутренние точки (Точки одного треугольника располагающиеся внутри другого)
    IP.reserve(12);
    std::vector<double> TP; //Touch Points - точка соприкосновения (Когда точка одного треугольника находится на одной из сторон другого
    TP.reserve(12);
    std::vector<double> AllP; //All Points - все точки
    AllP.reserve(12);
    double tAB = 0; //параметр одного отрезка
    double tCD = 0; //параметр другого отрезка
    for (int i = 0; i < 6; i = i + 2) { // Поиск всех точек пересечения
        for (int k = i + 2; k < 6; k = k + 2) {
            for (int g = 0; g < 6; g = g + 2) {
                for (int h = g + 2; h < 6; h = h + 2) {
                    tAB = find_tAB(triangleN1[i], triangleN1[i + 1], triangleN1[k], triangleN1[k + 1], triangleN2[g], triangleN2[g + 1], triangleN2[h], triangleN2[h + 1]);
                    tCD = find_tCD(triangleN1[i], triangleN1[i + 1], triangleN1[k], triangleN1[k + 1], triangleN2[g], triangleN2[g + 1], triangleN2[h], triangleN2[h + 1]);
                    if (0 <= tAB && tAB <= 1 && 0 <= tCD && tCD <= 1) { //Проверка, пересекаются ли прямые
                        int key = 0;
                        double CPX = triangleN1[i] + (triangleN1[k] - triangleN1[i]) * tAB; //Координата X точки пересечения между прямыми
                        double CPY = triangleN1[i + 1] + (triangleN1[k + 1] - triangleN1[i + 1]) * tAB; //Координата Y точки пересечения между прямыми
                        for (int p = 0; p < CP.size(); p = p + 2) {
                            if (CP[p] == CPX && CP[p + 1] == CPY) {
                                key++;
                            }
                        }
                        if (key == 0) {
                            CP.push_back(CPX);
                            CP.push_back(CPY);
                        }
                    }
                }
            }
        }
    }
    double SN1 = Area_3_Dot(triangleN1[0], triangleN1[1], triangleN1[2], triangleN1[3], triangleN1[4], triangleN1[5]); // Площадь первого треугольника
    double SN2 = Area_3_Dot(triangleN2[0], triangleN2[1], triangleN2[2], triangleN2[3], triangleN2[4], triangleN2[5]); // Площадь второго треугольника
    for (int i = 0; i < 6; i = i + 2) {//Проверка нахождения точек первого треугольника во втором
        double S1 = Area_3_Dot(triangleN1[i], triangleN1[i + 1], triangleN2[2], triangleN2[3], triangleN2[4], triangleN2[5]);
        double S2 = Area_3_Dot(triangleN2[0], triangleN2[1], triangleN1[i], triangleN1[i + 1], triangleN2[4], triangleN2[5]);
        double S3 = Area_3_Dot(triangleN2[0], triangleN2[1], triangleN2[2], triangleN2[3], triangleN1[i], triangleN1[i + 1]);
        double Sum_S = S1 + S2 + S3;
        int key = 0;
        for (int p = 0; p < IP.size(); p = p + 2) {
            if (IP[p] == triangleN1[i] && IP[p + 1] == triangleN1[i + 1]) {
                key++;
            }
        }
        if (Sum_S == SN2 && key == 0) {
            IP.push_back(triangleN1[i]);
            IP.push_back(triangleN1[i + 1]);
        }
    }
    for (int i = 0; i < 6; i = i + 2) {//Проверка нахождения точек второго треугольника во первом
        double S1 = Area_3_Dot(triangleN2[i], triangleN2[i + 1], triangleN1[2], triangleN1[3], triangleN1[4], triangleN1[5]);
        double S2 = Area_3_Dot(triangleN1[0], triangleN1[1], triangleN2[i], triangleN2[i + 1], triangleN1[4], triangleN1[5]);
        double S3 = Area_3_Dot(triangleN1[0], triangleN1[1], triangleN1[2], triangleN1[3], triangleN2[i], triangleN2[i + 1]);
        double Sum_S = S1 + S2 + S3;
        int key = 0;
        for (int p = 0; p < IP.size(); p = p + 2) {
            if (IP[p] == triangleN2[i] && IP[p + 1] == triangleN2[i + 1]) {
                key++;
            }
        }
        if (Sum_S == SN2 && key == 0) {
            IP.push_back(triangleN2[i]);
            IP.push_back(triangleN2[i + 1]);
        }
    }

    for (int k = 0; k < CP.size(); k = k + 2) {
            AllP.push_back(CP[k]);
            AllP.push_back(CP[k + 1]);
     }
    for (int k = 0; k < IP.size(); k = k + 2) {
        int key = 0;
        for (int p = 0; p < AllP.size(); p = p + 2) {
            if (AllP[p] == IP[k] && AllP[p + 1] == IP[k + 1]) {
                key++;
            }
        }
        if (key == 0) {
            AllP.push_back(IP[k]);
            AllP.push_back(IP[k + 1]);
        }
    }
   /* std::cout << "Crossing points: ";
    for (int i = 0; i < CP.size(); i++) {
        std::cout << CP[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Inner points: ";
    for (int i = 0; i < IP.size(); i++) {
        std::cout << IP[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "All points: ";
    for (int i = 0; i < AllP.size(); i++) {
        std::cout << AllP[i] << " ";
    }*/
    double answ = 0;
    if (AllP.size() == 6) {
        answ = Area_3_Dot(AllP[0], AllP[1], AllP[2], AllP[3], AllP[4], AllP[5]);
    }
    else if (AllP.size() == 8) {
        answ = Area_4_Dot(AllP[0], AllP[1], AllP[2], AllP[3], AllP[4], AllP[5], AllP[6], AllP[7]);
    }
    else if (AllP.size() == 10) {
        answ = Area_5_Dot(AllP[0], AllP[1], AllP[2], AllP[3], AllP[4], AllP[5], AllP[6], AllP[7], AllP[8], AllP[9]);
    }
    else if (AllP.size() == 12) {
        answ = Area_6_Dot(AllP[0], AllP[1], AllP[2], AllP[3], AllP[4], AllP[5], AllP[6], AllP[7], AllP[8], AllP[9], AllP[10], AllP[11]);
    }
    std::cout << answ;
            
    return 0;
}
//Использовавшиеся сайты:
//https://www.interestprograms.ru/source-codes-peresechenie-dvuh-otrezkov
//https://www.youtube.com/watch?v=tgKmthxHtLc
//https://allcalc.ru/node/1052
//https://ru.wikipedia.org/wiki/Формула_площади_Гаусса
