#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <queue>
using namespace std;

int N, D, K;

struct Point {
  double quality;
  double *data;
};

const int keySize = 11;

struct Node
{
  double val;
  double key[keySize];
  Node *left;
  Node *right;
  Node(Point &p)
  {
    val = p.quality;
    for(int i = 0; i < D; i++) key[i] = p.data[i];
    left = right = NULL;
  }
};
typedef pair<double, double> pdd;
priority_queue <pdd> PQ;

Node *insert(Node *T, Point &p, int dim)
{
  if(T == NULL) return new Node(p);
  if(p.data[dim] < T->key[dim]) T->left = insert(T->left, p, (dim+1) % D);
  else T->right = insert(T->right, p, (dim+1) % D);
  return T;			       
}

Point *P;

double dist(Node *T1, Point &p)
{
  double dVal = 0;
  for(int i = 0; i < D; i++) dVal += (T1->key[i] - p.data[i]) * (T1->key[i] - p.data[i]);   
  return sqrt(dVal);
}

void nearestNeighbor(Node * T, Point &p, int dim)
{
  double pV;
  if(T == NULL) return;
  if(PQ.size() != K){ 
    if(dist(T,p) != 0) PQ.push(pdd(dist(T, p), T->val));    
  }
    else
    if(dist(T,p) != 0)
	{
	  PQ.push(pdd(dist(T,p), T->val));
	  PQ.pop();
	}
  if(p.data[dim] < T->key[dim])
    {
      nearestNeighbor(T->left, p, (dim+1)% D);
      pV = abs(T->key[dim] - p.data[dim]);
	if(pV < PQ.top().first) nearestNeighbor(T->right, p, (dim+1)% D);
    }
  else
    {
      nearestNeighbor(T->right, p, (dim+1)% D);
      pV = abs(T->key[dim] - p.data[dim]);
      if(pV < PQ.top().first) nearestNeighbor(T->left, p, (dim+1)% D);
    }
}

double classify()
{
  double weight = 0, values = 0;
  while(!PQ.empty())
    {
      weight += exp(-0.1 *  PQ.top().first);
      values += exp(-0.1 *  PQ.top().first) * PQ.top().second;
      PQ.pop();
    }
  return values/weight;
}

int main(int argc, char *argv[])
{
  double error1 = 0, fVal = 0;
  if (argc != 3) {
    cout << "Usage: wine <data file> <k>\n";
    return 0;
  }

  /* Read input data */
  ifstream fin(argv[1]);
  K = atoi(argv[2]);
  fin >> N >> D;
  P = new Point[N];
  for (int i=0; i<N; i++) {
    fin >> P[i].quality;
    P[i].data = new double[D];
    for (int j=0; j<D; j++)
      fin >> P[i].data[j];
  }
  fin.close();
  
  /* Normalize data in each coordinate */
  for (int j=0; j<D; j++) {
    double mean = 0.0;
    for (int i=0; i<N; i++) mean += P[i].data[j];
    mean /= N;
    for (int i=0; i<N; i++) P[i].data[j] -= mean;
    double var = 0.0;
    for (int i=0; i<N; i++) var += pow(P[i].data[j],2);
    double stddev = sqrt(var/N);
    for (int i=0; i<N; i++) P[i].data[j] /= stddev;
  }

  // Now in each coordinate, we have a mean of zero and 
  //variance/standard deviation
  // of one, so the data set is "centered" at the origin 
  //and has the same relative
  // scale along each axis (so no attribute is "more important" than any other
  // attribute when computing distances).
  Node * kdTree = NULL; 
  for(int i = 0; i < N; i++) kdTree = insert(kdTree, P[i], 0);
  for(int i = 0; i < N; i++)
    {
      nearestNeighbor(kdTree, P[i], 0);
      fVal = (classify() - P[i].quality);
      error1 += fVal * fVal;// * (classify() - P[i].quality);
    }

  cout << error1 / N << endl;
  return 0;
}
