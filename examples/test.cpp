#include "engine.hpp"

int main()
{
    Value a = Value(-2.0, "a");
    Value b = Value(3.0, "b");

    Value d = a*b;
    d.set_label("d");
    Value e = a+b;
    e.set_label("e");

    Value f = d*e;
    f.set_label("f");

    std::cout << f << std::endl; 
    f.backward();
    std::cout << "f.grad = " << f.get_grad() << std::endl;
    std::cout << "d.grad = " << d.get_grad() << std::endl;
    std::cout << "e.grad = " << e.get_grad() << std::endl;
    std::cout << "a.grad = " << a.get_grad() << std::endl;
    std::cout << "b.grad = " << b.get_grad() << std::endl;

    // std::cout << "a.grad = " << a.get_grad() << std::endl;
    // std::cout << "b.grad = " << b.get_grad() << std::endl;
    // std::cout << "c.grad = " << c.get_grad() << std::endl;
    // std::cout << "d.grad = " << d.get_grad() << std::endl;
    // std::cout << "e.grad = " << e.get_grad() << std::endl;
    // std::cout << "f.grad = " << f.get_grad() << std::endl;
}