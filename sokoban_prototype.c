#include "struct.h"

void systemClear()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
bool checkLose(Element grid[HEIGHT][WIDTH], int boxX, int boxY) 
{
   
    if (grid[boxX][boxY] == WALL) 
    {
        return true; 
    }
    return false; 
}

void playerMove(char direction, Element grid[HEIGHT][WIDTH], playerPosition* playerPos)
{
    int x = playerPos->x;
    int y = playerPos->y;

    int newX = x;
    int newY = y;

    switch (direction) 
    {
        case 'w': newX = x - 1; break; 
        case 's': newX = x + 1; break; 
        case 'a': newY = y - 1; break; 
        case 'd': newY = y + 1; break; 
        default:
            printf("Invalid move!\n");
            return;
    }

    
    if (grid[newX][newY] == WALL) 
    {
        printf("You can't move into a wall!\n");
        return;
    }


    if (grid[newX][newY] == BOX)
     {
        int boxNewX = newX + (newX - x); 
        int boxNewY = newY + (newY - y);


    if (checkLose(grid, boxNewX, boxNewY)) 
    {
            printf("You lost! A box cannot be pushed into a wall.\n");
            exit(0);
    }
        
        if (grid[boxNewX][boxNewY] == EMPTY) 
        {
            grid[boxNewX][boxNewY] = BOX; 
            grid[newX][newY] = PLAYER;  

            grid[x][y] = EMPTY;      

            playerPos->x = newX;          
            playerPos->y = newY;

            return;

        } else if (grid[boxNewX][boxNewY] == GOAL)
         {
            grid[boxNewX][boxNewY] = BOX; 
            grid[newX][newY] = PLAYER;  

            grid[x][y] = EMPTY;     

            playerPos->x = newX;          
            playerPos->y = newY;
            return;
        } else {
            printf("You can't push the box!\n");
            return;
        }
    }

    if (grid[newX][newY] == EMPTY || grid[newX][newY] == GOAL) 
    {
        grid[newX][newY] = PLAYER;   
        grid[x][y] = (grid[x][y] == GOAL) ? GOAL : EMPTY; 
        playerPos->x = newX;         
        playerPos->y = newY;
    }
}

bool checkWin(Element grid[HEIGHT][WIDTH]) 
{
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j] == GOAL) {
                return false;
            }
        }
    }
    return true;
}

void init_grid(Element grid[HEIGHT][WIDTH]) 
{
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                grid[i][j] = WALL;
            } else {
                grid[i][j] = EMPTY;
            }
        }
    }
}

void printGrid(Element grid[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

void spawnPlayer(Element grid[HEIGHT][WIDTH], playerPosition* playerPos) 
{
    int x, y;
    do {
        x = rand() % (8) + 1;
        y = rand() % (8) + 1;
    } while (grid[x][y] != EMPTY);

    grid[x][y] = PLAYER;
    playerPos->x = x;
    playerPos->y = y;
}

void spawnBox(Element grid[HEIGHT][WIDTH]) 
{
    int x, y;
    do {
        x = rand() % (8) + 1;
        y = rand() % (8) + 1;
    } while (grid[x][y] != EMPTY);

    grid[x][y] = BOX;
}

void spawnGoal(Element grid[HEIGHT][WIDTH]) 
{
    int x, y;
    do {
        x = rand() % (8) + 1;
        y = rand() % (8) + 1;
    } while (grid[x][y] != EMPTY);

    grid[x][y] = GOAL;
}

int main(int argc, char const *argv[])
{	

	Element grid[HEIGHT][WIDTH];
	init_grid(grid);
	systemClear(grid);
	srand(time(NULL));
	spawnBox(grid);
	spawnGoal(grid);

	playerPosition playerPos;
	
	spawnPlayer(grid, &playerPos);
	printGrid(grid);

    char move;
    while (true) 
    {
        printf("Move (W,A,S,D)\n");
        scanf(" %c", &move);
        
        systemClear(grid);
        playerMove(move, grid, &playerPos);
        printGrid(grid);

        if (checkWin(grid))
        {
            printf("You Won!\n");
            break;
        }
    }
    return 0;
}
