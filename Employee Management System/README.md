# Employee Management System

## 项目配置

### 编译器

gcc g++

编译器的英文为compiler，**其目的是将编程语言转换为CPU可以识别的二进制指令, GDB是Linux下的调试工具**

```bash
# 安装
sudo apt update
sudo apt install build-essential gdb
# 测试
gcc --version
g++ --version
gdb --version
```

#### Linux下c++程序的编译过程

**主要分为三个阶段：预处理 编译 链接**

```bash
g++ name -o name # 这一句话包含了以下的四步 
```

* 预处理：加载头文件等
* 编译(生成 .s 文件)
  * 编译：编译代码
  * 汇编：二进制指令

* 链接：生成可执行程序(生成 .o 文件)

<img src="./image/截屏2023-01-28 8.26.36.png" alt="截屏2023-01-28 8.26.36" style="zoom:30%;" />



### CMake

CMake是一个**跨平台**的编译(Build)工具,可以用简单的语句来描述所有平台的编译过程。

CMake是大部分C++开源项目的标配

CMake能够输出各种各样的makefile或者project文件，能测试编译器所支持的C++特性,类似UNIX下的automake。

```bash
# 安装
sudo apt install cmake
# 测试
cmake --version
```



#### 语法

- 基本语法格式：指令(参数1 参数2…..)
    - 参数使用()括起
    - 参数之间使用空格或者分号分开
- 指令是大小写无关的，参数和变量是大小写相关的
- 变量使用${ }方式取值，但是在IF控制语句中是直接使用变量名

#### 重要指令

- cmake_minimum_required - 指定CMake的最小版本要求
    - 语法：cmake_minimum_required(VERSION versionNumber[FATAL_ERROR[FORCE]])
    
    ```bash
    # CMake最小版本要求为2.8.3
    cmake_minimum_required(VERSION 2.8.3)
    ```
    
- project - 定义工程名称，并可指定工程支持的语言
    - 语法：project(projectname[CXX][C][Java])
    
    ```bash
    # 指定工程的名字为 HELLOWORLD
    project(HELLOWORLD)
    ```
    
- set-显式的定义变量
    - 语法：set(VAR [VALUE] [CACHE TYPE DOCSTRING])
    
    ```bash
    # 定义SRC变量，其值为sayhello.cpp hello.cpp
    set(SRC sayhello.cpp hello.cpp)
    # 定义SRC变量，以后使用SCR就是在使用 sayhello.cpp  hello.cpp
    ```
    
- include_directories - 向工程添加多个特定的头文件搜索路径 ——>相当于指定g++编译器的-L参数
    - 语法：include_directories(dir1 dir2)
    
    ```bash
    # 将/usr/lib/mylibfolder 和 ./lib 添加到头文件搜索路径中
    include_directories(/usr/lib/mylibfolder ./lib)
    ```
    
- link_directories - 向工程添加多个特征的库文件搜索路径
    - 语法：link_directories
    
    ```bash
    # 将/usr/lib/mylibfolder 和 ./lib 添加到库文件搜索路径中
    link_directories(/usr/lib/mylibfolder ./lib)
    ```
    
- add_library 生成库文件
    - 语法：add_library(libname [SHARED | STATIC | MODULE ][EXCLUDE_FROM_ALL] source1 source2….sourceN)
    
    ```bash
    # 通过变量SCR 生成 libhello.so 共享库
    add_library(hello SHARED ${SCR})
    ```
    
- add_compile_options 添加编译参数
    - 语法：add_compile_options
    
    ```bash
    add_compile_options(-wall -std=c++11 -o2)
    ```
    
- add_executable - 生成可执行文件
    - 语法：add_executable(exename source1 source2 sourceN)
    
    ```bash
    # 编译 main.cpp 生成可执行文件
    add_executable(main main.cpp)
    ```
    
- target_link_libraries - 为target添加需要链接的共享库
    - 语法：target_link_libraries(target library1)
    
    ```bash
    # 将hello动态库文件链接到可执行文件main
    target_link_libraries(main hello)
    ```
    
- add_subdirectory - 向当前工程添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置
  
    ```bash
    # 添加scr子目录，scr中需要有一个CMakeLists.txt
    add_subdirectory(scr)
    ```
    
- aux_source_directory - 发现一个目录下所有的源代码文件并将列表存储在一个变量中，这个指令临时被用来自动构建源文件列表
    - aux_source_directory(dir VARIABLE)
    
    ```bash
    # 定义SRC变量，其值为当前目录下的所有的代码源文件
    aux_source_directory(. SRC)
    # 编译SRC变量所代表的源代码文件，生成main可执行文件
    add_executable(main ${SRC})
    ```
    

#### CMake常用变量

- CMAKE_C_FLAGS  gcc 编译选项
- CMAKE_CXX_FLAGS  g++ 编译选项
- CMAKE_BUILD_TYPE 编译类型(Debug, Release)

#### CMake编译工程

Cmake目录结构：项目的主目录存在一个CMakeList.txt文件

**两种方式设置编译规则：**

1. 包含源文件的子文件夹包含CMakeList.txt，主目录的CMakeList.txt通过add_subdirectory添加子目录即可；
2. 包含源文件的子文件夹未包含CMakeList.txt文件，子目录的编译规则体现在主目录的CMakeList.txt文件中；

#### 使用CMake的编译流程

**在Linux平台下使用CMake构建C/C++工程的流程：**

- 手动编写CmakeLists.txt文件
- 执行命令cmake PATH生成Makefile(PATH是顶层CmakeLists.txt所在的目录)
- 执行make进行编译

#### 两种构建方式

- **内部构建( in-source build ): 不推荐**
  
    内部构建会在同级目录下产生一大堆中间文件，显得杂乱无章
    
    ```bash
    # 执行两条指令
    cmake ./
    make
    ```
    
- **外部构建( out-of-source build)**
  
    将编译输出的文件与源文件放在不同的目录中
    
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
    

#### 编写一个简单的CMakeLists.txt文件

```cmake
cmake_minimum_required(VERSION 3.0) 
# 指定最小的cmake版本

project(SOLID)
# 指定项目的名字

include_directories(${CMAKE_SOURCE_DIR}/include)
# 添加要使用的include文件

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall" )  
# -O2会将调试过程的信息优化没了
# 设置一些参数

set(CNAKE_BUILD_TYPE Debug)
# 如果写release就是生成可执行文件，也不能调试

add_executable(my_cmake_exe main.cpp src/Gun.cpp src/Solider.cpp)
# 生成可执行文件
```

### 配置VSCode

##### 目录结构

* `.vscode` : vscode的配置选项主要包括`c_cpp_properties.json` `launch.json` `tasks.json`

* `save`：存放项目保存的文件
* `build`: CMake使用外部编译
* `include`: 自己编写的头文件
* `scr`: 自己编写的.cpp文件

##### 配置调试

详见 `launch.json` `tasks.json` 两个文件

配置完成后即可不输入命令进行调试

**Note：在CMake时需要调试到Bebug的模式，并且不要使用-o2进行压缩**