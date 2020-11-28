#include "red-black-tree.cpp"
#include <iostream>
#include <random>
#include <chrono>
#include "smp.cpp"
#include <fstream>
#include <vector>
#include <set>

void test(){

   std::ofstream os("result_2.txt");
   int total=1000000;
   int d=10000;
    auto begin = std::chrono::high_resolution_clock::now();
    for(int i=0; i<total/d; i++) {
        RED_BLACK_TREE<int> rbt;
        for (int j = 0; j < i*d; j++) {
            rbt.insert(j);
        }
//        auto end = std::chrono::high_resolution_clock::now();
//        std::chrono::duration<double> dur_1 = end - begin;
//        begin = std::chrono::high_resolution_clock::now();
        std::set<int> s;
        for (int j = 0; j < i*d; j++) {
            s.insert(j);
        }
//        end = std::chrono::high_resolution_clock::now();
//        std::chrono::duration<double> dur_2 = end - begin;
//        os << i*d <<' '<<dur_2/dur_1<<'\n';
    }

    for(int i=0; i<total/d; i++) {
        RED_BLACK_TREE<int> rbt;
        for (int j = 0; j < i*d; j++) {
            rbt.erase(j);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dur_1 = end - begin;
        begin = std::chrono::high_resolution_clock::now();
        std::set<int> s;
        for (int j = 0; j < i*d; j++) {
            s.erase(j);
        }
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dur_2 = end - begin;
        os << i*d <<' '<<dur_2/dur_1<<'\n';
    }
}

int main(){
   test();
    return 0;
}
