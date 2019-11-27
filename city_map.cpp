#include "city_map.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <queue>
#include<stack>
#define inf INT_MAX
using namespace std;


/*city_map::city_map(vector<edge> const &edges)
{
	for (auto edge : edges)
	{
		char src = edge.src;
		char dest = edge.dest;
		int weight = edge.weight;

		my_map[src].push_back(make_pair(dest, weight));
		my_map[dest].push_back(make_pair(src, weight));
	}
	
	setup();
	dijkstras();
}*/

city_map::city_map()
{
	ifstream infile("location.txt");

	string line;
	vector<string> v;
	char src, dest;
	int distance;
	getline(infile, line);
	while (getline(infile, line))
	{
		split(line, '|', v);
		src = v[0][0];
		dest = v[1][0];
		distance = stoi(v[2]);
		my_map[src].push_back(make_pair(dest, distance));
		my_map[dest].push_back(make_pair(src,distance));
		v.clear();
		//cout << endl;
	}

	setup();
	dijkstras();
}

bool city_map::check_locations(char s, char e)
{
	return (my_map.find(s) != my_map.end() && my_map.find(e) != my_map.end()) ? true : false;
}

void city_map::add_location()
{
	char choice='y',src,dest;
	int weight;
	do
	{
		if (choice != 'y')
			break;
		else
		{
			cout << "\nsource : \t";
			cin >> src;
			cout << "\n destination : \t";
			cin >> dest;
			cout << "\n distance : \t";
			cin >> weight;

			my_map[src].push_back(make_pair(dest, weight));
			my_map[dest].push_back(make_pair(src, weight));

			ofstream locfile;
			locfile.open("location.txt", ios::app);
			locfile << src<< "|" << dest << "|" << weight << "\n";
			locfile.close();
		}
		cout << "press 'y' to add place\n";
		cin >> choice;
	} while (choice == 'y');

	path.clear();
	setup();
	dijkstras();
	

		
}

void city_map::remove_location()
{
	vector<char> toberemoved;
	vector<string> tobeadded;
	string line;
	char choice='y', src;
	do
	{
		if (choice != 'y')
			break;
		else
		{
			cout << "\nenter the location to be removed \t";
			cin >> src;
			toberemoved.push_back(src);
			for (auto dest : my_map[src])
			{
				for (auto it=my_map[dest.first].begin(); it!= my_map[dest.first].end();it++)
				{
					if ((*it).first == src)
					{
						my_map[dest.first].erase(it);
						break;
					}
				}
			}
			my_map.erase(src);
		
		}
		cout << "enter 'y' to delete more\n";
		cin >> choice;
	} while (choice == 'y');

	fstream locfile;
	locfile.open("location.txt", ios::in);

	int flag = 0;
	while (getline(locfile, line))
	{
		flag = 0;
		for (auto l : toberemoved)
		{
			if ((line).find(l) != string::npos)
			{
				flag = 1;
				break;
			}

		}
		if (flag == 0)
			tobeadded.push_back(line);
	}

	locfile.close();

	locfile.open("location.txt", ios::out);
	for (auto l : tobeadded)
		locfile << l << "\n";
	locfile.close();

	path.clear();
	setup();
	dijkstras();
}

void city_map::update_location()
{
	char choice = 'y', src, dest;
	vector<string> tobeadded, toberemoved;
	string line;
	int weight;
	do
	{
		if (choice != 'y')
			break;
		else
		{
			cout << "note: locations should have connections previously, incase of new connection use add location\n";
			cout << "\nsource : \t";
			cin >> src;
			cout << "\n destination : \t";
			cin >> dest;
			cout << "\n distance : \t";
			cin >> weight;

			if (my_map.find(src) == my_map.end() || my_map.find(dest) == my_map.end())
			{
				cout << "New location found rather you add it first\n";
			}
			else
			{
				for(auto itr1=my_map[src].begin(); itr1!= my_map[src].end();itr1++)
				{
					if ((*itr1).first == dest)
					{
						my_map[src].erase(itr1);
						my_map[src].push_back(make_pair(dest, weight));
						break;
					}
				}
				for (auto itr2 = my_map[dest].begin(); itr2 != my_map[dest].end(); itr2++)
				{
					if ((*itr2).first == src)
					{
						my_map[dest].erase(itr2);
						my_map[dest].push_back(make_pair(src, weight));
						break;
					}
				}

				toberemoved.push_back(src + "|" + dest);

			}
		}
		cout << "press 'y' to add place\n";
		cin >> choice;
	} while (choice == 'y');

	fstream locfile;
	locfile.open("location.txt", ios::in);

	int flag = 0;
	while (getline(locfile, line))
	{
		flag = 0;
		for (auto l : toberemoved)
		{
			if ((line).find(l)!=string::npos)
			{
				flag = 1;
				break;
			}
				
		}
		if(flag==0)
		tobeadded.push_back(line);
	}

	locfile.close();

	locfile.open("location.txt", ios::out);
	for (auto l : tobeadded)
		locfile << l << "\n";
	locfile.close();

	path.clear();
	setup();
	dijkstras();
}

void city_map::city_info()
{
	for (auto it = my_map.begin(); it != my_map.end(); it++)
	{
		cout << (*it).first << "-> \n";
		for (auto location : (*it).second)
		{
			cout << location.first << " distance is " << location.second << "\n";
		}
		cout << "\n";
	}
}

pair<stack<char>,int> city_map::distance(char src, char dest)
{
	int dist;
	char temp;
	stack<char> points;

	if (src == dest)
	{
		points.push(src);
		return make_pair(points, 0);
	}
	points.push(dest);
	dist = path[src][dest].first;
	temp = dest;
	while (path[src][temp].second != src)
	{
		temp = path[src][temp].second;
		points.push(temp);
	}
	points.push(src);
		
	return make_pair(points, dist);
		//cout << "Destination is not available \n";
		
}


void city_map::dijkstras()
{	
	map<char, int> distance;
	map<char, bool> visited;
	char u;
	priority_queue<pair<int, char>, vector<pair<int, char>>, less<pair<int, char>> > pq;
	for (auto loc : my_map)
	{
		distance[loc.first] = inf;
		visited[loc.first] = false;
		cout << loc.first << "\t";
	}
	cout << "\n";
	for (auto location : my_map)
	{
		char cur_loc = location.first;
		distance[cur_loc] = 0;
		pq.push({distance[cur_loc],cur_loc});

		while (!pq.empty())
		{
			u = pq.top().second;
			pq.pop();
			
			if (visited[u])
				continue;
			visited[u] = true;
			for (auto p : my_map[u])
			{
				if (distance[p.first] > distance[u] + p.second)
				{
					distance[p.first] = distance[u] + p.second;
					pq.push({ distance[p.first],p.first });
					path[cur_loc][p.first] = make_pair(distance[p.first], u);
					cout << p.first << "  " << distance[p.first] << "  " << u << "\n";
				}
			}
			

		}
		cout << "\n";
		for (auto loc : my_map)
		{
			distance[loc.first] = inf;
			visited[loc.first] = false;
		}

	}
	system("pause");
	system("cls");
}

void city_map::setup()
{
	for (auto loc : my_map)
	{
		char point = loc.first;
		for (auto location : my_map)
		{
			path[point][location.first]= make_pair(inf, '-');
		}
		path[point][point] = make_pair(0, '-');

	}
}


void city_map::split(const string &s, char delim, vector<string> &elems) {
	stringstream ss;
	ss.str(s);
	string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
}

	