#pragma once
#include<string>
using namespace std;
class customer
{
public:
	customer(string,char,char,double,double);
	string customer_id();
	char pick_point();
	char drop_point();
	double amount();
	double duration();

private:
	string c_id;
	char p_point, d_point;
	double amt, dur;

};

