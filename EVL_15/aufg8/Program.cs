using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufg8 {
    class Student {
        private string strName;
        private int iMatNr;
        private bool nameSet = false;
        private bool matNrSet = false;

        public string Name {
            get {
                return strName;
            }
            set {
                if (!nameSet) { // hinzugefügt, damit Wert nur 1x gesetzt werden kann
                    strName = value;
                    nameSet = true;
                }
            }
        }
        public int MatNr {
            get {
                return iMatNr;
            }
            set {
                if (!matNrSet) { // hinzugefügt, damit Wert nur 1x gesetzt werden kann
                    iMatNr = value;
                    matNrSet = true;
                }
            }
        }
    }

    class Program {
        static void Main(string[] args) {
            Student Teststudent = new Student {
                Name = "Andre Becker",
                MatNr = 4001651
            };
            Console.WriteLine("Name: {0}, Matrikel-Nummer: {1}", Teststudent.Name, Teststudent.MatNr);
            Teststudent.Name = "Rico Dittrich";
            Teststudent.MatNr = 4001811;
            Console.WriteLine("Name: {0}, Matrikel-Nummer: {1}", Teststudent.Name, Teststudent.MatNr);
        }
    }
}
