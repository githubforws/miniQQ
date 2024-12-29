#include "USER.h"
#include <unistd.h>
#include <fstream>
#include <random>
#include <algorithm>

/*
从用户文件里将所有用户的所有信息读入
*/
USER::USER()
{
	std::ifstream file;
	std::ifstream friendfile;
	USERINFO userinfo;

	file.open("./USERADD/USERADD.txt", std::ios::out); // 将USERADD.txt中的全部用户信息读入USERLIST
	std::string bufferid;							   // 用户账号
	std::string buffername;							   // 用户姓名
	std::string bufferpassword;						   // 用户密码
	std::string friendid;							   // 好友账号
	std::string filename;
	char buf[USERIDMAX]; // 缓冲区，限制账号id，昵称，密码的最大长度20

	/*
	 *多线程遍历读入
	 *文件格式为一行id，一行姓名，一行密码，以此类推
	 */
	while (file.getline(buf, USERIDMAX))
	{
		bufferid = buf;
		userinfo.ID = bufferid;
		file.getline(buf, USERIDMAX);
		buffername = buf;
		userinfo.name = buffername;
		file.getline(buf, USERIDMAX);
		bufferpassword = buf;
		userinfo.PassWord = bufferpassword;
		bufferid.clear();
		buffername.clear();
		bufferpassword.clear();

		filename = "./USERADD/";
		std::string IDcstr(userinfo.ID.c_str());
		// std::string IDis(IDcstr,7);
		// filename += IDis;
		filename += IDcstr;
		friendfile.open(filename.c_str(), std::ios::out); // open the friendfile read friend`s info
		std::cout << "friendfilename:" << filename << std::endl;
		while (friendfile.getline(buf, USERIDMAX))
		{
			friendid = buf;
			userinfo.Friends.push_back(friendid);
			friendid.clear();
		}
		friendfile.close();

		UserList.push_back(userinfo);
		userinfo.name.clear();
		userinfo.ID.clear();
		userinfo.PassWord.clear();
		userinfo.Friends.erase(userinfo.Friends.begin(), userinfo.Friends.end());
	}
	BEGIN = atoi(UserList.begin()->ID.c_str());
	END = atoi((UserList.end() - 1)->ID.c_str()); // 更新用户列表
	file.close();
	test();
}

/*
将所有用户信息写会用户文件里
*/
USER::~USER()
{
}

/*
打印所有用户信息
*/
void USER::test()
{
	for (std::vector<USERINFO>::iterator it = UserList.begin(); it != UserList.end(); ++it)
	{
		std::cout << "ID是：" << it->ID << "  name是：" << it->name << "  密码是：" << it->PassWord << std::endl;
		for (std::vector<std::string>::iterator it2 = it->Friends.begin(); it2 != it->Friends.end(); ++it2)
		{
			std::cout << "朋友有：" << *it2 << std::endl;
		}
	}
}

/*
注册用户
参数  USERINFO
返回值 false 失败  true 成功
*/
bool USER::AddUser(USERINFO &userinfo)
{
	/*
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(100000,999999);

	int random_id = dist(gen);
	std::cout<<"测试：生成的随机id为："<<random_id<<std::endl;
	random_id = 100000;//test
	userinfo.ID = random_id;
	std::vector<USERINFO>::iterator it;
	while((it = std::find(UserList.begin(),UserList.end(),userinfo.ID)) != UserList.end()){
		std::cout<<"该账号已存在:"<<userinfo.ID<<std::endl;
	}
	不使用随机生成账号，随用户数增多，效率降低
	*/
	mtx.lock();
	std::cout << "开始注册" << std::endl;
	auto end = UserList.end() - 1;
	std::cout << "最后一个账号ID为：" << end->ID << std::endl;
	if (atoi(end->ID.c_str()) > 999999)
		return false;

	userinfo.ID = std::to_string(atoi(end->ID.c_str()) + 1);
	std::cout << "新添加的账号ID为：" << userinfo.ID << std::endl;
	;
	UserList.push_back(userinfo);
	test();
	BEGIN = atoi(UserList.begin()->ID.c_str());
	END = atoi((UserList.end() - 1)->ID.c_str()); // 更新用户列表
	std::cout << "新用户注册后BEGIN" << BEGIN << "  " << END << std::endl;
	mtx.unlock();
	return true;
}

/*
用户注销，暂时不写
*/
bool USER::DelUser()
{
	BEGIN = atoi(UserList.begin()->ID.c_str());
	END = atoi((UserList.end() - 1)->ID.c_str()); // 更新用户列表
	// 非必要功能，暂时不写
	return true;
}

/*
用户修改信息暂时不写
*/
bool SetInfo()
{
	return true;
}

/*
登录验证
返回值：0成功  1账号不存在  2密码错误
参数USER::USERINFO用户信息
？？？在注册时会对UserList加锁，是否会影响到登录验证？？？
*/
int USER::Login(USERINFO &userinfo)
{
	std::cout << "Login验证" << std::endl;
	// UserList[atoi(userinfo.ID.c_str())-100000];
	int id = atoi(userinfo.ID.c_str()); // 获取用户登录的id
	std::cout << "登录id=" << id << std::endl;

	std::cout << "begin:" << BEGIN << "  end:" << END << std::endl;

	if (!((id >= BEGIN) && (id <= END)))
	{
		std::cout << "账号不存在：" << std::endl;
		return 1; // 账号不存在，超过用户列表范围
	}
	if (UserList[id - BEGIN].PassWord.compare(userinfo.PassWord))
	{
		std::cout << "密码错误" << UserList[id - BEGIN].PassWord << "!=" << userinfo.PassWord << std::endl;
		return 2; // 密码错误
	}
	std::cout << "登录成功" << std::endl;
	UserList[id - BEGIN].Listenfd = userinfo.Listenfd; // 保存用户Listenfd
	return 0;										   // 登录成功
}

/*
找到好友Listenfd并返回
返回值int（成功Listenfd  -1好友不在线  -2不存在好友）
参数 好友id 用户信息
*/
int USER::FindUserFriend(std::string friendid, USERINFO &userinfo)
{
	int id = atoi(userinfo.ID.c_str()); // 获取用户的id

	int fid = atoi(friendid.c_str());
	// 遍历用户的好友列表
	// 后续优化，在添加好友是对好友id进行排序，直接获取好友Listenfd
	std::vector<std::string>::iterator it;
	std::cout << "查找的账号" << fid << std::endl;
	if (!((fid >= BEGIN) && (fid <= END)))
	{
		std::cout << "好友账号错误" << std::endl;
		return -2; // 账号不存在，超过用户列表范围
	}
	std::cout << "测试=" << id - BEGIN << "  end-begin=" << UserList[id - BEGIN].Friends.end() - UserList[id - BEGIN].Friends.begin() << std::endl;
	for (it = UserList[id - BEGIN].Friends.begin(); it < UserList[id - BEGIN].Friends.end(); it++)
	{
		if (!friendid.compare(*it))
		{
			std::cout << "UserList[fid - begin].Listenfd:" << UserList[fid - BEGIN].Listenfd << std::endl;
			return UserList[fid - BEGIN].Listenfd; // 找到好友Listenfd并返回
		}
	}
	std::cout << "FindUserFriend返回-3" << std::endl;
	return -3; // 不存在该好友
}

/*
添加好友：向用户发送一个好友请求（用户处理好友请求后会向该用户发送一条消息）
返回值 //返回-2没有这个账号  返回-1用户不在线  返回-4已有该好友 返回其他值为用户listenfd
要添加的新好友用户id，用户id
*/
int USER::AddFriendRequest(std::string id, std::string newfriendid)
{
	std::cout << "添加好友信息已处理" << std::endl; // 这里是直接添加好友还是发送验证信息？

	/*
	时间不够就直接加
	向被添加者发送一条验证消息，内容为为请求好友信息，为请求者的id，可增加消息
	*/
	USERINFO user;
	user.ID = id;
	if (-3 == FindUserFriend(newfriendid, user))
	{
		return FindUser(newfriendid);
	}
	std::cout << "AddFriendRequest返回-4" << std::endl;
	return -4; // 没有该好友才能添加好友
}

/*
返回-2没有这个账号  返回-1用户不在线  返回其他值为用户listenfd
*/
int USER::FindUser(std::string id)
{
	int userid = atoi(id.c_str());
	std::vector<USERINFO>::iterator it;
	if (!((userid >= BEGIN) && (userid <= END)))
	{
		std::cout << "账号不存在，超出用户列表范围" << std::endl;
		return -2; // 账号不存在，超过用户列表范围
	}
	for (it = UserList.begin(); it != UserList.end(); it++)
	{
		std::cout << "查询的id：" << id << "，比较的id" << it->ID << std::endl;
		if (!id.compare(it->ID))
			return it->Listenfd;
	}
	std::cout << "FindUser返回-2" << std::endl;
	return -2;
}

/// @brief *为用户1添加好友用户2
/// @param id1 用户1
/// @param id2 用户2
/// @return true成功
bool USER::AddFriend(std::string id1, std::string id2)
{
	int id = atoi(id1.c_str());
	UserList[id - BEGIN].Friends.push_back(id2);
	std::cout << "已向" << id1 << "添加好友" << id2 << std::endl;
	test();
	return true;
}

/// @brief 获取用户的所有好友id
/// @param id 用户
/// @return 所有好友id的一个字符串，id之间用\n间隔
std::string USER::GetFriend(std::string id)
{
	std::string friendid;
	int userid = atoi(id.c_str());
	for (std::vector<std::string>::iterator it = UserList[userid - BEGIN].Friends.begin(); it != UserList[userid - BEGIN].Friends.end(); ++it)
	{
		friendid += *it;
		friendid += '/';
		std::string tmp = *it;
		int fid = atoi(tmp.c_str());
		friendid += UserList[fid - BEGIN].name;
		friendid += '\n';
	}
	std::cout << "用户：" << id << "的所有好友：" << friendid << std::endl;
	return friendid;
}

std::string USER::GetUserName(std::string id)
{
	int userid = atoi(id.c_str());
	return UserList[userid - BEGIN].name;
}