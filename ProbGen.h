#ifndef __ProbGen__
#define __ProbGen__
#include <stdbool.h>
#include <stdint.h>
//expression
typedef struct _expr expr;

//equation
typedef struct _equa equa;

//Arithmetic Operators
typedef enum _Arith_Op 
{
    //P

    LP = '(',
    RP = ')',
    
    //E

    Exp = '#',
    
    //M

    Mul = '*',

    //D

    Div = '/',
    
    //A

    Add = '+',

    //S

    Sub = '-'
   

}Arith_Op;

typedef double ans;
#ifdef __cplusplus
extern "C" 
{
#endif // __cplusplus
expr* expr_create();

bool expr_addConstant(expr* expression, double constant);

bool expr_addOperator(expr* expression, Arith_Op operator_);

ans expr_evaluate(expr* expression);

void expr_print_stdout(expr* expression);

bool expr_print_cstring(const expr* expression, char ** out_str);
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // __ProbGen__