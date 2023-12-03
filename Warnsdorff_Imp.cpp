//
// Created by Kei on 3/12/2023.
//
#include"ChessClassHead.h"

/******回溯法（Warnsordff规则）******/

//快速排序的划分
int ChessBoardProblem::Partition(point direction[], int low, int high)
{
    int pivot = low;
    while (low < high)
    {
        while (low<high && direction[high].weight>direction[pivot].weight)
            high--;
        while (low < high && direction[low].weight <= direction[pivot].weight)
            low++;
        Swap(direction[low], direction[high]);
    }
    Swap(direction[low], direction[pivot]);
    return low;
}

void ChessBoardProblem::QSort(point direction[], int low, int high) // NOLINT(*-no-recursion)
{
    if (low < high)
    {
        int pivot = Partition(direction, low, high);
        QSort(direction, low, pivot - 1);
        QSort(direction, pivot + 1, high);
    }
}

void ChessBoardProblem::QuickSort(point direction[], int size)
{
    QSort(direction, 0, size - 1);
}

bool ChessBoardProblem::check(int x, int y)
{
    return (x >= 0 && x < BOARD_SIZE&& y >= 0 && y < BOARD_SIZE);
}
void ChessBoardProblem::forward(point& now, point direction[], int& index)
{
    //标记棋盘顺序
    Board[direction[index].x][direction[index].y] = ++order;
    //设置权值
    now.weight = direction[index].weight;
    //设置index指针
    now.index = direction[index].index;
    push(s, now);
    //更新该点的信息
    memset(&now, 0, sizeof(now));
    now.x = direction[index].x;
    now.y = direction[index].y;
    //更新index指针
    index = 0;
}

void ChessBoardProblem::backward(point& now, int& index)
{
    --order;
    //将棋盘上的这个点置为0
    Board[now.x][now.y] = 0;
    //获取该点以便在下一次循环中重新搜索
    point temp = getTop(s); pop(s);
    now.x = temp.x;
    now.y = temp.y;
    index = temp.index;
    //更新index指针
    index++;
}

int ChessBoardProblem::calculateTheWeight(int x, int y)
{
    //遍历周围八个方向，如果未下一步存在未到达的点，该点的权值就增加
    //采用sum记录权值
    int sum = 0;
    for (int i = 0; i < 8; ++i) {
        int x_next = x + dx[i];
        int y_next = y + dy[i];
        if (check(x_next, y_next)) {
            if (Board[x_next][y_next] == 0) {
                sum++;
            }
        }
    }
    return sum;
}

void ChessBoardProblem::Warnsdorff()
{
    clock_t start, end;
    start = clock();
    InitStack(s);
    int index = 0;//可行方向的index指针
    point now;//初始点
    point direction[8];//方向
    memset(direction, 0, sizeof(direction));
    initState();
    Board[startX][startY] = order;
    now.x = startX; now.y = startY;
    //将order<BOARD_SIZE*BOARD_SIZE设置为循环退出的条件
    while (order < BOARD_SIZE*BOARD_SIZE)
    {
        int size = 0;//可行方向的数量
        //搜索8个方向并计算权值
        for (int i = 0; i < 8; i++)
        {
            int x_next = now.x + dx[i];
            int y_next = now.y + dy[i];
            if (check(x_next, y_next) && Board[x_next][y_next] == 0) //如果未越过边界并且还未走过
            {
                int weight = calculateTheWeight(x_next, y_next); //计算权值
                direction[size].x = x_next; direction[size].y = y_next;
                direction[size].weight = weight;
                size++;
            }
        }
        QuickSort(direction, size);
        for (int i = 0; i < size; i++) direction[i].index = i;//这里的index和i刚好是一一对应的关系
        //如果有路可走，则向该点前进
        if (order >= 1 && size > 0 && index < size)
        {
            forward(now, direction, index);
            Q.push(now);
        }
        else
        {
            backward(now, index);
            Q.pop();
        }
    }
    std::cout << BOARD_SIZE<<"×" << BOARD_SIZE << "马踏棋盘问题的路径为:\n";
    std::cout << "(" <<startX << "," << startY<< "),";
    int cnt = 2;//判定是否输出换行符
    while (!Q.empty())
    {
        point p = Q.front(); Q.pop();
        std::cout << "(" << p.x << "," << p.y << ")";
        if (cnt % BOARD_SIZE == 0) std::cout << endl;
        else std::cout << ",";
        cnt++;
    }
    end = clock();
    cout << "回溯法（Warnsordff规则）运行时间:" << end - start <<"毫秒"<< endl;
}