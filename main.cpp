#include "board.hpp"
#include "io.hpp"

class Game
{
    Board board;
    IO io;
public:
    void Run() {
        Block block { possibleShape[std::rand() % 3],  defaultPosition } ;
        board.addBlock(block);
        board.drawBoard();
        char input = 0;
        while(true) {
            input = io.lastInput();
            if(input == 'q') 
                return;
            block = board.handleInput(input, block);
            board.removeFullLines();
            if(!board.tryNextStep(block))
                break;
            board.drawBoard();
        }
    }
};

int main(int argc, char ** argv) 
{
    Game().Run();
}
