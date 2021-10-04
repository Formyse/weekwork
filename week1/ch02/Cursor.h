#pragma once
#ifndef Cursor.h
#define SpaceSize 100 //定义数组大小
typedef int PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;


typedef int ElementType;
void InitializeCursorSpace(void);//初始化游标大小

List MakeEmpty(List L);//置空
int IsEmpty(const List L);//判断是否为空
int IsLast(const Position P, const List L);//判断是否为尾
void PrintList(const List L);//打印链表
Position Find(ElementType X, const List L);//查询位置
void Delete(ElementType X, List L);//删除某值
Position FindPrevious(ElementType X, const List L);//查寻某值的前一节点
void Insert(ElementType X, List L, Position P);//插入节点
void DeleteList(List L);//删除链表
Position Header(const List L);//头节点
Position First(const List L);//第一个节点
Position Advance(const Position P);//移动节点
ElementType Retrieve(const Position P);//返回节点数据

#endif // !Cursor.h

