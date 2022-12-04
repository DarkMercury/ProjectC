#include"employee.h"
#include<string>
#include<iostream>
using namespace std;

Employee::Employee(int id, string name, int did)
{
    this->m_ID = id;
    this->m_name = name;
    this->m_DeptID = did;
}

void Employee::showInfo()
{
    cout<<"职工编号："<<this->m_ID
        <<"\t职工姓名:"<<this->m_name
        <<"\t岗位职责:"<<this->m_DeptID
        <<"\t岗位职责: 完成经理分配的任务"<<endl;
}

string Employee::getDepartment()
{
    return string("Employee");
}

Employee::~Employee()
{

}