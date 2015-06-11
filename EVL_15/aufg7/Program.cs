using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufg7 {
    class Something {
        public static void SomeMethod(params object[] paramlist) {
            foreach (object param in paramlist) 
                if (param is int)
                    Console.WriteLine((int) param);
        }
    }

    class Program {
        static void Main(string[] args) {
            Something.SomeMethod(1, 3.14, 5, "test", 'c', -7);
        }
    }
}
