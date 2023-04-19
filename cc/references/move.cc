#include <iostream>
#include <memory>
/*
   Theory: 

    ___sym___ _no_sym_
   /         X        \
  /         / \        \
 |   l     | x |  pr    |
  \         \ /        /
   \_________X________/
       gl        r
*/

class Y {
    public:
    Y() {
    }
    ~Y() {
        std::cout << "Y destructor" << std::endl;
    }
};
class X {
public:
int* ptr;
int i = 0;
    X() {
    }
    X(const X& rhs) {
        std::cout << "lvalue copy constructor" << std::endl;
    }

    X(X&& rhs) {
        std::cout << "rvalue move constructor" << std::endl;
    }

    X& operator=(const X& rhs) {
        std::cout << "lvalue copy assignment" << std::endl;
        return *this;
    }
    X& operator=(X&& rhs) {
        std::cout << "rvalue move assignment" << std::endl;
        return *this;
    }

    ~X() {
        std::cout << "X Destructing!" << std::endl;
    }

};

X boo() {
    return X();
}


void Group0() {
    // Question 0  lifetime
    X x = boo();
    //boo();
    // lifetime
    //X&& x = boo();
    //X&& x = std::move(boo());
    std::cout << "=======================" << std::endl;
    //Y yy = x.y;
    //X y = x;
}

X&& foo() {
    X x;
    return std::move(x);
}


void Group1() {
    // Question 1
    X&& x = foo();
    X x2 = x;

    std::cout << "=======================" << std::endl;
    // Question 2
    //X x1 = foo();
}

// Question 3
template<typename T, typename Arg>
std::shared_ptr<T> factory(Arg arg) {
    std::cout << "===========2===========" << std::endl;
    return std::make_shared<T>(T(arg));
}


void Group2() {
    // Here we introduces perfect forwarding
    X x;
    std::cout << "===========1===========" << std::endl;
    factory<X>(std::move(x));

}

/*  Theory: collapsing rules:
Recall that in pre-11 C++, it was not allowed to take a reference to a reference: 
something like A& & would cause a compile error. 
C++11, by contrast, introduces the following reference collapsing rules1:
 
    A& & becomes A&
    A& && becomes A&
    A&& & becomes A&
    A&& && becomes A&&
*/

/* template deduction rules:

template<typename T>
void foo(T&&);

template <X>
void foo(X&&)

Here, the following apply:
X x;
foo(X&&)
    When foo is called on an lvalue of type A, then T resolves to A& 
    and hence, by the reference collapsing rules above, the argument type effectively becomes A&.
    When foo is called on an rvalue of type A, then T resolves to A, 
    and hence the argument type becomes A&&. 
*/

// Question 4: change Q3: factory(Arg -> Arg&&) and add forward

template<class S>
S&& polo_forward(typename std::remove_reference<S>::type& a) noexcept
{
  return static_cast<S&&>(a);
} 

template<typename T, typename Arg> 
std::shared_ptr<T> factory2(Arg&& arg)
{ 
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    return std::make_shared<T>(T (std::forward<Arg>(arg)));
} 



void Group3() {
    // Here we introduces perfect forwarding
    X x;
    std::cout << "===========1===========" << std::endl;
    factory2<X>(x);
    std::cout << "===========2===========" << std::endl;
    factory2<X>(std::move(x));
    std::cout << "===========3===========" << std::endl;

}
/*  Theory: rvalue reference? universal reference?
    Whether there's Deduct
 
    std::string &s = "asd";
*/



// Question 5 RVO
X simple()
{
    X x;
    return x;
}
X simple_with_move()
{
    X x;
    // move prohibits NRVO
    return std::move(x);
}
X complicated(int n)
{
    X x1;
    X x2;
    // branch disturbs NRVO
    if (n % 2 == 0) {
        return x1;
    } else {
        return x2;
    }
}
void Group4() {
    std::cout << "*** 1 ***" << std::endl;
    auto obj1 = simple();
    std::cout << "*** 2 ***" << std::endl;
    auto obj2 = simple_with_move();
    std::cout << "*** 3 ***" << std::endl;
    auto obj3 = complicated(42);
}


int main() {
    Group0();

}


