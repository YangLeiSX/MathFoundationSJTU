// MathFoundation.hpp
// MathBase
// 信息安全的数学基础课程依赖库
// 实现信息安全的数学基础运算
//
//  Created by 杨磊 on 2019/4.
//  Copyright © 2019 杨磊. All rights reserved.
//

#ifndef MathFoundation_hpp
#define MathFoundation_hpp

#include <cmath>
#include <vector>
#include <list>
#include <algorithm>

//使用欧几里得除法计算最大公因数，两个参数为给定的两个整数，返回值为最大公因数
int MaxCommonFactor(const int numa, const int numb){
    int a,b,r;
    if(numa == 0 && numb == 0){
        return -1;//不存在最大公因数
    }
    if(numa == 0 || numb == 0){
        return (numa == 0 ? numb:numa);//0和任意数A的最大公因数为A
    }
    //设置初始值
    a = abs(numa) > abs(numb)? abs(numa):abs(numb);
    b = abs(numa) < abs(numb)? abs(numa):abs(numb);
    r = abs(numa);
    //迭代相除
    while(r != 0){
        r = a%b;
        a = b;
        b = r;
    }
    return a;
}

//使用最大公因数判断两个整数是否互质/互素
bool isCoprime(const int numa,const int numb){
    return (MaxCommonFactor(numa, numb) == 1);
}

//计算Bezout等式，前两个参数为给定的整数，后两个参数为计算得到的系数的引用
//printResult为真时，输出 s*a+t*b = (a,b)
void BezoutEquation(const int a,const int b,int & s,int & t,bool printResult = true){
    std::vector<int> va,vb,vq,vr;//存放计算得到的序列
    std::vector<int>::iterator itr;
    std::vector<int> ans;//存放反向迭代得到的参数
    
    //特殊情况的处理
    if(a == 0 || b == 0){
        if(a == 0 && b == 0){
            s = t = 0;
            std::cout << "a and b should not be both 0 \n";
            return ;
        }
        s = (a == 0? 0:1);
        t = (b == 0? 0:1);
        std::cout << s << " * " << a << " + "
        << t << " * " << b << " = "
        << "(" << a << "," << b << ") = "
        << MaxCommonFactor(a,b) << "\n" ;
        return ;
    }
    //赋初值
    va.push_back(abs(a) > abs(b)? abs(a):abs(b));
    vb.push_back(abs(a) < abs(b)? abs(a):abs(b));
    //计算a=q*b+r
    while(true){
        vq.push_back(va.back()/vb.back());
        vr.push_back(va.back()%vb.back());
        if(vr.back() == 0)break;
        va.push_back(vb.back());
        vb.push_back(vr.back());
    }
    //为便于计算，移除最后r=0的系数并反转
    vq.pop_back();
    std::reverse(vq.begin(),vq.end());
    //赋初值
    ans.push_back(-vq[0]);
    ans.push_back(1);
    //反向代回
    for(int i = 1; i < vq.size();i++){
        ans[i] -= ans[i-1] * vq[i];
        ans.push_back(ans[i-1]) ;
    }
    //为便于导出结果，移除最后一次的push并反转
    ans.pop_back();
    std::reverse(ans.begin(), ans.end());
    //得到与输入相符合的结果
    s = (a<b?ans[0]:ans[1]);
    t = (a<b?ans[1]:ans[0]);
    //输出结果
    if(printResult){
        std::cout << s << " * " << a << " + "
        << t << " * " << b << " = "
        << "(" << a << "," << b << ") = "
        << MaxCommonFactor(a,b) << "\n" ;
    }
    return ;
}

//使用递归方法计算欧几里得除法，前两个参数为被除数和除数，后两个参数为商和余数的引用
//形式为：dividend = qoutient * divisor + remainder
void EuclidDivide(const int dividend, const int divisor, int &quotient, int &remainder){
    if(dividend < divisor){//递归终止条件
        remainder = dividend;
        return ;
    }
    else{
        quotient += 1;
        EuclidDivide(dividend - divisor, divisor, quotient, remainder);
    }
}

//使用欧几里得除法判断素数
//printInfo 为真时输出：number is multiple of i
bool isPrime(const int number,bool printInfo = false){
    int quo = 0,re = 0;
    for(int i = 2;i <= sqrt(number);i++){//这里i的取值还可以进一步优化
        EuclidDivide(number, i, quo, re);
        if(re == 0){
            if(printInfo)std::cout << number << " is multiple of " << i << "\n";
            return false;
        }
    }
    return true;
}

//判断素数的交互式工具
void isPrimeNum(){
    int number;
    std::cout << "please enter a number:";
    std::cin >> number;
    if(isPrime(number)){
        std::cout << number << " is prime\n" ;
    }
    else{
        std::cout << number << " is not prime\n";
    }
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

//计算因数次数的辅助函数
//判断因数的次数
int countFactor(int number, int factor){
    int exp = 0;
    
    while(number % factor == 0){
        exp ++;
        number /= factor;
    }
    return exp;
}

//分解素因数
void findFactor(const int number,bool printResult = false){
    int factor = 1;
    std::list<int> factors;
    std::list<int> exps;
    
    while(factor <= number){
        factor ++;
        //除去非素因数的情况
        if(!isPrime(factor))continue;
        if(number % factor != 0)continue;
        factors.push_back(factor);
        exps.push_back(countFactor(number, factor));
    }
    //打印结果
    if(printResult){
        std::cout << std::endl << number << " = ";
        while(!factors.empty()){
            std::cout << factors.front() << " ^ " << exps.front() << " ";
            if(factors.size() != 1){
                std::cout << " * ";
            }
            factors.pop_front();
            exps.pop_front();
        }
    }
}


//分解质因数的交互式工具
void opeFF(void){
    int number = 0;
    std::cout << "please enter the number:";
    std::cin >> number;
    std::cout << "the answer is:";
    findFactor(number,true);
    
}

//使用贝祖等式计算不定方程
//方程形式：factor1 * x + factor2 = rightValue
bool DiophantineEquation(int factor1,int factor2,int rightValue,bool printResult = true){
    int x,y;
    int CF = MaxCommonFactor(factor1, factor2);
    int ratio = rightValue / CF;
    
    if(rightValue % CF != 0){
        if(printResult){
            std::cout << "the equation " << factor1 << " * x + " << factor2 << " * y = " << rightValue
            << " have no solution" << std::endl;
        }
        return false;
    }
    BezoutEquation(factor1, factor2, x, y);
    x *= ratio;
    y *= ratio;
    if(printResult){
        std::cout << "Special solution: x = " << x << " , y = " << y << std::endl;
        std::cout << "Common solution: x = " << x << " - " << factor2/CF << " * t , y = "
        << y << " + " << factor1/CF << " * t . (t = 1,2,3...)" << std::endl;
        
    }
    return true;
}

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


//雅可比符号的计算
int JacobiSignal(int up, int down){
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
#endif /*MathFoundation_hpp*/
