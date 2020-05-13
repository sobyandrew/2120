#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

typedef pair<double, double> Coord;
typedef pair<string, Coord> Location;
typedef pair<int, int> Point;
typedef pair<double, Point> Graph;

Graph **g;

double dist(Coord a, Coord b)
{
  double xVal = (a.first - b.first) * (a.first - b.first);
  double yVal = (a.second - b.second)* (a.second - b.second);
  return sqrt(xVal + yVal);
}
vector <Location> lmarks;
vector <Location> rest;

void printPath(Graph **g,int currX, int currY, int last1,int last2)
{
  if(currX == lmarks.size() && currY == rest.size())
    {
      cout << lmarks[lmarks.size()].first << " " <<lmarks[lmarks.size()].second.first << " " << lmarks[lmarks.size()].second.second << endl;
    }
  if(g[currX][currY].first == 0)
    {
      cout << lmarks[0].first << " " << lmarks[0].second.first << " "
	   << lmarks[0].second.second << endl;
      return;
    }
  printPath(g,last1, last2, g[last1][last2].second.first, g[last1][last2].second.second);
  if(last2!= currY)
    {
      cout << rest[currY].first << " " << rest[currY].second.first << " " <<
	rest[currY].second.second << endl;
    }
  if(last1 != currX)
    {
      cout << lmarks[currX].first << " " << lmarks[currX].second.first <<
        " " << lmarks[currX].second.second << endl;
    }
}

int main()
{
  double d1 = 0, d2 = 0, distTour = -1;
  string s;
  ifstream in1 ("landmarks.txt");
  Location temp;
  while(in1 >> s >> d1 >> d2)
    {
      temp.first = s;
      temp.second.first = d1;
      temp.second.second = d2;
      lmarks.push_back(temp);
    }
  in1.close();
  ifstream in2 ("restaurants.txt");
  while(in2 >> s >> d1 >> d2)
    {
      temp.first = s;
      temp.second.first = d1;
      temp.second.second = d2;
      rest.push_back(temp);
    }
  in2.close();
  sort(lmarks.begin(), lmarks.end());
  sort(rest.begin(), rest.end());

  vector<Location> :: iterator it = lmarks.begin();
  lmarks.insert(it, *it);
  vector<Location> :: iterator it2 = rest.begin();
  rest.insert(it2, *it2);
  g = new Graph *[lmarks.size()];
  for(int i = 0; i < lmarks.size(); i++)
    {
      g[i] = new Graph[rest.size() + 1];
    }

  int count = 1;
  for(int i = 0; i < lmarks.size(); i++)
    {
      for(int j = 0; j< rest.size();j++)
	{
	  g[i][j].first = 999999999;
	}
    }
  g[0][0].first = 0.0;
  //initialize top distances of graph
  for(int i = 1; i < lmarks.size(); i++)
    {      
      g[i][0].first = g[i-1][0].first + dist(lmarks[i].second, lmarks[i-1].second);	  
    }
  double vert = 0, diag = 0;
  for(int i = 1; i < lmarks.size(); i++)
    {
      for(int j = 1; j < rest.size() + 1; j++)
	{
	  //check above and left above against each other
	  vert = g[i-1][j].first + dist(lmarks[i].second, lmarks[i-1].second);
	  diag = g[i-1][j-1].first + 
	    dist(lmarks[i-1].second, rest[j].second)+ 
	    dist(rest[j].second, lmarks[i].second);

	  if(vert < diag)
	    {
	      g[i][j].first = vert;
	      g[i][j].second.first = i-1;
	      g[i][j].second.second = j;
	    }
	  else
	    {
	      g[i][j].first = diag;
	      g[i][j].second.first = i-1;
	      g[i][j].second.second = j-1;
	    }
	}
    } 
  
  distTour = g[lmarks.size()-1][rest.size()-1].first;
  cout << "Total tour distance: " << distTour << endl;

  printPath(g, lmarks.size()- 1, rest.size()-1,g[lmarks.size()-1][rest.size()-1].second.first, g[lmarks.size()-1][rest.size()-1].second.second);
  return 0;
}
