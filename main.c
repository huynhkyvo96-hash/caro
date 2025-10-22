#include <stdio.h>
#include <ctype.h>
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

// ---------------- HÀM PLAYGAME ----------------
//  cập nhật thêm chức năng save và load
void playGame() {
    int size;
    char board[MAX_SIZE][MAX_SIZE];
    printf("Nhap kich thuoc ban co (axa): ");
    scanf("%d", &size);

    while (size <= 0)
    {
        printf("Kich thuoc khong hop le!\n");
        printf("Hay nhap lai kich thuoc: ");
        scanf("%d", &size);
    }
    char currentPlayer = 'X';
    initializeBoard(board, size);
    printBoard(board, size);

    while (1) {
        char nameX[30], nameO[30];
        printf("Nhap ten nguoi choi X: ");
        scanf("%s", nameX);
        printf("Nhap ten nguoi choi O: ");
        scanf("%s", nameO);
        makeMove(board, size, currentPlayer);
        printf("\033[H\033[J");
        printBoard(board, size);

        if (checkWin(board, size, currentPlayer)) {
            printf(" Nguoi choi %c thang\n", currentPlayer);
            break;
        }

        if (checkTie(board, size)) {
            printf(" Hoa roi!\n");
            break;
        }

        //  Hỏi người chơi có muốn lưu game không
        char ans;
        printf("Ban co muon luu game khong (y/n)? ");
        scanf(" %c", &ans);
        if (ans == 'y' || ans == 'Y') {
            saveGame(board, size, currentPlayer);
        }

        // Đổi lượt
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

//==================PHẦN 5: ĐIỂM VÀ HƯỚNG DẪN NGƯỜI CHƠI====================
#include <string.h>

typedef struct{
    char name[30];
    int win,lose,tie;
} Player;

//HÀM LƯU ĐIỂM VÀO FILE THẮNG BAO NHIÊU THUA BAO NHIÊU
void SaveScores(char Player[],int win,int lose,int tie)
{
    FILE *f = fopen("scores.txt","a");// append mode: ghi thêm vào cuối file, đây là chức năng của đọc file trong C.
    if (f==NULL)
    {
        printf("Khong the mo file scores.txt de ghi!\n");
        return;
    }
    fprintf(f, "%s %d %d %d\n",Player,win,lose,tie);
    fclose(f);
    printf("Diem cua %s da duoc luu!\n",Player);
}

//HÀM HIỂN THỊ TOP 10 NGƯỜI CHƠI
void ShowTopPlayers()
{
    FILE *f = fopen("scores.txt","r");
    if (f==NULL)
    {
        printf("Chua co du lieu nguoi choi nao!\n");
        return;
    }
    Player list[100];
    int count=0;

    while(fscanf(f,"%s %d %d %d",list[count].name,&list[count].win,&list[count].lose,&list[count].tie)==4)
        count++;
    fclose(f);

    //Sắp xếp theo số  trận thắng giảm dần
    for (int i=0; i<count-1; i++)
        for(int j=i+1; j<count; j++)
            if(list[i].win < list[j].win)
            {
              Player tmp=list[i];
              list[i]=list[j];
              list[j]=tmp;
            }
     printf("\n=====🏆 TOP 10 NGUOI CHOI 🏆 =====\n");
     printf("%-15s %-5s %-5s %-5s\n","Ten","Thang","Thua","Hoa");

     for (int i = 0; i<count && i<10; i++)
        printf("%-15s %-5d %-5d %-5d\n",list[i].name,list[i].win,list[i].lose,list[i].tie);
}

//HÀM HIỂN THỊ HƯỚNG DẪN
void ShowInstructions()
{
    printf("\n===== HUONG DAN CHOI CARO =====\n");
    printf("1. Moi nguoi choi nhap toa do (dong cot), vi du: 3 5\n");
    printf("2. Nguoi choi X di truoc, O di sau.\n");
    printf("3. Thang khi co 5 quan lien tiep (ngang, doc hoac cheo).\n");
    printf("4. Co the luu game (y) hoac tai lai game cu.\n");
    printf("5. Diem thang/thua/hoa se luu trong file scores.txt.\n");
    printf("===================================\n");
}

int main(){
    int option;
    do
    {
     printf("\n===== MENU CHINH =====\n");
     printf("1. Bat dau game moi\n");
     printf("2. Tai game da luu\n");
     printf("3. Xem top 10 nguoi choi\n");
     printf("4. Xem huong dan choi\n");
     printf("0. Thoat\n");
     printf("Chon: ");
     scanf("%d",&option);

     switch (option) {
            case 1:
                playGame();
                break;
            case 2:
                // tải game cũ (gọi playGame() có load)
                loadGame();
                break;
            case 3:
                ShowTopPlayers();
                break;
            case 4:
                ShowInstructions();
                break;
            case 0:
                printf("Tam biet\n");
                break;
            default:
                printf("Lua chon khong hop le, moi nhap lai!\n");
        }
    } while (option != 0);

    return 0;
}
