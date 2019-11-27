#include<iostream>
#include <conio.h>
#include <string>
#include<vector>
#include <cmath>
#include <fstream>
#include<sstream>
#include "driver.h"
#include "customer.h"
#include "city_map.h"

using namespace std;

vector<driver> drivers;
//vector<edge> edges = { {'a','b',2},{'a','c',3},{'c','d',5},{'b','d',4}};
//city_map my_city(edges);
city_map my_city;

int driver_count = 0;

void print_welcome();
void admin_services();
void user_services();
void welcome_page(char);
void welcome_page_admin();
void welcome_page_user();
void add_taxis();
void split(const string&, char, vector<string>&);
void check_availability(string, char,char, double);
void get_driver_engaged(driver*, char, char, double,int,string);
double calculate_amount(int);
void report();
void fare_details();
void about();
void read_feedback();
void leave_feedback();
void add_driver();
void remove_driver(string);
void update_driver(string);
void remove_line(string, string);

int main()
{
	
	add_taxis();
	driver_count = drivers.size();
	system("cls");
	char choice;
	while (1)
	{
		print_welcome();
		cout << "Enter your choice" << endl;
		cin >> choice;
		if (choice == 'x')
		{
			cout << "Thank you so much for using our service" << endl;
			system("pause");
			break;
		}
		else
			welcome_page(choice);
		//system("pause");
		system("cls");

	}

}



void print_welcome()
{
	cout << "\t\t\t ****************************\n";
	cout << "\t\t\t * WELCOME TO KRISHNAN CABS *\n";
	cout << "\t\t\t *\t 1.ADMIN                *\n";
	cout << "\t\t\t *\t 2.USER                 *\n";
	cout << "\t\t\t ****************************\n";
}



void user_services()
{
	cout << "\t\t\t ****************************\n";
	cout << "\t\t\t * WELCOME TO KRISHNAN CABS *\n";
	cout << "\t\t\t *\t 1.BOOKING              *\n";
	cout << "\t\t\t *\t 2.AVAILABILITY         *\n";
	cout << "\t\t\t *\t 3.GET FARE DETAILS          *\n";
	cout << "\t\t\t *\t 4.LEAVE FEEDBACK       *\n";
	cout << "\t\t\t *\t 5.READ FEEDBACKS       *\n";
	cout << "\t\t\t *\t 6.CITY MAP INFO       *\n";
	cout << "\t\t\t *\t 7.ABOUT                *\n";
	cout << "\t\t\t *\t 8.EXIT             *\n";
	cout << "\t\t\t ****************************\n";
}

void admin_services()
{
	cout << "\t\t\t ****************************\n";
	cout << "\t\t\t * WELCOME TO KRISHNAN CABS *\n";
	cout << "\t\t\t *\t 1.REPORT               *\n";
	cout << "\t\t\t *\t 2.ADD DRIVER           *\n";
	cout << "\t\t\t *\t 3.REMOVE DRIVER        *\n";
	cout << "\t\t\t *\t 4.UPDATE DRIVER        *\n";
	cout << "\t\t\t *\t 5.ADD LOCATION         *\n";
	cout << "\t\t\t *\t 6.REMOVE LOCATION      *\n";
	cout << "\t\t\t *\t 7.UPDATE LOCATION      *\n";
	cout << "\t\t\t *\t 8.PRINT CITY INFO     *\n";
	cout << "\t\t\t *\t 9.READ FEEDBACKS       *\n";
	cout << "\t\t\t *\t 10.EXIT      *\n";
	cout << "\t\t\t ****************************\n";
}

void welcome_page(char choice)
{
	switch (choice)
	{
	case '1':
		system("cls");
		welcome_page_admin();
		break;

	case '2':
		system("cls");
		welcome_page_user();
		break;
	default:
		cout << "Incorrect selection";
		break;
	}
}

void welcome_page_admin()
{
	int choice;
	string id;
	while (1)
	{
		admin_services();
		cout << "Enter your choice" << endl;
		cin >> choice;
		if (choice == 10)
			break;
		else
		{
			switch (choice)
			{
			case 1:
				report();
				break;

			case 2:
				add_driver();
				break;

			case 3:
				cout << "enter taxi id : \t";
				cin >> id;
				remove_driver(id);
				break;

			case 4:
				cout << "enter taxi id : \t";
				cin >> id;
				update_driver(id);
				break;

			case 5:
				my_city.add_location();
				break;

			case 6:
				my_city.remove_location();
				break;

			case 7:
				my_city.update_location();
				break;

			case 8:
				my_city.city_info();
				break;

			case 9:
				read_feedback();
				break;

			case 10:
				break;
			}
		}

		system("pause");
		system("cls");
	}
}

void welcome_page_user()
{
	char choice;
	while (1)
	{
		user_services();
		cout << "Enter your choice" << endl;
		cin >> choice;

		if (choice == '8')
			break;
		else
		{
			string id;
			char s_point, e_point;
			double time;
			switch (choice)
			{
			case '1':
				//cout << "welcome buddy " << choice << endl;

				cout << "Enter customer id" << endl;
				cin >> id;
				cout << "pickup point" << endl;
				cin >> s_point;
				cout << "drop point" << endl;
				cin >> e_point;
				cout << "start time" << endl;
				cin >> time;

				if (!my_city.check_locations(s_point, e_point))
				{
					cout << "\nbuddy the location you have choosen is not in our list \n get city info and print accordingly";
					system("pause");
					system("cls");
					welcome_page_user();

				}
				check_availability(id, s_point, e_point, time);
				break;
				
			case '2':

				cout << "Enter time" << endl;
				cin >> time;
				cout << "Driver  Availability" << endl;
				for (auto it = drivers.begin(); it < drivers.end(); it++)
				{
					cout << (*it).get_driver_name();
					cout << "\t";
					if ((*it).is_free(time))
						cout << "Free" << endl;
					else
						cout << "Engaged" << endl;;
				}
				break;
			
			case '3':
				fare_details();
				break;
			case '4':
				leave_feedback();
				break;

			case '5':
				read_feedback();
				break;

			case '6':
				my_city.city_info();
				break;

			case '7':
				about();
				break;

			case '8':
				break;

			default:
				cout << "Made wrong selection buddy" << endl;
				break;
			}
		}
		system("pause");
		system("cls");
	}
}


/*void add_taxis(int n,int size)
{
	while (n > 0)
	{
		driver obj("TN"+to_string(size++));
		drivers.push_back(obj);
		n--;
	}
}*/

void add_taxis()
{
	ifstream infile("drivers.txt");
	string line;
	string taxiid,name,phone;
	vector<string> v;
	getline(infile, line);
	while (getline(infile, line))
	{
		split(line, '|', v);
		taxiid = v[0];
		name= v[1];
		phone= v[2];
		
		driver obj(taxiid,name,phone);
		drivers.push_back(obj);
		v.clear();
		//cout << endl;
	}
}

void check_availability(string id, char start, char end, double pick_time)
{
	int prev_distance=INT_MAX,distance,flag=0;
	double prev_earned=DBL_MAX,earned;
	driver *allocated_driver = NULL;
	string driver;
	string taxi_id;
	for (auto it = drivers.begin(); it < drivers.end(); it++)
	{
		
		if ((*it).is_free(pick_time))
		{
			earned = (*it).get_earned();
			distance = my_city.distance(start,(*it).get_location()).second;
			//cout << distance << "\n";
			if ( distance < prev_distance)
			{
				prev_distance = distance;
				prev_earned = earned;
				allocated_driver = &(*it);
				driver = (*it).get_driver_name();
				taxi_id = (*it).get_taxi_id();
				flag = 1;
			}
			else if (distance == prev_distance)
			{
				if (earned < prev_earned)
				{
					prev_earned = earned;
					allocated_driver = &(*it);
					driver = (*it).get_driver_name();
					taxi_id = (*it).get_taxi_id();
					flag = 1;
				}
			}
		}
	}
	if (flag != 0)
	{
		stack<char> route = my_city.distance(start, end).first;
		int dist= my_city.distance(start, end).second;
		cout << "Ha Ha !! Driver : " << driver << "  is assigned for you and Taxi Id is  : " << taxi_id << endl;
		cout << "just check " << (*allocated_driver).get_driver_name() << endl;
		while (!route.empty())
		{
			cout << route.top();
			route.pop();
			cout << "  ->  \t";
		}
		cout << " Ha Ha your destination";
		cout << "\n distance you are gonna travel is " << dist<<"\n";
		get_driver_engaged(allocated_driver, start, end, pick_time,my_city.distance(start,end).second , id);

	}
	else
	{
		cout << "WE ARE PLEASED TO INFORM YOU THAT NO TAXI IS AVAILABLE RIGHT NOW \n SORRY FOR INCONVINIENCE" << endl;
	}


}

void get_driver_engaged(driver *allocated_driver, char start, char end, double pick_time,int travel_distance,string id)
{
	(*allocated_driver).update_start_end_time(pick_time, pick_time + travel_distance);
	(*allocated_driver).update_location(end);
	double amount = calculate_amount(travel_distance);
	(*allocated_driver).update_earning(amount);

	customer cust(id, start, end, travel_distance, amount);

	(*allocated_driver).update_current_booking(&cust);

	ofstream logfile;
	logfile.open("log.txt", ios::app);
	logfile << (*allocated_driver).get_taxi_id() << "\t";
	logfile << id +"   ";
	logfile << start << "\t";
	logfile << end << "\t";
	logfile << to_string(round(pick_time)) << "\t";
	logfile << to_string(round(pick_time+travel_distance)) << "\t";
	logfile << to_string(round(amount)) <<"\n";
	

}

double calculate_amount(int d)
{
	return 200 + (((d * 15)-5 )* 15);
}

void report()
{
	string line;
	ifstream logfile;
	logfile.open("log.txt");
	
	if (logfile.is_open())
	{
		while (getline(logfile, line))
		{
			cout << line<<"\n";
		}
	}
	else
		cout << "unable to open\n";

}

void leave_feedback()
{
	string feedback;
	cout << "Please leave your valuable feedback \n";
	cin.ignore();
	getline(cin,feedback);
	
	ofstream feedbackfile;
	feedbackfile.open("feedback.txt", ios::app);
	feedbackfile << feedback<<"\n";
	feedbackfile.close();

}

void read_feedback()
{
	string line;
	ifstream feedbackfile;
	feedbackfile.open("feedback.txt");

	if (feedbackfile.is_open())
	{
		while (getline(feedbackfile, line))
		{
			cout << line << "\n";
		}
	}
	else
		cout << "unable to open\n";
	feedbackfile.close();
}

void fare_details()
{
	cout << "First 5km costs 200 rupees\n Then each kilometer is 15 rupees";
}

void about()
{
	cout << "KRISHNAN CABS\n";
	cout << "Developed by keerthi\n";
}

void add_driver()
{
	string taxi_id,name, phone;
	cout << "Enter name" << endl;
	cin >> name;
	cout << "Enter phone number" << endl;
	cin >> phone;
	taxi_id = "TN" + to_string(driver_count+1);
	driver d(taxi_id,name,phone);
	drivers.push_back(d);

	ofstream driverfile;
	driverfile.open("drivers.txt", ios::app);
	driverfile << taxi_id<<"|"<<name<<"|"<<phone<< "\n";
	driverfile.close();
}

void remove_driver(string id)
{
	
	for (auto it = drivers.begin(); it < drivers.end(); it++)
	{
		if ((*it).get_taxi_id() == id)
		{
			cout << "Taxi id  " << id << " is removed\n";
			string deleteline,filename="drivers.txt";
			deleteline = (*it).get_taxi_id() + "|" + (*it).get_driver_name() + "|" + (*it).get_phone_number();
			
			remove_line(filename, deleteline);

			drivers.erase(it);
			return;
		}
	}
	cout << "No such Taxi id is available \n";
}

void update_driver(string id)
{
	for (auto it = drivers.begin(); it < drivers.end(); it++)
	{
		if ((*it).get_taxi_id() == id)
		{

			string name,phone,deleteline,includeline,filename="drivers.txt";
			deleteline = (*it).get_taxi_id() + "|" + (*it).get_driver_name() + "|" + (*it).get_phone_number();
			remove_line(filename, deleteline);
			cout << "Enter the driver name\n";
			cin.ignore();
			getline(cin, name);
			cout << "Enter the driver phone number\n";
			cin >> phone;
			(*it).set_driver_name(name);
			(*it).set_phone_number(phone);

			includeline= (*it).get_taxi_id() + "|" + (*it).get_driver_name() + "|" + (*it).get_phone_number();

			ofstream driverfile;
			driverfile.open("drivers.txt", ios::app);
			driverfile << includeline << "\n";
			driverfile.close();
			return;
		}
	}
	cout << "No such Taxi id is available \n";
}

void split(const string &s, char delim, vector<string> &elems) {
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

void remove_line(string filename, string deleteline)
{
	fstream driverfile;
	vector<string> lines;
	string line;
	driverfile.open("drivers.txt", ios::in);

	while (getline(driverfile, line))
	{
		if (line != deleteline)
			lines.push_back(line);
	}

	driverfile.close();

	driverfile.open("drivers.txt", ios::out);
	for (auto l : lines)
		driverfile << l << "\n";
}

