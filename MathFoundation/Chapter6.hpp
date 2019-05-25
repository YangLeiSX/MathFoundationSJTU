//
//  Chapter6.hpp
//  MathFoundation
//
//  第六章 素性检验
//  Created by 杨磊 on 2019/5/24.
//  Copyright © 2019 杨磊. All rights reserved.
//

#ifndef Chapter6_hpp
#define Chapter6_hpp

#include "MathFoundation.hpp"
#include <cstdlib>
#include <ctime>

//费马素性检验
bool fermatPrimalityTest(const long num,const int secIndex = 10){
    long base;
    srand(unsigned(time(NULL)));
    for(int i = 0; i < secIndex;i++){
        //随机得到b的值
        //base = rand() % (num-3) + 2;
        base = rand() % 1000;
        long testvar = opeMod(base,num -1,num);
        std::cout << base << "\t" << testvar << "\n";
        if(testvar != 1){
            return false;//不满足费马小定理
        }
    }
    return true;//可能是素数
}


//找到伪素数满足费马定理的基
void findBaseForFakePrimeNum(const long &num){
    for(int i = 1;i < num;i++){
        if(opeMod(i, num-1, num) == 1)
            std::cout << num << "是对于基" << i << "的伪素数\n";
    }
}

//生成指定长度的伪素数
long fakePrimeNumGen(const int &length){
    srand(unsigned(time(NULL)));
    long num = 0;
    //生成随机数
    for(int i = 0;i <= length;i++){
        num *= 10;
        num += rand() % 10 + 1;
    }
    //素性检验
    while(!fermatPrimalityTest(num)){
        std::cout << num << " fail\n";
        num = 0;
        for(int i = 0;i <= length;i++){
            num *= 10;
            num += rand() % 9 + 1;
        }
    }
    return num;
}
//使用顺序查找生成伪素数
long fakefakePrimeNumGen(const int &length){
    long num = long(pow(10,length)) + 1;
    while(!fermatPrimalityTest(num)){
        std::cout << num << " fail\n";
        num += 2;
    }
    return num;
}

//solovay-stassen素性检验
bool SolovayStassenPrimalityTest(const long num,const int secIndex = 15){
    ///初始化
    long base;
    int counter = 0;
    srand(unsigned(time(NULL)));
    
    while(counter < 0){
        //随机得到b的值
        base = rand() % (num - 3) + 2;
        if(opeMod(base, (num - 1)/2, num) != JacobiSignal(base, num))
            std::cout << base << "\t";
            return false;//不满足欧拉判别条件
        counter ++;
    }
    return true;
}

//找到伪素数满足欧拉法则的基
void findBaseForEularFakePrimeNum(const long &num){
    for(long i = 0; i < num;i++)
        if(opeMod(i, (num - 1) /2, num) == JacobiSignal(i, num))
            std::cout << num << "是对于基" << i << "的eular伪素数\n";
}

//生成指定大小的Eular伪随机数
long EularFakePrimeNumGen(const int &length){
    srand(unsigned(time(NULL)));
    long num = 0;
    //生成随机数
    for(int i = 0;i <= length;i++){
        num *= 10;
        num += rand() % 10 + 1;
    }
    
    while(!SolovayStassenPrimalityTest(num)){
        std::cout << num << " fail\n";
        num = 0;
        for(int i = 0;i <= length;i++){
            num *= 10;
            num += rand() % 9 + 1;
        }
    }
    return num;
}

//miller-rabin素性检验
bool MillerRabinPrimalityTest(const long num,int secIndex = 10){
    //因数分解
    long s = 0;
    long t = num - 1;
    while(t % 2 == 0){
        t /= 2;
        s ++;
    }
    //初始化
    bool pass = false;
    long r;
    long base;
    //多次检验
    while((secIndex--) > 0){
        //新的一次检验
        pass = false;
        base = rand() % (num - 3) + 2;
        r = opeMod(base, t, num);//r_0
        if(r == 1 || r == num - 1)
            continue;
        for(int i = 1;i < s;i++){
            r = opeMod(r, 2, num);//r_i
            pass = (r == num-1)|| (r == -1);
        }
        if(pass)
            continue;
        else
            return false;
    }
    return true;
}

//找到强伪素数的基
bool findBaseForHighFakePrimeNum(const long &num){
    //因数分解
    long s = 0;
    long t = num - 1;
    while(t % 2 == 0){
        t /= 2;
        s ++;
    }
    //初始化
    bool pass = false;
    long r;
    long base;
    //多次检验
    for(base = 1;base < num-1;base ++){
        //新的一次检验
        pass = false;
        r = opeMod(base, t, num);//r_0
        if(r == 1 || r == num - 1){
            std::cout << num << " 是关于基 " << base << " 的强伪素数.\n";
            continue;
        }
        if(s >= 2){
            for(int i = 1;i <= s;i++){
                r = opeMod(r, 2, num);//r_i
                pass = (r == num-1)|| (r == -1);
            }
        }
        if(pass){
            std::cout << num << " 是关于基 " << base << " 的强伪素数.\n";
            continue;
        }else
            return false;
    }
    return true;
}
//生成指定大小的强伪素数
long HighFakePrimeNumGen(const int &length){
    srand(unsigned(time(NULL)));
    long num = 0;
    //生成随机数
    for(int i = 0;i <= length;i++){
        num *= 10;
        num += rand() % 10 + 1;
    }
    
    while (!MillerRabinPrimalityTest(num)) {
        std::cout << num << " fail.\n";
        num = 0;
        for(int i = 0;i <= length;i++){
            num *= 10;
            num += rand() % 9 + 1;
        }
    }
    return num;
}

#endif /* Chapter6_hpp */
