#include "flowers.h"
#include <cmath>

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
		return  2 + (index/6)*3;
	}
	if(index%4 == 0 || index%4 == 1)
	{
		return 3*(index/4);
	}
	if(index == 11)
	{
		return 8;
	}
	if(index == 16)
	{
		return 11;
	}
	if(index == 14)
	{
		return 9;
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
	y.numerator = spit(fr,n);
    y.denominator = 1;

    if(n == 1 || spit(fr,n) == 0)
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
		x.numerator = x.numerator + x.denominator*spit(fr,n);
		return x;
    }

}

double getAngle(ContinuedFraction &theta, int k) {
   Fraction frac = getApproximation(theta,7);

   return (frac.numerator*k*2*M_PI)/(frac.denominator);
}

Seed getSeed(ContinuedFraction &theta, int k) {

	Seed s;

	s.x = sqrt(k/M_PI) * cos(getAngle(theta,k));
	s.y = sqrt(k/M_PI) * sin(getAngle(theta,k));

	return s;
}
void pushSeed(std::list<Seed> &flower, ContinuedFraction &theta) {
	Seed s = getSeed(theta,theta.periodicPart[1]);
	flower.push_front(s);
}

int spitNextMagicBox(MagicBox &box) {
    // TODO : add code here
}

ContinuedFraction getCFUsingMB(ContinuedFraction &f, int a, int b, int length) {
    // TODO : add code here
}


