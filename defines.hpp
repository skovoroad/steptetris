#include <array>

static constexpr size_t BlockHeight = 3;
static constexpr size_t BlockWidth = 3; 
using BlockLine = std::array<bool, BlockWidth>;
using BlockField = std::array<BlockLine, BlockHeight>;
using BlockPosition = std::pair<int, int>;


static constexpr size_t BoardHeight = 25;
static constexpr size_t BoardWidth = 10; 
using BoardLine = std::array<bool, BoardWidth>;
using BoardField = std::array<BoardLine, BoardHeight>;

static constexpr BlockField possibleShape[] {
    BlockField{BlockLine{false,true,false}, BlockLine{false,true,false}, BlockLine{false,true,false}},
    BlockField{BlockLine{true, true,false}, BlockLine{false,true,false}, BlockLine{false,true,false}},
    BlockField{BlockLine{true, false,false}, BlockLine{true,true,false}, BlockLine{false,true,false}}
};

static constexpr BlockPosition defaultPosition = {BoardHeight, BoardWidth/2 - BlockHeight/2};

