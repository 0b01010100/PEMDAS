using System;

class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine(double.Parse("2"));
        if (args.Length == 0)
        {
            Console.WriteLine("Faild: Please provide a file path as a command-line argument.");

            return;
        }
        string filePath = args[0];
        try
        {
            throw new Exception("dd");
            // Read all the content from the file
            string fileContent = File.ReadAllText(filePath);
            Console.WriteLine("Detected Equation:");
            Console.WriteLine(fileContent);
            Console.WriteLine("Solving Equation...");
            
        }
        catch (Exception ex)
        {
            // Handle any exceptions that occur while reading the file
            Console.WriteLine("An error occurred while reading the file:");
            Console.WriteLine(ex.Message);
        }
    }
}