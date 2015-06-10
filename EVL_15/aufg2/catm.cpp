#include "catm.h"

CBankAutomat::CBankAutomat() {
    accounts = new int[3];
    pins = new int[3];
    credits = new float[3];
    accounts[0] = 12345;
    accounts[1] = 23456;
    accounts[2] = 34567;
    pins[0] = 1234;
    pins[1] = 2345;
    pins[2] = 3456;
    credits[0] = 5000.0;
    credits[1] = 6000.0;
    credits[2] = 4000.0;
}

CBankAutomat::~CBankAutomat() {
    delete accounts;
    delete pins;
    delete credits;
}

int CBankAutomat::get_account_index(int account) const {
    for(int i = 0; i < 3; i++) {
        if(accounts[i] == account)
            return i;
    }
    return -1;
}

float CBankAutomat::get_credit(int account) const {
    int accountindex = get_account_index(account);
    if(accountindex == -1)
        return -1;
    return credits[accountindex];
}

int CBankAutomat::withdraw(int account, float amount) {
    int accountindex = get_account_index(account);
    if(accountindex == -1)
        return -1;
    if(amount > credits[accountindex])
        return -2;
    credits[accountindex] -= amount;
    return 0;
}

int CBankAutomat::check_login(int account, int pin) const {
    int accountindex = get_account_index(account);
    if(accountindex == -1)
        return 0;
    if(pins[accountindex] == pin)
        return 1;
    return 0;
}