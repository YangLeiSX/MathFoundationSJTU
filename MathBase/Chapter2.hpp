//
//  Chapter2.hpp
//  MathBase
//
//  第二章 同余
//  Created by 杨磊 on 2019/5/14.
//  Copyright © 2019 杨磊. All rights reserved.
//

#ifndef Chapter2_hpp
#define Chapter2_hpp

//模m同余类
class DiffMod{};
class Congruence{
private:
    int value;
    int m;
public:
    Congruence(int theM,int theValue = 0){
        m = theM;
        value = theValue % theM;
    }
    Congruence(const Congruence &obj){
        m = obj.m;
        value = obj.value;
    }
    //加法和乘法的重载
    Congruence operator+(const Congruence &obj){
        if(m != obj.m)throw DiffMod();
        Congruence answer(m,value+obj.value);
        return answer;
    }
    
    Congruence operator*(const Congruence &obj){
        if(m != obj.m)throw DiffMod();
        Congruence answer(m,value*obj.value);
        return answer;
    }
    //类型转换
    operator int(){
        return value;
    }
    
};

//计算欧拉函数的值
int EularFunction(int number){
    int answer = 0;
    int i = 1;
    while(i < number){
        if(isCoprime(number, i))
            answer++;
        i++;
    }
    
    return answer;
}

//使用模重复平方算法计算
//base^exp (mod mod)
int opeMod(int base,int exp,int mod){
    //设置初值
    unsigned long answer = 1;
    unsigned long val = base % mod;
    
    while(exp != 0){
        if(exp % 2 == 1){
            answer = (answer *val) % mod;
        }
        exp /= 2;
        val = (val * val) % mod ;
    }
    //设置结果为正
    while(answer <= 0)answer += mod;
    return int(answer % mod);
}

//模平方计算法的交互工具
void opeM(){
    int base,exp,mod;
    std::cout << "enter base:";std::cin >> base;
    std::cout << "enter exp:";std::cin >> exp;
    std::cout << "enter mod:";std::cin >> mod;
    std::cout << "answer is :" << opeMod(base, exp, mod) << std::endl;
}

#endif /* Chapter2_hpp */
