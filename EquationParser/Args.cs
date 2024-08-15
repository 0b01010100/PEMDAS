using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EquationParser
{
    static class Args
    {
        public
        static void Parser(string[] args) 
        {
            int argc = args.Length;
            string[] argv = args;
            
            for (int i = 1; i < argc; i++)
            {
                ReadOnlySpan<char> stringView = argv[i].AsSpan(0, argv[i].Length);
                char firstChar = argv[1].Trim().FirstOrDefault();

                if (firstChar == '-')
                {
                    Console.WriteLine("The first character of the second argument is '-'.");
                }
                else
                {
                    Console.WriteLine("The first character of the second argument is not '-'.");
                }
            }
        }
    }
}
