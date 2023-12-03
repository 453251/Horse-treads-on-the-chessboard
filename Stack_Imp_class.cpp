//
// Created by Kei on 3/12/2023.
//

#include"ChessClassHead.h"

using namespace std;

/***********栈的操作**********/
void ChessBoardProblem::InitStack(Stack& s){
    if (!(s.elem)) {
        s.elem = new point[MAX_STACK_SIZE];
    }
    s.top = 0;
    s.base = 0;
}

void ChessBoardProblem::push(Stack& s, point p){
    s.elem[s.top++] = p;
}

void ChessBoardProblem::pop(Stack& s){
    s.top--;
}

void ChessBoardProblem::Swap(point& a, point& b){
    point temp = a;
    a = b;
    b = temp;
}

point ChessBoardProblem::getTop(Stack s){
    return s.elem[s.top - 1];
}

bool ChessBoardProblem::isEmpty(Stack s){
    return s.top == s.base;
}