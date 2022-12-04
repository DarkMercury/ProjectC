#include<iostream>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;

int main()
{
    Worker *worker = NULL;
    worker = new Employee(1,"star",1);
    worker->showInfo();
    delete worker;

    worker = new Manager(2,"fly",2);
    worker->showInfo();
    delete worker;

    worker = new Boss(3,"lizhuohang",3);
    worker->showInfo();
    delete worker;

    // 实例化对象
    WorkerManager wm;
    int select = 0;

    while (true)
    {
        wm.Show_Menu();
        cin>>select;


        switch (select)
        {
        case 1:
        // 1. Add Employee Information
            wm.Add_Emp();
            break;

        case 2:
        // 2. Show Employee Information
            wm.show_Emp();
            break;
        
        case 3:
            wm.Del_Emp();
            break;
        case 4:
        // 4. Modify Employee Information
            wm.Mod_Emp();
            break;
        
        case 5:
        // 5. Find Employee Information
            wm.Find_Emp();
            break;
        
        case 6:
        // 6. Sort by Number
            break;

        case 7:
        // 7. Clear all Document
            wm.Clean_File();
            break;
        
        case 0:
        // 0. Exit Management System
            wm.exitSystem();
            break;
        
        default:
            cout<<"Choice don't exit. Please input again!!!"<<endl;
            break;
        }
    }

    return 0;
}
