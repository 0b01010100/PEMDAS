//using System;
//using System.Text.RegularExpressions;

//class EquationParser
//{
//    private static readonly Dictionary<string, double> Constants = new Dictionary<string, double>
//    {
//        { "π", Math.PI }
//    };

//    public double Evaluate(string expression)
//    {
     
//        foreach (var symbol in Constants.Keys)
//        {
//            expression = expression.Replace(symbol, Constants[symbol].ToString());
//        }

//        // parentheses first
//        while (expression.Contains("("))
//        {
//            int start = expression.LastIndexOf('(');
//            int end = expression.IndexOf(')', start);
//            string subExpression = expression.Substring(start + 1, end - start - 1);
//            double subResult = Evaluate(subExpression);
//            expression = expression.Substring(0, start) + subResult.ToString() + expression.Substring(end + 1);
//        }

//        // summation ∑(i=start,end,expression)
//        expression = Regex.Replace(expression, @"∑\((.*?),(.*?),(.*?)\)", m =>
//        {
//            int start = int.Parse(m.Groups[1].Value);
//            int end = int.Parse(m.Groups[2].Value);
//            string summationExpr = m.Groups[3].Value;
//            double sumResult = 0;

//            for (int i = start; i <= end; i++)
//            {
//                sumResult += Evaluate(summationExpr.Replace("i", i.ToString()));
//            }

//            return sumResult.ToString();
//        });

//        // factorial n!
//        expression = Regex.Replace(expression, @"(\d+)!$", m =>
//        {
//            int number = int.Parse(m.Groups[1].Value);
//            return Factorial(number).ToString();
//        });

//        //multiplication and division
//        string[] additionSubtractions = Regex.Split(expression, @"(?=[+-])");
//        double result = 0;
//        foreach (string subExpr in additionSubtractions)
//        {
//            if (subExpr.Contains('*') || subExpr.Contains('/'))
//            {
//                string[] multiplicationDivisions = Regex.Split(subExpr, @"(?<=[*/])|(?=[*/])");
//                double subResult = double.Parse(multiplicationDivisions[0]);
//                for (int i = 1; i < multiplicationDivisions.Length; i += 2)
//                {
//                    string op = multiplicationDivisions[i];
//                    double value = double.Parse(multiplicationDivisions[i + 1]);
//                    if (op == "*")
//                        subResult *= value;
//                    else if (op == "/")
//                        subResult /= value;
//                }
//                result += subResult;
//            }
//            else
//            {
//                result += double.Parse(subExpr);
//            }
//        }

//        return result;
//    }

//    // factorial
//    private double Factorial(int n)
//    {
//        if (n == 0 || n == 1) return 1;
//        return n * Factorial(n - 1);
//    }
//}

//class Program
//{
//    static void Main()
//    {
//        EquationParser parser = new EquationParser();

//        string equation = "∑(1,4,i) + 5!";
//        double result = parser.Evaluate(equation);

//        Console.WriteLine($"The result of '{equation}' is {result}");
//    }
//}
