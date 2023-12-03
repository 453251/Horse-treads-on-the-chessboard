//
// Created by Kei on 3/12/2023.
//
#include"ChessClassHead.h"

using namespace std;

/***回溯法**/

int ChessBoardProblem::is_valid(int x, int y)
{
    if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE)
        return 0;
    if (sol[x][y] != -1)
        return 0;
    return 1;
}

int ChessBoardProblem::solve_knight_tour(int move_num, int cur_x, int cur_y) // NOLINT(*-no-recursion)
{
    if (move_num == BOARD_SIZE * BOARD_SIZE)
        return 1;

    for (int i = 0; i < 8; i++) {
        int new_x = cur_x + dx[i];
        int new_y = cur_y + dy[i];
        if (is_valid(new_x, new_y)) {
            sol[new_x][new_y] = move_num;
            path[move_num][0] = new_x;
            path[move_num][1] = new_y;
            if (solve_knight_tour(move_num + 1, new_x, new_y) == 1)
                return 1;
            else
                sol[new_x][new_y] = -1;  // backtracking
        }
    }
    return 0;
}

void ChessBoardProblem::knight_tour()
{
    for (auto & x : sol)
        for (int & y : x)
            y = -1;

    sol[startX][startY] = 0;
    path[0][0] = startX;
    path[0][1] = startY;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    if (solve_knight_tour(1, startX, startY) == 0) {
        printf("No solution found.\n");
    }
    else {
        print_solution(BOARD_SIZE*BOARD_SIZE);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("回溯法运行时间: %f 毫秒\n", cpu_time_used * 1000);
}

void ChessBoardProblem::print_solution(int move_num)
{
    printf("8x8马踏棋盘问题的路径为：\n");
    for (int i = 0; i < move_num; i++)
    {
        printf("(%d,%d) ", path[i][0], path[i][1]);
        if ((i + 1) % BOARD_SIZE == 0)	cout << endl;
    }
}