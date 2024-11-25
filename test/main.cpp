// Copyright (c) 2024. All rights reserved.
// Kabylkas Labs and Texer.AI.

// C++ libraries.
#include <cassert>
#include <iostream>
#include <memory>

// Local libraries.
#include "board.h"
#include "cell.h"

int main()
{
    sudsol::Board board;
    std::string err_message;
    bool is_loaded = board.Load("../../test/golden_data/board.txt", err_message);
    if (!is_loaded)
    {
        std::cout << err_message << std::endl;
    }

    std::vector<std::shared_ptr<sudsol::Cell>> cell_ptrs;
    if (board.GetHorizontalLine(3, cell_ptrs, err_message))
    {
        assert(cell_ptrs[0]->value == 0);
        assert(cell_ptrs[1]->value == 4);
        assert(cell_ptrs[2]->value == 5);
        assert(cell_ptrs[3]->value == 6);
        assert(cell_ptrs[4]->value == 4);
        assert(cell_ptrs[5]->value == 0);
        assert(cell_ptrs[6]->value == 0);
        assert(cell_ptrs[7]->value == 0);
        assert(cell_ptrs[8]->value == 0);
    }
    else
    {
        std::cout << err_message << std::endl;
    }

    return 0;
}