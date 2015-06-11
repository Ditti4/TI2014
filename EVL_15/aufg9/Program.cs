using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufg9 {
    interface Tier {
        string Name { get; set; }
        void KannEtwas();
    }

    class Vogel : Tier {
        private string _name;
        public string Name {
            get {
                return _name;
            }
            set {
                _name = value;
            }
        }
        public void KannEtwas() {
            Console.WriteLine("{0} kann fliegen.", Name);
        }
    }

    class Fisch : Tier {
        private string _name;
        public string Name {
            get {
                return _name;
            }
            set {
                _name = value;
            }
        }
        public void KannEtwas() {
            Console.WriteLine("{0} kann schwimmen.", Name);
        }
    }

    class Program {
        static void Main(string[] args) {
            Tier fisch = new Fisch {
                Name = "Fisch"
            };
            Tier vogel = new Vogel {
                Name = "Vogel"
            };

            fisch.KannEtwas();
            vogel.KannEtwas();
        }
    }
}
