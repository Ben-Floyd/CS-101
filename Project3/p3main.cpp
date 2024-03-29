#include <iostream>
using namespace std;
#include "dList.cpp"

int main() {
	const int size = 10;
	float avgTime[size] = { 93, 99, 96, 97, 95,100, 94, 98, 92, 98 };
	float fuelEfficiency[size] = { 194,201,196,156,193,100,194,198,200,140 };

	dList dl = dList(avgTime, fuelEfficiency, size);
	cout << "First Output" << endl;
	dl.out('a');
	//  92, 93,  95,  97,  98, 100
	//200, 194, 193, 156, 140, 100

	dl.insert(96, 145);
	cout << endl << "Second Output" << endl;
	dl.out('a');
	//  92, 93,  95,  96,  98, 100
	//200, 194, 193, 145, 140, 100

	dl.insert(50, 300);
	dl.insert(110, 75);
	cout << endl << "Third Output" << endl;
	dl.out();
	// 50,  92,  93,  95,  96,  98, 100, 110
	//300, 200, 194, 193, 145, 140, 100,  75	

	dl.insert(97, 70);
	cout << endl << "Fourth Output" << endl;
	dl.out();
	// 50,  92,  93,  95,  96,  97
	//300, 200, 194, 193, 145,  70

	cout << endl << "Fifth Output" << endl;
	dl.out('d');
	// 97,  96,  95,  93,  92,  50
	// 70, 145, 193, 194, 200, 300	

	int x = dl.index_before(4), y = dl.index_after(4);
	cout << "Before is : " << x << "   After is : " << y << endl;

	for (int i = 0; i < 500000; i++) dl.insert(100 + i % 47 - (i % 10001) / 251.1 - .000001*i, 100 - i % 91 + i % 13 + .0001*i);
	cout << endl << "Sixth Output" << endl;
	dl.out();

	for (int i = 0; i < 500000; i++) dl.insert(50 - .00001*i, 10 + .0001*i);
	cout << endl << "Seventh Output" << endl;
	dl.out(10, 'a');
	cout << endl << "At the back" << endl;
	dl.out(10, 'd');

	for (int i = 1000013; i > 500013; i -= 5)
	{
		dl.decrease_time(0.00045, i);
	}
	cout << endl << "Eighth Output" << endl;
	dl.out(10, 'a');
	cout << endl << "At the back" << endl;
	dl.out(10, 'd');

	cin.get();
	return 0;
}

/*
Output should be:

First Output
Time 92  Fuel 200
Time 93  Fuel 194
Time 95  Fuel 193
Time 97  Fuel 156
Time 98  Fuel 140
Time 100  Fuel 100

Second Output
Time 92  Fuel 200
Time 93  Fuel 194
Time 95  Fuel 193
Time 96  Fuel 145
Time 98  Fuel 140
Time 100  Fuel 100

Third Output
Time 50  Fuel 300
Time 92  Fuel 200
Time 93  Fuel 194
Time 95  Fuel 193
Time 96  Fuel 145
Time 98  Fuel 140
Time 100  Fuel 100
Time 110  Fuel 75

Fourth Output
Time 50  Fuel 300
Time 92  Fuel 200
Time 93  Fuel 194
Time 95  Fuel 193
Time 96  Fuel 145
Time 97  Fuel 70

Fifth Output
Time 97  Fuel 70
Time 96  Fuel 145
Time 95  Fuel 193
Time 93  Fuel 194
Time 92  Fuel 200
Time 50  Fuel 300
Before is : 0   After is : 10

Sixth Output
Time 50  Fuel 300
Time 59.751  Fuel 120.004
Time 59.7632  Fuel 77.0039
Time 59.7887  Fuel 71.0022
Time 59.8871  Fuel 67.0023
Time 59.9369  Fuel 66.0012
Time 59.9867  Fuel 65.0001
Time 60.0352  Fuel 62.0013
Time 60.0851  Fuel 61.0002
Time 60.1349  Fuel 59.9991
Time 60.1847  Fuel 58.998
Time 60.446  Fuel 23.9928
Time 60.4959  Fuel 22.9917
Time 60.8703  Fuel 22.9823
Time 61.2448  Fuel 22.9729
Time 61.6192  Fuel 22.9635
Time 62.9897  Fuel 22.9542
Time 66.2998  Fuel 22.846
Time 66.6742  Fuel 22.8366
Time 67.0487  Fuel 22.8272
Time 67.4231  Fuel 22.8178
Time 69.7896  Fuel 22.8086
Time 71.7293  Fuel 22.7097
Time 72.1037  Fuel 22.7003
Time 72.4782  Fuel 22.6909
Time 72.8526  Fuel 22.6815
Time 73.2271  Fuel 22.6721
Time 76.5895  Fuel 22.663
Time 77.5332  Fuel 22.564
Time 77.9076  Fuel 22.5546
Time 78.2821  Fuel 22.5452
Time 78.6565  Fuel 22.5358
Time 80.027  Fuel 22.5265
Time 83.3371  Fuel 22.4183
Time 83.7116  Fuel 22.4089
Time 84.086  Fuel 22.3995
Time 84.4605  Fuel 22.3901
Time 86.8269  Fuel 22.3809
Time 88.7666  Fuel 22.282
Time 89.141  Fuel 22.2726
Time 89.5155  Fuel 22.2632
Time 89.8899  Fuel 22.2538
Time 90.2644  Fuel 22.2444
Time 93.6269  Fuel 22.2353
Time 94.5705  Fuel 22.1363
Time 94.945  Fuel 22.1269
Time 95.3194  Fuel 22.1175
Time 95.6939  Fuel 22.1081
Time 97.0643  Fuel 22.0988
Time 100.427  Fuel 22.0897
Time 103.789  Fuel 22.0806
Time 107.152  Fuel 22.0715
Time 110.514  Fuel 22.0624
Time 113.877  Fuel 22.0533
Time 117.239  Fuel 22.0442
Time 120.602  Fuel 22.0351
Time 123.964  Fuel 22.026
Time 127.327  Fuel 22.0169
Time 130.689  Fuel 22.0078

Seventh Output
Time 45  Fuel 59.9999
Time 45  Fuel 59.9998
Time 45  Fuel 59.9997
Time 45  Fuel 59.9996
Time 45  Fuel 59.9995
Time 45.0001  Fuel 59.9994
Time 45.0001  Fuel 59.9993
Time 45.0001  Fuel 59.9992
Time 45.0001  Fuel 59.9991
Time 45.0001  Fuel 59.999

At the back
Time 50  Fuel 10
Time 50  Fuel 10.0001
Time 50  Fuel 10.0002
Time 50  Fuel 10.0003
Time 50  Fuel 10.0004
Time 50  Fuel 10.0005
Time 49.9999  Fuel 10.0006
Time 49.9999  Fuel 10.0007
Time 49.9999  Fuel 10.0008
Time 49.9999  Fuel 10.0009

Eighth Output
Time 45  Fuel 59.9995
Time 45.0001  Fuel 59.999
Time 45.0001  Fuel 59.9985
Time 45.0002  Fuel 59.998
Time 45.0002  Fuel 59.9974
Time 45.0003  Fuel 59.9969
Time 45.0003  Fuel 59.9964
Time 45.0004  Fuel 59.9959
Time 45.0004  Fuel 59.9954
Time 45.0005  Fuel 59.9949

At the back
Time 50  Fuel 9.99995
Time 49.9999  Fuel 10.0005
Time 49.9999  Fuel 10.0009
Time 49.9998  Fuel 10.0014
Time 49.9998  Fuel 10.002
Time 49.9997  Fuel 10.0024
Time 49.9997  Fuel 10.0029
Time 49.9996  Fuel 10.0034
Time 49.9996  Fuel 10.004
Time 49.9995  Fuel 10.0044

*/