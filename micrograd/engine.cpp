#include "engine.hpp"

void Value::backward()
{
    std::vector<ValuePtr> topo;
    std::unordered_set<std::string> visited;
    build_topo(std::make_shared<Value>(*this), topo, visited);
    this->grad = 1.0;
    for (int i = topo.size() - 1; i >= 0; i--)
    {   
        std::cout << "Calling backward on " << topo[i] -> label << std::endl;
        topo[i]->bwd();
    }
}

void Value::build_topo(ValuePtr node, std::vector<ValuePtr> &topo, std::unordered_set<std::string> &visited)
{
    if (visited.find(node -> label) == visited.end())
    {
        visited.insert(node -> label);
        for (auto child : node->get_parents())
        {
            build_topo(child, topo, visited);
        }
        topo.push_back(node);
    }
}