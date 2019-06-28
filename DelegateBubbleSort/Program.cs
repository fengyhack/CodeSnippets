using System;
using System.Collections.Generic;

namespace BubbleSortDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            Employee[] employees =
            {
                new Employee("Locky",2000.0m),
                new Employee("Daffy",2800.0m),
                new Employee("Rood",1200.0m),
                new Employee("Yang",3000.0m)
            };

            foreach (var e in employees)
            {
                Console.WriteLine(e);
            }

            BubbleSorter.Sort(employees, Employee.CompareSalary);

            Console.WriteLine("===============");
            foreach(var e in employees)
            {
                Console.WriteLine(e);
            }

            Console.WriteLine("\nPress any key to continue...");
            Console.ReadKey();
        }
    }

    class BubbleSorter
    {
        public static void Sort<T> (IList<T> srcArray, Func<T,T,bool> compare)
        {
            bool swapped = true;
            int count=srcArray.Count;
            do
            {
                swapped = false;
                for (int i = 0; i < count - 1; ++i)
                {
                    if (compare(srcArray[i], srcArray[i + 1]))
                    {
                        T tmp = srcArray[i];
                        srcArray[i] = srcArray[i + 1];
                        srcArray[i + 1] = tmp;
                        swapped = true;
                    }
                }
            } while (swapped);
        }
    }

    class Employee
    {
        public Employee(string name,decimal salary)
        {
            Name = name;
            Salary = salary;
        }

        public string Name { get; private set; }
        public decimal Salary { get; private set; }

        public override string ToString()
        {
            return string.Format("{0}, {1}", Name, Salary);
        }

        public static bool CompareSalary(Employee e1,Employee e2)
        {
            return (e1.Salary < e2.Salary);
        }

    }

}
