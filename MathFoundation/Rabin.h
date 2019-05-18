//
//  Rabin.h
//  编程实现Rabin密码系统
//  MathBase
//
//  Created by 杨磊 on 2019/5/14.
//  Copyright © 2019 杨磊. All rights reserved.
//

#ifndef Rabin_h
#define Rabin_h

/*
 Rabin加密算法的基本流程：
 1.选择两个大素数P、Q，且P = Q = 4k+3
 2.计算N = P * Q
 3.密文CT = (明文PT) ^ 2 (mod N)
 4.求解 密文CT = (明文PT) ^ 2 (mod N) 得到明文
 
 用法：
 Rabin system;//创建实例
 system.runSystem();//运行实例
 */

class Rabin{
    
}
#endif /* Rabin_h */
