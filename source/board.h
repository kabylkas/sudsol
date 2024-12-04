// Copyright (c) 2024.
// Kabylkas Labs. and Texer.AI. All rights reserved.

// C++ libraries.
#include <memory>
#include <vector>

namespace sudsol
{
    // Forward declarations.
    struct Cell;

    class Board
    {
    public:
        Board();
        ~Board();
        bool GetHorizontalLine(uint16_t y, std::vector<std::shared_ptr<Cell>>& cell_ptrs, std::string& err_message) const;
        bool GetVerticalLine(uint16_t x, std::vector<std::shared_ptr<Cell>>& cell_ptrs, std::string& err_message) const;
        bool GetSquare(uint16_t x, uint16_t y, std::vector<std::shared_ptr<Cell>>& cell_ptrs, std::string& err_message) const;
        bool Load(const std::string& file_path, std::string& err_message);
        bool SetValue(uint16_t x, uint16_t y, uint16_t value, std::string& err_message);

        // Sudoku related constants.
        static const uint16_t kMaxXY = 9;

    private:
       struct BoardImpl;
       BoardImpl* pimpl_ = nullptr;
    };
}
