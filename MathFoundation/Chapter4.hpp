//
//  Chapter4.hpp
//  MathBase
//
//  第四章 二次同余式与平方剩余
//  Created by 杨磊 on 2019/5/14.
//  Copyright © 2019 杨磊. All rights reserved.
//

#ifndef Chapter4_hpp
#define Chapter4_hpp

//雅可比符号的计算
int JacobiSignal(long up, long down){
    //求模
    up = up % down;
    //递归终点
    if(up == 1 || up == 0)
        return 1;
    //保证上方为正的奇整数
    if(up % 2 == 0){
        //2/p的计算
        return JacobiSignal(up/2, down) * pow(-1,(down * down -1 )/8);
    }else if(up < 0){
        //-1/p的计算
        return JacobiSignal(-up, down) * pow(-1,(down *down -1)/2);
    }else{
        //二次互反律
        return JacobiSignal(down, up) * pow(-1, (up - 1)*(down - 1)/4);
    }
    
    return 0;
}

//计算-1模p的平方根
//形如x^2 = -1(mod p)
int noSquareRoot(const int &p,bool printResult = false){
    int answer = 0;
    if(!isPrime(p) || p % 8 != 5){
        if(printResult)
            std::cout << "no solution.";
        return 0;
    }
    
    int a = 2;
    while(a++ < p){
        if(JacobiSignal(a, p) == -1)
            break;
    }
    answer = opeMod(a, (p-1)/4 , p);
    if(printResult)
        std::cout << answer << " ^ 2 = -1 (mod " << p << ") \n";
    return answer;
}

//求解费马平方和问题
//形如x^2+y^2=p(p是素数)的问题的求解
bool FermatSquareSum(const int &p,bool printResult = false){
    if(p == 2){
        if(printResult)
            std::cout << "x = 1, y = 1.\n";
        return true;
    }
    if(p % 4 != 1){
        if(printResult)
            std::cout << "no solution.\n";
        return false;
    }
    
    long x,y,u,v,m;
    long nx,ny;
    x = y = u = v = m = 0;
    nx = ny = 0;
    //赋初值
    x = noSquareRoot(p);
    y = 1;
    m = (x*x + y*y)/p;
    while(m != 1){
        u = x % m;
        v = y % m;
        
        nx = u*x + v*y;
        ny = u*y - v*x;
        
        x = nx / m;
        y = ny / m;
        
        m = (x*x + y*y)/p;
    }
    x = (x > 0)?x:-x;
    y = (y > 0)?y:-y;
    if(printResult)
        std::cout << "|x| = " << x << ", |y| = " << y << ".\n";
    
    return true;
}
#endif /* Chapter4_hpp */
