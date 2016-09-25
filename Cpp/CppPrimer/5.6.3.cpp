# include <iostream>
using namespace std;
int main()
{
	int x, y;
	try
	{
		cin >> x >> y;
		if (y == 0)
			throw range_error("y!=0");
		else cout << x / y;
	}
	catch (range_error err)
	{
		cout << err.what() << endl;
	}
	return 0;
}
