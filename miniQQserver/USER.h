#include <iostream>
#include <vector>
#include <mutex>
// #include <atomic>

class USER
{
public:
    struct USERINFO
    {
        std::string name;
        std::string ID;
        std::string PassWord;
        std::string IP;
        int Listenfd = -1; // 文件描述符，当文件描述符为-1时说明用户不在线
        std::vector<std::string> Friends;
    };

private:
#define USERIDMAX 20
    std::vector<USERINFO> UserList;
    std::mutex mtx;
    int BEGIN;
    int END;
    // std::vector<USERINFO> RegistList;
    // std::atomic<std::vector<USERINFO>> UserListtest;//不是TriviallyCopyable（可平凡复制）不能使用atomic锁，只能去add或del处手动加锁

public:
    USER();
    ~USER();
    void test();
    bool AddUser(USERINFO &userinfo); // 添加用户（注册）
    bool DelUser();                   // 删除用户（注销）
    bool SetInfo();
    int FindUser(std::string id);                                 // 查找用户
    int FindUserFriend(std::string friendid, USERINFO &userinfo); // 查找用户是否有该好友
    int AddFriendRequest(std::string, std::string);               // 添加好友请求
    bool AddFriend(std::string id1, std::string id2);             // 为id1添加好友id2
    bool DelFriend();                                             // 删除好友
    int Login(USERINFO &userinfo);                                // 账号登录
    std::string GetUserName(std::string id);                      // 获取用户姓名
    // bool AgreeFriendRequest();                                    // 同意好友请求
    std::string GetFriend(std::string id); // 获取用户的所有好友id
};
