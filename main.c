#include <stdio.h>

#define MAX_SIZE 20  // Kích thước tối đa của bàn cờ

// Hàm khởi tạo bàn cờ (gán ký tự trống '.')
void initializeBoard(char board[][MAX_SIZE], int size) {
    for (int i = 0; i <= size; i++) {
        for (int j = 0; j <= size; j++) {
            board[i][j] = '.';
        }
    }
}

// Hàm in bàn cờ ra màn hình
void printBoard(char board[][MAX_SIZE], int size) {
// xuống hàng rùi cách vô một đoạn
    printf("\n   ");
// in theo dòng  (1 2 3 4 ...)
    for (int i = 1; i <= size; i++)
        printf("%2d", i);
    printf("\n");

    for (int i = 1; i <= size; i++) {
        // in theo dạng cột (1 2 3 4 ...)
        printf("%2d ", i);
        // in '.' theo dòng và cột
        for (int j = 0; j <= size; j++) {
            printf(" %c", board[i][j]);
        }
// xuống dòng in tiếp cột 2: "2 . . . . . . ." nếu quá size thì dừng (i<=size và j<=size)
        printf("\n");
    }
}

void runboardgame() {
    int size;
    char board[MAX_SIZE][MAX_SIZE];//kich thước max của bàn cờ

    if (size >= MAX_SIZE || size <= 0) {
        printf("Kich thuoc khong hop le!\n");
        return;
    }

    initializeBoard(board, size);
    printBoard(board, size);
}
// ---------------- PHAN 2: DANH QUAN X / O ----------------

// ⚙️ Hàm này giúp người chơi nhập tọa độ và đặt quân lên bàn cờ
void makeMove(char board[][MAX_SIZE], int size, char player) {
    int row, col;

    while (1) { // Lặp cho đến khi nhập hợp lệ
        printf("Nguoi choi %c, nhap toa do (hang cot): ", player);
        scanf("%d %d", &row, &col);

        // 🔸 Kiểm tra tọa độ có nằm trong giới hạn bàn cờ không
        if (row < 1 || row > size || col < 1 || col > size) {
            printf("❌ Toa do khong hop le! Vui long nhap lai (1-%d).\n", size);
            continue;
        }

        // 🔸 Kiểm tra ô đã có quân hay chưa
        if (board[row - 1][col - 1] != '.') {
            printf("⚠️ O nay da duoc danh roi! Hay chon o khac.\n");
            continue;
        }

        // ✅ Nếu hợp lệ → đặt quân vào vị trí
        board[row - 1][col - 1] = player;
        break; // Thoát khỏi vòng lặp
    }
}

// ⚙️ Hàm điều khiển lượt chơi luân phiên giữa 2 người
void playGame() {
    char board[MAX_SIZE][MAX_SIZE];
    int size;
    printf("Nhap kich thuoc ban co (15, 19, hoac khac): ");
    scanf("%d", &size);
    char currentPlayer = 'X'; // Người chơi bắt đầu là X
    initializeBoard(board, size);
    printBoard(board, size);
    // 🕹️ Vòng lặp chơi (mỗi lượt người chơi nhập 1 tọa độ)
    for (int turn = 0; turn < size * size; turn++) {
        makeMove(board, size, currentPlayer); // Gọi hàm đặt quân

        // In lại bàn sau khi người chơi đánh
        printf("\nBan co hien tai:\n");
        printf("   ");
        for (int i = 1; i <= size; i++)
            printf("%2d", i);
        printf("\n");

        for (int i = 0; i < size; i++) {
            printf("%2d ", i + 1);
            for (int j = 0; j < size; j++)
                printf(" %c", board[i][j]);
            printf("\n");
        }

        // 🔁 Đổi lượt người chơi
        if (currentPlayer == 'X')
            currentPlayer = 'O';
        else
            currentPlayer = 'X';
    }
    for (int i = 0; i < 50; i++)
    {
        printf("\n");
    }


}

int main(){
    playGame();
    return 0;
}


