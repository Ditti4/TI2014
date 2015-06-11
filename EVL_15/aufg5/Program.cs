using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufg5 {
    class Program {
        static void Main(string[] args) {
            int[] input = new int[10];
            int evenCount = 0;
            for (int i = 0; i < 10; i++)
                input[i] = Convert.ToInt32(Console.ReadLine());
            foreach(int number in input)
                evenCount += 1 - (number % 2);
            // Alternativ:
            // evenCount = input.Where(number => number % 2 == 0).Count();
            Console.WriteLine("Anzahl der geraden Zahlen: " + evenCount);
        }
    }
}
