#include <iostream>
#include <stdlib.h>
#include <time.h>

#define   SIZE   5
#define NUMBER_OF_UNKOWNS 3

using namespace std;

void BackTracking(float matrix[SIZE][SIZE])
{
	int n = NUMBER_OF_UNKOWNS;
	float Results[SIZE] = { 0 };

	Results[n] = matrix[n][n + 1] / matrix[n][n];

	for (int i = n - 1; i >= 1; i--)
	{
		Results[i] = matrix[i][n + 1];
		for (int j = i + 1; j <= n; j++)
		{
			Results[i] = Results[i] - matrix[i][j] * Results[j];
		}
		Results[i] = Results[i] / matrix[i][i];
	}


	cout << endl << "Solution: " << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << "x[" << i << "] = " << Results[i] << endl;
	}
	
}

void ForwardThreeLoops(float matrix[SIZE][SIZE])
{
	float ratio;
	int n = NUMBER_OF_UNKOWNS;
	int x;
	int counter = 0;

	for (int i = 1; i <= n - 1; i++)
	{
	
		for (int j = i + 1; j <= n; j++)
		{
			 ratio = matrix[j][i] / matrix[i][i];

			for (int k = 1; k <= n + 1; k++)
			{
				matrix[j][k] = matrix[j][k] - ratio * matrix[i][k];
			}
		}
	}
	cout << "Triangulated Matrix" << endl;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n + 1; j++)
		{
			cout << "matrix[" << i << "]" << "[" << j << "]= " << matrix[i][j] << endl;

		}
	}
	//LOOP TO CHECK IF INDETERMINATE / INCOMPATIBLE
	for (x = 1; x <= n + 1; x++)
	{
		if (matrix[n][x] == 0)
		{
			counter++;
		}
	}
	//CHECK IF INDETERMINATE OR INCOMPATIBLE
	if (counter == n)
	{
		cout << endl;
		cout << "INCOMPATIBLE" << endl;
		cout << "-----------------" << endl;
		cout << "It is an incompatible system therefore there are no solutions" << endl;;
		exit(0);
	}
	else if (counter == n + 1)
	{
		cout << endl;
		cout << "INDETERMINATE" << endl;
		cout << "-----------------" << endl;
		cout << "There are infinite solutions therefore is an indeterminate matrix" << endl;
		cout << "You can solve the problem using a parameter" << endl;
		exit(0);
	}
	//AS THE STATEMENTS BEFORE ARE NOT COMPLETED WE CONCLUDE THAT THE SYSTEM IS NOT INDETERMINATE NEITHER INCOMPATIBLE
	BackTracking(matrix);
}

void ForwardTwoLoops(float matrix[SIZE][SIZE])
{
	int n = NUMBER_OF_UNKOWNS;
	float pivot;
	float rowPivot;
	float SubPivot;
	float RowSubPivot;
	int z;
	int y = n + 1;
	int x;
	int counter=0;

		for (int i = 1; i <= n - 1; i++)
		{
			
			for (int j = i + 1; j <= n; j++)
			{
				z = i+1;
				
				pivot = matrix[i][i];
				SubPivot = matrix[i][j];
			
				rowPivot = matrix[i + n - j][i];
				RowSubPivot = matrix[n][i];

				float ratio = matrix[j][i] / matrix[i][i];
				matrix[j][z] = matrix[j][z] - ratio * matrix[i][z];

				matrix[j][z] = matrix[j][z] - ratio * matrix[i][z];	
			
				


				matrix[j][i] = RowSubPivot - (rowPivot * (RowSubPivot / rowPivot));	//Apply 0's to the lower part of the matrix
				
				//CHANGE LAST COLUMN
				if (j <= n)
				{
					matrix[j][y] = matrix[j][y] - ratio * matrix[i][y];
				}
				
			}
		}
		//LOOP TO CHECK IF INDETERMINATE / INCOMPATIBLE
		for (x = 1; x <= n + 1; x++)
		{
			if (matrix[n][x] == 0)
			{
				counter++;
			}
		}
		//CHECK IF INDETERMINATE OR INCOMPATIBLE
		if (counter == n)
		{
			cout << endl;
			cout << "INCOMPATIBLE" << endl;
			cout << "-----------------" << endl;
			cout << "It is an incompatible system therefore there are no solutions" << endl;;
			exit(0);
		}
		else if (counter == n + 1)
		{
			cout << endl;
			cout << "INDETERMINATE" << endl;
			cout << "-----------------" << endl;
			cout << "There are infinite solutions therefore is an indeterminate matrix" << endl;
			cout << "You can solve the problem using a parameter" << endl;
			exit(0);
		}
		//AS THE STATEMENTS BEFORE ARE NOT COMPLETED WE CONCLUDE THAT THE SYSTEM IS NOT INDETERMINATE NEITHER INCOMPATIBLE
	
	
		cout << "Triangulated Matrix" << endl;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n+1; j++)
			{
				cout << "matrix[" << i << "]" << "[" << j << "]= " << matrix[i][j] << endl;

			}
		}

		BackTracking(matrix);

}

int main()
{
	float fr, t1, t2;

	t1 = _Query_perf_counter();

	float a[SIZE][SIZE] = {0};
	int n = NUMBER_OF_UNKOWNS; 
	srand(time(NULL));
	cout << "Enter Coefficients of Augmented Matrix: " << endl;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n+1; j++)
		{
			
			cout << "a[" << i << "]" <<"[" << j << "]= ";
			cin >> a[i][j];
			
		}
	}
	
	ForwardThreeLoops(a);
	//ForwardTwoLoops(a);

	t2=_Query_perf_counter();

	fr=_Query_perf_counter();

	double diff_sec = (t2 - t1) / (double)fr;

	cout <<endl<< diff_sec << "  seconds  " << endl;
	
	return(0);
}