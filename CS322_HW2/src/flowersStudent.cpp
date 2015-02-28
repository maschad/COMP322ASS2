#include "flowers.h"

unsigned int spitEulerSquare(unsigned int index) {
	if(index ==0)return 7;
	if(index == 1) return 2;
	if(index%5 == 3 || index%5 == 2) return 1;
	if(index%5 == 0)
	{
		return 6 + (index/5)*12;
	}
	if(index%6 == 0)
	{
		return 2 + (index/6)*3;
	}
	if(index%4 == 0)
	{
		return (index/4)*3;
	}

}

ContinuedFraction ignoreInt(ContinuedFraction f)
{
	f.fixedPart[0] = 0;
	return f;
}

Fraction getApproximation(ContinuedFraction &fr, unsigned int n){

	fr = ignoreInt(fr);

    Fraction y;
    y.numerator= fr.fixedPart[1];
    y.denominator = 1;

    if(n == 1 || fr.fixedPart[1] == 0)
    {
    	return y;
    }
    else
    {
		Fraction x = getApproximation(fr,n-1);
		Fraction temp;
		temp.numerator = x.numerator;
		temp.denominator = x.denominator;
		x.denominator = temp.numerator;
		x.numerator = temp.denominator;
		x.numerator = x.numerator + x.denominator*fr.fixedPart[0];
		return x;
    }

}

double getAngle(ContinuedFraction &theta, int k) {
   Fraction frac = getApproximation(theta,7);

   return (frac.numerator*k)/(frac.denominator);
}

Seed getSeed(ContinuedFraction &theta, int k) {
    // TODO : add code here
}

void pushSeed(std::list<Seed> &flower, ContinuedFraction &theta) {
    // TODO : add code here
}

int spitNextMagicBox(MagicBox &box) {
    // TODO : add code here
}

ContinuedFraction getCFUsingMB(ContinuedFraction &f, int a, int b, int length) {
    // TODO : add code here
}


