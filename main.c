#include <stdio.h>

#define MAX_SIZE 20
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

// ---------------- PHAN 2: DANH QUAN X / O ----------------

// Hàm này giúp người chơi nhập tọa độ và đặt quân lên bàn cờ
void makeMove(char board[][MAX_SIZE], int size, char player)
{
    int row, col;

    while (1) // Lặp cho đến khi nhập hợp lệ
    { 
        printf("Nguoi choi %c, nhap toa do (dong cot): ", player);
        int kt = scanf("%d %d", &row, &col);
        if (kt != 2) //nếu là chữ thì k được.
    {
            // dọn bộ đệm khi nhập sai kiểu
            int c; 
            while ((c = getchar()) != '\n' && c != EOF) {} //dọn dẹp bộ nhớ đệm tới nút enter  
            printf("Nhap khong hop le. Vui long nhap 2 so.\n");
            continue; //quay lại vòng while 
    }


        // Kiểm tra tọa độ có nằm trong giới hạn bàn cờ không
        if (row < 1 || row > size || col < 1 || col > size) {
            printf(" Toa do khong hop le! Vui long nhap lai (1-%d).\n", size);
            continue;
        }

        // 🔸 Kiểm tra ô đã có quân hay chưa
        if (board[row - 1][col - 1] != '.') {
            printf(" O nay da duoc danh roi! Hay chon o khac.\n");
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
//Vòng i duyệt tất cả các hàng.

//Vòng j duyệt tất cả vị trí bắt đầu có thể của đoạn dài 5 trong hàng: vì đoạn 5 ô bắt đầu tại j và kết thúc j+4, nên j chỉ chạy tới size-5.

//Bên trong, vòng k kiểm tra 5 ô liên tiếp board[i][j+k]. Nếu tất cả 5 đều là player, count==5 → trả về thắng.

//Trả về sớm return 1 để tiết kiệm thời gian (không cần kiểm thêm nếu đã thấy thắng).
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
            //Tương tự, nhưng đổi vai trò hàng/cột: i chạy tới size-5 (vì cần đủ 5 ô theo chiều dọc), j chạy 0..size-1.
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
            //Đoạn 5 ô là (i+k, j+k) cho k=0..4. Do đó i và j chỉ cần chạy tới size-5.
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
            //Ở hướng /, vị trí bắt đầu thường ở hàng lớn (vì ta đi lên i-k), nên i bắt đầu từ 4 (đảm bảo i-4 >= 0) và chạy tới size-1. j là cột bắt đầu ngang như trước.
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
//  Hàm điều khiển lượt chơi luân phiên giữa 2 người
/*
void playGame() 
{
    int size;
    char board[MAX_SIZE][MAX_SIZE];//kich thước max của bàn cờ
    printf("Nhap kich thuoc ban co (0<x<20): ");
    scanf("%d", &size);
    if (size > MAX_SIZE || size <= 0) 
    {
        printf("Kich thuoc khong hop le!\n");
        return;
    }
    char currentPlayer = 'X'; // Người chơi bắt đầu là X
    initializeBoard(board, size);
    printBoard(board, size);
    // ️ Vòng lặp chơi (mỗi lượt người chơi nhập 1 tọa độ)
    for (int turn = 0; turn < size * size; turn++)
    {
        makeMove(board, size, currentPlayer); // Gọi hàm đặt quân

        // In lại bàn sau khi người chơi đánh

        printf("\033[H\033[J"); 
        printf("\n   ");
        for (int i = 1; i <= size; i++)
            printf("%3d", i);
        printf("\n");

        for (int i = 0; i < size; i++)
        {
            printf("%2d ", i + 1);
            for (int j = 0; j < size; j++)
                printf("%3c", board[i][j]);
            printf("\n");
        }

        //  Đổi lượt người chơi
        if (currentPlayer == 'X')
            currentPlayer = 'O';
        else
            currentPlayer = 'X';
    }


}
*/
// ---------------- PHẦN 4: LƯU & TẢI LẠI GAME ----------------

// Ghi bàn cờ và lượt chơi hiện tại vào file
void saveGame(char board[][MAX_SIZE], int size, char currentPlayer) {
    FILE *f = fopen("save.txt", "w");
    if (f == NULL) {
        printf(" Không thể mở file để lưu game.\n");
        return;
    }

    fprintf(f, "%d %c\n", size, currentPlayer);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(f, "%c", board[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf(" Game đã được lưu thành công vào file save.txt!\n");
}

// Đọc bàn cờ và lượt chơi từ file
int loadGame(char board[][MAX_SIZE], int *size, char *currentPlayer) {
    FILE *f = fopen("save.txt", "r");
    if (f == NULL) {
        printf(" Không tìm thấy file save.txt. Hãy bắt đầu game mới.\n");
        return 0;
    }

    fscanf(f, "%d %c\n", size, currentPlayer);
    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            fscanf(f, "%c", &board[i][j]);
        }
        fgetc(f);
    }

    fclose(f);
    printf(" Game đã được tải lại thành công!\n");
    return 1;
}

// ---------------- HÀM CHÍNH PLAYGAME ----------------
// thay bằng hàm play game mới vì cập nhật thêm chức năng save và load
void playGame() {
    int size;
    char board[MAX_SIZE][MAX_SIZE];
    char currentPlayer = 'X';
    int choice;

    printf("===== GAME CARO =====\n");
    printf("1. Bắt đầu game mới\n");
    printf("2. Tải lại game đã lưu\n");
    printf("Chọn (1-2): ");
    scanf("%d", &choice);

    if (choice == 2) {
        if (!loadGame(board, &size, &currentPlayer)) {
            printf(" Không thể tải game. Bắt đầu ván mới!\n");
            printf("Nhập kích thước bàn cờ (0 < x < 20): ");
            scanf("%d", &size);
            initializeBoard(board, size);
        }
    } else {
        printf("Nhập kích thước bàn cờ (0 < x < 20): ");
        scanf("%d", &size);
        initializeBoard(board, size);
    }

    printBoard(board, size);

    while (1) {
        makeMove(board, size, currentPlayer);
        printBoard(board, size);

        if (checkWin(board, size, currentPlayer)) {
            printf(" Người chơi %c thắng!\n", currentPlayer);
            break;
        }

        if (checkTie(board, size)) {
            printf(" Hòa rồi!\n");
            break;
        }

        //  Hỏi người chơi có muốn lưu game không
        char ans;
        printf("Bạn có muốn lưu game lại không (y/n)? ");
        scanf(" %c", &ans);
        if (ans == 'y' || ans == 'Y') {
            saveGame(board, size, currentPlayer);
        }

        // Đổi lượt
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}


int main(){
    playGame();
    return 0;
}

