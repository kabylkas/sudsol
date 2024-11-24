// Copyright (c) 2024.
// Kabylkas Labs. and Texer.AI. All rights reserved.
#include "board.h"

// Local libraries.
#include "cell.h"

namespace sudsol
{
    // Class implementation.
    struct Board::BoardImpl
    {
        std::array<std::array<Cell, 9>, 9> board;
    };

    Board::Board()
    {
        if (pimpl_ == nullptr)
        {
            pimpl_ = new BoardImpl();
        }
    }

    bool Board::GetHorizontalLine(std::vector<std::shared_ptr<Cell>>& cell_line, std::string& err_message)
    {
        err_message = "Not implemented";
        return false;
    }

    bool Board::GetVerticalLine(std::vector<std::shared_ptr<Cell>>& cell_line, std::string& err_message)
    {
        err_message = "Not implemented";
        return false;
    }

    bool Board::GetSquare(std::vector<std::shared_ptr<Cell>>& cell_square, std::string& err_message)
    {
        err_message = "Not implemented";
        return false;
    }

    Board::~Board()
    {
        if (pimpl_ != nullptr)
        {
            delete pimpl_;
        }
    }
}