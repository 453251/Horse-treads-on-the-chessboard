#ifndef _CHESSBOARDPROBLEM_H_
#define _CHESSBOARDPROBLEM_H_
#define MAX_STACK_SIZE 200
#define BOARD_SIZE 8
#include<iostream>
#include<queue>
using namespace std;
// 定义点
typedef struct point {
    int x, y; // 初始点的横坐标和纵坐标
    int index; // 方向指针
    int weight; // 该点的权值
    point() {} // 默认构造函数
} point;

//定义栈
typedef struct Stack
{
    point* elem; //点的坐标
    int base, top; //头尾指针
}Stack;

extern const int dx[8]; //x方向移动
extern const int dy[8]; //y方向移动

class ChessBoardProblem
{
private:
    int startX, startY;//起点和终点
    int order; //标记点被访问的顺序（Warnsdorff要用）
    Stack s;//栈，用于启发式搜索时存储点
    queue<point>Q;//队列,用于存储路径
    int Board[BOARD_SIZE][BOARD_SIZE];//棋盘
    int path[BOARD_SIZE * BOARD_SIZE][2]; //用于回溯法存储路径
    int sol[BOARD_SIZE][BOARD_SIZE];//用于回溯法存棋盘
public:
    ChessBoardProblem(int start_x, int start_y,int Order) :startX(start_x), startY(start_y),order(Order) {}//初始化列表
    /*栈的操作*/
    void InitStack(Stack& s);
    void push(Stack& s, point p);
    void pop(Stack&s);
    point getTop(Stack s);
    bool isEmpty(Stack s);
    void Swap(point& a, point& b);
    /*回溯法（Warnsdorff规则）（我做）*/
    int Partition(point direction[], int low, int high);
    void QSort(point direction[], int low, int high);
    void QuickSort(point direction[], int size);  //快速排序
    bool check(int x, int y); //检查边界
    void forward(point& now, point direction[], int& index);//向前
    void backward(point& now, int& index);//回溯
    int calculateTheWeight(int x, int y);//计算权重
    void Warnsdorff();
    //初始化
    void initState();
    /*深度优先搜索*/
    void DFS(point& now, point path[], int flag[BOARD_SIZE][BOARD_SIZE], int& found, int count);
    int greedyOpt(point now, int flag[BOARD_SIZE][BOARD_SIZE]);
    point nextPoint(point now, int flag[BOARD_SIZE][BOARD_SIZE]);
    bool checkDFS(int x, int y, int flag[BOARD_SIZE][BOARD_SIZE]);
    void output();
    /*回溯法*/
    void print_solution(int move_num);
    int is_valid(int x, int y);
    int solve_knight_tour(int move_num, int cur_x, int cur_y);
    void knight_tour();
};

#endif
