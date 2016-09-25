# include <iostream>
# include <string>

# define KEY "123456"

using namespace std;

int main()
{
	string key = KEY;
	while (1)
	{
		unsigned int dif = 0;
		try
		{
			cout << "Please input your KEY:";
			for (auto c : key)
			{
				dif += (c != getchar()) ? 1 : 0;
			}
			getchar();
			
			if (dif == 0)
			{
				cout << "Right!";
				break;
			}
			else if (dif < 3)
				throw runtime_error("Key have a little error!");
			else
			{
				cout << "Totally wrong!" << endl;
				exit(EXIT_FAILURE);
			}
		}
		catch (runtime_error err)
		{
			cout << err.what()
				<< "\nTry again?Y/N" << endl;
			if (getchar() != 'Y')
				break;
			getchar();
		}
	}
	
	return 0;
}
