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

static const uint16_t kDontCare = 0;

enum class SudokuBoardSubset
{
    kUndefined,
    kHorizontalLine,
    kVerticalLine,
    kSquare
};

namespace aux
{
    static void TestEqual(const sudsol::Board& board, uint16_t x, uint16_t y,
        SudokuBoardSubset board_subset, const std::vector<uint16_t> compare_values,
        uint32_t line_number)
    {
        bool is_retrieved = false;
        std::vector<std::shared_ptr<sudsol::Cell>> cell_ptrs;
        std::string err_message;
        switch (board_subset)
        {
        case SudokuBoardSubset::kHorizontalLine:
            is_retrieved = board.GetHorizontalLine(y, cell_ptrs, err_message);
            break;
        case SudokuBoardSubset::kVerticalLine:
            is_retrieved = board.GetVerticalLine(x, cell_ptrs, err_message);
            break;
        case SudokuBoardSubset::kSquare:
            is_retrieved = board.GetSquare(x, y, cell_ptrs, err_message);
            break;
        default:
            err_message = "Error: Could not retrieve subset from the board.";
            break;
        }

        bool are_equal = false;
        if (is_retrieved)
        {
            are_equal = cell_ptrs.size() == compare_values.size();
            for (size_t i = 0; are_equal && i < sudsol::Board::kMaxXY; i++)
            {
                are_equal = (cell_ptrs[i]->value == compare_values[i]);
            }

            if (!are_equal)
            {
                err_message = "Error: Comparison failed.";
            }
        }


        if (!is_retrieved || !are_equal)
        {
            std::cerr << "Test case at line " << line_number << " failed. " << err_message << "." << std::endl;
        }
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

    aux::TestEqual(board, kDontCare, 3, SudokuBoardSubset::kHorizontalLine, {0, 4, 5, 6, 4, 0, 0, 0, 0}, __LINE__);

    return 0;
}