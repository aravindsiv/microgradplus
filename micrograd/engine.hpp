#include "defs.hpp"

class Value
{
    private:
    double data;
    std::unordered_set<ValuePtr> parents;
    operate op;
    std::string label;

    protected:
    double grad = 0.0;

    public:
    Value(double data) : data(data) {}
    Value(double data, std::string label) : data(data), label(label) {}
    Value(double data, std::unordered_set<ValuePtr> parents, operate op, std::string label) : data(data), parents(parents), op(op), label(label) {}
    ~Value() {}

    std::function<void()> bwd = [](){};

    void backward();

    void build_topo(ValuePtr node, std::vector<ValuePtr> &topo, std::unordered_set<std::string>  &visited);

    double get_data() const { return data; }

    double get_grad() const { return grad; }

    void set_label(std::string label) { this->label = label; }

    std::string get_label() const { return label; }

    std::unordered_set<ValuePtr> get_parents() const { return parents; }

    // Overload the std::cout << operator to print the value.
    friend std::ostream& operator<<(std::ostream& os, const Value& v)
    {
        os << "Value(data = " << v.data << ")";
        return os;
    }

    // Overload the + operator to add two values.
    Value operator+(const Value& other) const
    {
        ValuePtr a = std::make_shared<Value>(*this);
        ValuePtr b = std::make_shared<Value>(other);
        std::unordered_set<ValuePtr> parents = {a, b};
        ValuePtr c = std::make_shared<Value>(this->data + other.data, parents, ADD, "");
        
        // c's bacwkard is a function that assigns gradients as follows.
        // a.grad += c.grad
        // b.grad += c.grad
        // It needs to get the value of c.grad that may change in the future.
        // So we use a lambda function to capture the value of c.grad at runtime.
        c->bwd = [a, b, c]()
        {
            std::cout << "Called backward on " << c->get_label() << std::endl;
            a->grad += c->get_grad();
            b->grad += c->get_grad();
        }; 

        // c -> bwd = [&, a, b, c]() 
        // {
        //     std::cout << "Current value of this.grad = " << c->grad << std::endl;
        //     std::cout << "Called backward on " << c-> label << std::endl;
        //     a -> grad += 1.0 * c -> grad;
        //     std::cout << "a.grad = " << a -> grad << std::endl;
        //     b -> grad += 1.0 * c -> grad;
        //     std::cout << "b.grad = " << b -> grad << std::endl;
        // };
        return *c;
    }

    // Overload the * operator to multiply two values.
    Value operator*(const Value& other) const
    {
        ValuePtr a = std::make_shared<Value>(*this);
        ValuePtr b = std::make_shared<Value>(other);
        std::unordered_set<ValuePtr> parents = {a, b};
        ValuePtr c = std::make_shared<Value>(this->data * other.data, parents, MUL, "");
        
        // c's bacwkard is a function that assigns gradients as follows.
        // a.grad += b.data * c.grad
        // b.grad += a.data * c.grad
        // It needs to get the value of c.grad that may change in the future.
        // So we use a lambda function to capture the value of c.grad.
        c->bwd = [a, b, c]()
        {
            std::cout << "Called backward on " << c->get_label() << std::endl;
            a->grad += b->get_data() * c->get_grad();
            b->grad += a->get_data() * c->get_grad();
        };
        
        // c->bwd = [&, a, b, c]() 
        // {
        //     std::cout << "Current value of this.grad = " << c->grad << std::endl;
        //     std::cout << "Called backward on " << c -> label << std::endl;
        //     a -> grad += b -> data * c -> grad;
        //     std::cout << "a.grad = " << a -> grad << std::endl;
        //     b -> grad += a -> data * c -> grad;
        //     std::cout << "b.grad = " << b -> grad << std::endl;
        // };
        return *c;
    }
};