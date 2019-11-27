#include "customer.h"
#include<string>
using namespace std;

customer::customer(string id,char pick,char drop,double duration,double amount)
{
	c_id = id;
	p_point = pick;
	d_point = drop;
	dur = duration;
	amt = amount;

}

string customer::customer_id()
{
	return c_id;
}
char customer::pick_point()
{
	return p_point;
}
char customer::drop_point()
{
	return d_point;
}
double customer::amount()
{
	return amt;
}
double customer::duration()
{
	return dur;
}

