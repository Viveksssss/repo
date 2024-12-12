#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_set>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <windows.h>

// 设置输出颜色
void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    wColor = csbi.wAttributes;

    // 设置前景色
    wColor = ForgC + (wColor & 0xF0);
    SetConsoleTextAttribute(hStdOut, wColor);
}
// 命令列表
std::unordered_set<std::string> command = {
    "ls",       // 显示目录内容
    "ll",       // 显示详细目录内容
    "cd",       // 切换目录
    "mkdir",    // 创建文件夹
    "rmdir",    // 删除文件夹
    "rm",       // 删除文件
    "cp",       // 复制文件夹
    "touch",    // 创建文件夹
    "tree",     // n叉树形结构
    "shutdown", // 关机
    "date",     // 日期
    "pwd",      // 显示当前目录
    "mv",       // 移动文件
};
// 定义文件类型
enum class types
{
    DIRECTORY, // 文件夹
    FFILE,     // 普通文件

    // 只是类型排列，不涉及具体操作
    LINK,  // 链接文件
    BLOCK, // 块设备文件
};
// 定义文件节点sss
class node
{
public:
    // 类型名字
    types type;
    // 类型操作对应的操作点
    std::string types;
    // 文件的实际大小
    int size = 0; // 这里简单的功能并没有用上，只是为了方便理解
    // 文件的名字
    std::string name;
    // 子指针指向文件或者目录
    std::vector<struct node *> child;
    // 子指针的个数
    int num = 0;
    // 父结点
    struct node *parent;
};
// 文件系统
class file_system
{
public:
    // 根节点
    node *root;
    // 当前目录
    std::stack<node *> current;
    // 构造函数
    file_system()
    {
        root = new node();
        root->type = types::DIRECTORY;
        root->name = "/";
        current.push(root);
        root->parent = NULL;
    }
};
// 析构
void deletespace(node *p)
{
    for (int i = 0; i < p->num; i++)
    {
        if (p->child[i]->type == types::DIRECTORY)
        {
            deletespace(p->child[i]);
        }
        else
        {
            delete p->child[i];
            p->child.erase(p->child.begin() + i);
            p->num--;
            i--;
        }
    }
}
// 以树形结构递归输出目录结构
void printtree(node *p, int level)
{
    for (int i = 0; i < p->num; i++)
    {
        SetColor(FOREGROUND_RED);
        std::cout << "|";
        for (int i = 0; i < level; i++)
            std::cout << "    ";
        if (p->child[i]->type == types::DIRECTORY)
        {
            std::cout << "|---" << p->child[i]->name << std::endl;
            printtree(p->child[i], level + 1);
        }
        else
        {

            std::cout << "|---" << p->child[i]->name << std::endl;
        }
    }
    SetColor(7); // 白色
}
// 主操作
void mainoperation(file_system &fs)
{
    while (1)
    {
        std::cout << "root@exployer >>>";
        std::string s;
        std::getline(std::cin, s);
        std::istringstream is(s);
        std::string order; // 命令
        is >> order;
        if (command.count(order) == 0)
        {
            std::cout << "Invalid command" << std::endl;
            continue;
        }
        // 具体命令的操作
        if (order == "ls")
        {
            SetColor(3);
            for (int i = 0; i < fs.current.top()->num; i++)
            {
                std::cout << fs.current.top()->child[i]->name << " ";
            }
            if (fs.current.top()->num != 0)
                std::cout << std::endl;
            SetColor(7);
        }
        else if (order == "ll")
        {
            SetColor(3);
            for (int i = 0; i < fs.current.top()->num; i++)
            {
                std::cout << (fs.current.top()->child[i]->name) << " ";
                std::cout << (fs.current.top()->child[i]->size) << " ";
                std::cout << (fs.current.top()->child[i]->types) << std::endl;
            }
            if (fs.current.top()->num != 0)
                std::cout << std::endl;
            SetColor(7);
        }
        else if (order == "cd")
        {
            std::string name;
            is >> name;

            if (name == "..")
            {
                if (fs.current.size() == 1)
                {
                }
                else
                    fs.current.pop();
            }
            else
            {
                int flag = 0;
                for (int i = 0; i < fs.current.top()->num; i++)
                {
                    if (fs.current.top()->child[i]->name == name)
                    {
                        if (fs.current.top()->child[i]->type != types::DIRECTORY)
                        {
                            std::cout << "Invalid path" << std::endl;
                            flag = 1;
                            break;
                        }
                        fs.current.push(fs.current.top()->child[i]);
                        flag = 1;
                        break;
                    }
                }
                if (!flag)
                    std::cout << "No such file or directory" << std::endl;
            }
        }
        else if (order == "mkdir")
        {
            int flag = 0;
            std::string name;
            is >> name;
            node *p = fs.current.top();

            for (int i = 0; i < p->num; i++)
            {
                if (name == p->child[i]->name)
                {
                    std::cout << "the name already exists" << std::endl;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                p->child.push_back(new node());
                p->child[p->num]->type = types::DIRECTORY;
                p->child[p->num]->name = name;
                p->child[p->num]->parent = p;
                p->child[p->num]->types = "directory";
                p->num++;
            }
        }
        else if (order == "rmdir")
        {
            std::string name;
            is >> name;
            node *p = fs.current.top();
            int flag = 0;
            for (int i = 0; i < p->num; i++)
            {
                if (p->child[i]->name == name && p->child[i]->type == types::DIRECTORY)
                {
                    p->child.erase(p->child.begin() + i);
                    free(p->child[i]);
                    flag = 1;
                    p->num--;
                    break;
                }
            }
            if (!flag && p->num != 0)
            {
                std::cout << "No such file or directory" << std::endl;
            }
        }
        else if (order == "rm")
        {
            std::string name;
            is >> name;
            node *p = fs.current.top();
            int flag = 0;
            for (int i = 0; i < p->num; i++)
            {
                if (p->child[i]->name == name)
                {
                    p->child.erase(p->child.begin() + i);
                    free(p->child[i]);
                    flag = 1;
                    p->num--;
                    break;
                }
            }
            if (!flag && p->num != 0)
            {
                std::cout << "No such file or directory" << std::endl;
            }
        }
        else if (order == "cp")
        {
            std::string src, dst;
            is >> src >> dst;
            if (dst == "")
                std::cout << "the destination path is empty" << std::endl;
            else
            {
                int flag = 0;
                node *p = fs.current.top();
                for (int i = 0; i < p->num; i++)
                {
                    if (dst == p->child[i]->name)
                    {
                        flag = 1;
                        std::cout << "the name already exists" << std::endl;
                        break;
                    }
                }
                if (flag == 0)
                    for (int i = 0; i < p->num; i++)
                    {
                        if (p->child[i]->name == src)
                        {
                            flag = 1;
                            if (p->child[i]->type == types::DIRECTORY)
                            {
                                node *new_dir = new node();
                                new_dir->type = types::DIRECTORY;
                                new_dir->name = dst;
                                new_dir->parent = p;
                                new_dir->types = "directory";
                                p->child.push_back(new_dir);
                                p->num++;
                                for (int j = 0; j < p->child[i]->num; j++)
                                {
                                    node *new_node = new node();
                                    new_node->type = p->child[i]->child[j]->type;
                                    new_node->name = p->child[i]->child[j]->name;
                                    new_node->parent = new_dir;
                                    new_node->size = p->child[i]->child[j]->size;
                                    new_node->types = p->child[i]->child[j]->types;
                                    new_dir->child.push_back(new_node);
                                    new_dir->num++;
                                }
                            }
                            else
                            {
                                node *new_file = new node();
                                new_file->type = types::FFILE;
                                new_file->name = dst;
                                new_file->parent = p;
                                new_file->types = "file";
                                new_file->size = p->child[i]->size;
                                p->child.push_back(new_file);
                                p->num++;
                            }
                        }
                    }
                if (!flag)
                    std::cout << "No such file or directory" << std::endl;
            }
        }
        else if (order == "touch")
        {
            int flag = 0;
            std::string name;
            is >> name;
            node *p = fs.current.top();
            for (int i = 0; i < p->num; i++)
            {
                if (name == p->child[i]->name)
                {
                    flag = 1;
                    std::cout << "the name already exists" << std::endl;
                    break;
                }
            }
            if (flag == 0)
            {
                p->child.push_back(new node());
                p->child[p->num]->type = types::FFILE;
                p->child[p->num]->name = name;
                p->child[p->num]->parent = p;
                p->child[p->num]->types = "file";
                p->num++;
            }
        }
        else if (order == "tree")
        {
            printtree(fs.root, 0);
        }
        else if (order == "shutdown")
        {
            std::cout << "the system will be shutdown" << std::endl;
            deletespace(fs.root);
            exit(0);
        }
        else if (order == "date")
        {
            SetColor(6);
            std::time_t now = std::time(nullptr);
            std::tm *now_tm = std::localtime(&now);
            std::cout << "Current time: "
                      << (now_tm->tm_year + 1900) << '-'
                      << (now_tm->tm_mon + 1) << '-'
                      << now_tm->tm_mday << ' '
                      << now_tm->tm_hour << ':'
                      << now_tm->tm_min << ':'
                      << now_tm->tm_sec << std::endl;
            SetColor(7);
        }
        else if (order == "pwd")
        {
            SetColor(6);
            std::stack<node *> tmp = fs.current;
            std::vector<std::string> path;
            while (!tmp.empty())
            {
                path.push_back(tmp.top()->name);
                tmp.pop();
            }
            std::reverse(path.begin(), path.end());
            for (auto s : path)
            {
                if (s == "/")
                    std::cout << "/";
                else
                    std::cout << s << "/";
            }
            std::cout << std::endl;
            SetColor(7);
        }
        else if (order == "mv")
        {
            // mv比较复杂，就只实现了简单移动功能
            std::string src, dst;
            is >> src >> dst;

            node *src_node = nullptr;
            node *dst_parent = fs.current.top();

            // 查找源文件或文件夹
            for (int i = 0; i < fs.current.top()->num; i++)
            {
                if (fs.current.top()->child[i]->name == src)
                {
                    src_node = fs.current.top()->child[i];
                    break;
                }
            }

            if (src_node == nullptr)
            {
                std::cout << "Source file or directory not found" << std::endl;
            }
            else
            {
                for (int i = 0; i < fs.current.top()->num; i++)
                {
                    if (fs.current.top()->child[i]->type == types::DIRECTORY &&
                        fs.current.top()->child[i]->name == dst)
                    {
                        dst_parent = fs.current.top()->child[i];
                        break;
                    }
                }

                // 检查目标位置是否已存在同名文件或文件夹
                for (int i = 0; i < dst_parent->num; i++)
                {
                    if (dst_parent->child[i]->name == src_node->name)
                    {
                        std::cout << "Destination already has a file or directory with the same name" << std::endl;
                        break;
                    }
                }

                // 从源位置移除
                for (int i = 0; i < src_node->parent->num; i++)
                {
                    if (src_node->parent->child[i] == src_node)
                    {
                        src_node->parent->child.erase(src_node->parent->child.begin() + i);
                        src_node->parent->num--;
                        break;
                    }
                }

                // 更新源节点的父指针指向目标父目录
                src_node->parent = dst_parent;

                // 添加到目标位置
                dst_parent->child.push_back(src_node);
                dst_parent->num++;

                std::cout << "Move operation successful" << std::endl;
            }
        }
    }
}
int main()
{
    file_system fs;
    mainoperation(fs);
    deletespace(fs.root);
    return 0;
}
