//
// Created by Kei on 3/12/2023.
//
#include"ChessClassHead.h"

/**深度优先搜索**/
void ChessBoardProblem::DFS(point& now, point pPoint[], int flag[BOARD_SIZE][BOARD_SIZE], int& found, int count) // NOLINT(*-no-recursion)
{
    if (found) //找到一次就退出
        return;
    if (count >= BOARD_SIZE*BOARD_SIZE) //马已经踏过了所有棋盘
    {
        found += 1;
    }
    if (!checkDFS(now.x, now.y, flag)) //出界或已访问过
        return;

    pPoint[count] = now;
    count++; //满足条件计数加1
    flag[now.x][now.y] = count; //对应节点记录访问顺序，第几次被访问的

    point next = nextPoint(now, flag);
    DFS(next, pPoint, flag, found, count); //下一步的搜索
    flag[now.x][now.y] = 0; //回溯，标记清零
}

int ChessBoardProblem::greedyOpt(point now, int flag[BOARD_SIZE][BOARD_SIZE])
{
    int nextCnt[8] = { -1,-1,-1,-1,-1,-1,-1,-1 };
    for (int i = 0; i < 8; i++)
    {
        int Xnext = now.x + dx[i];
        int Ynext = now.y + dy[i];
        if (checkDFS(Xnext, Ynext, flag))
        {
            nextCnt[i]++;
            for (int j = 0; j < 8; j++)
            {
                int Xnext_next = Xnext + dx[j];
                int Ynext_next = Ynext + dy[j];
                if (checkDFS(Xnext_next, Ynext_next, flag))
                    nextCnt[i]++;
            }
        }
    }
    int opt = 0; //记录下一步的方向
    for (int i = 0; i < 8; i++)
    {
        if (nextCnt[opt] == -1)
            opt = i;
        if ((nextCnt[i] < nextCnt[opt]) && nextCnt[i] != -1)
        {
            opt = i;
        }
    }
    return opt;
}

point ChessBoardProblem::nextPoint(point now, int flag[BOARD_SIZE][BOARD_SIZE])
{
    int opt = greedyOpt(now, flag);
    point next;
    next.x = now.x + dx[opt];
    next.y = now.y + dy[opt];
    return next;
}

bool ChessBoardProblem::checkDFS(int x, int y, int flag[BOARD_SIZE][BOARD_SIZE])
{
    if (x > 8 - 1 || y > 8 - 1 || x < 0 || y < 0 || flag[x][y] != 0) //边界条件
        return false;
    else
        return true;
}

void ChessBoardProblem::output()
{

    //计时
    clock_t start_a, end_a;
    start_a = clock();


    point pPoint[64];
    int flag[BOARD_SIZE][BOARD_SIZE] = { 0 };
    int found = 0;
    int count = 0;
    point start;
    start.x = startX;
    start.y = startY;
    DFS(start, pPoint, flag, found, count); //开始搜索

    int cnt = 1;
    for (auto & i : pPoint)
    {
        std::cout << '(' << i.x << ',' << i.y << ')';
        if (cnt % BOARD_SIZE == 0) cout << endl;
        else cout << ",";
        cnt++;
    }


    end_a = clock();
    double time_a = (double)(end_a - start_a) / CLOCKS_PER_SEC;
    cout << "深度优先搜索（剪枝）用时：" << time_a * 1000 << "毫秒";
}
