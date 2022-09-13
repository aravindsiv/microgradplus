// Some includes that will be needed library-wide.
#pragma once

#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <unordered_set>

class Value;
typedef std::shared_ptr<Value> ValuePtr;

enum operate { ADD, MUL };