#ifndef USERSINGLETON_H
#define USERSINGLETON_H
#include <QString>

class UserSingleton{
public:
    static UserSingleton& getInstance(){
        static UserSingleton instance;
        return instance;
    };
    int getLoginId() const{
        return loginId;
    };
    void setLoginId(const int id){
        loginId = id;
    };
private:
    UserSingleton(){}
    UserSingleton(const UserSingleton&)=delete;
    UserSingleton& operator=(const UserSingleton&)=delete;
    int loginId;
};



#endif // USERSINGLETON_H
