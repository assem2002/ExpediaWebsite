#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED


class user{
private:
    std::string email;
    std::string name;
    std::string password;
    std::string userName;
public:
    std::vector<userInfoCard> allCards;
    std::vector<std::vector<reservation*>> myItineraries;
    user(){}
    user(std::string email ,std::string name, std::string password, std::string userName):
        email(email),name(name),password(password),userName(userName){}
    std::string getUserName(){
        return userName;
    }
    std::string getPassowrd(){
        return password;
    }
    void viewProfile(){
        std::cout<<"\n\nName: "<<name;
        std::cout<<"\nEmail : "<<email;
        std::cout<<"\nUserName : "<<userName;
    }
};

std::vector<user> allUsers;


#endif // USER_H_INCLUDED
