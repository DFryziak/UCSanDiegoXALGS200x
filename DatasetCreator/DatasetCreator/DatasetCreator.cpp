
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

void create_integers_file(int sz)
{
	string oname = "C:\\Users\\dfryz\\OneDrive\\Courses\\Edx Algorithms and Data Structures\\repos\\Enteros.txt";
	ofstream ost(oname.c_str());
	if (!ost) throw runtime_error("No se pudo abrir el archivo para escritura");

	vector<int> v(sz);
	for (int i = 0; i < sz; i++)
	{
		v[i] = i;
	}

	for (int i = 0; i < v.size(); i++)
		ost << v[i] << '\n';
}

int main(int argc, char *argv[])
{
	//int count;

	//// Display each command-line argument.
	//cout << "\nCommand-line arguments:\n";
	//for (count = 0; count < argc; count++)
	//	cout << "  argv[" << count << "]: "<< argv[count] << "\n";

	if (argc <= 1) return 0;
	string arg = argv[1];

	// string arg = "200000";
	
	try
	{
		size_t pos;
		int n = stoi(arg, &pos);
		if (pos < arg.size()) {
			cerr << "Trailing characters after number: " << arg << '\n';
		}

		create_integers_file(n);
		cout << "Programa finalizado  correctamente";
	}
	catch (invalid_argument const &ex)
	{
		cerr << "Invalid number: " << arg << '\n';
	}
	catch (out_of_range const &ex)
	{
		cerr << "Number out of range: " << arg << '\n';
	}

	return 0;
}
