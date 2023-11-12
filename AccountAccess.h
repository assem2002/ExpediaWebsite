#ifndef ACCOUNTACCESS_H_INCLUDED
#define ACCOUNTACCESS_H_INCLUDED

void add_card(user* currentUser){
    while(true){
    std::cout<<"\n\n1)PayPal\n2)Stripe\n3)Square\n Choose A Card Provider: ";
    int cardProvider;
    std::cin>>cardProvider;
    std::vector<std::string> cardTypes{"Debit Card","Credit Card","Prepaid Card"};
    for (int card = 1 ; card<=3 ; card++) std::cout<<card<<") "<<cardTypes[card-1]<<std::endl;
    std::cout<<"Choose a Card Type 1-3 :";
    int cardType;
    std::cin>>cardType;
    std::cout<<"\nEnter Your name:";
    std::string name;
    std::cin. ignore(1000,'\n');
    std::getline(std::cin,name);
    std::cout<<"Enter Your Address:";
    std::string address;
    std::getline(std::cin,address);
    std::cout<<"Enter Your ID  :";
    std::string id;
    std::getline(std::cin,id);
    std::cout<<"Enter Your ExpiryDate : ";
    std::string expiryDate;
    std::getline(std::cin,expiryDate);
    std::cout<<"Enter Your CCV : ";
    int ccv;
    std::cin>>ccv;
    std::cin. ignore(1000,'\n');
    currentUser->allCards.push_back({name,address,id,expiryDate,cardTypes[cardType-1],ccv,cardProvider});
    std::cout<<"\n\n Would you like to add another card?";
    std::cout<<"\n1)Yes\n2)No";
    std::cout<<"\nEnter Choice 1-2:";
    std::string yesNo;
    std::getline(std::cin,yesNo);
    if (yesNo == "2") break;

    }
}
class accountAccess{
private:
    std::pair<user*,bool> userFinder(std::string userName, std::string password,bool signUpMode){ //signUpMode = 1 if signup,0 if logInMode
        for (user &singleUser : allUsers){
            if (singleUser.getUserName() == userName && ((singleUser.getPassowrd() == password &&!signUpMode) || signUpMode)){
                return std::make_pair(&singleUser,1);
            }
        }
        user emptyUser;
        return std::make_pair(&emptyUser,0);
    }

    std::pair<user*,bool> login(){
        std::string userNameTemp;
        std::string passwordTemp;
        while(true){
            std::cout<<"\nEnter Your UserName : ";
            std::getline(std::cin, userNameTemp);
            std::cout<<"Enter Your Password : ";
            std::getline(std::cin, passwordTemp);
            user* userTemp;
            bool foundTemp;
            std::tie(userTemp,foundTemp)=  userFinder(userNameTemp,passwordTemp,0);
            if (!foundTemp){
                std::cout<<"\n\nUser Does Not Exist !";
                std::string choiceTemp;
                while(true){
                    std::cout<<"\n1)Try Again!";
                    std::cout<<"\n2)Try To SignUp";
                    std::cout<<"\nEnter Your Choice 1-2 :";
                    std::getline(std::cin,choiceTemp);
                    if(choiceTemp=="1" || choiceTemp == "2") break;
                }
                if (choiceTemp == "2")
                    return std::make_pair(userTemp,0);
            }
            else
                return std::make_pair(userTemp,1);



        }

    }
    std::pair<user*,bool>signUp(){
        std::string userNameTemp;
        std::string emailTemp;
        std::string nameTemp;
        std::string passwordTemp;
        while(true){
            std::cout<<"\n\nEnter Your UserName : ";
            std::getline(std::cin, userNameTemp);
            std::cout<<"Enter Your Password : ";
            std::getline(std::cin, passwordTemp);
            std::cout<<"Enter Your Name : ";
            std::getline(std::cin, nameTemp);
            std::cout<<"Enter Your Email : ";
            std::getline(std::cin,emailTemp);
            user* userTemp;
            bool found;
            std::tie(userTemp,found) = userFinder(userNameTemp,passwordTemp,1);

            if (found){
                std::cout<<"\n\nUser Exist Before!";
                std::string choiceTemp;
                while(true){
                    std::cout<<"\n1)Try Again!\n2)Try To Log In\nEnter Your Choice 1-2: ";
                    std::getline(std::cin,choiceTemp);
                    if(choiceTemp=="1" ||choiceTemp == "2") break;
                }
                if(choiceTemp =="2") return std::make_pair(userTemp,0);
            }

            else if(!found){
                user newUser(emailTemp,nameTemp,passwordTemp,userNameTemp);
                std::cout<<"\n\nWould You Like To Add a Card?";
                std::string choiceTemp;
                while(true){ //for the sake of wrong Entry.
                    std::cout<<"\n1)Yes\n2)No\nEnter Your Choice 1-2: ";
                    std::getline(std::cin,choiceTemp);
                    if(choiceTemp=="1" ||choiceTemp == "2") break;
                }
                if (choiceTemp =="1"){
                    add_card(&newUser);
                }
                allUsers.push_back(newUser);
                return std::make_pair(&allUsers.back(),1);
            }



        }



    }
public:

    user* start(){
        while(true){
            std::cout<<"\n\n1)Login";
            std::cout<<"\n2)SignUp";
            std::cout<<"\nEnter Your Choice 1-2 :";
            std::string choiceTemp;
            std::getline(std::cin,choiceTemp);
            user* whoGotIn;
            bool validUser;
            if (choiceTemp =="1"){
                std::tie(whoGotIn,validUser) = login();
                if (validUser) return whoGotIn; // if the user exist before, finish the function.
            }
            else if (choiceTemp == "2"){
                std::tie(whoGotIn, validUser) = signUp();
                if (validUser) return whoGotIn;
            }
            else
                std::cout<<"\nInvalid Choice !";
        }
    }

};

#endif // ACCOUNTACCESS_H_INCLUDED
