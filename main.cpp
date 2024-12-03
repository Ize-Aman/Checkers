
#include <iostream>
#include <string>
#include <fstream>
#include <raylib.h>

const int BOARD_WIDTH = 1000;
const int BOARD_HEIGHT = 800;
const int CELL_SIZE = 100;
const int CELL_CENTER_POS = CELL_SIZE / 2;
const int Piece_SIZE = 40;

enum cellType{
    emptyCell,
    player1Piece,
    player2Piece,
    player1KingPiece,
    player2KingPiece,
    voidCell
};

struct Cell{
    int row;
    int col;
    int cellType;
    int cellSize = CELL_SIZE;
};

struct Piece{
    Color PieceColor;
    int PieceSize = Piece_SIZE;
    int PieceOrientation;
};

struct Board{
    int boardWidth;
    int boardHeight;
    Color boardColor;
};

struct Game{
    Board board;
    Cell cellInfo[8][8];
    std::string playerOneName;
    std::string playerTwoName;
    int P1Score = 0;
    int P2Score = 0;
    const char* filename = "checkers";
};

enum turn{
    playerone,
    playertwo   

};

/// @brief initializes the game
/// @param game the game to initialize
void initGame(Game& game);

/// @brief initializes the board
/// @param board the board to initialize
void initBoard(Board& board);

/// @brief draws the board based on board properties
/// @param board the board to draw
void drawBoard(Board board);

/// @brief gets the cell type based on the row and col on initialization
/// @param row,col the row and col to get the cell type
int initCellType(int row, int col);

/// @brief draw the cells based on their type
/// @param cell,board the cells to draw and the board in which the cells will be drawn
void drawCellsOnBoard(Cell cell[8][8]);

/// @brief getCellColor based on the cell type
/// @param cell the cell to get the color
Color getCellColor(Cell cell);

/// @brief draw Piece based on the cell type
/// @param cell the cell to draw the Piece on
void drawPiece(Cell cell[8][8]);

/// @brief returns qokri color based on cell type.
/// @param cell the cell to get the cell type from and determine the Piece color.
Color getPieceColor(Cell cell);

/// @brief updates the game cellInfo array based on user click
/// @param cells the cell infos of the current game.
void updateGame(Cell cells[8][8],turn &turns, Game& game);

/// @brief returns the cell the user clicked on
/// @param x,y the x and y coordinates of the click
Cell getCell(int x, int y);

/// @brief moves the Piece from the selected cell to the target cell
/// @param selectedCell,targetCell,cells the selected cell, target cell and the game cell info array
void movePiece(Cell selectedCell, Cell targetCell, Cell cells[8][8],bool isEvenRow ,bool isEvenCol,turn& turns);

/// @brief handles the Piece actions
/// @param selectedCell,targetCell,cells the selected cell, target cell and the game cell info array
void handlePieceMove(Cell selectedCell, Cell targetCell, Cell cells[8][8],bool isEvenRow ,bool isEvenCol,turn &turns, Game& game);

/// @brief checks if a move is a legal checkers move 
/// @param selectedCell,targetCell,cells the selected cell, target cell and the game cell info array
bool isMoveValid(Cell selectedCell, Cell targetCell, Cell cells[8][8],bool isEvenRow ,bool isEvenCol,turn &turns, Game& game);

/// @brief moves the Piece
/// @param selectedCell,targetCell,cells,middlerow,middlecol,isEvenRow,isEvenCol,turns 
void MovePiece(Cell selectedCell, Cell targetCell, Cell cells[8][8],int middlerow,int middlecol,bool isEvenRow ,bool isEvenCol,turn &turns);

/// @brief removes the cell from the game
/// @param cell,cells the cell to remove and the game cell info array
void removePiece(Cell cell, Cell cells[8][8]);

/// @brief handles the capture 
/// @param selectedCell,targetCell,cells,isEvenRow,isEvenCol,turns 
void capture(Cell selectedCell, Cell targetCell, Cell cells[8][8],bool isEvenRow ,bool isEvenCol,turn &turns, Game& game);

/// @brief changes the player turns
/// @param turns 
void turnning(turn &turns);

/// @brief moves the king
/// @param selectedCell,targetCell,cells 
void Kingmove(Cell selectedCell, Cell targetCell, Cell cells[8][8]);

/// @brief checks for possible column and row moves for king (diagonal moves only)
/// @param selectedCell,targetCell  
bool colchecker(Cell selectedCell, Cell targetCell);

/// @brief processes the move and divides it accordingly
/// @param selectedCell,targetCell,cells,turns,game 
void processMove(Cell selectedCell, Cell targetCell, Cell cells[8][8],turn &turns, Game& game);

/// @brief checks if it is a regular move
/// @param selectedCell,targetCell,cells,turns 
bool isRegularMove(Cell selectedCell, Cell targetCell, Cell cells[8][8], turn &turns);

/// @brief checks if the move is a promotion move
/// @param selectedCell,targetCell,cells 
bool isPromotionMove(Cell selectedCell, Cell targetCell, Cell cells[8][8]);

/// @brief checks if the move is a king move
/// @param selectedCell,targetCell,cells,turns 
bool isKingMove(Cell selectedCell, Cell targetCell, Cell cells[8][8], turn &turns);

/// @brief handles the promotion
/// @param selectedCell,targetCell,cells,turns 
void handlePromotion(Cell selectedCell, Cell targetCell, Cell cells[8][8], turn &turns);

/// @brief display the main menu and return the player's choice
void displayMenu(Game& game, const char* filename);

/// @brief save the current game state to a file 
/// @param game the game to save
void SaveGame(const Game& game, const char* filename);

/// @brief load a saved game from a file 
/// @param game the game to load
void LoadGame(Game& game, const char* filename);
/// @brief displays the score
/// @param game 

/// @brief check the score
/// @param game 
bool checkGameEnd(Game &game);
void displayScores(Game& game);
int main(){
    turn turns;
    Game game;
    SetTargetFPS(60);
    displayMenu(game, game.filename);
    newGame:
    initGame(game);
    initBoard(game.board);
    InitWindow(game.board.boardWidth, game.board.boardHeight, "Checkers");
    while (!WindowShouldClose()){ 
        BeginDrawing();
            ClearBackground(RAYWHITE);
            drawBoard(game.board); 
            drawCellsOnBoard(game.cellInfo);
            drawPiece(game.cellInfo);
            updateGame(game.cellInfo, turns, game);
            displayScores(game);
            if (checkGameEnd(game)) 
            {
                DrawText("Game Over", 150, 150, 30, RED);
            }
            DrawText("Help", 910, 1, 37, BLACK);
            DrawText("S - Save game", 817, 50, 20, BLACK);
            DrawText("L - Load game", 817, 75, 20, BLACK);
            DrawText("N - New game", 817, 100, 20, BLACK);
            DrawText("Esc - Exit Game", 817, 125, 20, BLACK);
            DrawText("Scores", 870, 210, 35, BLACK);

            if (IsKeyPressed(KEY_S)) {
                SaveGame(game, "savegame.dat");
            }
            if (IsKeyPressed(KEY_L)) {
                LoadGame(game, "savegame.dat");
            }
            if(IsKeyPressed(KEY_N)){
                EndDrawing();
                CloseWindow();
                goto newGame;
            }
            
        EndDrawing();
    }

    CloseWindow();        

    return 0;
}

void initGame(Game& game){
    game.playerOneName = "Player 1";
    game.playerTwoName = "Player 2";

    for(int row = 0; row < 8; row++){
        for(int col =0; col <8; col++){
            game.cellInfo[row][col].row = row;
            game.cellInfo[row][col].col = col;
            game.cellInfo[row][col].cellType = initCellType(row, col);
        }
    }
}

void initBoard(Board& board){
    board.boardHeight = BOARD_HEIGHT;
    board.boardWidth = BOARD_WIDTH;
    board.boardColor = RAYWHITE;
}

void drawBoard(Board board){
    DrawRectangle(0, 0, board.boardWidth, board.boardHeight, board.boardColor);
}

int initCellType(int row, int col){
    bool isEvenRow = row % 2 == 0;
    bool isEvenCol = col % 2 == 0;
    if((isEvenRow && !isEvenCol) || (!isEvenRow && isEvenCol)){
        if(row < 3){
            return player1Piece;
        }
        if(row > 4){
            return player2Piece;
        }
    }
   if((isEvenRow && isEvenCol))
    {
         return voidCell;
    }
    else
    return emptyCell;
}

void drawCellsOnBoard(Cell cell[8][8]){
    for(int row = 0; row < 8; row++)
        for(int col = 0; col < 8; col++){
            Cell currentCell = cell[row][col];
            Color cellColor = getCellColor(cell[row][col]);
            DrawRectangle(col * currentCell.cellSize, row * currentCell.cellSize, currentCell.cellSize, currentCell.cellSize, cellColor);
        }
}

Color getCellColor(Cell cell){
    bool isEvenRow = cell.row % 2 == 0;
    bool isEvenCol = cell.col % 2 == 0;
    if((isEvenRow && !isEvenCol) || (!isEvenRow && isEvenCol)){
        return {181, 136, 99, 255}; //dark colour
    }
    return {240, 217, 181, 255}; //light colour
}

void drawPiece(Cell cells[8][8]){
    Piece Piece;
    float cellCenterPos = cells[0][0].cellSize / 2;
    for(int row = 0; row < 8; row++)
    {
        int rowPos = row * cells[0][0].cellSize;
        for(int col = 0; col < 8; col++)
        {
            int colPos = col * cells[0][0].cellSize;
            Cell currentCell = cells[row][col];
            if(currentCell.cellType != voidCell && currentCell.cellType != emptyCell)
            {
                Color PieceColor = getPieceColor(currentCell);
                DrawCircle(cellCenterPos + colPos, cellCenterPos + rowPos, Piece.PieceSize,PieceColor);
            }
        }
    }
}

Color getPieceColor(Cell cell){
    switch(cell.cellType)
    {
        case player1Piece:
            return WHITE;
        case player1KingPiece:
            return DARKBLUE;
        case player2Piece:
            return BLACK;
        case player2KingPiece:
            return PINK;
            default:
            return WHITE;
        //other cell type.
        //default:
    }
}

void updateGame(Cell cells[8][8],turn &turns, Game& game){
    Cell static selectedCell;
    Cell static targetCell;
   
    int selectedXPos;
    int selectedYPos;
   
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        selectedXPos = GetMouseX();
        selectedYPos = GetMouseY();
        selectedCell = getCell(selectedXPos,selectedYPos);
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
        selectedXPos = GetMouseX();
        selectedYPos = GetMouseY();
        targetCell = getCell(selectedXPos,selectedYPos);
        processMove(selectedCell,targetCell, cells, turns, game);
        SaveGame(game, "savegame.dat");
    }        
}

void processMove(Cell selectedCell, Cell targetCell, Cell cells[8][8], turn &turns, Game &game) {
    bool isEvenRow = targetCell.row % 2 == 0;
    bool isEvenCol = targetCell.col % 2 == 0;

    if (isRegularMove(selectedCell, targetCell, cells, turns)) {
        handlePieceMove(selectedCell, targetCell, cells, isEvenRow, isEvenCol, turns, game);
        turnning(turns);
    } else if (isPromotionMove(selectedCell, targetCell, cells)) {
        handlePieceMove(selectedCell, targetCell, cells, isEvenRow, isEvenCol, turns, game);
    } else if (isKingMove(selectedCell, targetCell, cells, turns)) {
        handlePieceMove(selectedCell, targetCell, cells, isEvenRow, isEvenCol, turns, game);
        turnning(turns);
    }
}

bool isRegularMove(Cell selectedCell, Cell targetCell, Cell cells[8][8], turn &turns) {
    return ((cells[selectedCell.row][selectedCell.col].cellType == player1Piece && targetCell.row <= 6) ||
            (cells[selectedCell.row][selectedCell.col].cellType == player2Piece && targetCell.row >= 1)) &&
           ((turns == playerone && cells[selectedCell.row][selectedCell.col].cellType == player1Piece && selectedCell.row < targetCell.row && cells[targetCell.row][targetCell.col].cellType == emptyCell) ||
            (turns == playertwo && cells[selectedCell.row][selectedCell.col].cellType == player2Piece && selectedCell.row > targetCell.row && cells[targetCell.row][targetCell.col].cellType == emptyCell));
}

bool isPromotionMove(Cell selectedCell, Cell targetCell, Cell cells[8][8]) {
    return ((cells[selectedCell.row][selectedCell.col].cellType == player1Piece && targetCell.row == 7) ||
            (cells[selectedCell.row][selectedCell.col].cellType == player2Piece && targetCell.row == 0)) &&
           cells[targetCell.row][targetCell.col].cellType == emptyCell;
}

bool isKingMove(Cell selectedCell, Cell targetCell, Cell cells[8][8], turn &turns) {
    return (cells[selectedCell.row][selectedCell.col].cellType == player1KingPiece && turns == playerone) ||
           (cells[selectedCell.row][selectedCell.col].cellType == player2KingPiece && turns == playertwo);
}

Cell getCell(int x, int y){
    Cell c;
    c.row = y/c.cellSize;
    c.col = x/c.cellSize;
    return c;
}

void handlePieceMove(Cell selectedCell, Cell targetCell, Cell cells[8][8],bool isEvenRow ,bool isEvenCol,turn &turns, Game& game){
    if(isMoveValid(selectedCell,targetCell,cells,isEvenRow ,isEvenCol,turns, game)){
        movePiece(selectedCell,targetCell,cells,isEvenRow ,isEvenCol,turns);
    }
}

void movePiece(Cell selectedCell, Cell targetCell, Cell cells[8][8],bool isEvenRow ,bool isEvenCol,turn &turns){
    cells[targetCell.row][targetCell.col].cellType = cells[selectedCell.row][selectedCell.col].cellType;
    handlePromotion(selectedCell, targetCell, cells, turns);
    removePiece(selectedCell, cells);
}

void handlePromotion(Cell selectedCell, Cell targetCell, Cell cells[8][8], turn &turns){
    if (cells[selectedCell.row][selectedCell.col].cellType == player1Piece && targetCell.row == 7) {
        cells[targetCell.row][targetCell.col].cellType = player1KingPiece;
        turnning(turns);
    }
    if (cells[selectedCell.row][selectedCell.col].cellType == player2Piece && targetCell.row == 0) {
        cells[targetCell.row][targetCell.col].cellType = player2KingPiece;
        turnning(turns);
    }
}

void removePiece(Cell cell, Cell cells[8][8]){
    cells[cell.row][cell.col].cellType = emptyCell;
}

bool isMoveValid(Cell selectedCell, Cell targetCell, Cell cells[8][8],bool isEvenRow ,bool isEvenCol,turn &turns, Game& game)
{

    // Check if the selected cell has a Piece
    if (cells[selectedCell.row][selectedCell.col].cellType == emptyCell)
        return false;
    // Check if the target cell already has a Piece
   if((cells[selectedCell.row][selectedCell.col].cellType == player1Piece)||(cells[selectedCell.row][selectedCell.col].cellType == player2Piece))
   {
        if(colchecker(selectedCell,targetCell))
        {
            if(cells[selectedCell.row][selectedCell.col].cellType == player1Piece) 
           {
    int middleRowP = ( (targetCell.row +2)+ targetCell.row) / 2;
    int middleColP = ((targetCell.col +2)+ targetCell.col) / 2;
     int middleRowN = ( (targetCell.row +2)+ targetCell.row) / 2;
    int middleColN = ((targetCell.col -2)+ targetCell.col) / 2;
    
                       if(targetCell.row == selectedCell.row + 1)
            {
                if(targetCell.col == selectedCell.col + 1 || targetCell.col == selectedCell.col - 1)
                    return true;
                else return false;
            }

            if (targetCell.row == selectedCell.row + 2 && (targetCell.col == selectedCell.col + 2 || targetCell.col == selectedCell.col - 2)){
                if (((cells[targetCell.row + 2][targetCell.col + 2].cellType == emptyCell) || 
    (cells[targetCell.row + 2][targetCell.col - 2].cellType == emptyCell)) &&
  (  (cells[middleRowP][middleColP].cellType == player2Piece) || 
    (cells[middleRowN][middleColN].cellType == player2Piece) )) {
                  std::cout<<"i'm inline 400\n";
                    capture(selectedCell, targetCell, cells, isEvenRow, isEvenCol, turns, game);
                    turnning(turns);
                    std::cout<<turns;
                    return false;
                }
                else
                capture(selectedCell,targetCell,cells,isEvenRow ,isEvenCol,turns, game);
                std::cout<<"i'm inline 407\n";
                return false;
            }
            }
            if(cells[selectedCell.row][selectedCell.col].cellType == player2Piece)
           { 
    int middleRowP = ( (targetCell.row -2)+ targetCell.row) / 2;
    int middleColP = ((targetCell.col +2)+ targetCell.col) / 2;
     int middleRowN = ( (targetCell.row -2)+ targetCell.row) / 2;
    int middleColN = ((targetCell.col -2)+ targetCell.col) / 2;
    
                if(targetCell.row == selectedCell.row - 1)
            {
                if(targetCell.col == selectedCell.col + 1 || targetCell.col == selectedCell.col - 1)
                    return true;
                else return false;
            }
            if (targetCell.row == selectedCell.row - 2 && (targetCell.col == selectedCell.col + 2 || targetCell.col == selectedCell.col - 2)){
                if (((cells[targetCell.row - 2][targetCell.col + 2].cellType == emptyCell) || 
    (cells[targetCell.row - 2][targetCell.col - 2].cellType == emptyCell)) &&
   ( (cells[middleRowP][middleColP].cellType == player1Piece) || 
    (cells[middleRowN][middleColN].cellType == player1Piece))) {
                    std::cout<<"i'm inline 400\n";
                    capture(selectedCell, targetCell, cells, isEvenRow, isEvenCol, turns, game);
                    turnning(turns);
                    std::cout<<turns;
                    return false;
                }
                else
                    capture(selectedCell,targetCell,cells,isEvenRow ,isEvenCol,turns, game);
                std::cout<<"i'm inline 407\n";
                return false;
            }
            }
        
        }
                if (selectedCell.row == targetCell.row && selectedCell.col == targetCell.col)
            return false;
    }

    if((cells[selectedCell.row][selectedCell.col].cellType == player1KingPiece) ||(cells[selectedCell.row][selectedCell.col].cellType == player2KingPiece))
    {
        if(cells[targetCell.row][targetCell.col].cellType != emptyCell || (cells[targetCell.row][targetCell.col].cellType == voidCell))
            return false;
        if((isEvenRow && !isEvenCol) || (!isEvenRow && isEvenCol))
        {
            if(colchecker(selectedCell,targetCell))
            {
    int middleRowP = ( (targetCell.row +2)+ targetCell.row) / 2;
    int middleColP = ((targetCell.col +2)+ targetCell.col) / 2;
     int middleRowN = ( (targetCell.row +2)+ targetCell.row) / 2;
    int middleColN = ((targetCell.col -2)+ targetCell.col) / 2;
                        if (targetCell.row == selectedCell.row + 2 && (targetCell.col == selectedCell.col + 2 || targetCell.col == selectedCell.col - 2)){
                            if (((cells[targetCell.row + 2][targetCell.col + 2].cellType == emptyCell) || 
    (cells[targetCell.row + 2][targetCell.col - 2].cellType == emptyCell)) &&
    ((cells[middleRowP][middleColP].cellType != emptyCell) || 
    (cells[middleRowN][middleColN].cellType != emptyCell))) {
                  std::cout<<"i'm inline 400\n";
                    capture(selectedCell, targetCell, cells, isEvenRow, isEvenCol, turns, game);
                    turnning(turns);
                    std::cout<<turns;
                    return false;
                }
                else
                    capture(selectedCell,targetCell,cells,isEvenRow ,isEvenCol,turns, game);
                std::cout<<"i'm inline 407\n";
                return false;
            }
    middleRowP = ( (targetCell.row -2)+ targetCell.row) / 2;
    middleColP = ((targetCell.col +2)+ targetCell.col) / 2;
    middleRowN = ( (targetCell.row -2)+ targetCell.row) / 2;
    middleColN = ((targetCell.col -2)+ targetCell.col) / 2;
    
            if (targetCell.row == selectedCell.row - 2 && (targetCell.col == selectedCell.col + 2 || targetCell.col == selectedCell.col - 2))
            {
                if (((cells[targetCell.row - 2][targetCell.col + 2].cellType == emptyCell) || 
    (cells[targetCell.row - 2][targetCell.col - 2].cellType == emptyCell) )&&
   ( (cells[middleRowP][middleColP].cellType != emptyCell) || 
    (cells[middleRowN][middleColN].cellType != emptyCell))) {
                    capture(selectedCell, targetCell, cells, isEvenRow, isEvenCol, turns, game);
                    turnning(turns);
                    std::cout<<turns;
                    return false;
                }
                else
                    capture(selectedCell,targetCell,cells,isEvenRow ,isEvenCol,turns, game);
                std::cout<<"i'm inline 407\n";
                return false;
            }
            else 
              return true;
            }
        }
    }
    return true;
}
void capture(Cell selectedCell, Cell targetCell, Cell cells[8][8],bool isEvenRow ,bool isEvenCol,turn &turns, Game& game){
    int middleRow = (selectedCell.row + targetCell.row) / 2;
    int middleCol = (selectedCell.col + targetCell.col) / 2;

    // Check if the middle cell contains the opponent's piece
    if (cells[selectedCell.row][selectedCell.col].cellType == player1Piece && (cells[middleRow][middleCol].cellType == player2Piece)){
        // Move the Piece to the target cell
       // movePiece(selectedCell, targetCell, cells,isEvenRow ,isEvenCol,turns);
        // Remove the captured piece
        if(cells[targetCell.row][targetCell.col].row ==cells[7][7].row)
        {
            //std::cout<<"i'm a copy inline 443";
        movePiece(selectedCell, targetCell, cells,isEvenRow ,isEvenCol,turns);
        cells[middleRow][middleCol].cellType = emptyCell;
        game.P1Score++;
        turnning(turns);

        }
        else
        {
            movePiece(selectedCell, targetCell, cells,isEvenRow ,isEvenCol,turns);
            game.P1Score++;
        cells[middleRow][middleCol].cellType = emptyCell;
        }
    } 
    if (cells[selectedCell.row][selectedCell.col].cellType == player2Piece && (cells[middleRow][middleCol].cellType == player1Piece)){
       //promotion and capture
               if(cells[targetCell.row][targetCell.col].row ==cells[0][0].row)
        {
            //std::cout<<"i'm a copy inline 443";
        movePiece(selectedCell, targetCell, cells,isEvenRow ,isEvenCol,turns);
        cells[middleRow][middleCol].cellType = emptyCell;
        game.P2Score++;
        turnning(turns);
        }
        else
        {
            movePiece(selectedCell, targetCell, cells,isEvenRow ,isEvenCol,turns);
            game.P2Score++;
        cells[middleRow][middleCol].cellType = emptyCell;
        }
       
    }
    if (cells[selectedCell.row][selectedCell.col].cellType == player1KingPiece &&
    (cells[middleRow][middleCol].cellType == player2Piece || cells[middleRow][middleCol].cellType == player2KingPiece ||cells[middleRow][middleCol].cellType == emptyCell))
    {
        std::cout<<"i'm a copy inline 443";
        movePiece(selectedCell, targetCell, cells,isEvenRow ,isEvenCol,turns);
        game.P1Score++;
        cells[middleRow][middleCol].cellType = emptyCell;
    }
    if (cells[selectedCell.row][selectedCell.col].cellType == player2KingPiece &&
    (cells[middleRow][middleCol].cellType == player1Piece || cells[middleRow][middleCol].cellType == player1KingPiece||cells[middleRow][middleCol].cellType == emptyCell))
    {
        // Move the Piece to the target cell
        movePiece(selectedCell, targetCell, cells,isEvenRow ,isEvenCol,turns);
        game.P2Score++;
        // Remove the captured piece
        cells[middleRow][middleCol].cellType = emptyCell;
    } 
    
}

void turnning(turn &turns){
    turns = (turns == playerone) ? playertwo : playerone;
}
bool colchecker(Cell selectedCell, Cell targetCell){
    if(targetCell.col == selectedCell.col + 1 || targetCell.col == selectedCell.col - 1){ 
        std::cout<<"hi0";
        return true;
    }
    if(targetCell.col == selectedCell.col + 2 || targetCell.col == selectedCell.col - 2){
        std::cout<<"  hi:2";
        return true;
    }
    if(targetCell.col == selectedCell.col + 3 || targetCell.col == selectedCell.col - 3)
        return true;
    if(targetCell.col == selectedCell.col + 4 || targetCell.col == selectedCell.col - 4)
        return true;
    if(targetCell.col == selectedCell.col + 5 || targetCell.col == selectedCell.col - 5)
        return true;
    if(targetCell.col == selectedCell.col + 6 || targetCell.col == selectedCell.col - 6)
        return true;
    if(targetCell.col == selectedCell.col + 7 || targetCell.col == selectedCell.col - 7)
        return true;
    else
        return false;
}

void displayMenu(Game& game, const char* filename){
    InitWindow(500, 300, "Menu");
    Image image = LoadImage("png/board.png");
    ImageResize(&image, 500, 300);
    Texture2D Texture = LoadTextureFromImage(image);
    UnloadImage(image);
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(Texture, 0, 0, WHITE);
            DrawText("1. New Game", 200, 105, 20, WHITE);
            DrawText("2. Exit", 200, 155, 20, WHITE);

            if(IsKeyPressed(KEY_ONE)){  // New Game
                EndDrawing();
                CloseWindow();
                return;
            }   
            if(IsKeyPressed(KEY_TWO)){  // exit game
                EndDrawing();
                CloseWindow();
                exit(0);
            }   
        EndDrawing();
    }
    CloseWindow();
}

void SaveGame(const Game& game, const char* filename) {
    std::ofstream saveFile(filename, std::ios::binary);
    if (!saveFile.is_open()) {
        std::cout << "Failed to open file for saving!" << std::endl;
        return;
    }

    // Save board dimensions and color
    saveFile.write((char*)&game.board.boardWidth, sizeof(int));
    saveFile.write((char*)&game.board.boardHeight, sizeof(int));
    saveFile.write((char*)&game.board.boardColor, sizeof(Color));

    // Save player names
    size_t playerOneNameSize = game.playerOneName.size();
    size_t playerTwoNameSize = game.playerTwoName.size();
    saveFile.write((char*)&playerOneNameSize, sizeof(size_t));
    saveFile.write(game.playerOneName.c_str(), playerOneNameSize);
    saveFile.write((char*)&playerTwoNameSize, sizeof(size_t));
    saveFile.write(game.playerTwoName.c_str(), playerTwoNameSize);

    // Save the board cells
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            saveFile.write((char*)&game.cellInfo[row][col], sizeof(Cell));
        }
    }

    saveFile.close();
    std::cout << "Game saved successfully!" << std::endl;
}

void LoadGame(Game& game, const char* filename) {
    std::ifstream loadFile(filename, std::ios::binary);
    if (!loadFile.is_open()) {
        std::cout << "Failed to open file for loading!" << std::endl;
        return;
    }

    // Load board dimensions and color
    loadFile.read((char*)&game.board.boardWidth, sizeof(int));
    loadFile.read((char*)&game.board.boardHeight, sizeof(int));
    loadFile.read((char*)&game.board.boardColor, sizeof(Color));

    // Load player names
    size_t playerOneNameSize, playerTwoNameSize;
    loadFile.read((char*)&playerOneNameSize, sizeof(size_t));
    game.playerOneName.resize(playerOneNameSize);
    loadFile.read(&game.playerOneName[0], playerOneNameSize);

    loadFile.read((char*)&playerTwoNameSize, sizeof(size_t));
    game.playerTwoName.resize(playerTwoNameSize);
    loadFile.read(&game.playerTwoName[0], playerTwoNameSize);

    // Load the board cells
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            loadFile.read((char*)&game.cellInfo[row][col], sizeof(Cell));
        }
    }

    loadFile.close();
    std::cout << "Game loaded successfully!" << std::endl;
}
void displayScores(Game& game){
    DrawText(TextFormat("Player 1 Score: %d", game.P1Score), 830, 259, 20, BLACK);
    DrawText(TextFormat("Player 2 Score: %d", game.P2Score), 830, 284, 20, BLACK);
}
bool checkGameEnd(Game& game)
{
    if (game.P1Score == 12 || game.P2Score == 12) 
    {
        return true;
    }
    return false;
    
}