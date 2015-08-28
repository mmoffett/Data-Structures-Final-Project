///** Phone directory application that uses console I/O. */
//
//#include <iostream>
//#include <istream>
//#include <ostream>
//#include <limits>
//using namespace std;
//
//
//void do_lookup_entry();
//void do_display();
//
//int main(int argc, char* argv[])
//{
//	if (argc < 2) {
//		cerr << "Must specify the name of the data file"
//			" that contains the directory\n";
//		return 1;
//	}
//	//Phone_Directory the_directory;
//	//the_directory.load_data(argv[1]);
//	process_commands();//the_directory);
//}
//void process_commands()
//{
//	string commands[] = {
//		"Look Up Entry",
//		"Display Patient List",
//		"Exit" };
//	const int NUM_COMMANDS = 2;
//	int choice = NUM_COMMANDS - 1;
//	do 
//	{
//		for (int i = 0; i < NUM_COMMANDS; i++)
//		{
//			cout << "Select: " << i << " " << commands[i] << "\n";
//		}
//		cin >> choice;
//		cin.ignore(numeric_limits<int>::max(), '\n');
//		switch (choice) 
//		{
//		case 0: do_lookup_entry(); break;
//		case 1: do_display(); break;
//			break;
//		}
//	} while (choice < NUM_COMMANDS - 1);
//
//	do_lookup_entry()
//	{
//		string name;
//		cout << "Enter name: ";
//		getline(cin, name);
//		...
//	}
//	do_display()
//	{
//
//	}
//
//}