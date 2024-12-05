// Copyright (c) 2024.
// Kabylkas Labs. and Texer.AI. All rights reserved.
#include "observe_algo.h"

// C++ libraries.
#include <memory>
#include <vector>

// Local libraries.
#include "board.h"
#include "cell.h"

namespace sudsol
{
    bool ObserveAlgo::Solve(Board& board_to_solve, std::string& err_message)
    {
        bool is_fail = false;

        for (size_t i = 0; !is_fail && i < board_to_solve.kMaxXY; i++)
        {
            std::string err_message;
            std::vector<std::shared_ptr<Cell>> horizontal_cell_ptrs;
            if (board_to_solve.GetHorizontalLine(i, horizontal_cell_ptrs, err_message))
            {
                for (size_t j = 0; !is_fail && j < board_to_solve.kMaxXY; j++)
                {
                    uint16_t value = 0;
                    bool is_retrieved = board_to_solve.GetValue(j, i, value, err_message);
                    if (is_retrieved && value == 0)
                    {
                        // Get the values in the vertical line and add them to the exclude set.
                        std::vector<std::shared_ptr<Cell>> vertical_cell_ptrs;
                        is_retrieved = board_to_solve.GetVerticalLine(j, vertical_cell_ptrs, err_message);
                        if (is_retrieved)
                        {
                            for (const auto& cell_ptr : horizontal_cell_ptrs)
                            {
                                board_to_solve.AddExcludeValue(j, i, cell_ptr->value);
                            }
                        }
                    }
                    else
                    {
                        is_fail = true;
                    }
                }
            }
            else
            {
                is_fail = true;
            }
        }

        return !is_fail;
    }
}