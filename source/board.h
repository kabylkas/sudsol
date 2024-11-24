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

        bool GetHorizontalLine(std::vector<std::shared_ptr<Cell>>& cell_line, std::string& err_message);
        bool GetVerticalLine(std::vector<std::shared_ptr<Cell>>& cell_line, std::string& err_message);
        bool GetSquare(std::vector<std::shared_ptr<Cell>>& cell_square, std::string& err_message);

    private:
       struct BoardImpl;
       BoardImpl* pimpl_ = nullptr;
    };
}
