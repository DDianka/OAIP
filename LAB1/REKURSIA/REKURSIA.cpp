
#include <iostream> 
using namespace std;

 double recursia(int N)
{
	if (N == 1)
	{
		return 1.0 / (1 + 1.0 / 2);
	}

	return 1.0 / (N + recursia(N - 1));
}

int main()
{
	int N;
	cout << "Enter n: ";
	cin >> N;

	cout << endl << "recursia " << recursia(N);

}


























/* double function(int n)
{
	double result = 1;
	int i = 0;
	while ((n - i) != 0) {
		if ((n - i) == 1) {
			result /= 1.0 / (1 + 1.0 / 2);
		}
		else {
			result /= ((n - i) + 1.0);
		}
		i++;
	}
	return result;
}
*/