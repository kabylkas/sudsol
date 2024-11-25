// Copyright (c) 2024. All rights reserved.
// Kabylkas Labs and Texer.AI.

// C++ libraries.
#include <iostream>
#include <memory>

// Local libraries.
#include "board.h"
#include "cell.h"

int main()
{
    sudsol::Board board;

    std::string err_message;
    std::vector<std::shared_ptr<sudsol::Cell>> cell_ptrs;
    if (!board.GetHorizontalLine(3, cell_ptrs, err_message))
    {
        std::cout << err_message << std::endl;
    }

    return 0;
}