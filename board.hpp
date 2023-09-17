#pragma once
#include <iostream>
#include "defines.hpp"
#include "io.hpp"

struct Block {
    BlockField field {};
    BlockPosition upperLeft {}; 
};

struct Board {
    BoardField field;
    IO io;

    Block handleInput(char input, Block& block);
    bool tryNextStep(Block& block); 
    bool isCorrectMove(const Block& block, const Block newBlock); 
    void removeBlock(const Block& block);
    bool addBlock(const Block& block);
    void removeFullLines();
    void drawBoard() const;
    Block dropBlock(const Block& block);
    Block rotateBlock(const Block& block) const;
    Block lowerBlock(const Block& block) const;
    Block moveBlockLeft(const Block& block) const;
    Block moveBlockRight(const Block& block) const;
    Block newPosition(const Block& block, char input);
};

bool operator!=(const Block& l, const Block& r) {
    return l.field != r.field || l.upperLeft != r.upperLeft;
}

bool Board::isCorrectMove(const Block& block, const Block newBlock) {
    removeBlock(block);
    for(int x = 0; x < BlockWidth; ++x) 
        for(int y = 0; y < BlockHeight; ++y) 
            if(newBlock.field[x][y] == true) {
                if( newBlock.upperLeft.first - y <= 0 ||
                    newBlock.upperLeft.second + x < 0 ||
                    newBlock.upperLeft.second + x > BoardWidth - 1  ||
                    field[newBlock.upperLeft.first - y - 1][newBlock.upperLeft.second + x]){
                  addBlock(block);
                  return false;  
                }
            }
    addBlock(block);
    return true;
}

void Board::removeBlock(const Block& block) {
    for(size_t x = 0; x < BlockWidth; ++x) 
        for(size_t y = 0; y < BlockHeight; ++y) 
            if(block.field[x][y] == true)
                field[block.upperLeft.first - y - 1][block.upperLeft.second + x] = false;
}

bool Board::addBlock(const Block& block) {
    for(size_t x = 0; x < BlockWidth; ++x)
        for(size_t y = 0; y < BlockHeight; ++y) 
            if(block.field[x][y] == true) {
                bool& square = field[block.upperLeft.first - y - 1][block.upperLeft.second + x];
                if(square)
                     return false;
                square = true;
            }
    return true;
}

void Board::removeFullLines()
{
    const auto isFullLine = [](const BoardLine& line)        {
        for(const auto square: line)
            if(!square)
                 return false;
        return true;
    };
    size_t shift = 0;
    for(size_t y = 0; y < BoardHeight; ++y) {
        if(isFullLine(field[y])) {
            ++shift; 
            continue;
        }
        if(shift > 0) 
            field[y - shift] = field[y];
    } 
}

void Board::drawBoard() const {
    io.clearOutput();
    for(size_t y = 0; y < BoardHeight; ++y) {
        std::cout << "|";
        for(size_t x = 0; x < BoardWidth; ++x) 
            std::cout << (field[BoardHeight - y - 1][x] ? "*" : " ");
        std::cout << "|" << std::endl;
        std::cout << "\r" << std::flush;
    }
    for(size_t x = 0; x < BoardWidth + 2; ++x) 
        std::cout << "=" ;
    std::cout << "\r" << std::flush;
}

Block Board::dropBlock(const Block& block) {
    Block newBlock = block;
    while(isCorrectMove(block, newBlock)) 
        --newBlock.upperLeft.first;
    ++newBlock.upperLeft.first;
    return newBlock;
}

Block Board::rotateBlock(const Block& block) const {
    Block newBlock = block;
    for(size_t x = 0; x < BlockWidth; ++x) 
        for(size_t y = 0; y < BlockHeight; ++y) 
            newBlock.field[x][y] = block.field[y][x];
    return newBlock;
}

Block Board::lowerBlock(const Block& block) const {
    return Block{block.field, { block.upperLeft.first - 1, block.upperLeft.second}};
}

Block Board::moveBlockLeft(const Block& block) const {
    return Block{block.field, { block.upperLeft.first, block.upperLeft.second - 1}};
}

Block Board::moveBlockRight(const Block& block) const {
    return Block{block.field, { block.upperLeft.first, block.upperLeft.second + 1}};
}

Block Board::newPosition(const Block& block, char input) {
    switch (input) {
        case 'w': return rotateBlock(block);
        case 'a': return moveBlockLeft(block);
        case 'd': return moveBlockRight(block);
        case 's': return dropBlock(block);
    }
    return block;
}

Block Board::handleInput(char input, Block& block)  {
    auto newBlock = newPosition(block, input);
    if (isCorrectMove(block, newBlock)) {
         removeBlock(block);
         addBlock(newBlock);
         block = newBlock;
    }
    return block;
}

bool Board::tryNextStep(Block& block) 
{
    auto newBlock = lowerBlock(block);
    if (isCorrectMove(block, newBlock) && block != newBlock) {
         removeBlock(block);
         addBlock(newBlock);
         block = newBlock;
         return true;
    }
    else {
         block = { possibleShape[std::rand() % 3],  defaultPosition };
         return addBlock(block);
    }
 }

