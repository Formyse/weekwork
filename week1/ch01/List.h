#pragma once
#ifndef List.h
struct Node; //定义一个结构体
typedef struct Node *ptrToNode; //定义一个指向结构体的指针
typedef ptrToNode List; //该指针起别名
typedef ptrToNode Position;//起别名

typedef int ElementType;//int类型测试类型，若是其他类型数据，更改即可

List CreateList();//创建链表节点
List MakeEmpty(List L);//将链表清空
int IsEmpty(List L);//判断是否为空
int IsLast(Position P, List L);//判断是否是链表尾部
void PrintList(const List L);//打印链表
Position Find(ElementType X, List L);//查询某值第一次出现的位置
void Delete(ElementType X, List L);//删除某元素
Position FindPrevious(ElementType X, List L);//查询某值的前一节点位置
void Insert(ElementType X, List L, Position P);//插入节点
void DeleteList(List L);//删除链表
Position Header(List L);//头节点
Position First(List L);//第一个节点
Position Advance(Position P);//返回某节点的下一节点
ElementType Data(Position P);//返回该位置的值

#endif // List.h

