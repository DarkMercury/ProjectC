#include"workerManager.h"
using namespace std;


WorkerManager::WorkerManager()
{
    // 文件不存在
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // 读文件
    if(!ifs.is_open())
    {
        cout<<"The file is not exist"<<endl;
        // 初始化属性
        // 初始化记录人数
        this->m_EmpNum = 0;
        // 初始化数组指针
        this->m_EmpArray = NULL;
        // 初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    // case 2: 文件存在 数据为空

    char ch;
    ifs >> ch;
    // 读走文件尾标志,否则文件不是空的

    if(ifs.eof())
    {
        // 文件为空
        cout<<"File is Empty!"<<endl;
        this->m_EmpNum = 0;
        // 初始化数组指针
        this->m_EmpArray = NULL;
        // 初始化文件是否为空
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //case 3 文件存在 且记录数据
    int num = this->get_EmpNum();
    cout<<"the number of employee is  "<<num<<endl;
    this->m_EmpNum = num;
    // 开辟空间，将文件中的数据存入数组中
    this->m_EmpArray = new Worker*[this->m_EmpNum];
    this->init_Emp();

    for(int i = 0; i<this->m_EmpNum; i++)
    {
        cout<<"the number of employee "<<this->m_EmpArray[i]->m_ID
            <<" Name: "<<this->m_EmpArray[i]->m_name
            <<" Department id "<<this->m_EmpArray[i]->m_DeptID<<endl;
    }
}

WorkerManager::~WorkerManager()
{
    if(this->m_EmpArray != NULL)
    {
        delete [] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}

void WorkerManager::Show_Menu()
{
    cout<<"********************************************************"<<endl;
    cout<<"************* 0. Exit Management System  ***************"<<endl;
    cout<<"************* 1. Add Employee Information  *************"<<endl;
    cout<<"************* 2. Show Employee Information *************"<<endl;
    cout<<"************* 3. Delete Employee Information ***********"<<endl;
    cout<<"************* 4. Modify Employee Information ***********"<<endl;
    cout<<"************* 5. Find Employee Information *************"<<endl;
    cout<<"************* 6. Sort by Number ************************"<<endl;
    cout<<"************* 7. Clear all Document ********************"<<endl;
    
}

void WorkerManager::exitSystem()
{
    cout<<"See you next time!!"<<endl;
    cout<<"Thank You"<<endl;
    exit(0);
}

void WorkerManager::Add_Emp()
{
    int addNum = 0; // 保存用户的输入数量
    cout<<"Please input the number of employees:";
    cin>>addNum;
    if(addNum > 0)
    {
        // 添加
        // 计算添加空间大小
        int newSize = this->m_EmpNum + addNum; // 新空间人数 = 原来记录人数+新增人数
        // 开辟新空间
        Worker ** newSpace =  new Worker*[newSize];

        // 拷贝原来数据到新空间
        if(this->m_EmpArray != NULL)
        {
            for(int i = 0; i< this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }

        // 批量添加新数据
        for(int i =0; i < addNum; i++)
        {
            int id; // 职工编号
            string name; // 职工姓名
            int dSelect; // 部门选择

            cout<<"Please input"<<(i+1)<<"th new employ id:"<<endl;
            cin>>id;
            

            cout<<"Please input"<<(i+1)<<"th new employ name:"<<endl;
            cin>>name;

            cout<<"Please select position: "<<endl;
            cout<<"1. Employee"<<endl;
            cout<<"2. Manager"<<endl;
            cout<<"3. Boss"<<endl;
            cin>>dSelect;

            Worker *worker = NULL;

            switch (dSelect)
            {
            case 1:
                worker = new Employee(id,name,1);
                break;
            
            case 2:
                worker = new Manager(id,name,2);
                break;

            case 3:
                worker = new Boss(id,name,3);
                break;

            default:
                break;
            }
            // 将创建职工保存到数组中
            newSpace[this->m_EmpNum + i] = worker;
            
        }
        // 释放原有空间
        delete [] this->m_EmpArray;
        // 更新新空间的指向
        this->m_EmpArray = newSpace;
        // 更新职工人数
        this->m_EmpNum = newSize;

        // 更新职工不为空标志
        this->m_FileIsEmpty = false;

        // 提示添加成功
        cout<<"Add number successfully"<< addNum << "New employee"<<endl;
        
        // 保存数据到文件中
        this->save();
    }
    else
    {
        cout<<"The number has mistake!"<<endl;
    }

}

void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out); // 用输出的方式打开文件（写文件）

    // 将每个人的数据写入到文件中
    for(int i = 0; i < this->m_EmpNum; i++)
    {
        ofs<<this->m_EmpArray[i]->m_ID<<" "
           <<this->m_EmpArray[i]->m_name<<" "
           <<this->m_EmpArray[i]->m_DeptID<<endl;
    }
    ofs.close();
}

int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // 打开文件
    
    // 接受对象
    int id;
    string name;
    int did;
    int num = 0;
    while(ifs>>id && ifs>>name && ifs>>did)
    {
        num++;
    }
    return num;
    ifs.close();
}

void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int did;
    int index = 0;

    while(ifs>>id && ifs>>name && ifs>>did)
    {
        Worker *worker = NULL;
        if(did == 1)
        {
            // 普通员工
            worker = new Employee(id,name,did);
        }
        else if(did == 2)
        {
            worker = new Manager(id, name, did);
        }
        else
        {
            worker = new Boss(id, name, did);
        }
        this->m_EmpArray[index] = worker;
        index++;
    }
    // 关闭文件
    ifs.close();
}

void WorkerManager::show_Emp()
{
    // 判断函数是否为空
    if(this->m_FileIsEmpty)
    {
        cout<<"File is Empty or don't exist"<<endl;
    }
    else
    {

        for(int i = 0; i<this->m_EmpNum; i++)
        {
            // 利用多态调用程序接口
            this->m_EmpArray[i]->showInfo();
        }
    }  
}

int WorkerManager::IsExist(int id)
{
    // 存在返回位置，否则返回-1
    int index = -1;
    for(int i = 0; i < this->m_EmpNum;i++)
    {
        if(this->m_EmpArray[i]->m_ID == id)
        {
            // 找到职工
            index = i;
            break;
        }
    }
    return index;
}

void WorkerManager::Del_Emp()
{
    // 删除分为两部：1. 判断存在 2. 进行删除
    if(this->m_FileIsEmpty)
    {
        cout<<"The file is not exit"<<endl;
    }
    else
    {
        cout<<"Please input the id: "<<endl;
        int id;
        cin >> id;
        int index = this->IsExist(id);
        if(index != -1)
        {
            for(int i = index; i<this->m_EmpNum-1; i++)
            {
                // 数据前移
                this->m_EmpArray[i] = this->m_EmpArray[i+1];
            }
            this->m_EmpNum--;
            // 同步更新到文件中
            this->save();
            cout<<"Delete succefully!"<<endl;
        }
        else
        {
            cout<<"Delete fail"<<endl;
        }
        
    }

}

void WorkerManager::Mod_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout<<"The file is not exist!!"<<endl;
    }
    else
    {
        cout<<"Please input id : "<<endl;
        int id;
        cin>>id;
        int ret = this->IsExist(id);

        if(ret!=-1)
        {
            // 查找到编号的员工
            delete this->m_EmpArray[ret];
            int newID = 0;
            string newName = "";
            int dSelect = 0;

            cout<<"Find: "<< id << " Please input new id"<<endl;
            cin >> newID;

            cout<<"Please input new name: "<<endl;
            cin>>newName;

            cout<<"please input position: "<<endl;
            cout<<"1. Employee"<<endl;
            cout<<"2. Manager"<<endl;
            cout<<"3. Boss"<<endl;
            cin >> dSelect;

            Worker *worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(newID, newName, dSelect);
                break;
            case 2:
                worker = new Manager(newID, newName, dSelect);
                break;
            case 3:
                worker = new Boss(newID, newName, dSelect);
                break;
            default:
                break;
            }
            // 更新数据
            this->m_EmpArray[ret] = worker;

            cout<<"Modify Successful!!"<<endl;
            // 保存到文件中
            this->save();
        }
        else
        {
            cout<<"Modify fail"<<endl;
        }
    }

}

void WorkerManager::Find_Emp()
{
    if(this->m_FileIsEmpty)
    {
        cout<<"File is not exist"<<endl;
    }
    else
    {
        cout<<"The finding way"<<endl;
        cout<<"1. According id"<<endl;
        cout<<"2. According name"<<endl;
        int select = 0;
        cin>>select;
        if(select == 1)
        {
            // 按照id查找
            int id;
            cout<<"Please input id: "<<endl;
            cin>>id;
            int ret = IsExist(id);
            if(ret != -1)
            {
                cout<<"Find the Employee: "<<endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                cout<<"Find fail"<<endl;
            }
        }

        else if(select == 2)
        {
            // 按照姓名查找
            string name;
            cout<<"Please Input the name: "<<endl;
            cin >> name;

            bool flag = false;
            for(int i = 0; i<this->m_EmpNum; i++)
            {
                if(this->m_EmpArray[i]->m_name == name)
                {
                    cout<<"Find the Employee: "<<endl;
                    this->m_EmpArray[i]->showInfo();
                    flag = true;
                }
            }
            if(flag == false)
            {
                cout<<"Find fail"<<endl;
            }

        }
    }
}

void WorkerManager::Clean_File()
{
    cout<<"Are you sure to clean all data?"<<endl;
    cout<<"1. Sure"<<endl;
    cout<<"2. Not Sure"<<endl;

    int select = 0;
    cin>>select;

    if(select == 1)
    {
        // 清空文件
        ofstream ofs(FILENAME, ios::trunc); // 删除文件后重新创建
        ofs.close();

        if(this->m_EmpArray != NULL)
        {
            for(int i = 0; i < this->m_EmpNum; i++)
            {
                // 删除堆区的每一个职工对象
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = NULL;
            }
            // 删除堆区数组指针
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
        }

        cout<<"Clean Up Successful!"<<endl;
    }
}
