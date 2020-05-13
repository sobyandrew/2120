#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Candy //contains a weight and yummy value and then the candy val
{
  int weight, yummy, bag;
  double candyVal;
  
  Candy(){weight = 0; yummy = 0; candyVal = 0; bag = 0;}
};

struct Bag
{
  int yummy;
  double weight;
  Bag(){weight = 0; yummy = 0;}
};

void bSort(Candy *candies)
{
for(int j = 0; j < 16; j++)
    {
      for(int n = j + 1; n < 16; n++)
	{
	  if(candies[n].candyVal > candies[j].candyVal)
	    {
	      swap(candies[n], candies[j]);
	    }
	}
    }

}

int calcVal(Bag *b)
{
  int val = 0;
  for(int i = 0; i < 3; i++)
    {
      
      val += b[i].yummy;
    }
  return val;
}
/*
void fillBag(Bag &b, Candies *c)
{
  int i = 0;
  while(b.weight + c[i].weight <= 2000)
    {
      b.weight += c[i].weight;
      b.yummy += c[i].yummy;
      i++;
    }
}
*/

void copyCandy(Candy *c, Candy *c2)
{
  for(int i = 0; i < 16; i++)
    {
      c2[i].yummy = c[i].yummy;
      c2[i].weight = c[i].weight;
      c2[i].candyVal = c[i].candyVal;
    }
}

void greedyFill(Bag *b , Candy *c)
{
  //Candy c2[16];
  //copyCandy(c, c2);
  
  for(int i = 0; i < 16; i++)
    {
      if(b[0].weight + c[i].weight <= 2000 && c[i].bag == 0)
        {
          b[0].weight += c[i].weight;
          b[0].yummy += c[i].yummy;
	  c[i].bag = 1;
	}
      else if(b[1].weight + c[i].weight <= 2000 && c[i].bag == 0)
        {
          b[1].weight += c[i].weight;
          b[1].yummy += c[i].yummy;
	  c[i].bag = 2;
	}
      else if(b[2].weight + c[i].weight <= 2000 && c[i].bag == 0)
        {
          b[2].weight += c[i].weight;
          b[2].yummy += c[i].yummy;
	  c[i].bag = 3;
	}
      else
	{
	  c[i].bag = 0;
	}
    }
   return;
}

void greedyRemove(Bag *b, Candy *c)
{
  Candy c2[16];
  copyCandy(c, c2);
  bSort(c2);
  for(int i = 15; i >= 0; i--)
    {
      if(c[i].bag == 1)
	{
	 
	      while( b[0].weight > 2000)
		{
		  b[0].weight -= c[i].weight;
		  b[0].yummy -= c[i].yummy;
		  c[i].bag = 0;
		}
	     
	  
	}
      if(c[i].bag == 2)
	{
	  while(b[1].weight > 2000)
	    {
	       b[1].weight -= c[i].weight;
	       b[1].yummy -= c[i].yummy;
	       c[i].bag = 0;
	    }
	}
      if(c[i].bag == 3)
	{
	  while(b[2].weight > 2000)
	    {
	       b[2].weight -= c[i].weight;
	       b[2].yummy -= c[i].yummy;
	       c[i].bag = 0;
	    }
	}
    }


}

void randomize(Bag *b, Candy * c)
{
  for(int i = 0; i < 3; i++)
    {
      b[i].weight = 0;
      b[i].yummy = 0;
    }
  for(int i = 0; i < 16; i++)
    {
      c[i].bag = rand() % 4;
         
      /*
      int randNum = rand() % 16;
      swap(c[i], c[randNum]);
      c[i].bag = 0;    
     */    
    }
  for(int i =0; i < 16; i++)
    {
      if(c[i].bag == 1)
	{
	  b[0].weight += c[i].weight;
	  b[0].yummy  += c[i].yummy;
	}
      if(c[i].bag == 2)
	{
	  b[1].weight += c[i].weight;
	  b[1].yummy  += c[i].yummy;
	}
      if(c[i].bag == 3)
	{
	  b[2].weight += c[i].weight;
	  b[2].yummy  += c[i].yummy;
	}
      
    }
}
void bagReplace(Bag &b1, Bag &b2, Candy &c)
{
  b1.yummy -= c.yummy;
  b1.weight -= c.weight;
  b2.yummy += c.yummy;
  b2.weight += c.weight;
}
void repair()//implement
{

  return;
}
int vBest = 0, better = 0;
//move candies
void switchC(Bag *b, Candy *c)
{
  int original = 0, isBetter = 0, isBetter2 = 0;
  for(int i = 0; i < 16; i++)
    {
      if(c[i].bag == 1)
	{
	      original = calcVal(b);
	      bagReplace(b[0],b[1], c[i]);
	      c[i].bag = 2;
	      greedyRemove(b, c);
	      isBetter = calcVal(b);
	  
	      if(isBetter < original)
		{
		  bagReplace(b[1], b[0], c[i]);
		  c[i].bag = 1;
		  greedyFill(b,c);
		}
	      else
		{
		  original = isBetter;
		}

	 
	      bagReplace(b[0], b[2], c[i]);
	      c[i].bag = 3;
	      greedyRemove(b,c);
	      isBetter2 = calcVal(b);
	      
	      if(isBetter2 < original)
		{
		  bagReplace(b[2], b[0], c[i]);
		  c[i].bag = 1;
		  greedyFill(b,c);
		}
	      else
		{
		  original = isBetter2;
		}
	 

	}
      
      	if(c[i].bag == 2)
	{
	 
	      original = calcVal(b);
	      bagReplace(b[1],b[0], c[i]);
	      c[i].bag = 2;
	      greedyRemove(b,c);
	      isBetter = calcVal(b);
	  
	      if(isBetter < original)
		{
		  bagReplace(b[0], b[1], c[i]);
		  c[i].bag = 2;
		  greedyFill(b,c);
		}
	      else
		{
		  original = isBetter;
		}
	 	 
	      bagReplace(b[1], b[2], c[i]);
	      c[i].bag = 3;
	      greedyRemove(b,c);
	      isBetter2 = calcVal(b);
	      
	      if(isBetter2 < original)
		{
		  bagReplace(b[2], b[1], c[i]);
		  c[i].bag = 2;
		  greedyFill(b,c);
		}
	      else
		{
		  original = isBetter2;
		}
	}

      	if(c[i].bag == 3)
	{
	 
	      original = calcVal(b);
	      bagReplace(b[2],b[0], c[i]);
	      c[i].bag = 1;
	      greedyRemove(b,c);
	      isBetter = calcVal(b);
	      
	      if(isBetter < original)
		{
		  bagReplace(b[1], b[0], c[i]);
		  c[i].bag = 3;
		  greedyFill(b,c);
		}
	      else
		{
		  original = isBetter;
		}
	 
	 
	      bagReplace(b[2], b[1], c[i]);
	      c[i].bag = 2;
	      greedyRemove(b,c);
	      isBetter2 = calcVal(b);
	      
	      if(isBetter2 < original)
		{
		  bagReplace(b[1], b[2], c[i]);
		  c[i].bag = 3;
		  greedyFill(b,c);
		}
	      else
		{
		  original = isBetter2;
		}
	 
	}
	if(original > better)
	  {
	    better = original;
	  }
    }
    greedyRemove(b,c);
}
/*
void copyCandy(Candy *c, Candy *c2)
{
  for(int i = 0; i < 16; i++)
    {
      c2[i].yummy = c[i].yummy;
      c2[i].weight = c[i].weight;
      c2[i].candyVal = c[i].candyVal;
    }
}
*/
void fillBag(Bag &b, Candy *c, int bagVal)
{
  for(int i = 0; i < 16; i++)//only if unused?
    {
      if(b.weight + c[i].weight <= 2000 && c[i].bag == 0)
	{
	  b.weight += c[i].weight;
	  b.yummy += c[i].yummy;
	  c[i].bag = bagVal;//marks it as used
	}
    }
}

void unfillBag(Bag &b, Candy *c, int val)
{
  int lowest = 10000;
  int W;
  int Y;
  for(int i = 0; i < 16; i++)//only if in this bag?
    {
       if(b.weight > 2000  && c[i].bag == val)
	 {
	   b.weight -= c[i].weight;
	   b.yummy -= c[i].yummy;
	   c[i].bag = 0;//marks as unused
	   if(c[i].candyVal < lowest)
	     {
	       lowest = c[i].candyVal;
	       
	     }
	 }
    }
}

int veryBest = 0;

void iterativeR(Bag * b, Candy * c)
{
  int best = 0;
  bool bestFlag = false;
  for(int i = 0; i < 1000; i++)
    {
      randomize(b, c);
      greedyFill(b,c);
      switchC(b, c);

      best = calcVal(b);
 
      if(best > veryBest)
	{
	  veryBest = best;
	}
      bestFlag = false;
    }

  return;
}
int bestExhaust = 0;
void exhaustive(int counter, Bag * b, Candy *c)
{
  //base case
  if(counter == 16) 
    {
      int val = b[0].yummy + b[1].yummy + b[2].yummy;
      if(val > bestExhaust)
	{
	  bestExhaust = val;
	}
      return;
    }
    for(int i = 0; i < 4; i++)
      {
	b[i].weight += c[counter].weight;
	b[i].yummy += c[counter].yummy;
	if(i == 3 || (i < 3 && b[i].weight <= 2000))
	  exhaustive(counter + 1, b, c);
	b[i].weight -= c[counter].weight;
	b[i].yummy -= c[counter].yummy;
      }
}

int main()
{
  bool bestFlag = false;
  bool candiesUsed[16];
  Candy candies[16];
  Bag greedyBag[3], iterBag[3], eBag[4];
  int interVal = 0;
  int iterYum = 0;
  
//Values for all the algorithms will be set to -1 so easy to spot error
  int greedyVal = -1, refineVal = -1, exhaustVal = -1;
  int weightVal, yummyVal, i = 0;
  double candyWorth;
  ifstream in("candy.txt");

  while(in >> weightVal >> yummyVal)
    {
      candyWorth = (double)yummyVal / (double)weightVal;
      candies[i].weight = weightVal;
      candies[i].yummy = yummyVal;
      candies[i].candyVal = candyWorth;      
      i++;
    }
  bSort(candies);
  greedyFill(greedyBag, candies);
  greedyVal = calcVal(greedyBag);
  iterativeR(iterBag, candies);
  exhaustive(0, eBag, candies);
  greedyRemove(iterBag, candies);

  //cout << iterBag[0].weight << " " << iterBag[1].weight << " " << iterBag[2].weight << endl;
  //print statements for the values of each algorithm search
  cout << "Greedy: " << greedyVal << endl << "Refinement: " << calcVal(iterBag)       << endl << "Exhaustive: " << bestExhaust << endl;
  //iter val is wrong everything else is right couldnt solve it.  
  return 0;
}
