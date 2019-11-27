#include "driver.h"
#include "customer.h"
#include <iostream>
#include <string>
using namespace std;



driver::driver(string id,string d_name,string d_phone)
{
	taxi_id = id;
	driver_name = d_name;
	phone_number = d_phone;
	available = true;
	location = 'a';
	total_earning = 0.0;
	start_time = 0.0;
	end_time = 0.0;
}

bool driver::is_free(double time)
{
	return time >= end_time ? true : false;
}

void driver::set_engaged()
{
	available = false;
}
string driver:: get_taxi_id()
{
	return taxi_id;
}

string driver::get_driver_name()
{
	return driver_name;
}

string driver::get_phone_number()
{
	return phone_number;
}

void driver::set_phone_number(string phone)
{
	 phone_number=phone;
}

void driver::set_driver_name(string d_name)
{
	driver_name= d_name;
}

char driver::get_location()
{
	return location;
}

double driver::get_earned()
{
	return total_earning;
}

void driver::update_location(char loc)
{
	location = loc;
}

void driver::update_earning(double money)
{
	total_earning += money;
}

void driver::update_start_end_time(double s, double e)
{
	start_time = s;
	end_time = e;
}

void driver::update_current_booking(customer *cust)
{
	customers.push_back(*cust);


}

void driver::get_report()
{
	cout << "  taxi_id   cust_id   pick   drop   duration  amount\n";
	for (auto it = customers.begin(); it < customers.end(); it++)
	{
		cout << "\t" << taxi_id;
		cout << "\t" << (*it).customer_id();
		cout << "\t" << (*it).pick_point();
		cout << "\t" << (*it).drop_point();
		cout << "\t" << (*it).duration();
		cout << "\t" << (*it).amount();
		cout << "\n";
	}
}