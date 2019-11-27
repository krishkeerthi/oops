#pragma once
#include"customer.h"
#include <string>
#include<vector>
using namespace std;
class driver
{
private:
	string taxi_id;
	string driver_name;
	string phone_number;
	char location;
	bool available;
	double start_time;
	double end_time;
	double total_earning;
	vector<customer> customers;

public:
	driver(string,string,string);
	bool is_free(double);
	void set_engaged();
	string get_taxi_id();
	string get_driver_name();
	string get_phone_number();
	void set_phone_number(string);
	void set_driver_name(string);
	char get_location();
	double get_earned();
	void update_location(char);
	void update_start_end_time(double, double);
	void update_earning(double);
	void update_current_booking(customer*);
	void get_report();

};

