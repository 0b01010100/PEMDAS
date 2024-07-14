#include "ProbGen.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h> 
#include <ctype.h>

struct _expr
{
    char * str;
    size_t strLen;
    double Ans;
};

expr* expr_create()
{
    expr* e = (expr*)malloc(sizeof(expr));
    if(!e) return NULL;
    memset(e, NULL, sizeof(expr));
    e->str = (char*)malloc(sizeof(char) * 1);
    strcpy(e->str, "");
    return e;
}

bool expr_addConstant(expr* expression, double constant)
{
    if(!expression){
        fprintf(stderr, "the expression pointer was null in expr_addConstant function.\n");
        return false;
    }

    //convert double to cstring
    char u64Str[32];
    int ret = snprintf(u64Str, 32, "%g", constant);
    
    //if the lenght of string '0' no need for a white space
    char White_Space = false;
    if(expression->strLen){
        White_Space = true;
        //append white space
        strcat(expression->str, " ");
    }
    //get the lenght of the string
    expression->strLen = strlen(expression->str) + (size_t)White_Space + strlen(u64Str);
      
    //append constant to string
    strcat(expression->str, u64Str);
    return true;
}

bool expr_addOperator(expr* expression, Arith_Op operator_)
{
    //check for potential errors
    if 
    (
        expression == NULL 
        || 
        operator_ == NULL 
        || 
        expression->strLen == 0
    ) 
    {
        return false;
    }
    //append operator
    char temp[2] = "";
    temp[0] = operator_;
    strcat(expression->str, temp);
    //add in the lenght of the operator
    expression->strLen+=1;
    return true;
}

//TODO: fix this shit of an implementation 

ans expr_evaluate(expr* expression)
{
    //result of a evalu ated equation
    static double result = 0;
    //current character(usefull when we solve sub equations in () and when multiplying)
    static char* currentChar = NULL;
    //current operator to use
    static char currentOperator = '+';
    //suppoed to be the result -- temporary rn
    static union {
        double currentNumber;
        char currentNumber_str[32];
    }u;
    size_t pos = 0;
    char *main_input = expression->str = "2.2 + (1 + 1)";
    static char* currentInput;
    if(currentChar == NULL){
        currentInput = main_input;
    }
    size_t currentInput_size = strlen(currentInput);

    while (pos < currentInput_size) {
        
        if((currentChar = strchr(currentInput, '(')))
        {
            char* currentChar1 = strchr(currentInput, ')');
            size_t offset = currentChar1 - currentChar;
            pos = (size_t)(currentInput + (currentInput - currentChar))+1;
            if(offset == 0) 
            {
                fprintf(stderr, "Error: OFFSET should not be 0\n");
                exit(EXIT_FAILURE);
            }
            strncpy(currentInput, currentChar + 1, offset - 1);
            currentInput[offset - 1] = '\0';
            printf(currentInput);
            expr_evaluate(expression);//recursive to solve sub equations
            printf(u.currentNumber_str);
            printf(u.currentNumber_str);
        }
        
        else if (isdigit(currentInput[pos]) || currentInput[pos] == '.') {
            char str_number[32] = "";
            size_t num_pos = 0;

            while (isdigit(currentInput[pos]) || currentInput[pos] == '.') {
                str_number[num_pos++] = currentInput[pos++];
            }
            switch (currentOperator)
            {
            case Add:
                u.currentNumber += atof(str_number);
                break;
            case Sub:
                u.currentNumber -= atof(str_number);
                break;
            default:
                u.currentNumber = atof(str_number);
                break;
            }
            
        }

        else if (currentInput[pos] == Add || currentInput[pos] == Sub) {
            currentOperator = currentInput[pos];
        }
        pos++;
    }

}

void expr_print_stdout(expr* expression)
{
    if(expression) printf(expression->str);
}

bool expr_print_cstring(const expr* expression, char ** out_str)
{
    if (expression == NULL || out_str == NULL) return false;
    *out_str = malloc(sizeof(char) * (expression->strLen)+1); 
    if(!(*out_str)) return false;
    strcpy(*out_str, expression->str);
    return true;
}