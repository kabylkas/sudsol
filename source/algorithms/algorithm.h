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
        virtual bool Solve(const Board& board_to_solve, Board& solved_board, std::string& err_message) = 0;
    };
}