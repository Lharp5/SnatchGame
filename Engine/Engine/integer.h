#ifndef _INTEGER_H
#define _INTEGER_H

class Integer
{
public:
	Integer(int num=0) : i(num) {};
	~Integer();
	operator int() { return i; };
private:
	int i;
};

#endif