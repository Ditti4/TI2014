#ifndef __VOGEL_H
#define __VOGEL_H

#include "tier.h"

class CVogel: public CTier {
public:
    CVogel(string name);
    virtual void KannEtwas();
};

#endif