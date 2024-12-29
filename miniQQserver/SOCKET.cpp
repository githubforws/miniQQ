/*
 * 非阻塞TCP server
 */
#include "./SOCKET.h"

SOCKET::SOCKET()
{
	// 初始化socket
	// listenfd = socket(AF_INET, SOCK_STREAM, 0); // ipv4,tcp
	// setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	// bzero(&serveraddr, sizeof(serveraddr));
	// serveraddr.sin_family = AF_INET;
	// serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	// serveraddr.sin_port = htons(SERVERPORT);
	// bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	// listen(listenfd, 128); // 设置监听队列长度为128

	// maxfd = listenfd;		   // 最大监听描述符
	// FD_ZERO(&allset);		   // 初始化select的readset
	// FD_SET(listenfd, &allset); // 将待监听的文件描述符加入监听集合
}

SOCKET::~SOCKET()
{
	close(listenfd);
}

/*
初始化套接字
*/
void SOCKET::Init()
{
	// 初始化socket
	listenfd = socket(AF_INET, SOCK_STREAM, 0); // ipv4,tcp
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	listen(listenfd, LISTENFD_MAX); // 设置监听队列长度为128

	maxfd = listenfd;		   // 最大监听描述符
	FD_ZERO(&allset);		   // 初始化select的readset
	FD_SET(listenfd, &allset); // 将待监听的文件描述符加入监听集合
}

/*
监听端口接收消息
*/
void SOCKET::LISTEN()
{
	while (true)
	{
		readset = allset;
		nready = select(maxfd + 1, &readset, NULL, NULL, 0); // 建立非阻塞型select监听，不设置超时时间，使用轮询
		if (nready < 0)
		{
			throw std::runtime_error("select error");
			exit(-1);
		}

		if (FD_ISSET(listenfd, &readset))
		{
			// listenfd文件描述符可读，说明有新的连接请求
			std::cout << "have new connect!" << std::endl;
			socklen_t clie_addr_len = sizeof(clientaddr);

			connctfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clie_addr_len); // 与客户端建立新连接
			// std::string userinfo_test = inet_ntoa(clientaddr.sin_addr);//获取到发送者ip，将ip保存用于后续发送消息
			// std::cout<<"来自ip:"<<userinfo_test<<"的连接"<<listenfd<<std::endl;
			FD_SET(connctfd, &allset); // 将新连接的文件描述符加入监听文件描述符集合

			maxfd = connctfd > maxfd ? connctfd : maxfd; // 更新最大文件描述符

			// 只有一个时必是连接请求，无需下一步
			if (nready == 1)
				continue;
		}
		for (int i = listenfd + 1; i <= maxfd; i++)
		{
			int n;
			// 遍历监控文件描述符集合检查是哪个文件描述符有数据就绪
			// 处理满足读事件的文件描述符fd
			std::cout << "heve new message:" << std::endl;
			if (FD_ISSET(i, &readset))
			{
				if ((n = read(i, buffer, sizeof(buffer))) == 0)
				{
					// 文件描述符i无数据，说明连接断开,关闭文件描述符i并从监控文件描述符集合中删除
					close(i);
					FD_CLR(i, &allset);
					// 更新Listenfd为0  LogOut(i);
					// 更新Online为false
					std::cout << "connect end!" << std::endl;
				}
				else if (n > 0)
				{
					// 文件描述符i有数据，处理数据
					// 处理数据
					std::cout << buffer << std::endl;
					// write(i, buffer, sizeof(buffer));
					// MessageAnalysis(readJsonFromMsg(buffer), i, buffer); // 这个i是该用户的唯一识别码，用于向指定用户发送数据
					Message AnalysisMsg = readJsonFromMsg(buffer);							  // 将json消息处理为Message格式方便使用
					std::thread thrd(&SOCKET::MessageAnalysis, this, AnalysisMsg, i, buffer); // 使用多线程对数据进行处理
					thrd.detach();															  // 设置不等待线程结束就返回
					memset(buffer, '\0', sizeof(buffer));
				}
				// else
				// {
				// 	std::cout << "else垃圾信息：" << buffer;
				// 	memset(buffer, '\0', sizeof(buffer));
				// }
			}
		}
	}
}

/*
消息处理
参数：处理后的消息 文件描述符（标识码）  源消息
根据操作码的不同进行处理：
注册REGIST
登录LOGIN
添加好友ADDFRIEND
转发消息SENDMSG
*/
void SOCKET::MessageAnalysis(Message AnalysisMsg, int i, std::string SourceMsg)
{
	USER::USERINFO userinfo;
	// Message error_msg;
	userinfo.Listenfd = i;	// 用户链接服务器的标识码，必须实时更新
	std::string sendbuffer; // 将要发送的数据
	// 将发送的控制码全都得换成客户端的控制码

	std::cout << AnalysisMsg.CODE << "对消息进行处理" << std::endl;

	switch (AnalysisMsg.CODE)
	{
	case REGIST:
	{
		/*注册账号
		  发过来的昵称（从content中获取），密码，发送回一个账号
		*/
		std::cout << "注册消息:" << std::endl;
		std::cout << AnalysisMsg.CODE << "  " << AnalysisMsg.content << "  " << AnalysisMsg.password << std::endl;
		userinfo.name = AnalysisMsg.content;	  // 用户注册时的昵称存放在消息体中
		userinfo.PassWord = AnalysisMsg.password; // 用户注册的密码

		if (user.AddUser(userinfo))
		{
			std::cout << "注册成功，返回ID账号：" << userinfo.ID << std::endl;
			StructureMsg(sendbuffer, std::to_string(REGISTERSUCCESFUL), "", "", "", "", userinfo.ID); // 构造要发送的消息
			SendMessage(sendbuffer, userinfo);														  // 发送回账号ID,并将该账号ID与listenfd绑定
		}
		else
		{
			std::cout << "注册失败，返回错误信息" << std::endl;
			StructureMsg(sendbuffer, "", "", "", "", "", "账号上限，注册失败");
			SendMessage(sendbuffer, userinfo);
		}
		break;
	}
	case LOGIN:
	{
		/*登录帐号
		接受id密码，验证返回，返回1帐号错误，返回2密码错误
		*/
		std::cout << "登录消息:" << std::endl;
		userinfo.ID = AnalysisMsg.fromwho;
		userinfo.PassWord = AnalysisMsg.password;
		userinfo.Listenfd = i;

		switch (user.Login(userinfo))
		{
		case 0:
		{
			std::cout << "用户：" << userinfo.ID << "登录成功" << std::endl;
			StructureMsg(sendbuffer, std::to_string(LOGINSUCCESFUL), "", "", "", "", user.GetUserName(userinfo.ID));
			// 向所有朋友更新在线状态
			// 检查是否有离线消息如有则发送离线消息

			SendMessage(sendbuffer, userinfo); // 发送登录成功消息
			std::cout << "用户" << userinfo.ID << "的fld:" << userinfo.Listenfd << std::endl;

			Update(userinfo.ID); // 更新其好友列表
			break;
		}
		case 1:
		{
			std::cout << "用户：" << userinfo.ID << "登录失败，账号不存在" << std::endl;
			StructureMsg(sendbuffer, std::to_string(LOGINERRORACCOUNTNUM), "", "", "", "", "");
			SendMessage(sendbuffer, userinfo);
			break;
		}
		case 2:
		{
			std::cout << "用户：" << userinfo.ID << "登录失败，密码错误" << std::endl;
			StructureMsg(sendbuffer, std::to_string(LOGINERRORPASSWD), "", "", "", "", "");
			SendMessage(sendbuffer, userinfo);
			break;
		}
		}

		break;
	}
	case ADDFRIENDREQUEST:
	{
		/*添加好友
			消息格式：
			ADDFRIEND 用户id 新好友id -- -- 内容可以为请求加好友的验证信息
		*/
		int newfriend = user.AddFriendRequest(AnalysisMsg.fromwho, AnalysisMsg.towho);
		std::cout << "AddFriendRequest返回" << newfriend << std::endl;
		if (-2 == newfriend)
		{
			std::cout << "添加好友失败，没有那个用户" << std::endl;
			StructureMsg(sendbuffer, "0", "", "", "", "", "没有搜索到相关用户");
			SendMessage(sendbuffer, userinfo);
		}
		else if (-1 == newfriend)
		{
			// 用户离线，将消息加入离线消息队列
			StructureMsg(sendbuffer, "1", "", "", "", "", "已发送好友申请");
			SendMessage(sendbuffer, userinfo);
			std::cout << "已将" << AnalysisMsg.towho << "添加好友消息加入离线消息队列" << std::endl;
		}
		else if (-4 == newfriend)
		{
			StructureMsg(sendbuffer, "1", "", "", "", "", "已有该好友");
			SendMessage(sendbuffer, userinfo);
			std::cout << "已有" << AnalysisMsg.towho << "好友" << std::endl;
		}
		else
		{
			StructureMsg(sendbuffer, "1", "", "", "", "", "已发送好友申请");
			SendMessage(sendbuffer, userinfo);
			//		    请求添加好友控制码，谁请求的加好友        向谁请求加好友               请求加好友的附加信息
			// userinfo.Listenfd = newfriend; // 向被请求用户发消息
			StructureMsg(sendbuffer, std::to_string(ADDFRIENDREQUEST), AnalysisMsg.fromwho, AnalysisMsg.towho, "", "", AnalysisMsg.content);
			SendMessage(sendbuffer, newfriend);
			std::cout << "已向" << AnalysisMsg.towho << "发送添加好友消息" << std::endl;
		}
		break;
	}
	case DELFRIEND:
	{
		break;
	}
	case SENDMSG:
	{
		std::cout << "sendmsg" << std::endl;
		/*将用户a的消息转发给用户b*/

		StructureMsg(sendbuffer, std::to_string(NEWFRIENDMESSAGE), AnalysisMsg.fromwho, AnalysisMsg.towho, "", "", AnalysisMsg.content);
		// std::cout << "ceshi gei 100000 huixin:" << sendbuffer << std::endl;
		userinfo.ID = AnalysisMsg.towho;
		userinfo.Listenfd = user.FindUser(AnalysisMsg.towho);
		SendMessage(sendbuffer, userinfo);

		std::cout << "用户：" << AnalysisMsg.fromwho << "向用户" << AnalysisMsg.towho << "发送消息" << std::endl;
		// ForwardMessage(AnalysisMsg, SourceMsg, userinfo);
		break;
	}
	case RETURNFRIENDREQUEST:
	{
		int request = atoi(AnalysisMsg.content.c_str());
		if (request)
		{
			std::cout << "用户" << AnalysisMsg.fromwho << "同意了用户" << AnalysisMsg.towho << "的好友申请" << std::endl;
			user.AddFriend(AnalysisMsg.fromwho, AnalysisMsg.towho);
			user.AddFriend(AnalysisMsg.towho, AnalysisMsg.fromwho); // 将两者互添为好友
			Update(AnalysisMsg.fromwho);
			Update(AnalysisMsg.towho); // 向两者发送更新后的好友信息
		}
		else
		{
			std::cout << "用户" << AnalysisMsg.fromwho << "拒绝了用户" << AnalysisMsg.towho << "的好友申请" << std::endl;
			// 不用做任何处理
		}
		break;
	}

	default:
		break;
	}
	sendbuffer.clear();
}

/*
返回值 成功返回ture 失败返回false
参数 构造好的消息 用户信息
向指定用户发送消息
*/
bool SOCKET::SendMessage(std::string buffer, USER::USERINFO &userinfo)
{
	std::cout << "要发送的消息是：" << buffer << std::endl;
	if (write(userinfo.Listenfd, buffer.c_str(), buffer.length()))
	{
		std::cout << "向" << userinfo.ID << "  " << userinfo.Listenfd << "发送消息成功" << std::endl;
		return true;
	}
	std::cout << "向" << userinfo.ID << "发送消息失败" << std::endl;
	return false;
}
/// @brief 向指定fd发送消息，一般用于服务器发送消息
/// @param buffer 要发送的消息
/// @param fd 用户fd
/// @return true
bool SOCKET::SendMessage(std::string buffer, int fd)
{
	if (write(fd, buffer.c_str(), buffer.length()))
	{
		std::cout << "向" << fd << "发送消息成功" << std::endl;
		return true;
	}
	std::cout << "向" << fd << "发送消息失败" << std::endl;
	return false;
}

/*
转发消息，将用户a的消息转发给用户b
返回值 成功返回ture 失败返回false
参数 源消息 用户信息
*/
bool SOCKET::ForwardMessage(Message AnalysisMsg, std::string SourceMsg, USER::USERINFO &userinfo)
{
	int friendfd; // 好友Listenfd
	// 判断是否有该好友有则返回好友Listenfd
	friendfd = user.FindUserFriend(AnalysisMsg.towho, userinfo);
	std::cout << "friendfd返回值为：" << friendfd << std::endl;
	// 朋友是否在线
	if (friendfd == -1)
	{
		// 离线则将消息放入离线队列
		std::cout << "好友" << AnalysisMsg.towho << "离线，将消息放入用户离线消息列表" << std::endl;
	}
	else if (friendfd == -2 || friendfd == -3)
	{
		// 不存在好友，返回错误信息
		std::string sendbuffer;
		StructureMsg(sendbuffer, "", "", "", "", "", "不存在该好友");
		SendMessage(sendbuffer, userinfo);
	}
	else
	{
		// 在线则获取Listenfd，转发消息
		std::cout << "向好友" << AnalysisMsg.towho << "转发消息成功" << std::endl;
		std::cout << "发送了：" << write(friendfd, SourceMsg.c_str(), SourceMsg.length()) << std::endl;
		;
		return true;
	}
	std::cout << "向好友" << AnalysisMsg.towho << "转发消息失败" << std::endl;
	return false;
}

/*
将json数据解析为Message数据
返回一个解析后的Message
交给消息分析函数根据操作码处理
*/
Message SOCKET::readJsonFromMsg(std::string msg)
{
	Json::Reader reader;
	Message Msg;
	Json::Value root;
	std::cout << "json 读取数据" << std::endl;
	std::cout << "msg :" << msg << std::endl;
	if (msg[0] != '{')
	{
		std::cout << "msg[0]!={";
		return Msg;
	}
	// 从字符串中读取数据
	if (reader.parse(msg, root))
	{
		std::string a = root["CODE"].asString();
		Msg.CODE = atoi(a.c_str());
		// std::cout << "code" << Msg.CODE << std::endl;
		Msg.fromwho = root["fromwho"].asString();
		// std::cout << "fromwho" << Msg.fromwho << std::endl;
		Msg.towho = root["towho"].asString();
		// std::cout << "towho" << Msg.towho << std::endl;
		Msg.content = root["content"].asString();
		// std::cout << "content" << Msg.content << std::endl;
		Msg.timeis = root["timeis"].asString();
		// std::cout << "timeis" << Msg.timeis << std::endl;
		Msg.password = root["password"].asString();
		// std::cout << "password" << Msg.password << std::endl;
	}
	Msg.buffer = msg;
	// std::cout << "json读取的数据为：" << Msg.CODE;
	// std::cout << Msg.fromwho << Msg.towho << Msg.timeis << Msg.password << Msg.content;
	std::cout << "json 读取数据完毕" << std::endl;
	return Msg;
}

/*
构造要发送的字符串
无返回值
参数 要发送的字符串 剩余的为消息的各个内容
*/
void SOCKET::StructureMsg(std::string &sendbuffer, std::string sendcode, std::string sendfromwho, std::string sendtowho, std::string sendtimeis, std::string sendpassword, std::string sendcontent)
{
	sendbuffer = code + sendcode + fromwho + sendfromwho + towho + sendtowho + timeis + sendtimeis + password + sendpassword + content + sendcontent + endis;
}

void SOCKET::test()
{
}

/// @brief 向指定用户更新好友信息
/// @param id 用户
/// @return true
bool SOCKET::Update(std::string id)
{
	std::string friendid = user.GetFriend(id);
	std::string sendbuffer;
	int fd = user.FindUser(id);
	// 构建更新好友列表的消息，控制码要替换成客户端的控制码！！！
	// 用户不在线不用发送，登录时会自动更新
	if (fd > 0)
	{
		StructureMsg(sendbuffer, std::to_string(UPDATEFRIEND), "", id, "", "", friendid);
		SendMessage(sendbuffer, fd);
		std::cout << "已向" << id << "发送最新好友信息" << std::endl;
	}
	return true;
}
