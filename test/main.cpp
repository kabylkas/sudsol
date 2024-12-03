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
            std::cerr << "Test case at line " << line_number << " failed. " << err_message << std::endl;
        }
    }

}

int main()
{
    sudsol::Board board;
    std::string err_message;
    bool is_loaded = board.Load("../../test/golden_data/board.txt", err_message);
    if (is_loaded)
    {
        // Check horizontal.
        aux::TestEqual(board, kDontCare, 0, SudokuBoardSubset::kHorizontalLine, {1, 2, 3, 4, 5, 6, 7, 8, 0}, __LINE__);
        aux::TestEqual(board, kDontCare, 1, SudokuBoardSubset::kHorizontalLine, {4, 5, 6, 1, 2, 0, 0, 0, 1}, __LINE__);
        aux::TestEqual(board, kDontCare, 2, SudokuBoardSubset::kHorizontalLine, {2, 1, 0, 0, 0, 3, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, kDontCare, 3, SudokuBoardSubset::kHorizontalLine, {0, 4, 5, 6, 4, 0, 0, 0, 0}, __LINE__);
        aux::TestEqual(board, kDontCare, 4, SudokuBoardSubset::kHorizontalLine, {5, 4, 5, 4, 0, 0, 0, 4, 4}, __LINE__);
        aux::TestEqual(board, kDontCare, 5, SudokuBoardSubset::kHorizontalLine, {0, 0, 0, 9, 8, 7, 4, 5, 0}, __LINE__);
        aux::TestEqual(board, kDontCare, 6, SudokuBoardSubset::kHorizontalLine, {0, 0, 8, 9, 0, 5, 5, 0, 1}, __LINE__);
        aux::TestEqual(board, kDontCare, 7, SudokuBoardSubset::kHorizontalLine, {0, 9, 8, 7, 0, 0, 1, 1, 2}, __LINE__);
        aux::TestEqual(board, kDontCare, 8, SudokuBoardSubset::kHorizontalLine, {4, 5, 6, 1, 2, 0, 0, 0, 1}, __LINE__);

        // Check vertical.
        aux::TestEqual(board, 0, kDontCare, SudokuBoardSubset::kVerticalLine, {1, 4, 2, 0, 5, 0, 0, 0, 4}, __LINE__);
        aux::TestEqual(board, 1, kDontCare, SudokuBoardSubset::kVerticalLine, {2, 5, 1, 4, 4, 0, 0, 9, 5}, __LINE__);
        aux::TestEqual(board, 2, kDontCare, SudokuBoardSubset::kVerticalLine, {3, 6, 0, 5, 5, 0, 8, 8, 6}, __LINE__);
        aux::TestEqual(board, 3, kDontCare, SudokuBoardSubset::kVerticalLine, {4, 1, 0, 6, 4, 9, 9, 7, 1}, __LINE__);
        aux::TestEqual(board, 4, kDontCare, SudokuBoardSubset::kVerticalLine, {5, 2, 0, 4, 0, 8, 0, 0, 2}, __LINE__);
        aux::TestEqual(board, 5, kDontCare, SudokuBoardSubset::kVerticalLine, {6, 0, 3, 0, 0, 7, 5, 0, 0}, __LINE__);
        aux::TestEqual(board, 6, kDontCare, SudokuBoardSubset::kVerticalLine, {7, 0, 2, 0, 0, 4, 5, 1, 0}, __LINE__);
        aux::TestEqual(board, 7, kDontCare, SudokuBoardSubset::kVerticalLine, {8, 0, 1, 0, 4, 5, 0, 1, 0}, __LINE__);
        aux::TestEqual(board, 8, kDontCare, SudokuBoardSubset::kVerticalLine, {0, 1, 0, 0, 4, 0, 1, 2, 1}, __LINE__);

        // Check sub-boxes.
        // First sub-box.
        aux::TestEqual(board, 0, 0, SudokuBoardSubset::kSquare, {1, 2, 3, 4, 5, 6, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 0, 1, SudokuBoardSubset::kSquare, {1, 2, 3, 4, 5, 6, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 0, 2, SudokuBoardSubset::kSquare, {1, 2, 3, 4, 5, 6, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 1, 0, SudokuBoardSubset::kSquare, {1, 2, 3, 4, 5, 6, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 1, 1, SudokuBoardSubset::kSquare, {1, 2, 3, 4, 5, 6, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 1, 2, SudokuBoardSubset::kSquare, {1, 2, 3, 4, 5, 6, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 2, 0, SudokuBoardSubset::kSquare, {1, 2, 3, 4, 5, 6, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 2, 1, SudokuBoardSubset::kSquare, {1, 2, 3, 4, 5, 6, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 2, 2, SudokuBoardSubset::kSquare, {1, 2, 3, 4, 5, 6, 2, 1, 0}, __LINE__);

        // Second sub-box.
        aux::TestEqual(board, 3, 0, SudokuBoardSubset::kSquare, {4, 5, 6, 1, 2, 0, 0, 0, 3}, __LINE__);
        aux::TestEqual(board, 3, 1, SudokuBoardSubset::kSquare, {4, 5, 6, 1, 2, 0, 0, 0, 3}, __LINE__);
        aux::TestEqual(board, 3, 2, SudokuBoardSubset::kSquare, {4, 5, 6, 1, 2, 0, 0, 0, 3}, __LINE__);
        aux::TestEqual(board, 4, 0, SudokuBoardSubset::kSquare, {4, 5, 6, 1, 2, 0, 0, 0, 3}, __LINE__);
        aux::TestEqual(board, 4, 1, SudokuBoardSubset::kSquare, {4, 5, 6, 1, 2, 0, 0, 0, 3}, __LINE__);
        aux::TestEqual(board, 4, 2, SudokuBoardSubset::kSquare, {4, 5, 6, 1, 2, 0, 0, 0, 3}, __LINE__);
        aux::TestEqual(board, 5, 0, SudokuBoardSubset::kSquare, {4, 5, 6, 1, 2, 0, 0, 0, 3}, __LINE__);
        aux::TestEqual(board, 5, 1, SudokuBoardSubset::kSquare, {4, 5, 6, 1, 2, 0, 0, 0, 3}, __LINE__);
        aux::TestEqual(board, 5, 2, SudokuBoardSubset::kSquare, {4, 5, 6, 1, 2, 0, 0, 0, 3}, __LINE__);

        // Third sub-box.
        aux::TestEqual(board, 6, 0, SudokuBoardSubset::kSquare, {7, 8, 0, 0, 0, 1, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 6, 1, SudokuBoardSubset::kSquare, {7, 8, 0, 0, 0, 1, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 6, 2, SudokuBoardSubset::kSquare, {7, 8, 0, 0, 0, 1, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 7, 0, SudokuBoardSubset::kSquare, {7, 8, 0, 0, 0, 1, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 7, 1, SudokuBoardSubset::kSquare, {7, 8, 0, 0, 0, 1, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 7, 2, SudokuBoardSubset::kSquare, {7, 8, 0, 0, 0, 1, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 8, 0, SudokuBoardSubset::kSquare, {7, 8, 0, 0, 0, 1, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 8, 1, SudokuBoardSubset::kSquare, {7, 8, 0, 0, 0, 1, 2, 1, 0}, __LINE__);
        aux::TestEqual(board, 8, 2, SudokuBoardSubset::kSquare, {7, 8, 0, 0, 0, 1, 2, 1, 0}, __LINE__);

        // Fourth sub-box.
        aux::TestEqual(board, 0, 3, SudokuBoardSubset::kSquare, {0, 4, 5, 5, 4, 5, 0, 0, 0}, __LINE__);
        aux::TestEqual(board, 0, 4, SudokuBoardSubset::kSquare, {0, 4, 5, 5, 4, 5, 0, 0, 0}, __LINE__);
        aux::TestEqual(board, 0, 5, SudokuBoardSubset::kSquare, {0, 4, 5, 5, 4, 5, 0, 0, 0}, __LINE__);
        aux::TestEqual(board, 1, 3, SudokuBoardSubset::kSquare, {0, 4, 5, 5, 4, 5, 0, 0, 0}, __LINE__);
        aux::TestEqual(board, 1, 4, SudokuBoardSubset::kSquare, {0, 4, 5, 5, 4, 5, 0, 0, 0}, __LINE__);
        aux::TestEqual(board, 1, 5, SudokuBoardSubset::kSquare, {0, 4, 5, 5, 4, 5, 0, 0, 0}, __LINE__);
        aux::TestEqual(board, 2, 3, SudokuBoardSubset::kSquare, {0, 4, 5, 5, 4, 5, 0, 0, 0}, __LINE__);
        aux::TestEqual(board, 2, 4, SudokuBoardSubset::kSquare, {0, 4, 5, 5, 4, 5, 0, 0, 0}, __LINE__);
        aux::TestEqual(board, 2, 5, SudokuBoardSubset::kSquare, {0, 4, 5, 5, 4, 5, 0, 0, 0}, __LINE__);

        // Fifth sub-box.
        aux::TestEqual(board, 3, 3, SudokuBoardSubset::kSquare, {6, 4, 0, 4, 0, 0, 9, 8, 7}, __LINE__);
        aux::TestEqual(board, 3, 4, SudokuBoardSubset::kSquare, {6, 4, 0, 4, 0, 0, 9, 8, 7}, __LINE__);
        aux::TestEqual(board, 3, 5, SudokuBoardSubset::kSquare, {6, 4, 0, 4, 0, 0, 9, 8, 7}, __LINE__);
        aux::TestEqual(board, 4, 3, SudokuBoardSubset::kSquare, {6, 4, 0, 4, 0, 0, 9, 8, 7}, __LINE__);
        aux::TestEqual(board, 4, 4, SudokuBoardSubset::kSquare, {6, 4, 0, 4, 0, 0, 9, 8, 7}, __LINE__);
        aux::TestEqual(board, 4, 5, SudokuBoardSubset::kSquare, {6, 4, 0, 4, 0, 0, 9, 8, 7}, __LINE__);
        aux::TestEqual(board, 5, 3, SudokuBoardSubset::kSquare, {6, 4, 0, 4, 0, 0, 9, 8, 7}, __LINE__);
        aux::TestEqual(board, 5, 4, SudokuBoardSubset::kSquare, {6, 4, 0, 4, 0, 0, 9, 8, 7}, __LINE__);
        aux::TestEqual(board, 5, 5, SudokuBoardSubset::kSquare, {6, 4, 0, 4, 0, 0, 9, 8, 7}, __LINE__);

        // Sixth sub-box.
        aux::TestEqual(board, 6, 3, SudokuBoardSubset::kSquare, {0, 0, 0, 0, 4, 4, 4, 5, 0}, __LINE__);
        aux::TestEqual(board, 6, 4, SudokuBoardSubset::kSquare, {0, 0, 0, 0, 4, 4, 4, 5, 0}, __LINE__);
        aux::TestEqual(board, 6, 5, SudokuBoardSubset::kSquare, {0, 0, 0, 0, 4, 4, 4, 5, 0}, __LINE__);
        aux::TestEqual(board, 7, 3, SudokuBoardSubset::kSquare, {0, 0, 0, 0, 4, 4, 4, 5, 0}, __LINE__);
        aux::TestEqual(board, 7, 4, SudokuBoardSubset::kSquare, {0, 0, 0, 0, 4, 4, 4, 5, 0}, __LINE__);
        aux::TestEqual(board, 7, 5, SudokuBoardSubset::kSquare, {0, 0, 0, 0, 4, 4, 4, 5, 0}, __LINE__);
        aux::TestEqual(board, 8, 3, SudokuBoardSubset::kSquare, {0, 0, 0, 0, 4, 4, 4, 5, 0}, __LINE__);
        aux::TestEqual(board, 8, 4, SudokuBoardSubset::kSquare, {0, 0, 0, 0, 4, 4, 4, 5, 0}, __LINE__);
        aux::TestEqual(board, 8, 5, SudokuBoardSubset::kSquare, {0, 0, 0, 0, 4, 4, 4, 5, 0}, __LINE__);

        // Seventh sub-box.
        aux::TestEqual(board, 0, 6, SudokuBoardSubset::kSquare, {0, 0, 8, 0, 9, 8, 4, 5, 6}, __LINE__);
        aux::TestEqual(board, 0, 7, SudokuBoardSubset::kSquare, {0, 0, 8, 0, 9, 8, 4, 5, 6}, __LINE__);
        aux::TestEqual(board, 0, 8, SudokuBoardSubset::kSquare, {0, 0, 8, 0, 9, 8, 4, 5, 6}, __LINE__);
        aux::TestEqual(board, 1, 6, SudokuBoardSubset::kSquare, {0, 0, 8, 0, 9, 8, 4, 5, 6}, __LINE__);
        aux::TestEqual(board, 1, 7, SudokuBoardSubset::kSquare, {0, 0, 8, 0, 9, 8, 4, 5, 6}, __LINE__);
        aux::TestEqual(board, 1, 8, SudokuBoardSubset::kSquare, {0, 0, 8, 0, 9, 8, 4, 5, 6}, __LINE__);
        aux::TestEqual(board, 2, 6, SudokuBoardSubset::kSquare, {0, 0, 8, 0, 9, 8, 4, 5, 6}, __LINE__);
        aux::TestEqual(board, 2, 7, SudokuBoardSubset::kSquare, {0, 0, 8, 0, 9, 8, 4, 5, 6}, __LINE__);
        aux::TestEqual(board, 2, 8, SudokuBoardSubset::kSquare, {0, 0, 8, 0, 9, 8, 4, 5, 6}, __LINE__);

        // Eighth sub-box.
        aux::TestEqual(board, 3, 6, SudokuBoardSubset::kSquare, {9, 0, 5, 7, 0, 0, 1, 2, 0}, __LINE__);
        aux::TestEqual(board, 3, 7, SudokuBoardSubset::kSquare, {9, 0, 5, 7, 0, 0, 1, 2, 0}, __LINE__);
        aux::TestEqual(board, 3, 8, SudokuBoardSubset::kSquare, {9, 0, 5, 7, 0, 0, 1, 2, 0}, __LINE__);
        aux::TestEqual(board, 4, 6, SudokuBoardSubset::kSquare, {9, 0, 5, 7, 0, 0, 1, 2, 0}, __LINE__);
        aux::TestEqual(board, 4, 7, SudokuBoardSubset::kSquare, {9, 0, 5, 7, 0, 0, 1, 2, 0}, __LINE__);
        aux::TestEqual(board, 4, 8, SudokuBoardSubset::kSquare, {9, 0, 5, 7, 0, 0, 1, 2, 0}, __LINE__);
        aux::TestEqual(board, 5, 6, SudokuBoardSubset::kSquare, {9, 0, 5, 7, 0, 0, 1, 2, 0}, __LINE__);
        aux::TestEqual(board, 5, 7, SudokuBoardSubset::kSquare, {9, 0, 5, 7, 0, 0, 1, 2, 0}, __LINE__);
        aux::TestEqual(board, 5, 8, SudokuBoardSubset::kSquare, {9, 0, 5, 7, 0, 0, 1, 2, 0}, __LINE__);

        // Ninth sub-box.
        aux::TestEqual(board, 6, 6, SudokuBoardSubset::kSquare, {5, 0, 1, 1, 1, 2, 0, 0, 1}, __LINE__);
        aux::TestEqual(board, 6, 7, SudokuBoardSubset::kSquare, {5, 0, 1, 1, 1, 2, 0, 0, 1}, __LINE__);
        aux::TestEqual(board, 6, 8, SudokuBoardSubset::kSquare, {5, 0, 1, 1, 1, 2, 0, 0, 1}, __LINE__);
        aux::TestEqual(board, 7, 6, SudokuBoardSubset::kSquare, {5, 0, 1, 1, 1, 2, 0, 0, 1}, __LINE__);
        aux::TestEqual(board, 7, 7, SudokuBoardSubset::kSquare, {5, 0, 1, 1, 1, 2, 0, 0, 1}, __LINE__);
        aux::TestEqual(board, 7, 8, SudokuBoardSubset::kSquare, {5, 0, 1, 1, 1, 2, 0, 0, 1}, __LINE__);
        aux::TestEqual(board, 8, 6, SudokuBoardSubset::kSquare, {5, 0, 1, 1, 1, 2, 0, 0, 1}, __LINE__);
        aux::TestEqual(board, 8, 7, SudokuBoardSubset::kSquare, {5, 0, 1, 1, 1, 2, 0, 0, 1}, __LINE__);
        aux::TestEqual(board, 8, 8, SudokuBoardSubset::kSquare, {5, 0, 1, 1, 1, 2, 0, 0, 1}, __LINE__);
    }
    else
    {
        std::cout << err_message << std::endl;
    }


    return 0;
}