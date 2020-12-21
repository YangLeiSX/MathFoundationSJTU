//
//  main.cpp
//  MathBase
//  信息安全数学基础课程代码
//  思考题的编程实现
//
//  Created by 杨磊 on 2019/4.
//  Copyright © 2019 杨磊. All rights reserved.
//

#include <iostream>
#include "MathFoundation.hpp"

int main(int argc, const char * argv[]) {
    int msg = 688;
    int crypto = 0;
    int new_msg = 0;
    int pub = 79;
    int mod = 3337;
    int eular = EularFunction(static_cast<int>(mod));
    int priv = 0;
    int noUse = 0;
    int p = 47, q = 71;
    
    BezoutEquation(pub, eular, priv, noUse, true);
    while(priv <= 0) priv += eular;
    
    crypto = opeMod(static_cast<long>(msg), static_cast<long>(pub), static_cast<long>(mod));
    std::cout << "Private Key:" << priv << std::endl;
    std::cout << "Eular Function "  <<  eular << std::endl;
    std::cout << "Crypto:" << crypto << std::endl;
    
    
    new_msg = opeMod(static_cast<long>(crypto), static_cast<long>(priv), static_cast<long>(mod));
    std::cout << "Message: " << new_msg << std::endl;
    
    int crt[2] = {0};
    int crt_mod[2] = {p, q};
    crt[0] = opeMod(static_cast<long>(crypto),
                    opeMod(static_cast<long>(priv), 1, EularFunction(p)),
                    static_cast<long>(p));
    crt[1] = opeMod(static_cast<long>(crypto),
                    opeMod(static_cast<long>(priv), 1, EularFunction(q)),
                    static_cast<long>(q));
    int new_msg2 = ChineseRamainder(crt, crt_mod, 2);
    std::cout << "Message(CRT): " << new_msg2 << std::endl;

    return 0;
}
