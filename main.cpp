#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void list_add();
void list_print();
void list_edit();
void list_delete();
void list_search();
void file_load();
void file_save();

struct book
{
    string name;
    string version;
    string auther;
    string pubisher;
    string isbn;
    string date;
};

vector<book> book_list;

int main()
{
    cout << "个人图书信息管理系统v1.1" << endl << "By: Direktor 2020/9/30" << endl << endl;
    int key = -1;
    file_load();
    cout << setiosflags(ios::left);
    while(key != 0)
    {
        cout << "-------------------------主菜单-------------------------" << endl;
        cout << "1 - 录入新图书信息" << endl << "2 - 修改图书信息" << endl << "3 - 删除图书信息" << endl << "4 - 搜索图书信息" << endl << "5 - 显示所有图书" << endl << "0 - 退出管理系统" << endl;
        cin >> key;
        if(key == 1)
            list_add();
        if(key == 2)
            list_edit();
        if(key == 3)
            list_delete();
        if(key == 4)
            list_search();
        if(key == 5)
            list_print();
        file_save();
    }
}

void list_add()
{
    book tmp;
    cout << "------------------------信息录入------------------------" << endl;
    cout << "请输入名称：";
    cin >> tmp.name;
    cout << "请输入版本：";
    cin >> tmp.version;
    cout << "请输入作者：";
    cin >> tmp.auther;
    cout << "请输入出版社：";
    cin >> tmp.pubisher;
    cout << "请输入ISBN编号：";
    cin >> tmp.isbn;
    cout << "请输入出版日期（YYYY/MM/DD）：";
    cin >> tmp.date;
    cout << "录入成功" << endl << endl;
    book_list.push_back(tmp);
}

void list_edit()
{
    int num, key;
    cout << "------------------------信息修改------------------------" << endl;
    cout << "请输入要修改的图书编号:";
    cin >> num;
    if(num > book_list.size())
    {
        cout << "查无此书，修改失败" << endl << endl;
        return;
    }
    cout << endl << setw(10) << "编号" << setw(20) << "名称" << setw(10) << "版本" << setw(20) << "作者" << setw(20) << "出版社" << setw(20) << "ISBN" << setw(20) << "出版日期" << endl;
    cout << setw(10) << num << setw(20)  << book_list[num-1].name << setw(10) << book_list[num-1].version << setw(20) << book_list[num-1].auther << setw(20) << book_list[num-1].pubisher  << setw(20) << book_list[num-1].isbn << setw(20) << book_list[num-1].date << endl << endl;
    cout << "请选择要修改的条目：" << endl << "1 - 修改名称" << endl << "2 - 修改版本" << endl << "3 - 修改作者" << endl << "4 - 修改出版社" << endl << "5 - 修改ISBN" << endl << "6 - 修改出版日期" << endl;
    cin >> key;
    cout << "请输入信息：";
    if(key == 1)
        cin >> book_list[num-1].name;
    if(key == 2)
        cin >> book_list[num-1].version;
    if(key == 3)
        cin >> book_list[num-1].auther;
    if(key == 4)
        cin >> book_list[num-1].pubisher;
    if(key == 5)
        cin >> book_list[num-1].isbn;
    if(key == 6)
        cin >> book_list[num-1].date;
    cout << "修改完毕" << endl << endl;
}

void list_delete()
{
    int num;
    char key = 0;
    cout << "------------------------信息删除------------------------" << endl;
    cout << "请输入要删除的图书编号:";
    cin >> num;
    if(num > book_list.size())
    {
        cout << "查无此书，删除失败" << endl << endl;
        return;
    }
    cout << endl << setw(10) << "编号" << setw(20) << "名称" << setw(10) << "版本" << setw(20) << "作者" << setw(20) << "出版社" << setw(20) << "ISBN" << setw(20) << "出版日期" << endl;
    cout << setw(10) << num << setw(20)  << book_list[num-1].name << setw(10) << book_list[num-1].version << setw(20) << book_list[num-1].auther << setw(20) << book_list[num-1].pubisher  << setw(20) << book_list[num-1].isbn << setw(20) << book_list[num-1].date << endl << endl;
    cout << "按Y删除此书" << endl;
    cin >> key;
    if(key == 'Y' || key == 'y')
    {
        book_list.erase(book_list.begin() + num - 1);
        cout << "删除成功" << endl << endl;
    }
    else
    {
        cout << "删除成功" << endl << endl;
    }
    
}

void list_search()
{
    int key;
    string contant;
    cout << "------------------------信息搜索------------------------" << endl;
    cout << "1 - 按名称搜索" << endl << "2 - 按版本搜索" << endl << "3 - 按作者搜索" << endl << "4 - 按出版社搜索" << endl << "5 - 按ISBN搜索" << endl << "6 - 按出版日期搜索" << endl << "7 - 全局搜索" << endl;
    cin >> key;
    cout << "请输入搜索内容:";
    cin >> contant;
    cout << endl << setw(10) << "编号" << setw(20) << "名称" << setw(10) << "版本" << setw(20) << "作者" << setw(20) << "出版社" << setw(20) << "ISBN" << setw(20) << "出版日期" << endl;
    for(auto i = book_list.begin(); i != book_list.end(); i++)
    if(key == 7)
    {
        for(auto i = book_list.begin(); i != book_list.end(); i++)
            if(i->name == contant || i->version == contant || i->auther == contant || i->pubisher == contant || i->isbn == contant || i->date == contant)
                cout << setw(10) << i - book_list.begin() + 1 << setw(20)  << i->name << setw(10) << i->version << setw(20) << i->auther << setw(20) << i->pubisher  << setw(20) << i->isbn << setw(20) << i->date << endl;
        cout << endl;
        return;
    }
    for(auto i = book_list.begin(); i != book_list.end(); i++)
        if(key == 1 && i->name == contant || key == 2 && i->version == contant || key == 3 && i->auther == contant || key == 4 && i->pubisher == contant || key == 5 && i->isbn == contant || key == 6 && i->date == contant)
            cout << setw(10) << i - book_list.begin() + 1 << setw(20)  << i->name << setw(10) << i->version << setw(20) << i->auther << setw(20) << i->pubisher  << setw(20) << i->isbn << setw(20) << i->date << endl;
        cout << endl;
}

void list_print()
{
    cout << "------------------------图书列表------------------------" << endl;
    cout << setw(10) << "编号" << setw(20) << "名称" << setw(10) << "版本" << setw(20) << "作者" << setw(20) << "出版社" << setw(20) << "ISBN" << setw(20) << "出版日期" << endl;
    for(auto i = book_list.begin(); i != book_list.end(); i++)
        cout << setw(10) << i - book_list.begin() + 1 << setw(20)  << i->name << setw(10) << i->version << setw(20) << i->auther << setw(20) << i->pubisher  << setw(20) << i->isbn << setw(20) << i->date << endl;
    cout << endl;
}

void file_load()
{
    ifstream lib("lib.txt");
    if(!lib)
    {
        cout << "文件读取失败" << endl << endl;
        lib.close();
        return;
    }
    while(!lib.eof())
    {
        book tmp;
        lib >> tmp.name >> tmp.version >> tmp.auther >> tmp.pubisher >> tmp.isbn >> tmp.date;
        if(tmp.name.size() != 0)
            book_list.push_back(tmp);
    }
    lib.close();
    cout << "文件已读取" << endl << endl;
}

void file_save()
{
    ofstream lib("lib.txt");
    if(!lib)
    {
        cout << "文件写入失败" << endl << endl;
        lib.close();
        return;
    }
    for(auto i = book_list.begin(); i != book_list.end(); i++)
        lib << i->name << " " << i->version << " " << i->auther << " " << i->pubisher << " " << i->isbn << " " << i->date << endl;
    lib.close();
    cout << "文件已保存" << endl << endl;
}
