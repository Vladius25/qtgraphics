#include "calculator.h"
#include <QString>
#include <bits/stdc++.h>
const char SIN = 's';
const char COS = 'c';
const char TG = 't';
const char LN = 'l';
const char SQRT = 'q';

using namespace std;

struct steck
{

    char val;
    double num;
    steck *next;

};

void push(steck *&top, const char x, const double y)
{
    steck *myStack = new steck;

    myStack -> val = x;
    myStack -> num = y;
    myStack -> next = top;

    top = myStack;

}


steck pop(steck *&top)
{
    steck *myStack = top;
    if(!top)
        throw 0;

    top = top -> next;

    return *myStack;

}

char top(steck *top)
{
    if(top)
        return top -> val;
    else
        return '0';

}

int getPriority(char x)
{

    switch (x)
    {
    case ')':
    case '(':
        return 1;


    case '+':
    case '-':
        return 2;


    case '*':
    case '/':
        return 3;

    case '^':
        return 4;

    case -'-':
        return 5;

    case '0':
        return 0;

    default:
        return 6;
    }
}


double func(char x, steck *&p2)
{



    switch (x)
    {

    case '+':{
          double a = pop(p2).num, b = pop(p2).num;

        return a+b;
    }
    case '-':
    {
        double a = pop(p2).num, b = pop(p2).num;
        return b - a;

    }
    case '*':
        return pop(p2).num*pop(p2).num;

    case '/':
    {
        double a = pop(p2).num, b = pop(p2).num;
        if(a == 0) throw 0;
        return b/a;

    }

    case '^':
        return pow(pop(p2).num, pop(p2).num);

    case -'-':
    {
        double a = pop(p2).num;
        if(a == 0) return 0;
        return -1*a;
    }
    case SIN:
        return sin(pop(p2).num);

    case COS:
        return cos(pop(p2).num);

    case TG:
        return tan(pop(p2).num);

    case LN:
    {
        double a = pop(p2).num;
        if(a <= 0) throw 0;
        return log(a);
    }
    case SQRT:
    {
        double a = pop(p2).num;
        if(a < 0) throw 0;
        return sqrt(a);
    }
    default:
        throw 0;


    }
}

double calc(string expr)
{

    steck *p = 0;
    steck *p2 = 0;
    string number = "";
    bool mayUnary = true;
    double num;


        for(unsigned int i = 0; i <expr.size(); i++, number = "")
        {
            char x = expr[i];
            if(!isblank(x))
            {
                if(x == '(')
                {
                    push(p, x, 0);
                    mayUnary = true;
                }

                else if(x == ')')
                {
                    char sym = pop(p).val;
                    mayUnary = false;

                    while(sym != '(')
                    {

                        push(p2, 0, func(sym, p2));
                        sym = pop(p).val;
                    }


                }

                else if(isdigit(x))
                {

                    while(isdigit(expr[i]) || expr[i] == '.')
                    {
                        number += expr[i];
                        i++;
                    }

                    if(expr[i] == '(' || expr[i-number.size()-1] == ')' || count(number.begin(), number.end(), '.') > 1)
                        throw 0;

                    num = QString::fromStdString(number).toDouble();
                   // sscanf(number.c_str(), "%f", &num);

                     //printf("%.2f", num);

                    push(p2, 0, num);

                    i--;

                    mayUnary = false;

                }

                else
                {

                    if (mayUnary && x == '-')  x = -x;

                    while((getPriority(x) != 4 && getPriority(x) <= getPriority(top(p))) || (getPriority(x) >= 4 && getPriority(x) < getPriority(top(p))))
                        push(p2, 0, func(pop(p).val, p2));

                    push(p, x, 0);

                    mayUnary = false;
                }

            }

        }
        while(p!=0)
        {
            push(p2, 0, func(pop(p).val, p2));
        }

        double ff = pop(p2).num;
       // printf("%.2f", ff);
        return ff;



}

Calculator::Calculator(){


}

double Calculator::eval(QString qstr, double i)
{
    if(qstr[0] == '-')
        qstr = "0" + qstr;
    qstr.replace("sin", "s");
    qstr.replace("cos", "c");
    qstr.replace("tg", "t");
    qstr.replace("ln", "l");
    qstr.replace("sqrt", "q");

    qstr.replace("x", "(0.1*("+QString::number(i)+"))");
   string expr = qstr.toUtf8().constData();

    //printf("%s\n", expr.c_str());

   return  calc(expr);

}
