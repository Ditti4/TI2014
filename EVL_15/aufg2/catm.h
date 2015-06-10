#ifndef __CATM_H
#define __CATM_H

class CBankAutomat {
    int *accounts;
    int *pins;
    float *credits;
    int get_account_index(int account) const;
public:
    CBankAutomat();
    ~CBankAutomat();
    float get_credit(int account) const;
    int withdraw(int account, float amount);
    int check_login(int account, int pin) const;
};

#endif