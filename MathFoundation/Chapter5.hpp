//
//  Chapter5.hpp
//  MathBase
//
//  Created by 杨磊 on 2019/5/14.
//  Copyright © 2019 杨磊. All rights reserved.
//

#ifndef Chapter5_hpp
#define Chapter5_hpp

#include "MathFoundation.hpp"

//计算模m简化剩余系的指数
void findOrder(const int &m){
    int answer;//计算结果
    int e;//指数
    int phi = EularFunction(m);
    
    //选择底数
    for(int a = 1;a < m;a++){
        //筛选简化剩余系
        if(MaxCommonFactor(a, m) != 1)
            continue;
        e = 1;
        while(e < m){
            //指数整除欧拉函数
            if(phi - (phi / e * e) != 0){
                e++;
                continue;
            }
            answer = opeMod(a, e, m);
            if(answer == 1){
                std::cout << "Ord" << m << "(" << a << ") = " << e;
                if(e == phi)
                    std::cout << ",\t" << a << " 是原根";
                std::cout <<std::endl;
                break;
            }
            e++;
        }
    }
}

//计算a模m的指数
void opeOrder(const int &m, const int &a){
    int answer;
    int e = 1;//指数
    int phi = EularFunction(m);
    
    while(e < m){
        //指数整除欧拉函数
        if(phi - (phi / e * e) != 0){
            e++;
            continue;
        }
        answer = opeMod(a, e, m);
        if(answer == 1){
            std::cout << "Ord" << m << "(" << a << ") = " << e;
            if(e == phi)
                std::cout << ",\t" << a << " 是原根";
            std::cout <<std::endl;
            break;
        }
        e++;
    }
}

//计算模m的原根
void findPrimRoot(const int &m){
    int answer;//计算结果
    int e;//指数
    int phi = EularFunction(m);
    
    //选择底数
    for(int a = 1;a < m;a++){
        //筛选简化剩余系
        if(MaxCommonFactor(a, m) != 1)
            continue;
        e = 1;
        while(e < m){
            //指数整除欧拉函数
            if(phi - (phi / e * e) != 0){
                e++;
                continue;
            }
            answer = opeMod(a, e, m);
            if(answer == 1 ){
                if(e == phi)
                    std::cout << "," << a ;
                break;
            }
            e++;
        }
    }
}
#endif /* Chapter5_hpp */
