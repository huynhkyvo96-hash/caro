#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define MAX_SIZE 25
// Maximum board size

// Initialize the board (fill with '.')
void initializeBoard(char board[][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = '.';
        }
    }
}

// Print the board
void printBoard(char board[][MAX_SIZE], int size) {
    printf("\n   ");
    for (int i = 0; i < size; i++)
        printf("%3d", i+1);
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%2d ", i+1);
        for (int j = 0; j < size; j++) {
            printf("%3c", board[i][j]);
        }
        printf("\n");
    }
}

int runboardgame() {
    int size;
    while (1) {
        if (scanf("%d", &size) != 1) {
            printf("Error: You must enter an integer!\n");
            while (getchar() != '\n');
            continue;
        }
        if (size <= 0 || size > MAX_SIZE) {
            printf("Invalid size! (1-%d)\n", MAX_SIZE);
            continue;
        }
        break;
    }
    printf("Valid board size: %d x %d\n", size, size);
    return size;
}

// ---------------- PART 2: PLACE X / O ----------------

void makeMove(char board[][MAX_SIZE], int size, char player)
{
    int row, col;

    while (1)
    {
        printf("Player %c, enter coordinates (row column): ", player);
        int kt = scanf("%d %d", &row, &col);
        if (kt != 2)
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid input. Please enter 2 numbers.\n");
            continue;
        }

        if (row < 1 || row > size || col < 1 || col > size) {
            printf("Invalid coordinates! Please enter values (1-%d).\n", size);
            continue;
        }

        if (board[row - 1][col - 1] != '.') {
            printf("This cell is already taken! Choose another one.\n");
            continue;
        }

        board[row - 1][col - 1] = player;
        break;
    }
}

int checkWin(char board[][MAX_SIZE], int size, char player) {
    int i, j, k, count;

    for (i = 0; i < size; i++) {
        for (j = 0; j <= size - 5; j++) {
            count = 0;
            for (k = 0; k < 5; k++) {
                if (board[i][j + k] == player) count++;
            }
            if (count == 5) return 1;
        }
    }

    for (i = 0; i <= size - 5; i++) {
        for (j = 0; j < size; j++) {
            count = 0;
            for (k = 0; k < 5; k++) {
                if (board[i + k][j] == player) count++;
            }
            if (count == 5) return 1;
        }
    }

    for (i = 0; i <= size - 5; i++) {
        for (j = 0; j <= size - 5; j++) {
            count = 0;
            for (k = 0; k < 5; k++) {
                if (board[i + k][j + k] == player) count++;
            }
            if (count == 5) return 1;
        }
    }

    for (i = 4; i < size; i++) {
        for (j = 0; j <= size - 5; j++) {
            count = 0;
            for (k = 0; k < 5; k++) {
                if (board[i - k][j + k] == player) count++;
            }
            if (count == 5) return 1;
        }
    }

    return 0;
}

int checkTie(char board[][MAX_SIZE], int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (board[i][j] == '.') return 0;
        }
    }
    return 1;
}

// ---------------- PART 4: SAVE & LOAD ----------------

void saveGame(char board[][MAX_SIZE], int size, char currentPlayer, char namex[], char nameo[]) {
    FILE *f = fopen("save.txt", "w");
    if (f == NULL) {
        printf("Cannot open file to save game.\n");
        return;
    }

    fprintf(f, "%d %c %s %s\n", size, currentPlayer, namex, nameo);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(f, "%c", board[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Game saved successfully to save.txt!\n");
}

int loadGame(char board[][MAX_SIZE], int *size, char *currentPlayer, char namex[], char nameo[]) {
    FILE *f = fopen("save.txt", "r");
    if (f == NULL) {
        printf("save.txt not found. Start a new game.\n");
        return 0;
    }

    fscanf(f, "%d %c %s %s\n", size, currentPlayer, namex, nameo);

    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            fscanf(f, "%c", &board[i][j]);
        }
        fgetc(f);
    }

    fclose(f);
    printf("Game loaded successfully!\n");
    return 1;
}

// ---------------- PLAY GAME ----------------
void playGame()
{
    int size;
    char board[MAX_SIZE][MAX_SIZE];
    char currentPlayer = 'X';
    char namex[30], nameo[30];

    printf("Enter player X name: ");
    scanf(" %[^\n]", namex);
    do {
        printf("Enter player O name: ");
        scanf(" %[^\n]", nameo);
        if (strcasecmp(namex, nameo) == 0) {
            printf("Names are the same. Please enter a different name!\n");
        }
    } while (strcasecmp(namex, nameo) == 0);

    printf("Enter board size (1-%d): ", MAX_SIZE);
    size = runboardgame();
    initializeBoard(board, size);
    printBoard(board, size);

    while (1) {
        makeMove(board, size, currentPlayer);
        printf("\033[H\033[J");
        printBoard(board, size);

        if (checkWin(board, size, currentPlayer)) {
            printf("Player %c wins!\n", currentPlayer);
            if (currentPlayer =='X') {
                SaveScores(namex,1,0,0);
                SaveScores(nameo,0,1,0);
            } else {
                SaveScores(nameo,1,0,0);
                SaveScores(namex,0,1,0);
            }
            break;
        }

        if (checkTie(board, size)) {
            printf("It's a tie!\n");
            SaveScores(namex,0,0,1);
            SaveScores(nameo,0,0,1);
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        char ans;
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("Press Enter to continue, 's' to save game, 'e' to exit: ");
        ans = getchar();

        if (ans == 's' || ans == 'S') {
            saveGame(board, size, currentPlayer, namex, nameo);
            printf("Game saved!\n");
            while ((c = getchar()) != '\n' && c != EOF);
        } else if (ans == 'e' || ans == 'E') {
           printf("Exiting game early!\n");
           return;
        }
    }
}

// Continue saved game
void continueGame() {
    int size;
    char board[MAX_SIZE][MAX_SIZE];
    char currentPlayer;
    char namex[30], nameo[30];

    if (!loadGame(board, &size, &currentPlayer, namex, nameo))
        return;

    printBoard(board, size);

    while (1) {
        makeMove(board, size, currentPlayer);
        printf("\033[H\033[J");
        printBoard(board, size);

        if (checkWin(board, size, currentPlayer)) {
            printf("Player %c wins!\n", currentPlayer);
            if (currentPlayer == 'X') {
                SaveScores(namex, 1, 0, 0);
                SaveScores(nameo, 0, 1, 0);
            } else {
                SaveScores(nameo, 1, 0, 0);
                SaveScores(namex, 0, 1, 0);
            }
            break;
        }

        if (checkTie(board, size)) {
            printf("It's a tie!\n");
            SaveScores(namex, 0, 0, 1);
            SaveScores(nameo, 0, 0, 1);
            break;
        }

        char ans;
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("Press Enter to continue, 's' to save game, 'e' to exit: ");
        ans = getchar();

        if (ans == 's' || ans == 'S') {
            saveGame(board, size, currentPlayer, namex, nameo);
            printf("Game saved!\n");
            while ((c = getchar()) != '\n' && c != EOF);
        } else if (ans == 'e' || ans == 'E') {
           printf("Exiting game early!\n");
           return;
        }
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

// ================== SCORES & INSTRUCTIONS =====================
typedef struct{
    char name[30];
    int win,lose,tie;
} Player;

void SaveScores(char playerName[], int win, int lose, int tie) {
    FILE *f = fopen("scores.txt", "r");
    Player players[100];
    int count = 0, found = 0;

    if (f == NULL) {
        f = fopen("scores.txt", "w");
        fprintf(f, "%s %d %d %d\n", playerName, win, lose, tie);
        fclose(f);
        printf("New file created. Scores saved for %s!\n", playerName);
        return;
    }

    while (fscanf(f, "%s %d %d %d", players[count].name,
                  &players[count].win, &players[count].lose, &players[count].tie) == 4)
        count++;
    fclose(f);

    for (int i = 0; i < count; i++) {
        if (strcasecmp(players[i].name, playerName) == 0) {
            players[i].win  += win;
            players[i].lose += lose;
            players[i].tie  += tie;
            found = 1;
            break;
        }
    }

    if (!found) {
        strcpy(players[count].name, playerName);
        players[count].win  = win;
        players[count].lose = lose;
        players[count].tie  = tie;
        count++;
    }

    f = fopen("scores.txt", "w");
    for (int i = 0; i < count; i++)
        fprintf(f, "%s %d %d %d\n", players[i].name,
                players[i].win, players[i].lose, players[i].tie);
    fclose(f);

    printf("Scores updated for %s!\n", playerName);
}

void ShowTopPlayers()
{
    FILE *f = fopen("scores.txt","r");
    if (f==NULL)
    {
        printf("No player data available!\n");
        return;
    }
    Player list[100];
    int count=0;

    while(fscanf(f,"%s %d %d %d",list[count].name,&list[count].win,&list[count].lose,&list[count].tie)==4)
        count++;
    fclose(f);

    for (int i=0; i<count-1; i++)
        for(int j=i+1; j<count; j++)
            if(list[i].win < list[j].win)
            {
              Player tmp=list[i];
              list[i]=list[j];
              list[j]=tmp;
            }
     printf("\n===== TOP 10 PLAYERS =====\n");
     printf("%-15s %-5s %-5s %-5s\n","Name","Win","Lose","Tie");

     for (int i = 0; i<count && i<10; i++)
        printf("%-15s %-5d %-5d %-5d\n",list[i].name,list[i].win,list[i].lose,list[i].tie);
}

void ShowInstructions()
{
    printf("\n===== HOW TO PLAY CARO =====\n");
    printf("1. Each player enters coordinates (row column), e.g., 3 5\n");
    printf("2. Player X goes first, O goes second.\n");
    printf("3. Win by placing 5 consecutive pieces (horizontal, vertical, or diagonal).\n");
    printf("4. You can save ('s') or load ('e') a game.\n");
    printf("5. Win/Lose/Tie scores are saved in scores.txt.\n");
    printf("===================================\n");
}

int main(){
    int option;
    do
    {
     printf("\n===== MAIN MENU =====\n");
     printf("1. Start new game\n");
     printf("2. Load saved game\n");
     printf("3. Show top 10 players\n");
     printf("4. Show instructions\n");
     printf("0. Exit\n");
     printf("Choice: ");
     if (scanf("%d", &option) != 1)
     {
         printf("Invalid input! Please enter a number.\n");
         while (getchar() != '\n');
         continue;
     }

     switch (option) {
            case 1:
                playGame();
                break;
            case 2:
                continueGame();
                break;
            case 3:
                ShowTopPlayers();
                break;
            case 4:
                ShowInstructions();
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice, please try again!\n");
        }
    } while (option != 0);

    return 0;
}
