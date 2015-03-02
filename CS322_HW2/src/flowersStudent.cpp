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

}

ContinuedFraction ignoreInt(ContinuedFraction f)
{
	if(!f.fixedPart.empty())
	{
		f.fixedPart[0] = 0;
	}
	if(!f.periodicPart.empty() && f.fixedPart.empty())
	{
		f.periodicPart[0] = 0;
	}
	return f;
}

Fraction getApproximation(ContinuedFraction &fr, unsigned int n){

	Fraction *result = new Fraction;
	    int i = n;
	    int temp = 0;
		while (i > 1)
		{
			if (i == n)
			{
				result->numerator = 1;
				result->denominator = spit(fr, i-1);
				i--;
			}
			else
			{
				temp = result->numerator;
				result->numerator = result->denominator;
				result->denominator = result->denominator * spit(fr, i-1) + temp;
				i--;
			}
		}
		if (i == 1)
		{
			result->numerator = result->denominator * spit(fr, i-1) + result->numerator;
		}
		return *result;

}

double getAngle(ContinuedFraction &theta, int k) {
	theta = ignoreInt(theta);
	Fraction frac = getApproximation(theta,7);
	int y = frac.numerator * k;
	auto z = y % frac.denominator;
	return (z*2*M_PI)/frac.denominator;

}

Seed getSeed(ContinuedFraction &theta, int k) {

	Seed s;

	s.x = sqrt(k/M_PI) * cos(getAngle(theta,k));
	s.y = sqrt(k/M_PI) * sin(getAngle(theta,k));

	return s;
}
void pushSeed(std::list<Seed> &flower, ContinuedFraction &theta) {
	Seed s = getSeed(theta,flower.size());
	flower.push_back(s);
}

int spitNextMagicBox(MagicBox &box) {
	int temp1,temp2;

	if(box.l != 0 && box.k != 0)
	{
		if((int)(box.i/box.k) == (int)( box.j/box.l))
		{
			int q = (int)(box.i/box.k);

			temp1 = box.k;
			temp2 = box.l;

			box.k = box.i - (box.k*q);
			box.l = box.j - (box.l*q);

			box.i = temp1;
			box.j = temp2;

			return q;
		}
		if((int)(box.i/box.k) != (int)( box.j/box.l) && box.k != 0 && box.l == 0)
		{
			int p = spit(box.boxedFraction,box.indexInBoxedFraction);
			temp1 = box.j;
			temp2 = box.l;

			box.j = box.i + (box.j*p);
			box.l = box.k + (box.l*p);

			box.i = temp1;
			box.k = temp2;

			return p;
		}
		if((int)(box.i/box.k) != (int)( box.j/box.l) && box.l != 0 && box.k == 0)
		{
			int p = spit(box.boxedFraction,box.indexInBoxedFraction);
			temp1 = box.j;
			temp2 = box.l;

			box.j = box.i + (box.j*p);
			box.l = box.k + (box.l*p);

			box.i = temp1;
			box.k = temp2;

			return p;
		}
	}
	if(box.indexInBoxedFraction == box.boxedFraction.fixedPart.size() && (box.indexInBoxedFraction == box.boxedFraction.periodicPart.size()))
	{
		box.k = box.l;
		box.i = box.j;

	}

}

ContinuedFraction getCFUsingMB(ContinuedFraction &f, int a, int b, int length) {
		MagicBox box;

		while(f.fixedPart.size() < length)
		{
			f.fixedPart.push_back(a + b * spitNextMagicBox(box));
		}

		return f;
}


