#include"chessboardproblem.h"
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<queue>
#include<string.h>
#include<string>
#include<time.h>
using namespace std;

/***********栈的操作**********/
void ChessBoardProblem::InitStack(Stack& s)
{
	if (!(s.elem)) {
		s.elem = new point[MAX_STACK_SIZE];
	}
	s.top = 0;
	s.base = 0;
}

void ChessBoardProblem::push(Stack& s, point p)
{
	s.elem[s.top++] = p;
}

void ChessBoardProblem::pop(Stack& s)
{
	s.top--;
}

point ChessBoardProblem::getTop(Stack s)
{
	return s.elem[s.top - 1];
}

bool ChessBoardProblem::isEmpty(Stack s)
{
	return s.top == s.base;
}

void ChessBoardProblem::Swap(point& a, point& b)
{
	point temp = a;
	a = b;
	b = temp;
}
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

void ChessBoardProblem::QSort(point direction[], int low, int high)
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

/****初始化****/
void ChessBoardProblem::initState()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++) Board[i][j] = 0;
	while (!isEmpty(s))
		pop(s);
	while (!Q.empty())
		Q.pop();
}
/***回溯法**/
void ChessBoardProblem::print_solution(int move_num)
{
	printf("8x8马踏棋盘问题的路径为：\n");
	int cnt = 1;
	for (int i = 0; i < move_num; i++)
	{
		printf("(%d,%d) ", path[i][0], path[i][1]);
		if ((i + 1) % BOARD_SIZE == 0)	cout << endl;
	}
}

int ChessBoardProblem::is_valid(int x, int y)
{
	if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE)
		return 0;
	if (sol[x][y] != -1)
		return 0;
	return 1;
}

int ChessBoardProblem::solve_knight_tour(int move_num, int cur_x, int cur_y)
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
	for (int x = 0; x < BOARD_SIZE; x++)
		for (int y = 0; y < BOARD_SIZE; y++)
			sol[x][y] = -1;

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

/**深度优先搜索**/
void ChessBoardProblem::DFS(point& now, point path[], int flag[BOARD_SIZE][BOARD_SIZE], int& found, int count)
{
	if (found) //找到一次就退出
		return;
	if (count >= BOARD_SIZE*BOARD_SIZE) //马已经踏过了所有棋盘
	{
		found += 1;
	}
	if (!checkDFS(now.x, now.y, flag)) //出界或已访问过
		return;

	path[count] = now;
	count++; //满足条件计数加1
	flag[now.x][now.y] = count; //对应节点记录访问顺序，第几次被访问的

	point next = nextPoint(now, flag);
	DFS(next, path, flag, found, count); //下一步的搜索
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
	clock_t start_a, end_a, start_b, end_b;
	start_a = clock();
	

	point path[64];
	int flag[BOARD_SIZE][BOARD_SIZE] = { 0 };
	int found = 0;
	int count = 0;
	point start;
	start.x = startX;
	start.y = startY;
	DFS(start, path, flag, found, count); //开始搜索

	int cnt = 1;
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		std::cout << '(' << path[i].x << ',' << path[i].y << ')';
		if (cnt % BOARD_SIZE == 0) cout << endl;
		else cout << ",";
		cnt++;
	}

	
	end_a = clock();
	double time_a = (double)(end_a - start_a) / CLOCKS_PER_SEC;
	cout << "深度优先搜索（剪枝）用时：" << time_a * 1000 << "毫秒";
}
