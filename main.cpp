#include <iostream>
#include "User.h"
#include "Manager.h"
#include "DBUtil.h"
#include "Student.h"
#include "Book.h"
using namespace std;
/*
*								1.新书录入
                              2.图书查询
                              3.删除图书
                              4.图书列表
                              5.借阅记录
                              6.新增用户
                              7.用户列表
* 要增加3项功能
*借阅榜(用户那块第6个业务) 完成
* 8.丢失图书统计
* 9.借阅榜
* 10. 捐赠图书
* 11.捐赠图书榜
* 
*/

int main()
{
	string strUserName = "";
	string strUserPWD = "";
	bool bIsLogin = false;
	User user;
	cout << "                          请输入用户名：";
	cin >> strUserName;
	cout << endl;
	cout << "                          请输入密码：";
	cin >> strUserPWD;
	cout << endl;
	DBUtil dbUtil;
	dbUtil.OpenDB();
	user = dbUtil.ReadUser(strUserName, strUserPWD);
	while (user.m_nID == -1)
	{
		cout << "用户名或者密码错误，请重新输入,按任意键继续..." << endl;
		cin.get();
		cin.get();
		system("cls");
		cout << "                          请输入用户名：";
		cin >> strUserName;
		cout << endl;
		cout << "                          请输入密码：";
		cin >> strUserPWD;
		cout << endl;
		user = dbUtil.ReadUser(strUserName, strUserPWD);
	}
	if (user.m_nRole == 1)
	{
		Manager manager;
		manager.m_nID = user.m_nRole;
		manager.m_strName = user.m_strName;
		manager.m_nRole = user.m_nRole;
		int command = -1;		//选择命令
		bIsLogin = true;
		string strBookName = "";
		int nBookId = 0;
		while (bIsLogin)
		{
			system("cls");//清屏操作
			manager.ShowMenu();
			cout << "请选择命令：";
			cin >> command;
			switch (command)
			{
			case 1:
				//选择新增图书
				manager.AddBook();			
				break;
			case 2:
				cout << "请输入书名：";
				cin >> strBookName;
				manager.QueryBook(strBookName);
				break;
			case 3:
				cout << "请输入要删除图书的ID" << endl;
				cin >> nBookId;
				manager.DeleteBook(nBookId);
				break;
			case 4:
				manager.DisplayAllBook();
				break;
			case 5:
				manager.DiaplayAllBorrowRecord();
				break;
			case 6:
				manager.AddUser();
				break;
			case 7:
				manager.DisplayAllUser();
				break;
			case 0:
				//选择退出登录
				bIsLogin = false;
				break;
			default:
				break;
			}
		}
		cout << "您已退出登录，按任意键退出..." << endl;
	}
	else
	{
		Student student;
		student.m_nID = user.m_nRole;
		student.m_strName = user.m_strName;
		student.m_nRole = user.m_nRole;
		int command = -1;		//选择命令
		bIsLogin = true;
		string strBookName = "";
		int nBookId;
		while (bIsLogin)
		{
			system("cls");
			student.ShowMenu();
			cout << "请选择命令：";
			cin >> command;
			
		///	if (command ) {

			//}
				switch (command)
				{
				case 1:
					//选择查询图书
					cout << "请输入书名(结束查询请输入quit)：";
					cin >> strBookName;
					if (strBookName == "quit") {
						break;
					}
					student.QueryBook(strBookName);
					break;//如果成立就不往下走了
				case 2:
					//选择借书
					cout << "请输入图书ID:....(如果退出请输入-1)";
					cin >> nBookId;
					if (nBookId == -1) {
						break;
					}
					student.BorrowBook(nBookId);
					break;
				case 3:
					//归还图书
					student.ReturnBook();
					break;
				case 4:
					student.ShowMyBorrowRecord();
					break;
				case 5:
					student.RenewBook();
					break;
				case 6:
					student.HotListBook();//显示热榜图书
					break;
				case 0:
					//选择退出登录
					bIsLogin = false;
					exit(1);
					//break;
				default:
					break;
				}

		}
		cout << "您已退出登录，按任意键退出..." << endl;
	}
	cin.get();
	cin.get();
	return 0;
}