#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "USER.h"
#include <sys/types.h>
#include <errno.h>
#include "./jsoncpp-master/dist/json/json.h"
#include <thread>
// #include <future>

#define SERVERPORT 8888
#define MAX_BUFFER_SIZE 1024
#define LISTENFD_MAX 128

/*消息格式*/
typedef struct Message
{
	int CODE;			  // 操作码
	std::string fromwho;  // 谁发来的
	std::string towho;	  // 发给谁
	std::string timeis;	  // 发送的时间
	std::string password; // 发送者的输入的密码，特殊事件使用，如注册登录等
	std::string content;  // 消息内容
	std::string buffer;	  // 源消息
} Message;

class SOCKET
{
private:
// 服务器端操作码
#define REGIST 1001
#define LOGIN 1002
#define ADDFRIENDREQUEST 1003
#define SENDMSG 1004
#define DELFRIEND 1005
#define RETURNFRIENDREQUEST 1006

// 客户端操作码
#define TEST 2000
#define AGREEWITHFRIENDREQUEST 2001 // 同意好友请求
#define LOGINSUCCESFUL 2002			// 登录成功
#define LOGINERRORACCOUNTNUM 2003	// 登录失败账号错误
#define LOGINERRORPASSWD 2004		// 登录失败密码错误
#define REGISTERSUCCESFUL 2005		// 注册成功
#define UPDATEFRIEND 2006			// 更新好友信息
#define NEWFRIENDMESSAGE 1004		// 来自好友的新消息
#define SENDADDFRIENDSUCCES 2007	// 发送添加好友信息成功

	const char *code = "{\"CODE\":\"";
	const char *fromwho = "\",\"fromwho\":\"";
	const char *towho = "\",\"towho\":\"";
	const char *timeis = "\",\"timeis\":\"";
	const char *password = "\",\"password\":\"";
	const char *content = "\",\"content\":\"";
	const char *endis = "\"}\0";

private:
	USER user;
	int listenfd, connctfd, maxfd; // listenfd用于监听端口，connctfd用于连接，maxfd用于最大文件描述符
	char buffer[MAX_BUFFER_SIZE];
	struct sockaddr_in serveraddr, clientaddr;
	socklen_t clientlen;
	int optval = 1, nready;
	fd_set readset, allset; // 定义集合，readset用于监听所有请求，allset用于暂存备份

public:
	SOCKET();
	~SOCKET();
	virtual void Init();											// 虚函数，可重写为epoll，目前使用select
	void LISTEN();													// 监听
	bool Update(std::string id);									// 向客户端发送用户的所有信息
	bool ReturnFriendQuest();										// 返回是否通过好友请求
	void MessageAnalysis(Message, int, std::string);				// 消息处理
	bool SendMessage(std::string buffer, USER::USERINFO &userinfo); // 发送信息
	bool SendMessage(std::string buffer, int fd);
	bool ForwardMessage(Message AnalysisMsg, std::string SourceMsg, USER::USERINFO &userinfo); // 转发消息
	void StructureMsg(std::string &sendbuffer, std::string sendcode, std::string sendfromwho,
					  std::string sendtowho, std::string sendtimeis, std::string sendpassword,
					  std::string sendcontent); // 构造需要发送的消息
	Message readJsonFromMsg(std::string msg);	// 将json数据转为Message数据
	void test();								// 测试
	int CtorlUser(USER::USERINFO userinfo);		// 用户控制信息，将注册注销添加删除好友等需要改变UserList的功能整合，方便线程加锁
};
#endif
