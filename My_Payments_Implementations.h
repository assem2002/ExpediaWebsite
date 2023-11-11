#ifndef MY_PAYMENTS_IMPLEMENTATIONS_H_INCLUDED
#define MY_PAYMENTS_IMPLEMENTATIONS_H_INCLUDED
#include "expedia_payments_api.h"
class userInfoCard;


class Ipayment{
public:
    virtual bool withDraw(const userInfoCard &cardInfo,double moneyAmount) =0 ;
    virtual ~Ipayment(){};

};

Ipayment* cardFactory(int cardID);

class userInfoCard{
private:
public:
    //All data members here should be private, but i made them public for the sake of simplicity & they would be trivial getters and setters.
    std::string name;
    std::string address;
    std::string id;
    std::string expiryDate;
    std::string cardType;
    int ccv;
    int IpaymentFactoryId; // id for calling the card the upCasted pointer. (1->Paypal , 2->stripe , 3->Square)

    userInfoCard(std::string name,std::string address,std::string id,std::string expiryDate,std::string cardType,int ccv,int IpaymentFactoryId):
        name(name),address(address),id(id),expiryDate(expiryDate),cardType(cardType),ccv(ccv),IpaymentFactoryId(IpaymentFactoryId){}
    bool pay(double money){
        return cardFactory(IpaymentFactoryId)->withDraw(*this,money);

    }

    void showCardInfo(){
        std::cout<<"["<<cardType<<"]"<<" Owner :"<<name<<" "<<expiryDate;
    }



};

class paypalAPI_imp : public Ipayment{
private:

public:
    virtual bool withDraw(const userInfoCard &cardInfo,double moneyAmount){
        PayPalCreditCard paypalObj{};
        paypalObj.name = cardInfo.name;
        paypalObj.address = cardInfo.address;
        paypalObj.expiry_date = cardInfo.expiryDate;
        paypalObj.id = cardInfo.id;
        paypalObj.ccv = cardInfo.ccv;
        PayPalOnlinePaymentAPI API_instance;
        API_instance.SetCardInfo(&paypalObj);
        return API_instance.MakePayment(moneyAmount);

    }

};

class stripeAPI_imp : public Ipayment{
public:
    virtual bool withDraw(const userInfoCard &cardInfo,double moneyAmount){
        StripeCardInfo stripeInfo_firstPart;
        stripeInfo_firstPart.expiry_date = cardInfo.expiryDate;
        stripeInfo_firstPart.id = cardInfo.id;

        StripeUserInfo stripeInfo_secondPart;
        stripeInfo_secondPart.address =cardInfo.address;
        stripeInfo_secondPart.name = cardInfo.name;

        StripePaymentAPI API_instance;
        return API_instance.WithDrawMoney(stripeInfo_secondPart,stripeInfo_firstPart,moneyAmount);
    }
};

class squareAPI_imp :public Ipayment{
public:
    virtual bool withDraw(const userInfoCard &cardInfo,double moneyAmount){
        json::JSON objOfJson;
        objOfJson["name"]= cardInfo.name;
        objOfJson["address"] = cardInfo.address;
        objOfJson["id"] = cardInfo.id;
        objOfJson["expiryDate"] = cardInfo.expiryDate;
        objOfJson["CCV"] = cardInfo.ccv;
        std::string jsonToString =objOfJson.ToString();
        SquarePaymentAPI API_instance;
        return API_instance.WithDrawMoney(jsonToString);


    }

};

// A vector holds instances of the card implementation
// indexes of the instance is equivalent to the id saved in the "useInfoCard" object.
paypalAPI_imp card1;
stripeAPI_imp card2;
squareAPI_imp card3;
std::vector<Ipayment*> allcardsAPIs {&card1,&card2,&card3};

Ipayment* cardFactory(int cardID){
    switch(cardID){
        case 1:
            return allcardsAPIs[0];
        case 2:
            return allcardsAPIs[1];
        case 3:
            return allcardsAPIs[2];
        default:
            std::cout<<"Something Wrong happened!";
            exit(0);
    }

};

#endif // MY_PAYMENTS_IMPLEMENTATIONS_H_INCLUDED
