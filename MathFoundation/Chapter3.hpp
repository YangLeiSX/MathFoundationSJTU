//
//  Chapter3.hpp
//  MathBase
//
//  第三章 同余式
//  Created by 杨磊 on 2019/5/14.
//  Copyright © 2019 杨磊. All rights reserved.
//

#ifndef Chapter3_hpp
#define Chapter3_hpp

//使用贝祖等式计算模m逆元的交互式工具
void opeE(){
    int origin,answer,modx,noUse;
    std::cout << "enter origin:";std::cin >> origin;
    std::cout << "enter mod:";std::cin >> modx;
    BezoutEquation(origin, modx, answer, noUse);
    //设置结果为正
    while(answer <= 0)answer += modx;
    std::cout << "the answer:" << answer << std::endl;
}

//编程计算中国剩余定理
//参数为两个数组和一个数，分别是同余式组的值和模以及同余式组的个数
int ChineseRamainder(int* b,int* m,int size,bool printResult = false){
    //声明变量
    int* M;
    int* oppoM;
    int mq = 1;
    int noUse,answer = 0;
    M = new int[size];
    oppoM = new int [size];
    
    //设定初始值
    for(int i = 0; i < size;i++){
        mq *= m[i];
    }
    
    for(int i = 0;i < size;i++){
        M[i] = mq / m[i];
    }
    
    for(int i = 0;i < size;i++){
        BezoutEquation(M[i], m[i], oppoM[i], noUse,false);
        while(oppoM[i] < 0)oppoM[i] += m[i];
    }
    
    //求和计算结果
    for(int i = 0;i < size;i++){
        answer += b[i]*oppoM[i]*M[i];
    }
    
    //得到最小非负解
    answer = answer % mq;
    
    //显示运算结果
    if(printResult){
        std::cout << "the answer is:\n";
        std::cout << "x = " << answer << " + q * " << mq << std::endl;;
    }
    
    return answer;
}

//多项式类的实现
class Polynomial{
private:
    //节点类的定义
    struct Node{
        int factor;
        int exponent;
        
        Node(int fac,int exp){
            factor = fac;
            exponent = exp;
        }
    };
    std::list<Node> content;
    
    //辅助函数
    void removeZero(){
        std::list<Polynomial::Node>::iterator itr;
        itr = content.begin();
        while(itr != content.end()){
            if(itr->factor == 0){
                content.erase(itr);
            }
            itr++;
        }
    }
    
    int calculate(const int &mod,const int &x){
        std::list<Polynomial::Node>::iterator itr = content.begin();
        int answer = 0;
        for(int i = 0 ; i < content.size();i++,itr++){
            answer += int(itr->factor * pow(x,itr->exponent)) % mod;
        }
        return answer % mod;
    }
    //多项式欧几里得除法
    friend void EuclidDivide(Polynomial dividend,int &mod,Polynomial &remainder,bool symplify);
    friend void EuclidDivide(Polynomial dividend,int &mod,Polynomial &quotient,Polynomial &remainder,bool symplify);
    
public:
    //构造函数
    Polynomial(){}
    
    Polynomial(const Polynomial &obj){
        content = obj.content;
    }
    
    Polynomial(const Node &n){
        content.push_back(n);
    }
    
    Polynomial(const int &fac,const int &exp){
        content.push_back(Node(fac,exp));
    }
    
    Polynomial(const int *facs,const int *exps,const int size){
        for(int i = 0;i < size;i++){
            content.push_back(Node(facs[i],exps[i]));
        }
    }
    
    ~Polynomial(){
        this->clear();
    }
    
    //交互式赋值
    void assignValue(){
        int fac,exp;
        std::cout << "please enter fac and exp:";
        while(std::cin >> fac >> exp){
            content.push_back(Node(fac,exp));
            std::cout << "please enter fac and exp:";
        }
        std::cin.clear();
        
    }
    //显示多项式的内容
    void printPoly(){
        std::list<Node>::iterator itr;
        itr = content.begin();
        
        while(itr != content.end()){
            if(itr != content.begin())
                std::cout << " + ";
            std::cout << itr->factor << "*x^" << itr->exponent << " ";
            itr++;
        }
    }
    
    //重载算术运算符
    Polynomial operator+(Polynomial obj);
    
    Polynomial operator-(Polynomial obj);
    
    Polynomial operator*(Polynomial &obj);
    
    Polynomial operator/(Polynomial obj);
    
    void clear();
    
    bool empty()const;
    
    bool getHead(int &factor,int &exponent)const;
    
    //重载逻辑运算符
    bool operator<(const Polynomial &obj)const;
    
    bool operator>(const Polynomial &obj)const;
    
    bool operator==(const Polynomial &obj)const;
    
    bool operator!=(const Polynomial &obj)const;
    
    //求解同余式
    void solve(const int &mod,const int rValue);
    
};

Polynomial Polynomial::operator+(Polynomial obj){
    Polynomial answer;
    Polynomial left = *this;
    while(!obj.content.empty() || !left.content.empty()){
        if(left.content.empty()){
            answer.content.push_back(obj.content.front());
            obj.content.pop_front();
        }else if(obj.content.empty()){
            answer.content.push_back(left.content.front());
            left.content.pop_front();
        }else if(left.content.front().exponent == obj.content.front().exponent){
            answer.content.push_back(Node(left.content.front().factor + obj.content.front().factor,left.content.front().exponent));
            left.content.pop_front();
            obj.content.pop_front();
        }else if(left.content.front().exponent > obj.content.front().exponent){
            answer.content.push_back(left.content.front());
            left.content.pop_front();
        }else{
            answer.content.push_back(obj.content.front());
            obj.content.pop_front();
        }
    }
    
    return answer;
}

Polynomial Polynomial::operator-(Polynomial obj){
    Polynomial answer;
    Polynomial left = *this;
    
    while(!obj.content.empty() || !left.content.empty()){
        if(left.content.empty()){
            answer.content.push_back(Node(-obj.content.front().factor,obj.content.front().exponent));
            obj.content.pop_front();
        }else if(obj.content.empty()){
            answer.content.push_back(left.content.front());
            left.content.pop_front();
        }else if(left.content.front().exponent == obj.content.front().exponent){
            answer.content.push_back(Node(left.content.front().factor - obj.content.front().factor,left.content.front().exponent));
            left.content.pop_front();
            obj.content.pop_front();
        }else if(left.content.front().exponent > obj.content.front().exponent){
            answer.content.push_back(left.content.front());
            left.content.pop_front();
        }else{
            answer.content.push_back(Node(-obj.content.front().factor,obj.content.front().exponent));
            obj.content.pop_front();
        }
    }
    answer.removeZero();
    return answer;
}

Polynomial Polynomial::operator*(Polynomial &obj){
    Polynomial answer;
    std::list<Polynomial::Node>::iterator itr1,itr2;
    itr1 = content.begin();
    itr2 = obj.content.begin();
    
    for(int i = 0;i < content.size();i++){
        for(int j = 0;j < obj.content.size();j++){
            answer = answer + Polynomial(itr1->factor * itr2->factor, itr1->exponent + itr2->exponent);
            itr2++;
        }
        itr1++;
        itr2 = obj.content.begin();
    }
    answer.removeZero();
    return answer;
}

Polynomial Polynomial::operator/(Polynomial obj){
    Polynomial answer;
    Polynomial *tmp;
    Polynomial dividend = *this;
    std::list<Polynomial::Node>::iterator itr1;
    std::list<Polynomial::Node>::iterator itr2;
    itr2 = obj.content.begin();
    
    while(dividend > obj){
        itr1 = dividend.content.begin();
        tmp = new Polynomial(itr1->factor / itr2->factor , itr1->exponent - itr2->exponent);
        answer = answer + *tmp;
        dividend = dividend - *tmp * obj;
    }
    
    return answer;
}
bool Polynomial::operator<(const Polynomial &obj)const{
    if(content.front().exponent < obj.content.front().exponent)
        return true;
    else if(content.front().exponent == obj.content.front().exponent && content.front().factor < obj.content.front().factor)
        return true;
    else
        return false;
}

bool Polynomial::operator>(const Polynomial &obj)const{
    if(content.front().exponent > obj.content.front().exponent)
        return true;
    else if(content.front().exponent == obj.content.front().exponent && content.front().factor > obj.content.front().factor)
        return true;
    else
        return false;
}

bool Polynomial::operator==(const Polynomial &obj)const{
    return !(*this>obj)&&!(*this<obj);
}

bool Polynomial::operator!=(const Polynomial &obj)const{
    return !(*this == obj);
}

void Polynomial::clear(){
    while(!content.empty()){
        content.pop_back();
    }
}

bool Polynomial::empty()const{
    return content.empty();
}

bool Polynomial::getHead(int &factor,int &exponent)const{
    if(empty()){
        return false;
    }else{
        factor = content.front().factor;
        exponent = content.front().factor;
        return true;
    }
}

void Polynomial::solve(const int &mod, const int rValue = 0) {
    bool flag = false;
    for(int i = 0;i < mod;i++){
        if(calculate(mod,i) == rValue){
            flag =  true;
            std::cout << "one of the answer is " << i << "\n";
        }
    }
    if(!flag){
        std::cout << "Sorry, no solution." << std::endl;
    }
}

//使用简化方法计算多项式的欧几里得除法
//symplufy为true时 显示系数取同余后的等价余式
void EuclidDivide(Polynomial dividend,int &mod,Polynomial &remainder,bool symplify = false){
    Polynomial *tmp;
    remainder.clear();
    
    while(!dividend.content.empty()){
        tmp = new Polynomial(dividend.content.front().factor,dividend.content.front().exponent % (mod - 1));
        remainder = remainder + *tmp;
        dividend.content.pop_front();
    }
    
    if(symplify){
        std::list<Polynomial::Node>::iterator itr;
        int i;
        for(i= 0,itr = remainder.content.begin();i < remainder.content.size();i++,itr ++){
            itr->factor = itr->factor % mod;
        }
    }
}

//使用多项式类的算术运算计算多项式的欧几里得除法
//symplufy为true时 得到最简化同余式
void EuclidDivide(Polynomial dividend,int &mod,Polynomial &quotient,Polynomial &remainder,bool symplify = false){
    quotient.clear();
    remainder.clear();
    int facs[] = {1,-1};
    int exps[] = {mod,1};
    Polynomial divisor(facs,exps,2);
    quotient = dividend / divisor;
    remainder = dividend - divisor * quotient;
    
    if(symplify){
        std::list<Polynomial::Node>::iterator itr;
        int i;
        for(i= 0,itr = remainder.content.begin();i < remainder.content.size();i++,itr ++){
            itr->factor = itr->factor % mod;
        }
    }
}


#endif /* Chapter3_hpp */
