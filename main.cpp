#include <iostream>
#include <chrono>
#include <set>
#include "AVLtree.cpp"

int main(){
    AVL<int, int> b;
    double t;
    std::set<int> s;
	auto start = std::chrono::high_resolution_clock::now();
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    start = std::chrono::high_resolution_clock::now();
    for(int k = 1; k < 1000; k+=100){
		auto start = std::chrono::high_resolution_clock::now();
    	auto finish = std::chrono::high_resolution_clock::now();
    	std::chrono::duration<double> elapsed = finish - start;
		for(int i = 0 ; i < k; i++){
	        b.insert(i,i);
		}
		for(int i = 0; i < k; i++){
			b.erase(i);
		}
	    finish = std::chrono::high_resolution_clock::now();
	    elapsed = finish-start;
	    t = elapsed.count();
	    std::cout << t << " ";
	    auto start1 = std::chrono::high_resolution_clock::now();
    	auto finish1 = std::chrono::high_resolution_clock::now();
    	std::chrono::duration<double> elapsed1 = finish1 - start1;
		for(int i = 0 ; i < k; i++){
	        s.insert(i);
		}
		for(int i = 0; i < k; i++){
			s.erase(i);
		}
	    finish1 = std::chrono::high_resolution_clock::now();
	    elapsed1 = finish1-start1;
	    t = elapsed1.count();
	    std::cout << t << "\n";
	}
	for(int i = 0; i < 6; i++){
		b.insert(i,i);
	}
	for(int i = 0; i < 6; i++){
		b.print(b.find(i));
		std::cout << "\n";
	}
	return 0;
}
