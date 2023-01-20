#include<iostream>
#include<string>
#include"manager.h"
using namespace std;

Manager::Manager(int ID, string name, int did)
{
    this->m_ID = ID;
    this->m_name = name;
    this->m_DeptID = did;
}

void Manager::showInfo()
{
    cout<<"职工编号："<<this->m_ID
        <<"\t职工姓名:"<<this->m_name
        <<"\t岗位职责:"<<this->m_DeptID
        <<"\t岗位职责: 完成老板分配的任务, 并下发任务给员工"<<endl;
}

string Manager::getDepartment()
{
    return string("Manager");
}

Manager::~Manager()
{

}



