#include <algorithm>
#include <vector>
#include <iostream>

int main(){
    std::vector<int> v1;
    for(size_t i=0; i < 9; i++)
        v1.push_back(i);
    size_t i =0;
    while( i < v1.size())
    {
            std::cout <<i << ":" <<  v1.size() << std::endl;
            v1.erase(find(v1.begin(), v1.end(), v1[i]));
            
    }
    std::cout << v1.size() << std::endl;
}