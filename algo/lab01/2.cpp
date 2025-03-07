#include <iostream>

const int INT_MAX = 1 << 10;
int board[INT_MAX][INT_MAX];
int title = 0;

void cover (int tr, int tc, int dr, int dc, int size) {
    if (size == 1) {
        return;
    }

    int t = ++title;
    int s = size / 2;

    if (dr < tr + s && dc < tc + s) {
        cover(tr, tc, dr, dc, s);
    } else {
        board[tr + s - 1][tc + s - 1] = t;
        cover(tr, tc, tr + s - 1, tc + s - 1, s);
    }

    if (dr < tr + s && dc >= tc + s) {
        cover(tr, tc + s, dr, dc, s);
    } else {
        board[tr + s - 1][tc + s] = t;
        cover(tr, tc + s, tr + s - 1, tc + s, s);
    }

    if (dr >= tr + s && dc < tc + s) {
        cover(tr + s, tc, dr, dc, s);
    } else {
        board [tr + s][tc + s - 1] = t;
        cover(tr + s, tc, tr + s, tc + s - 1, s);
    }

    if (dr >= tr + s && dc >= tc + s) {
        cover(tr + s, tc + s, dr, dc, s);
    } else {
        board[tr + s][tc + s] = t;
        cover(tr + s, tc + s, tr + s, tc + s, s);
    }
}

void printBoard(int k) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            std::cout << board[i][j] << "\t";
        }
        std::cout << std::endl << std::endl;
    }
}

int main() {
    int k, dr, dc;
    std::cout << "Enter the size of the board: "<< std::endl;
    std::cin >> k;
    std::cout << "Enter the direction of the snake: " << std::endl;
    std::cin >> dr >> dc;
    cover(0, 0, dr, dc, 1 << k);
    printBoard(1 << k);
    return 0;
}