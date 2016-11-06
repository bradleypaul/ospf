// OSPF routing;
// Paul D. Bradley

#include <iostream>
#include <fstream>
#include <queue>
#include <iomanip>
#include <set>
#define infinity 1000000000000

using namespace std;
set <int> mySet;
bool hasTrue (bool isVisited[100], int numRouters)
{
	for (int i = 0; i < numRouters; i++)
	{
		if (!isVisited[i])
			return true;
	}

	return false;
}

int main ()
{
	ifstream fin ("ospf.in");
	if (fin)
	{
		ofstream fout ("ospf.out");
		int numRouters;
		int source, s;
		double cost[100][100];
		double dist[100];
		double temp;
		int count = 0;
		

		fin >> numRouters;
		fout << fixed;
		while (numRouters != 0)
		{
			if (count != 0) {
				fout << "*****" << endl;
				cout << "*****" << endl;
			}
			for (int i = 0; i < numRouters; i++)
			{
				for (int j = 0; j < numRouters; j++)
				{
					fin >> temp;
					if (i == j)
					{
						cost[i][j] = 0;
					}
					else if (temp == 0)
					{
						cost[i][j] = infinity;
					}
					else 
					{
						cost[i][j] = 100000000 / temp; 
					}
				
				}
			}
			
			fin >> source;


			while (source != 0)
			{

				bool isVisited[100]= {false};
				for (int i = 0; i < 100; i++)
				{
					dist[i] = infinity;
				}

				s = source - 1; 
				dist[s] = 0;

				while (hasTrue(isVisited, numRouters))
				{	
					isVisited[s] = true;
					for (int i = 0; i < numRouters; i++)
					{
						if (cost[s][i] + dist[s] < dist[i])
							dist[i] = cost[s][i] + dist[s];
					}

					double min = infinity;

					for (int i = 0; i < numRouters; i++)
					{
						if (dist[i] < min && !isVisited[i])
						{
							min = dist[i];
							s = i;
						}
					}
				}

				
				fout << source << ":";
				cout << source << ':';

				for (int i = 0; i < numRouters; i++)
				{
					if (i != source - 1)
					{
						fout << ' ' << (i + 1) << '(' << fixed << setprecision(2) << dist[i] << ')';
						cout << ' ' << (i + 1) << '(' << fixed << setprecision(2) << dist[i] << ')';
					}
				}
				fout << endl;
				cout << endl;
				fin >> source;
			}

			count++;
			fin >> numRouters;
		}

		fin.close();
		fout.close();
	}

	else
		cout << "The file could not be loaded. Please try again." << endl;

	return 0;
}