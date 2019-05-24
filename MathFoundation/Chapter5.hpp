//
//  Chapter5.hpp
//  MathBase
//
//  第五章 原根与指标
//  Created by 杨磊 on 2019/5/14.
//  Copyright © 2019 杨磊. All rights reserved.
//

#ifndef Chapter5_hpp
#define Chapter5_hpp

#include "MathFoundation.hpp"
#include <map>

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
//返回原根的数量
int findPrimeRoot(const int &m){
    int answer;//计算结果
    int e;//指数
    int phi = EularFunction(m);
    int count = 0;
    
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
                if(e == phi){
                    std::cout << "," << a ;
                    count ++;
                }
                break;
            }
            e++;
        }
    }
    
    return count;
}

//计算模m最小原根
int minPrimeRoot(const int &p){
    int answer;//计算结果
    int e;//指数
    int phi = EularFunction(p);
    bool found = false;
    
    int g = 2;
    while( g++ < p){
        if(MaxCommonFactor(g, p) != 1)
            continue;
        e = 1;
        while(e++ < p){
            if( phi % e != 0)
                continue;
            answer = opeMod(g, e, p);
            found = (answer == 1)&&(e == phi);
            if(found)break;
        }
        if(found)break;
    }
    return g;
}

//计算模p^a的原根,实际上为计算p的一个原根
//返回模p^a的最小原根
int findPAPrimeRoot(const int &p,const int a = 1,bool printAllRoot = false){
    //先求模p的最小原根
    int g = minPrimeRoot(p);
    
    if( opeMod(g,p-1,p) == 1)
        std::cout << g << " is prime root mod " << p << "^" << a << ".\n";
    if( opeMod(g+p, p-1, p) == 1)
        std::cout << g+p << " is prime root mod " << p << "^" << a << ".\n";
    
    if(printAllRoot){//显示所有的原根
        int phix = EularFunction(pow(p,a));
        int d = 2;
        std::cout << "all root is as follow:\n";
        std::cout << g;
        while(d++ < phix){
            if(MaxCommonFactor(d, phix) != 1)
                continue;
            std::cout << "," << opeMod(g, d, pow(p,a)) ;
        }
        std::cout << std::endl;
    }
    return g;
}

//使用原根简化乘法运算
int multiWithPR(const int &mod,const int &left,const int &right){
    std::map<int,int> table;
    std::map<int,int>::iterator itr;
    //数据初始化
    int g = minPrimeRoot(mod);
    int answer = 0;
    int phi = EularFunction(mod);
    
    //建立指数表
    int i = 0;
    while(i++ < phi){
        table.insert(std::pair<int, int>(opeMod(g,i,mod),i));
    }
    //查找指数
    int lefti,righti;
    itr = table.find(left);
    lefti = itr->second;
    itr = table.find(right);
    righti = itr->second;
    //从指数计算得到结果
    answer = opeMod(g,(lefti + righti) % phi , mod);
    
    return answer;
}
#endif /* Chapter5_hpp */
