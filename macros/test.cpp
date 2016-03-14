#include <vector>

int test(){
	vector<int>* vec = new vector<int>();
	vec->push_back(1);
	vec->push_back(2);
	vec->push_back(3);
	return vec->size();
}