#include "ProbGen.h"
int main()
{
    expr * e = expr_create();
    expr_addConstant(e, 400);
    expr_addOperator(e, Exp);
    expr_addConstant(e, 2);

    expr_evaluate(e);

    expr_print_stdout(e);
    return 0;
}