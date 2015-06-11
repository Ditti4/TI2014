using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufg6 {
    class Something {
        public static void Berechne(int a, int b, out float sum, out float average) {
            sum = a + b;
            average = ((float) (a + b)) / 2;
        }
    }

    class Program {
        static void Main(string[] args) {
            int a, b;
            float sum, average;
            Console.WriteLine("Bitte zwei Werte eingeben.");
            a = Convert.ToInt32(Console.ReadLine());
            b = Convert.ToInt32(Console.ReadLine());
            Something.Berechne(a, b, out sum, out average);
            Console.WriteLine(String.Format("a = {0}\tb = {1}\nSumme = {2}\tDurchschnitt = {3}", a, b, sum, average));
        }
    }
}
