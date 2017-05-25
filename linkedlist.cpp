
#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>

#include "llist.h"
#include "dllist.h"
#include "timing.h"



template <class Iter>
void selectionSort(Iter, Iter);				// implement
template <class Container, class T>
void insertNextToMatch(Container &, const T&);		// implement


struct time {
	uint64 start;
	std::string name;
	time(const std::string& str="") : start(GetTimeMs64()), name(str) {}
	void getTimeElapsed() {
		std::cout << name << "... " << GetTimeMs64() - start << std::endl;
	}
	void startAgain(const std::string& str="") {
		start = GetTimeMs64();
		name = str;
	}
};

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Usage: ./a.out <FILENAME>\n";
		return 0;
	}

	std::ifstream fin; //Included the std:: because it would not compile.
	fin.open(argv[1]);


	std::vector<int> v1, v2;
	int x;
	while (fin) {
		fin >> x;
		v1.push_back(x);
		if (v1.size() % 5 > 2) v2.push_back(x);
	}

	struct time t("filling list");
	List<int> lst;
	for (int i = 0; i < v1.size(); i++) {	lst.push_front(v1[i]); }
	t.getTimeElapsed();

	t.startAgain("filling dlist");
	DList<int> dlst;
	for (int i = 0; i < v1.size(); i++) {	dlst.push_front(v1[i]); }
	t.getTimeElapsed();

	t.startAgain("filling vector");
	std::vector<int> v;
	for (int i = 0; i < v1.size(); i++) { v.push_back(v1[i]); }
	t.getTimeElapsed();

	t.startAgain("sorting list");
	selectionSort(lst.begin(), lst.end());
	t.getTimeElapsed();

	t.startAgain("sorting dlist");
	selectionSort(dlst.begin(), dlst.end());
	t.getTimeElapsed();

	t.startAgain("sorting vector");
	selectionSort(v.begin(), v.end());
	t.getTimeElapsed();

	t.startAgain("adding more to list");
	for(int i = 0; i < v2.size(); i++) { insertNextToMatch(lst, v2[i]); }
	t.getTimeElapsed();

	t.startAgain("adding more to dlist");
	for(int i = 0; i < v2.size(); i++) { insertNextToMatch(dlst, v2[i]); }
	t.getTimeElapsed();

	t.startAgain("adding more to vector");
	for(int i = 0; i < v2.size(); i++) { insertNextToMatch(v, v2[i]); }
	t.getTimeElapsed();
}

//creates a double nested loop that places the smallest value in the min position.
template <class Iter>
void selectionSort(Iter it1, Iter it2){

	    Iter  iit;

	    for(Iter it = it1; it != it2; ++it)//loops through.
	    {
	        Iter min = it;//establishes the first in the list to be the least.
	        iit = it;//sets iit to it then increments by one for reasons of comparison.
	        ++iit;
	        for(; iit != it2; ++iit)//nested loop, loops through.
	        {
	            if(*iit < *min)//the value if the current node is less then the minimum.
	                min = iit;//saves the node.
	        }
	        std::swap(*it, *min);//swaps the two.
	    }


}

//Finds the match and inserts the value n, next to it.
template <class Container, class T>
void insertNextToMatch(Container &v, const T&n){

	    typename Container::iterator iter;


	    for(iter = v.begin(); iter != v.end(); ++iter)//loops through.
	    {
	        if(*iter == n)//if the value matches the target value.
	        {
	            v.insert(++iter, n);//calls insert to insert it.
	            return;
	        }
	    }

	    v.insert(iter, n);//if the value did not match the target inserts it at the end.


}

