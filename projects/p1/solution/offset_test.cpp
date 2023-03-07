#include <iostream>
#include "structure.hpp"

using namespace std;

int main()
{
	ClientDatagram cd;
	cout << "offset of cd.sequence_number: " << (char *) &cd.sequence_number - (char *) &cd << endl;
	cout << "offset of cd.payload_length:  " << (char *) &cd.payload_length - (char *) &cd << endl;
	cout << "sizeof(cd): " << sizeof(cd) << endl;
	return 0;
}