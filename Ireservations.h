#ifndef IRESERVATIONS_H_INCLUDED
#define IRESERVATIONS_H_INCLUDED

class reservation{

public:
    virtual void getInfo() = 0;
    virtual double getCost() = 0;
    virtual bool reserveThisOne()=  0;
    virtual ~reservation(){}
};


#endif // IRESERVATIONS_H_INCLUDED
