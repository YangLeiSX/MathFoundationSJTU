//
//  RSA.h
//编程实现RSA加密算法
//  MathBase
//
//  Created by 杨磊 on 2019/4/13.
//  Copyright © 2019 杨磊. All rights reserved.
//

#ifndef RSA_h
#define RSA_h

#include <ctime>
#include <cstdlib>
#include <queue>
#include "MathFoundation.hpp"
/*
 RSA加密算法的基本流程：
 1.选择两个大素数P，Q
 2.计算N = P * Q
 3.选择一个大数E，满足（E，(P-1)(Q-1)) = 1 做公钥加密
 4.选择D，满足D * E  = 1（mod （P-1)(Q-1)) 做私钥解密
 5.密文CT = (明文PT) ^ E (mod N)
 6.明文PT = (密文CT) ^ D (mod N)
 
 用法：
 RSA system;//创建实例
 system.runSystem();//运行实例
 */

class RSA{
public:
    RSA();
    ~RSA(){}
    void runSystem();
    
private:
    //用于密钥生成和加解密
    int P;
    int Q;
    int E;
    int D;
    int N;
    int PHI;
    
    //储存密文和明文的编码
    int* plain;
    int* crypto;
    int length;

    //用于密钥生成的辅助函数
    int primeNumGen(int length = 14);
    void printInfo();
    void keyGen();
    //用于加密和解密
    void Encode();
    void Decode();
    //用于交互的辅助函数
//    void getText(std::queue<char> &text);
    void printText(std::queue<char> text);
};

RSA::RSA(){
    P = -1;
    Q = -1;
    E = 65537;
    plain = new int[100];
    crypto = new int[100];
    srand((unsigned int)time(NULL));
}

void RSA::runSystem(){
    char choice;
    //打印信息
    printInfo();
    //输入选择
    while(std::cin.get(choice)){
        switch(choice){
            case 'G'://生成公私钥
                keyGen();break;
            case 'E'://加密
                if(P == -1){
                    std::cout << "please generate key first!\n";
                }else
                    Encode();
                break;
            case 'D'://解密
                Decode();
                break;
            case 'q'://退出
                exit(0);
            default:
                ;
            printInfo();
        }
    }
}

void RSA::printInfo(){
    std::cout << "----------------------------------\n";
    std::cout << "Welcome to RSA system by Yanglei\n";
    std::cout << "keyGen:G\tencode:E\tdecode:D\n";
    std::cout << "Enter your choice(q to quit):\n" ;
    std::cout << "----------------------------------\n";
}

void RSA::keyGen(){//生成密钥
    int noUse;
    //生成随机数
    do{
        P = primeNumGen();
        Q = primeNumGen();
    }while(CommonFactor(P, Q) != 1);
    //计算公钥
    N = P * Q;
    PHI = (P - 1) * (Q - 1);
    //计算私钥
    BezoutEquation(E, PHI, D, noUse);
    while(D <= 0)D += PHI;
    //显示结果
    std::cout << "finish generate key! \n";
    std::cout << "your public key is N:" << N << " and E: " << E << "\n";
    std::cout << "your private key is D:" << D << " P:" << P << " and Q: " << Q << "(please keep it secret!)\n";
    
}

int RSA::primeNumGen(int length){//生成随机数
    int randNum = 1;
    int randTest = 1;
    bool flag = false;

    while(!flag){
        //生成足够长的的随机数
        randNum = (  int)(pow(2,length)) + rand()%((  int)(pow(2,length+1)) - (  int)(pow(2,length)));
        flag = true;
        //初步素性检验
        for(int i = 2;i < 10000;i++){
            if(randNum % i == 0){
                flag = false;//不满足则重新生成
            }
        }
        //费马素性检验
        for(int i = 0;i < 10;i++){
            //检验因素
            randTest = rand();
            if(opeMod(randTest, randNum - 1, randNum) != 1)
                flag = false;//不满足则重新生成
        }
    }

    return randNum;
}

void RSA::Encode(){
    //设置队列
    std::queue<char> tmp;
    std::queue<char> plainText;
    std::queue<char> cryptoText;
    //读入明文
    std::cout << "please enter plain text(no more than 300 characters,use # as end):";
    
    char letter;
    while(std::cin.get(letter)){
        if(letter == '\n'){
            continue;
        }else if(letter == '#'){
            break;
        }else{
            plainText.push(letter);
        }
    }
    //明文画补全
    while( plainText.size() % 3 != 0){
        plainText.push('\0');
    }
    //处理数据
    char plainSet[3];
    char cryptoSet[3];
    int plainVul;
    int cryptoVul;
    length = int(plainText.size())/3;
    
    for(int i = 0;i < length;i++){
        //读取三个字符
        plainSet[0] = plainText.front();plainText.pop();plainText.push( plainSet[0]);
        plainSet[1] = plainText.front();plainText.pop();plainText.push( plainSet[1]);
        plainSet[2] = plainText.front();plainText.pop();plainText.push( plainSet[2]);
        //加密
        plain[i] = plainVul =  plainSet[0] * 128*128 +  plainSet[1]*128 +  plainSet[2];
        cryptoVul = opeMod(plainVul, E, N);
        crypto[i] = cryptoVul;
        //保存密文
        cryptoSet[2] = cryptoVul % 128;
        cryptoSet[1] = cryptoVul / 128 % 128;
        cryptoSet[0] = cryptoVul / 128 / 128 ;
        cryptoText.push( cryptoSet[0]);
        cryptoText.push( cryptoSet[1]);
        cryptoText.push( cryptoSet[2]);
        
    }
    //显示明文
    std::cout << "plainText : ";
    tmp = plainText;
    std::cout << "'";
    while(!tmp.empty()){
        std::cout << tmp.front();
        tmp.pop();
    }
    std::cout << "'";
    std::cout << std::endl;
    //显示密文
    std::cout << "cryptoText : ";
    tmp = cryptoText;
    std::cout << "'";
    while(!tmp.empty()){
        std::cout << tmp.front();
        tmp.pop();
    }
    std::cout << "'";
    std::cout << std::endl;
}

void RSA::Decode(){
    //设置队列
    std::queue<char> tmp;
    std::queue<char> plainText;
    std::queue<char> cryptoText;
    
    //读入选择
    char choice;
    std::cout << "do you want to use crypto text which is just generated?(y/n)";
    std::cin >> choice;
    
    if(choice == 'n'){
        //读入密文
        std::cout << "please enter crypto text(# as end):";
        
        char letter;
        while(std::cin.get(letter)){
            if(letter == '\n'){
                continue;
            }else if(letter == '#'){
                break;
            }else{
                cryptoText.push(letter);
            }
        }
        //补全密文
        while( cryptoText.size() % 3 != 0){
            cryptoText.push('\0');
        }
        
        //处理数据
        char plainSet[3];
        char cryptoSet[3];
        int plainVul;
        int cryptoVul;
        length = int(cryptoText.size())/3;
        for(int i = 0;i < cryptoText.size()/3;i++){
            //密文分组
            cryptoSet[0] = cryptoText.front();cryptoText.pop();cryptoText.push( cryptoSet[0]);
            cryptoSet[1] = cryptoText.front();cryptoText.pop();cryptoText.push( cryptoSet[1]);
            cryptoSet[2] = cryptoText.front();cryptoText.pop();cryptoText.push( cryptoSet[2]);
            //解密
            crypto[i] = cryptoVul =  cryptoSet[0] * 128*128 +  cryptoSet[1]*128 +  cryptoSet[2];
            plain[i] = plainVul = opeMod(cryptoVul, D, N);
            //保存明文
            plainSet[2] = plainVul % 128;
            plainSet[1] = plainVul / 128 % 128;
            plainSet[0] = plainVul / 128 / 128;
            plainText.push( plainSet[0]);
            plainText.push( plainSet[1]);
            plainText.push( plainSet[2]);
            
        }
        //显示明文
        std::cout << "plainText : ";
        tmp = plainText;
        std::cout << "'";
        while(!tmp.empty()){
            std::cout << tmp.front();
            tmp.pop();
        }
        std::cout << "'";
        std::cout << std::endl;
        //显示密文
        std::cout << "cryptoText : ";
        tmp = cryptoText;
        std::cout << "'";
        while(!tmp.empty()){
            std::cout << tmp.front();
            tmp.pop();
        }
        std::cout << "'";
        std::cout << std::endl;
        
    }else if (choice == 'y'){
        //设置变量
        char plainSet[3];
        int plainVul;
        int cryptoVul;
        //读取上一次生成的密文
        for(int i = 0; i <length;i++){
            //解密
            cryptoVul = crypto[i];
            plainVul = opeMod(cryptoVul, D, N);
            //保存明文
            plainSet[2] = plainVul % 128;
            plainSet[1] = plainVul / 128 % 128;
            plainSet[0] = plainVul / 128 / 128;
            plainText.push( plainSet[0]);
            plainText.push( plainSet[1]);
            plainText.push( plainSet[2]);
            
        }
        //显示明文
        std::cout << "plainText : ";
        tmp = plainText;
        std::cout << "'";
        while(!tmp.empty()){
            std::cout << tmp.front();
            tmp.pop();
        }
        std::cout << "'";
        std::cout << std::endl;
    }else{
        std::cout << "please enter y/n!";
    }
}

#endif /* RSA_h */
