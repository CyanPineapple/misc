#include <iostream>
#include <thread>

void update(int &data)  //expects a reference to int
{
    data = 15;
}

template<typename T>
void set(T& t){
    std::cout << "left reference" <<"\n";
}

template<typename T>
void set(T&& t){
    std::cout << "right reference" <<"\n";
}

template<typename T>
void wrapper(T&& t) {
    set(std::forward<T>(t));
}


int main()
{
    int data = 10;

    // This doesn't compile as the data value is copied when its reference is expected.
    //std::thread t1(update, data);         
    wrapper(0);
    
        

    return 0;
}
