// Copyright (c) 2024.
// Kabylkas Labs. and Texer.AI. All rights reserved.
#include "board.h"

// C++ libraries.
#include <fstream>
#include <iostream>

// Local libraries.
#include "cell.h"

namespace sudsol
{
    // Constants.
    static const uint16_t kMinValue            = 1;
    static const uint16_t kMaxValue            = 9;
    static const uint16_t kSudokuSubSquareSize = 3;

    // Constant error messages.
    static const char* kErrorStringXYOutOfRange      = "Error: Position is out of range.";
    static const char* kErrorStringValueOutOfRange   = "Error: Value is out of range.";
    static const char* kErrorStringNoFile            = "Error: Could not open the file.";
    static const char* kErrorIncorrectFileFormatRows = "Error: Incorrect file. Should be 9 rows.";
    static const char* kErrorIncorrectFileFormatCols = "Error: Incorrect file. Should be 9 columns.";
    static const char* kErrorIncorrectFileFormatChar = "Error: Incorrect file. Unexpected value in the board.";

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

    bool Board::GetHorizontalLine(uint16_t y, std::vector<std::shared_ptr<Cell>>& cell_ptrs, std::string& err_message) const
    {
        bool is_fail = false;
        if (y < kMaxXY)
        {
            cell_ptrs.resize(kMaxXY);
            for (size_t i = 0; i < kMaxXY; i++)
            {
                cell_ptrs[i] = std::make_shared<Cell>(pimpl_->board[y][i]);
            }
        }
        else
        {
            is_fail = true;
            err_message = kErrorStringXYOutOfRange;
        }
        return !is_fail;
    }

    bool Board::GetVerticalLine(uint16_t x, std::vector<std::shared_ptr<Cell>>& cell_ptrs, std::string& err_message) const
    {
        bool is_fail = false;
        if (x < kMaxXY)
        {
            cell_ptrs.resize(kMaxXY);
            for (size_t i = 0; i < kMaxXY; i++)
            {
                cell_ptrs[i] = std::make_shared<Cell>(pimpl_->board[i][x]);
            }
        }
        else
        {
            is_fail = true;
            err_message = kErrorStringXYOutOfRange;
        }
        return !is_fail;
    }

    bool Board::GetSquare(uint16_t x, uint16_t y, std::vector<std::shared_ptr<Cell>>& cell_ptrs, std::string& err_message) const
    {
        bool is_fail = false;

        if (x < kMaxXY && y < kMaxXY)
        {
            cell_ptrs.resize(kMaxXY);

            // Get the subsquare position.
            uint16_t subsquare_x = x;
            uint16_t subsquare_y = y;
            while (subsquare_x % kSudokuSubSquareSize != 0) --subsquare_x;
            while (subsquare_y % kSudokuSubSquareSize != 0) --subsquare_y;

            // Iterate over the board subsquare and get the pointers.
            for (size_t i = 0; i < kSudokuSubSquareSize; i++)
            {
                for (size_t j = 0; j < kSudokuSubSquareSize; j++)
                {
                    cell_ptrs[kSudokuSubSquareSize * i + j] = std::make_shared<Cell>(pimpl_->board[subsquare_y + i][subsquare_x + j]);
                }
            }
        }
        else
        {
            is_fail = true;
            err_message = kErrorStringXYOutOfRange;
        }

        return !is_fail;
    }

    bool Board::GetValue(uint16_t x, uint16_t y, uint16_t& value, std::string& err_message) const
    {
        bool is_fail = false;

        if (x < kMaxXY && y < kMaxXY)
        {
            value = pimpl_->board[x][y].value;
        }
        else
        {
            is_fail = true;
            err_message = kErrorStringXYOutOfRange;
        }

        return !is_fail;
    }

    bool Board::Load(const std::string& file_path, std::string& err_message)
    {
        bool is_fail = false;

        std::ifstream file(file_path);
        if (file.is_open())
        {
            std::string line;
            uint16_t row = 0;
            while (!is_fail && std::getline(file, line))
            {
                if (row < 9)
                {
                    if (line.size() == 9)
                    {
                        for (size_t i = 0; !is_fail && i < kMaxXY; i++)
                        {
                            char c = line[i];
                            if (c == '-')
                            {
                                pimpl_->board[row][i].value = 0;
                            }
                            else if (c >= '1' && c <= '9')
                            {
                                pimpl_->board[row][i].value = c - '0';
                            }
                            else
                            {
                                is_fail = true;
                                err_message = kErrorIncorrectFileFormatChar;
                            }
                        }
                    }
                    else
                    {
                        is_fail = true;
                        err_message = kErrorIncorrectFileFormatCols;
                    }
                }
                else
                {
                    is_fail = true;
                    err_message = kErrorIncorrectFileFormatRows;
                }

                ++row;
            }

            if (!is_fail && row < kMaxXY)
            {
                is_fail = true;
                err_message = kErrorIncorrectFileFormatRows;
            }
        }
        else
        {
            is_fail = true;
            err_message = kErrorStringNoFile;
        }

        // Close the file
        file.close();

        return !is_fail;
    }

    bool Board::SetValue(uint16_t x, uint16_t y, uint16_t value, std::string& err_message)
    {
        bool is_fail = false;

        if (x < kMaxXY && y < kMaxXY)
        {
            if (value >= kMinValue && value <=kMaxValue)
            {
                pimpl_->board[x][y].value = value;
            }
            else
            {
                is_fail = true;
                err_message = kErrorStringValueOutOfRange;
            }
        }
        else
        {
            is_fail = true;
            err_message = kErrorStringXYOutOfRange;
        }

        return !is_fail;
    }

    Board::~Board()
    {
        if (pimpl_ != nullptr)
        {
            delete pimpl_;
        }
    }
}