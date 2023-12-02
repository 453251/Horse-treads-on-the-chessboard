#ifndef _CHESSBOARDPROBLEM_H_
#define _CHESSBOARDPROBLEM_H_
#define MAX_STACK_SIZE 200
#define BOARD_SIZE 8
#include<iostream>
#include<queue>
using namespace std;
// �����
typedef struct point {
    int x, y; // ��ʼ��ĺ������������
    int index; // ����ָ��
    int weight; // �õ��Ȩֵ
    point() {} // Ĭ�Ϲ��캯��
} point;

//����ջ
typedef struct Stack
{
    point* elem; //�������
    int base, top; //ͷβָ��
}Stack;

extern const int dx[8]; //x�����ƶ�
extern const int dy[8]; //y�����ƶ�

class ChessBoardProblem
{
private:
    int startX, startY;//�����յ�
    int order; //��ǵ㱻���ʵ�˳��WarnsdorffҪ�ã�
    Stack s;//ջ����������ʽ����ʱ�洢��
    queue<point>Q;//����,���ڴ洢·��
    int Board[BOARD_SIZE][BOARD_SIZE];//����
public:
    ChessBoardProblem(int start_x, int start_y,int Order) :startX(start_x), startY(start_y),order(Order) {}//��ʼ���б�
    /*ջ�Ĳ���*/
    void InitStack(Stack& s);
    void push(Stack& s, point p);
    void pop(Stack&s);
    point getTop(Stack s);
    bool isEmpty(Stack s);
    void Swap(point& a, point& b);
    /*���ݷ���Warnsdorff���򣩣�������*/
    int Partition(point direction[], int low, int high);
    void QSort(point direction[], int low, int high);
    void QuickSort(point direction[], int size);  //��������
    bool check(int x, int y); //���߽�
    void forward(point& now, point direction[], int& index);//��ǰ
    void backward(point& now, int& index);//����
    int calculateTheWeight(int x, int y);//����Ȩ��
    void Warnsdorff();
    //��ʼ��
    void initState();
    /*�����������*/



    /*�����������*/



    /*���ݷ�*/
};

#endif