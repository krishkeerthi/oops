#pragma once
#include<vector>
#include <utility>
#include<string>
#include<map>
#include <stack>
using namespace std;

typedef pair<char, int> Pair;
struct edge
{
	char src, dest;
	int weight;
};
class city_map
{
private:
	map<char, vector<Pair>> my_map;
	map<char, map<char, pair<int, char>>> path;
public:
	//city_map(vector<edge> const&);
	city_map();
	void split(const string&, char, vector<string>&);
	void setup();
	bool check_locations(char, char);
	void city_info();
	void add_location();
	void remove_location();
	void update_location();
	pair<stack<char>,int> distance(char,char);
	void dijkstras();	
};

