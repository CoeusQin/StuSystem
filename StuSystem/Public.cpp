#include "stdafx.h"
#include "Public.h"


CPublic::CPublic()
{
}


CPublic::~CPublic()
{
}

int CPublic::status = 0;// 全局变量，用来表示身份
int CPublic::courseids[] = { 0 };// 全局变量，下标表示课程号，对应的值1表示该课程已开通，0表示该课程未开通