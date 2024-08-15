using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EquationParser
{
    public class Token 
    {
        public
        enum Token_Type : uint
        {
            Token_Type_INVALID = 0,

            // Parentheses
            Token_Type_OPAREN, // (
            Token_Type_CPAREN, // )

            // Square brackets
            Token_Type_OSQUARE, // [
            Token_Type_CSQUARE, // ] 

            // Curly braces
            Token_Type_OCURLY, // {
            Token_Type_CCURLY, // }

            // Angle brackets
            Token_Type_OANGLE, // <
            Token_Type_CANGLE, // >

            // Identifiers and numbers
            Token_Type_IDENTIFIER, // Variable name
            Token_Type_NUMBER, // Number

            // Constants
            Token_Type_PI, // 3.14....
            Token_Type_e, // 2.7...

            // Exponentiation
            Token_Type_Ex, // ^

            // Scientific notation
            Token_Type_E, // E

            // Calculus symbols
            Token_Type_INTE, // ∫(
            Token_Type_SUM, // ∑(
            Token_Type_PRODN, // ∏(

            // Arithmetic operations
            Token_Type_Add, // +
            Token_Type_Mul, // *
            Token_Type_Div, // /
            Token_Type_Rem, // %

            // Bitwise operations
            Token_Type_Bitwise_AND, // &
            Token_Type_Bitwise_OR, // |
            Token_Type_Bitwise_XOR, // ~^
            Token_Type_Bitwise_NOT, // ~
            Token_Type_Left_Shift, // <<
            Token_Type_Right_Shift, // >>

            // Additional tokens can be added here
        }


        public Token next;        
        public double value;       
        public string str;
        public Token_Type type;
    }
    public class TokenStream
    {
        public void Add(Token token) 
        {
            if (first == null)
            {
                // Adding the first token
                first = token;
                last = token;
            }
            else
            {
                // Adding to the end of the list
                last!.next = token;
                last = token;
            }
            count++;
        }

        public Token? first = null;
        public Token? last = null;
        public ulong count; // size_t
    }
}
