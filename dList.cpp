#include <iostream>
using namespace std;

struct Run
{
	float time;
	float fuel;
	Run *next, *last;
};

class dList
{
public:
	dList()
	{
		head = new Run{ 0.0f, 0.0f, nullptr, nullptr };
		tail = head;
		size = 1;
		elements = 1;
	}

	dList(float time[], float fuel[], int numElements)
	{
		//sort elements before adding them
		mergeSort(time, fuel, 0, numElements - 1);

		//used size of array 
		elements = numElements - 1;
		size = numElements;
		//first element in the list
		head = new Run{ time[0], fuel[0], nullptr, nullptr };
		tail = head;

		//parses through input arrays
		int dominations = 0;
		for (int i = 1; i < size; i++)
		{
			Run *tmp = new Run{ time[i + dominations], fuel[i + dominations], nullptr, tail };

			if (dominates(tail, tmp))
			{//ignores data entry and shrinks used aray
				i--;
				size--;
				dominations++;
			}
			else
			{//adds element to list 
				tail->next = tmp;
				tail = tmp;
			}
		}
	}

	/*
	*Prints out List in
	*acending 'a' or
	*decending 'd' order
	*/
	void out(char order = 'a')
	{
		if (order == 'a')
		{
			Run *run = head;
			for (int i = 0; i < size; i++)
			{
				cout << "Time " << run->time << " Fuel " << run->fuel << " This " << run << endl;

				run = run->next;
			}
		}
		else
		{
			Run *run = tail;
			for (int i = size - 1; i >= 0; i--)
			{
				cout << "Time " << run->time << " Fuel " << run->fuel << " This " << run << endl;

				run = run->last;
			}
		}
	}

	void out(int length, char order = 'a')
	{
		if (order == 'a')
		{
			Run *run = head;
			for (int i = 0; i < length; i++)
			{
				cout << "Time " << run->time << " Fuel " << run->fuel << " This " << run << endl;

				run = run->next;
			}
		}
		else
		{
			Run *run = tail;
			for (int i = length - 1; i >= 0; i--)
			{
				cout << "Time " << run->time << " Fuel " << run->fuel << " This " << run << endl;

				run = run->last;
			}
		}
	}

	int insert(float time, float fuel)
	{
		Run *tmp = new Run{ time, fuel, nullptr, nullptr };
		Run *run = head;
		int count;
		bool added = 0;
		for (count = 0; count < size; count++)
		{
			if (tmp->time < run->time)
			{//add element in the middle of the list
				/*if (tmp->time == 110)
				{
					cout << "test " << tmp->fuel << " " << run->last->fuel << endl;
				}*/
				if (run->last == nullptr)
				{
					head = tmp;
				}
				else if (tmp->fuel < run->last->fuel)
				{
					run->last->next = tmp;
				}
				else
				{
					cout << "\n\nHello\n\n";
					cin.get();
					return ++elements;
				}
				tmp->next = run;
				tmp->last = run->last;
				run->last = tmp;
				size++;
				added = true;
				count++;
				break;
			}
			else if ((tmp->fuel < run->fuel) && (tmp->time == run->time))
			{
				if (run->last == nullptr)
				{
					head = tmp;
				}
				else
				{
					run->last->next = tmp;
				}
				tmp->next = run;
				tmp->last = run->last;
				run->last = tmp;
				size++;
				added = true;
				count++;
				break;
			}

			run = run->next;
		}

		if (added)
		{
			int s = size;

			/*if (run->last != nullptr)
			{
				if (dominates(run->last, tmp)
				{
					run->next = tmp->next
				}
			}*/

			//cout << "\n\nNew " << tmp->time << " Start " << run << endl;

			for (count = count; count < s; count++)
			{
				//check dominations
				if (dominates(tmp, run))
				{
					if (run->next != nullptr)
					{
						tmp->next = run->next;
						run->next->last = tmp;
						size--;
					}
					else
					{
						tmp->next = nullptr;
						tail = tmp;
						size--;
					}
				}

				run = run->next;
			}
		}
		else
		{//add element at end of list
			tail->next = tmp;
			tmp->last = tail;
			tail = tmp;
			size++;
		}

		return ++elements;
	}

private:
	Run *head,//the first element in the list
		*tail;//last element in list;
	int size,//number of elemets in list
		elements;//number of entries

	/*
	* if a has a better time and has the same or better fuel usage
	* than b, return true
	*/
	bool dominates(Run* a, Run* b)
	{
		if ((a->time <= b->time) && (a->fuel <= b->fuel))
			return true;
		else
			return false;
	}

	void merge(float a[], float b[], int l, int r, int m)
	{
		int lowSize = m - l + 1,
			highSize = r - m;
		float *tmpALow = new float[lowSize],
			*tmpBLow = new float[lowSize],
			*tmpAHigh = new float[highSize],
			*tmpBHigh = new float[highSize];

		//copy low
		for (int i = 0; i < lowSize; i++)
		{
			tmpALow[i] = a[i + l];
			tmpBLow[i] = b[i + l];
		}

		//copy high
		for (int i = 0; i < highSize; i++)
		{
			tmpAHigh[i] = a[i + m + 1];
			tmpBHigh[i] = b[i + m + 1];
		}

		int lowCount = 0,
			highCount = 0;
		for (int i = l; i <= r; i++)
		{//loop through array segment
			//check low array bound
			if (lowCount < lowSize)
			{
				//check high array bound
				if (highCount >= highSize)
				{//pick element from low array
					a[i] = tmpALow[lowCount];
					b[i] = tmpBLow[lowCount];
					lowCount++;
				}
				else if (tmpALow[lowCount] < tmpAHigh[highCount])
				{//pick element from low array
					a[i] = tmpALow[lowCount];
					b[i] = tmpBLow[lowCount];
					lowCount++;
				}
				else if (tmpALow[lowCount] == tmpAHigh[highCount])
				{
					if (tmpBLow[lowCount] <= tmpBLow[highCount])
					{//pick element from low array
						a[i] = tmpALow[lowCount];
						b[i] = tmpBLow[lowCount];
						lowCount++;
					}
					else
					{//pick element from high array
						a[i] = tmpAHigh[highCount];
						b[i] = tmpBHigh[highCount];
						highCount++;
					}
				}
				else
				{//pick element from high array
					a[i] = tmpAHigh[highCount];
					b[i] = tmpBHigh[highCount];
					highCount++;
				}
			}
			else
			{//pick element from high array
				a[i] = tmpAHigh[highCount];
				b[i] = tmpBHigh[highCount];
				highCount++;
			}
		}
	}

	void mergeSort(float a[], float b[], int l, int r)
	{
		if (r - l > 0)
		{//split in two halves and recursive call
			int m = ((r - l) / 2) + l;
			mergeSort(a, b, l, m);
			mergeSort(a, b, m + 1, r);

			merge(a, b, l, r, m);
		}
		//one element base case
	}
};