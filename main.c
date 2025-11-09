#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define MAX_SIZE 25
// Kích thước tối đa của bàn cờ

// Hàm khởi tạo bàn cờ (gán ký tự trống '.')
void initializeBoard(char board[][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = '.';
        }
    }
}

// Hàm in bàn cờ ra màn hình
void printBoard(char board[][MAX_SIZE], int size) {
// xuống hàng rùi cách vô một đoạn
    printf("\n   ");
// in theo dòng  (1 2 3 4 ...)
    for (int i = 0; i < size; i++)
        printf("%3d", i+1);
    printf("\n");

    for (int i = 0; i < size; i++) {
        // in theo dạng cột (1 2 3 4 ...)
        printf("%2d ", i+1);
        // in '.' theo dòng và cột
        for (int j = 0; j < size; j++) {
            printf("%3c", board[i][j]);
        }
// xuống dòng in tiếp cột 2: "2 . . . . . . ." nếu quá size thì dừng (i<=size và j<=size)
        printf("\n");
    }
}

int runboardgame() {
    int size;
    while (1) {

        if (scanf("%d", &size) != 1) {
            printf("Error: You must enter an integer!\n");
            while (getchar() != '\n'); // xóa bộ đệm nếu nhập chữ
            continue;
        }
        if (size <= 0 || size > MAX_SIZE) {
            printf("Invalid board size! (1-%d)\n", MAX_SIZE);
            continue;
        }
        break;
    }
    printf("Valid board size: %d x %d\n", size, size);
    return size;
}

// ---------------- PHAN 2: DANH QUAN X / O ----------------

// Hàm này giúp người chơi nhập tọa độ và đặt quân lên bàn cờ
void makeMove(char board[][MAX_SIZE], int size, char player)
{
    int row, col;

    while (1) // Lặp cho đến khi nhập hợp lệ
    {
        printf("Player %c, enter coordinates (row col): ", player);
        int kt = scanf("%d %d", &row, &col);
        if (kt != 2) //nếu là chữ thì k được.
    {
            // dọn bộ đệm khi nhập sai kiểu
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {} //dọn dẹp bộ nhớ đệm tới nút enter
            printf("Invalid input. Please enter 2 numbers.\n");
            continue; //quay lại vòng while
    }


        // Kiểm tra tọa độ có nằm trong giới hạn bàn cờ không
        if (row < 1 || row > size || col < 1 || col > size) {
            printf("Invalid coordinates! Please enter (1-%d).\n", size);
            continue;
        }

        // 🔸 Kiểm tra ô đã có quân hay chưa
        if (board[row - 1][col - 1] != '.') {
            printf("This cell is already taken! Choose another.\n");
            continue;
        }

        //  Nếu hợp lệ → đặt quân vào vị trí
        board[row - 1][col - 1] = player;
        break; // Thoát khỏi vòng lặp
    }
}

// Hàm kiểm tra thắng cho player ('X' hoặc 'O').
// Trả về 1 nếu player có 5 ô liên tiếp theo 1 trong 4 hướng,
// ngược lại trả về 0.
int checkWin(char board[][MAX_SIZE], int size, char player) {
    int i, j, k, count;

    // Kiểm tra hàng ngang
    for (i = 0; i < size; i++) {
        for (j = 0; j <= size - 5; j++) {
            count = 0;
            for (k = 0; k < 5; k++) {
                if (board[i][j + k] == player) count++;
            }
            if (count == 5) return 1;
        }
    }

    // Kiểm tra cột dọc
    for (i = 0; i <= size - 5; i++) {
        for (j = 0; j < size; j++) {
            count = 0;
            for (k = 0; k < 5; k++) {
                if (board[i + k][j] == player) count++;
            }
            if (count == 5) return 1;
        }
    }

    // Kiểm tra đường chéo chính (\)
    for (i = 0; i <= size - 5; i++) {
        for (j = 0; j <= size - 5; j++) {
            count = 0;
            for (k = 0; k < 5; k++) {
                if (board[i + k][j + k] == player) count++;
            }
            if (count == 5) return 1;
        }
    }

    // Kiểm tra đường chéo phụ (/)
    for (i = 4; i < size; i++) {
        for (j = 0; j <= size - 5; j++) {
            count = 0;
            for (k = 0; k < 5; k++) {
                if (board[i - k][j + k] == player) count++;
            }
            if (count == 5) return 1;
        }
    }

    return 0; // Không thắng
}

// Hàm kiểm tra hòa
int checkTie(char board[][MAX_SIZE], int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (board[i][j] == '.') return 0; // còn ô trống, chưa hòa
        }
    }
    return 1; // Hòa
}


// ---------------- PHẦN 4: LƯU & TẢI LẠI GAME (HOÀN CHỈNH) ----------------

// Ghi bàn cờ, lượt chơi và tên người chơi vào file
void saveGame(char board[][MAX_SIZE], int size, char currentPlayer, char namex[], char nameo[]) {
    FILE *f = fopen("save.txt", "w");
    if (f == NULL) {
        printf("Cannot open file to save game.\n");
        return;
    }

    // Lưu size, lượt chơi hiện tại, tên X và O
    fprintf(f, "%d %c %s %s\n", size, currentPlayer, namex, nameo);

    // Lưu trạng thái bàn cờ
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(f, "%c", board[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Game successfully saved to save.txt!\n");
}

// Đọc bàn cờ, lượt chơi và tên người chơi từ file
int loadGame(char board[][MAX_SIZE], int *size, char *currentPlayer, char namex[], char nameo[]) {
    FILE *f = fopen("save.txt", "r");
    if (f == NULL) {
        printf("No save file found. Start a new game.\n");
        return 0;
    }

    fscanf(f, "%d %c %s %s\n", size, currentPlayer, namex, nameo);

    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            fscanf(f, "%c", &board[i][j]);
        }
        fgetc(f); // đọc bỏ ký tự xuống dòng
    }

    fclose(f);
    printf("Game successfully loaded!\n");
    return 1;
}

// Các phần còn lại cũng tương tự, chỉ đổi nội dung printf sang tiếng Anh, giữ nguyên ghi chú
