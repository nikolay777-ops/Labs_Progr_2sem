using System;

namespace Smth
{
  class Human
  {
    private int age;
    public const int abc = 55;

    public int Age
    {
      get
      {
        return age;
      }
      set
      {
        if (value > 120 || value < 1)
        {
          System.Console.WriteLine($"{nameof(value)} must be between 1 and 121!");
          return;
        }

        age = value;
      }
    }
  }

  class App
  {
    public static void ShowHello()
    {
      System.Console.WriteLine("Hello!");
    }

    public static void Main(string[] args)
    {
      string interp;
      int h = 2;
      interp = $"h = {h}";

      System.Console.WriteLine(interp);
      System.Console.WriteLine("Hello world!");
      ShowHello();

      Human hum = new Human();

      int a = Convert.ToInt32(Console.ReadLine());
      hum.Age = a;

      Console.WriteLine($"The human age: {hum.Age}");

      Console.WriteLine($"The human abc: {Human.abc}");
    }
  }
}
