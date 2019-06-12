#include <iostream>
using namespace std;

struct Run
{
	float time;
	float fuel;
	Run *next, *last;
	int index;
};

class dList
{
public:

	dList(const dList &list)
	{
		elements = list.elements;
		size = list.size;
		capacity = list.capacity;
		index = new Run*[capacity];
		head = new Run{ list.head->time, list.head->fuel, list.head->next, list.head->last, list.head->index };
		tail = new Run{ list.tail->time, list.tail->fuel, list.tail->next, list.tail->last, list.tail->index };

		for (int i = 1; i < capacity - 1; i++)
		{
			head = new Run{ list.index[i]->time, list.index[i]->fuel, list.index[i]->next, list.index[i]->last, list.index[i]->index };
		}
	}

	dList(float time[], float fuel[], int numElements)
	{

		//sort elements before adding them

		//used size of array 
		elements = numElements - 1;
		size = numElements;
		capacity = numElements * 2;
		index = new Run*[capacity];
		Run **sorted = new Run*[numElements];

		for (int i = 0; i < numElements; i++)
		{
			index[i] = new Run{ time[i], fuel[i], nullptr, nullptr, i };
			sorted[i] = index[i];
		}



		mergeSort(sorted, 0, numElements - 1);

		//first element in the list
		head = sorted[0];
		tail = head;

		//parses through input arrays
		int dominations = 0;
		for (int i = 1; i < size; i++)
		{
			if (dominates(tail, sorted[i + dominations]))
			{//ignores data entry and shrinks used aray
				i--;
				size--;
				dominations++;
			}
			else
			{//adds element to list 
				tail->next = sorted[i+dominations];
				sorted[i + dominations]->last = tail;
				tail = sorted[i + dominations];
			}
		}
	}

	dList& operator=(dList list)
	{
		elements = list.elements;
		size = list.size;
		capacity = list.capacity;
		index = list.index;
		head = list.head;
		tail = list.tail;
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
				cout << "Time " << run->time << " Fuel " << run->fuel << endl;
				//cout << "Pre " << run->last << " Next " << run->next << endl << endl;

				run = run->next;
			}
		}
		else
		{
			Run *run = tail;
			for (int i = size - 1; i >= 0; i--)
			{
				cout << "Time " << run->time << " Fuel " << run->fuel << endl;

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
				cout << "Time " << run->time << " Fuel " << run->fuel << endl;

				run = run->next;
			}
		}
		else
		{
			Run *run = tail;
			for (int i = length - 1; i >= 0; i--)
			{
				cout << "Time " << run->time << " Fuel " << run->fuel << endl;

				run = run->last;
			}
		}
	}

	int insert(float time, float fuel)
	{
		Run *tmp = new Run{ time, fuel, nullptr, nullptr, ++elements};
		Run *run = head;

		if (elements >= capacity)
		{
			capacity *= 2;
			Run **tmpIndex = new Run*[capacity];

			for (int i = 0; i < elements; i++)
			{
				tmpIndex[i] = index[i];
			}

			delete index;
			index = tmpIndex;
		}

		index[elements] = tmp;
		int count;
		bool added = 0;
		for (count = 0; count < size; count++)
		{
			if (tmp->time < run->time)
			{//add element in the middle of the list
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
					return elements;
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

			//cout << "\n\nNew " << tmp->time << " Start " << run << endl;

			for (; count < s; count++)
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
				else
				{
					break;
				}

				run = run->next;
			}
		}
		else if (tmp->fuel < tail->fuel)
		{//add element at end of list
			tail->next = tmp;
			tmp->last = tail;
			tail = tmp;
			size++;
		}

		return elements;
	}

	void increase_time(int index, float time)
	{
		Run *run = this->index[index];

		run->fuel += time;
		
		if (run->last != nullptr)
		{
			run->last->next = run->next;
		}

		if (run->next != nullptr)
		{
			run->next->last = run->last;
		}

		size--;
		insert(run);
	}

	void decrease_time(int index, float time)
	{
		Run *run = this->index[index];

		run->fuel -= time;

		if (run->last != nullptr)
		{
			run->last->next = run->next;
		}
		else
		{
			head = run->next;
		}

		if (run->next != nullptr)
		{
			run->next->last = run->last;
		}
		else
		{
			tail = run->last;
		}

		size--;
		insert(run);
	}

	void increase_fuel(int index, float fuel)
	{
		Run *run = this->index[index];

		run->fuel += fuel;
		
		if (run->last != nullptr)
		{
			if (run->fuel >= run->last->fuel)
			{
				run->last->next = run->next;
				run->next->last = run->last;
			}
		}
	}

	void decrease_fuel(int index, float fuel)
	{
		Run *run = this->index[index];

		run->fuel -= fuel;
		Run *ptr;

		for (ptr = run->next; ptr != tail; ptr = ptr->next)
		{
			if (run->time <= ptr->time && run->fuel <= ptr->fuel)
			{
				run->next = ptr->next;
				ptr->next->last = run;
			}
			else
			{
				break;
			}
		}
	}

	int index_before(int index)
	{
		return this->index[index]->last->index;
	}

	int index_after(int index)
	{
		return this->index[index]->next->index;
	}

private:
	Run *head,//the first element in the list
		*tail,//last element in list
		**index;//dynamic array of elements
	int size,//number of elements in list
		elements,//number of total entries
		capacity;//space in index array

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

	void merge(Run *a[], int l, int r, int m)
	{
		int lowSize = m - l + 1,
			highSize = r - m;

		Run **tmpLow = new Run*[lowSize],
			**tmpHigh = new Run*[highSize];

		//copy low
		for (int i = 0; i < lowSize; i++)
		{
			tmpLow[i] = a[i + l];
		}

		//copy high
		for (int i = 0; i < highSize; i++)
		{
			tmpHigh[i] = a[i + m + 1];
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
					a[i] = tmpLow[lowCount];
					lowCount++;
				}
				else if (tmpLow[lowCount]->time < tmpHigh[highCount]->time)
				{//pick element from low array
					a[i] = tmpLow[lowCount];
					lowCount++;
				}
				else if (tmpLow[lowCount]->time == tmpHigh[highCount]->time)
				{
					if (tmpLow[lowCount]->fuel <= tmpLow[highCount]->fuel)
					{//pick element from low array
						a[i] = tmpLow[lowCount];
						lowCount++;
					}
					else
					{//pick element from high array
						a[i] = tmpHigh[highCount];
						highCount++;
					}
				}
				else
				{//pick element from high array
					a[i] = tmpHigh[highCount];
					highCount++;
				}
			}
			else
			{//pick element from high array
				a[i] = tmpHigh[highCount];
				highCount++;
			}
		}
	}

	void mergeSort(Run *a[], int l, int r)
	{
		if (r - l > 0)
		{//split in two halves and recursive call
			int m = ((r - l) / 2) + l;
			mergeSort(a, l, m);
			mergeSort(a, m + 1, r);

			merge(a, l, r, m);
		}
		//one element base case
	}

	void insert(Run *tmp)
	{
		Run *run = head;

		int count;
		bool added = 0;
		for (count = 0; count < size; count++)
		{
			if (tmp->time < run->time)
			{//add element in the middle of the list
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
					return ;
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

			//cout << "\n\nNew " << tmp->time << " Start " << run << endl;

			for (; count < s; count++)
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
				else
				{
					break;
				}

				run = run->next;
			}
		}
		else if (tmp->fuel < tail->fuel)
		{//add element at end of list
			tail->next = tmp;
			tmp->last = tail;
			tail = tmp;
			size++;
		}

		return;
	}
};