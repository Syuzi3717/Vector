#include <iostream>
#include <iterator>
#include <vector>

namespace my_advance{

    template<typename It>
    constexpr void _advance(It& it, typename std::iterator_traits<It>::difference_type n, std::forward_iterator_tag )
    {
        std::cout<<"third"<<std::endl;
        while (n > 0) 
        {
            --n;
            ++it;
        }
    }

    template <typename It>
    constexpr void _advance(It& it, typename std::iterator_traits<It>::difference_type n, std::random_access_iterator_tag )
    {
        std::cout<<"second"<<std::endl;
        it+=n;
    }

    template<typename It>
    constexpr void _advance(It& it, typename std::iterator_traits<It>::difference_type n, std::bidirectional_iterator_tag )
    {
        std::cout<<"first"<<std::endl;
        while (n > 0) 
        {
            --n;
            ++it;
        }
        while (n < 0) 
        {
            ++n;
            --it;
        }
    }
}

template<typename It, typename D >
constexpr void _advance(It& it, D n){
    std::cout<<"final"<<std::endl;
    my_advance::_advance(it, typename std::iterator_traits<It>::difference_type(n), typename std::iterator_traits<It>::iterator_category() );
} 

int main() 
{
    std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
    auto ptr = v.begin();
    ::_advance(ptr, 4);
    std::cout << *ptr << std::endl;

}