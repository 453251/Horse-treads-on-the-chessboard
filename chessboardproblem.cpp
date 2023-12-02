#include"chessboardproblem.h"
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<queue>
#include<string.h>
#include<string>
using namespace std;

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
//��������Ļ���
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
	//�������˳��
	Board[direction[index].x][direction[index].y] = ++order;
	//����Ȩֵ
	now.weight = direction[index].weight;
	//����indexָ��
	now.index = direction[index].index;
	push(s, now);
	//���¸õ����Ϣ
	memset(&now, 0, sizeof(now));
	now.x = direction[index].x;
	now.y = direction[index].y;
	//����indexָ��
	index = 0;
}

void ChessBoardProblem::backward(point& now, int& index)
{
	--order;
	//�������ϵ��������Ϊ0
	Board[now.x][now.y] = 0;
	//��ȡ�õ��Ա�����һ��ѭ������������
	point temp = getTop(s); pop(s);
	now.x = temp.x;
	now.y = temp.y;
	index = temp.index;
	//����indexָ��
	index++;
}

int ChessBoardProblem::calculateTheWeight(int x, int y)
{
	//������Χ�˸��������δ��һ������δ����ĵ㣬�õ��Ȩֵ������
	//����sum��¼Ȩֵ
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
	InitStack(s);
	int index = 0;//���з����indexָ��
	point now;//��ʼ��
	point direction[8];//����
	memset(direction, 0, sizeof(direction));
	initState();
	Board[startX][startY] = order;
	now.x = startX; now.y = startY;
	//��order<BOARD_SIZE*BOARD_SIZE����Ϊѭ���˳�������
	while (order < BOARD_SIZE*BOARD_SIZE)
	{
		int size = 0;//���з��������
		//����8�����򲢼���Ȩֵ
		for (int i = 0; i < 8; i++)
		{
			int x_next = now.x + dx[i];
			int y_next = now.y + dy[i];
			if (check(x_next, y_next) && Board[x_next][y_next] == 0) //���δԽ���߽粢�һ�δ�߹�
			{
				int weight = calculateTheWeight(x_next, y_next); //����Ȩֵ
				direction[size].x = x_next; direction[size].y = y_next;
				direction[size].weight = weight;
				size++;
			}
		}
		QuickSort(direction, size);
		for (int i = 0; i < size; i++) direction[i].index = i;
		//�����·���ߣ�����õ�ǰ��
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
	cout << BOARD_SIZE<<"��" << BOARD_SIZE << "��̤���������·��Ϊ:\n";
	int flag = 0;//�ж��Ƿ���Ҫ�������
	int cnt = 1;//�ж��Ƿ�������з�
	while (!Q.empty())
	{
		point p = Q.front(); Q.pop();
		if (flag)
			cout << ",";
		cout << "(" << p.x << "," << p.y << ")";
		if (cnt % BOARD_SIZE == 0) cout << endl;
		cnt++;
	}
}

void ChessBoardProblem::initState()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++) Board[i][j] = 0;
	while (!isEmpty(s))
		pop(s);
}