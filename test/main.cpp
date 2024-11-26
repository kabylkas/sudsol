// Copyright (c) 2024. All rights reserved.
// Kabylkas Labs and Texer.AI.

// C++ libraries.
#include <cassert>
#include <iostream>
#include <memory>

// Local libraries.
#include "board.h"
#include "cell.h"

using CellPtrs = std::vector<std::shared_ptr<sudsol::Cell>>;

namespace aux
{
    static bool AreEqual(const CellPtrs& cell_ptrs, const std::vector<uint16_t> compare_values)
    {
        bool should_abort = cell_ptrs.size() != compare_values.size();
        for (size_t i = 0; !should_abort && i < sudsol::Board::kMaxXY; i++)
        {
            should_abort = (cell_ptrs[i]->value != compare_values[i]);
        }
        return !should_abort;
    }
}

int main()
{
    sudsol::Board board;
    std::string err_message;
    bool is_loaded = board.Load("../../test/golden_data/board.txt", err_message);
    if (!is_loaded)
    {
        std::cout << err_message << std::endl;
    }

    bool are_equal = false;
    std::vector<std::shared_ptr<sudsol::Cell>> cell_ptrs;
    if (board.GetHorizontalLine(3, cell_ptrs, err_message))
    {
        are_equal = aux::AreEqual(cell_ptrs, {0, 4, 5, 6, 4, 0, 0, 0, 0});
        assert(are_equal);
    }
    else
    {
        std::cout << err_message << std::endl;
    }

    return 0;
}