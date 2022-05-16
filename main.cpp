#include <iostream>
#include "vec.h"

int main()
{
    Vector<int> vec{1, 2, 3, 4, 5, 6, 7};
    Vector<int>::iterator it;
    vec.push_back(45);
    vec.pop_front();
    for(it = vec.begin();  it !=  vec.end(); ++it)
    {
        std::cout << *it << " ";
    }
    it = vec.find(vec.begin(), vec.end(), 3);
    std::cout<<std::endl<<*it<<std::endl;
    
}

