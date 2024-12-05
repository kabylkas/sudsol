// Copyright (c) 2024.
// Kabylkas Labs. and Texer.AI. All rights reserved.

// C++ libraries.
#include <string>

namespace sudsol
{
    // Forward declarations.
    class Board;

    class IAlgorithm
    {
    public:
        virtual bool Solve(Board& board_to_solve, std::string& err_message) = 0;
    };
}
