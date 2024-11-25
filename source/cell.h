// Copyright (c) 2024.
// Kabylkas Labs. and Texer.AI. All rights reserved.

// C++ libraries.
#include <cstdint>
#include <set>

namespace sudsol
{
    struct Cell
    {
        uint16_t value = 0;
        std::set<uint16_t> exculude_values;
    };
}
