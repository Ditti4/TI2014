#include <iostream>
#include "catm.h"

using namespace std;

int main(int argc, char **argv) {
    CBankAutomat atm;
    int account;
    int pin;
    float amount;
    int menu;

    while(1) {
        cout << "Willkommen am ATM. Bitte Kontonummer und PIN eingeben." << endl;
        cout << "Kontonummer: ";
        cin >> account;
        cout << "PIN: ";
        cin >> pin;
        if(atm.check_login(account, pin)) {
            cout << "Login erfolgreich." << endl;
            do {
                cout << "0) Ausloggen" << endl << "1) Kontostand anzeigen" << endl << "2) Geld abheben" << endl;
                cin >> menu;
                switch(menu) {
                    case 1:
                        cout << "Kontostand: " << atm.get_credit(account) << endl;
                        break;
                    case 2:
                        cout << "Abzuhebenden Betrag eingeben: ";
                        cin >> amount;
                        if(atm.withdraw(account, amount) == -2) {
                            cout << "Sie koennen nicht mehr Geld abheben als sich auf Ihrem Konto befindet." << endl;
                        } else {
                            cout << amount << " Euro erfolgreich abgehoben. Neuer Kontostand: " << atm.get_credit(account) << endl;
                        }
                        break;
                }
            } while(menu != 0);
        } else {
            cout << "Fehler beim Login." << endl;
        }
    }

    return 0;
}
