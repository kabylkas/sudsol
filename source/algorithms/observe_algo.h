// Copyright (c) 2024.
// Kabylkas Labs. and Texer.AI. All rights reserved.

// C++ libraries.
#include <string>

// Parent class.
#include "algorithm.h"

namespace sudsol
{
    // Forward declarations.
    class Board;

    class ObserveAlgo : public IAlgorithm
    {
    public:
        bool Solve(Board& board_to_solve, std::string& err_message) override;
    };
}