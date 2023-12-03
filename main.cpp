// 马踏棋盘.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include"ChessClassHead.hpp"

using namespace std;

//八个方向
const int dx[8] = { 1,2,2,1,-1,-2,-2,-1 };
const int dy[8] = { 2,1,-1,-2,-2,-1,1,2 };

/****初始化****/
void ChessBoardProblem::initState()
{
    for (auto & i : Board)
        for (int & j : i) j = 0;
    while (!isEmpty(s))
        pop(s);
    while (!Q.empty())
        Q.pop();
}

int main()
{
    ChessBoardProblem chessboardproblem(0, 0,1);

    chessboardproblem.Warnsdorff();
    chessboardproblem.knight_tour();
    chessboardproblem.output();
    return 0;
}
