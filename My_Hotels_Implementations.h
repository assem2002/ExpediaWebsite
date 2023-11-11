#ifndef MY_HOTELS_IMPLEMENTATIONS_H_INCLUDED
#define MY_HOTELS_IMPLEMENTATIONS_H_INCLUDED
#include "expedia_hotels_api.h"

class hotelCard;
class IHotel;
//Object for holding the data returned from the various APIs to be generic for my own function of querying a room.
class hotelsRoomsAvailable{
public:
    std::string hotelName;
    std::string roomType;
    double pricePerNight;
    std::string dateFrom;
    std::string dateTo;
    IHotel* iHotelPtr;
    void printHotelInfo(){
        std::cout<<"HotelName : "<<hotelName<<" | roomType :"<<roomType<<" |Departure Date :"<<dateFrom<<" |Arrival Date :"<<dateTo<<" |Price Per Night : "<<pricePerNight<<std::endl;
    }
};


//Hotel Interface for different hotel implementation.
class IHotel{
private:
public:
    virtual std::vector<hotelsRoomsAvailable> queryRooms(hotelCard& queryInfo) = 0;
    virtual bool reserve(hotelCard* dataToreserveUpon) =0 ;

};






//A class // Object to be Generic, so i can change the data entered from the user to the flight interface.
// i consider to be like a form that you fill when you search for a flight and then it's passed to the various functions as it's extremely generic.'s is considered to be a generic card which holds all query information and it's used also for making a reservation.
class hotelCard:public reservation{
private:
    std::string dateFrom;
    std::string dateTo;
    std::string country;
    std::string city;
    int adults;
    int children;
    int neededRooms;
    double pricePerNight;
    int nights;
    IHotel* IHotelPtr; //holds a pointer to specific hotel implementation to be used later in reservation
    std::string hotelName;

public:
    hotelCard(std::string dateFrom,std::string dateTo,std::string country,std::string city,int adults, int children ,int neededRooms , int nights):
    dateFrom(dateFrom),dateTo(dateTo),country(country),city(city),adults(adults),children(children),neededRooms(neededRooms),nights(nights)
    {}
    double getPricePerNight(){
        return pricePerNight;
    }
    virtual double getCost(){ //Ireservations implementation
        return pricePerNight*nights;
    }
    virtual bool reserveThisOne(){ //Ireservations implementation
        return IHotelPtr->reserve(this);
    }
    virtual void getInfo(){
        std::cout<<"\nHotel Reservation :"<<hotelName<<" : "<<country<<" @ "<<city<<std::endl;
        std::cout<<dateFrom<<" To "<<dateTo<<std::endl;
        std::cout<<"adults: "<<adults<<"Children: "<<children;
        std::cout<<"\nTotal Cost: "<<getCost();
    }
    void setPtr(IHotel* ptr){
        IHotelPtr = ptr;
    }
    void setHotelName(std::string _hotelname){
        hotelName = _hotelname;
    }
    const std::string& getDateFrom() const {
        return dateFrom;
    }
    const std::string& getDateTo() const {
        return dateTo;
    }
    const std::string& getCountry() const {
        return country;
    }
    const std::string& getCity() const {
        return city;
    }
    const int& getAdults() const{
        return adults;
    }
    const int& getChildren() const{
        return children;
    }
    const int& getNeededRooms() const {
        return neededRooms;

    }

    //intended to return a bool so I can validate the data passed to the function (enhancing the code later)
    bool setDateFrom(const std::string& dateFromPassed){
        dateFrom =dateFromPassed;
        return 1;
    }
    void setPrice(double _price){
        pricePerNight = _price;
    }
    bool setDateTo(const std::string& dateToPassed){
        dateTo =dateToPassed;
        return 1;
    }
    bool setCountry(const std::string& countryPassed){
        country =countryPassed;
        return 1;
    }
    bool setCity(const std::string& cityPassed){
        city =cityPassed;
        return 1;
    }
    bool setChildren(int numberOfChildren){
        children = numberOfChildren;
        return 1;
    }
    bool setAdults(int numberOfAdults){
        adults = numberOfAdults;
        return 1;
    }
    bool setNeededRooms(int numberOfRooms){
        neededRooms = numberOfRooms;
        return 1;
    }

};



MarriottHotelAPI MattiotHotelAPI_instance;

class marriottHotelAPI_imp:public IHotel{
public:
    virtual std::vector<hotelsRoomsAvailable> queryRooms(hotelCard& queryInfo){ //Notice that data get returned by reference of a new object, so remember to delete the pointer.

        const std::vector<MarriottFoundRoom> &allRooms = MattiotHotelAPI_instance.FindRooms(queryInfo.getDateFrom(),queryInfo.getDateTo(),queryInfo.getCountry(),queryInfo.getCity(),queryInfo.getNeededRooms(),queryInfo.getAdults(),queryInfo.getChildren());

        std::vector<hotelsRoomsAvailable> RoomsToSee ; //vector of my own object, same as "allRooms" vector but generic form for all APIs.

        for (const MarriottFoundRoom &Room:allRooms)
            RoomsToSee.push_back({"Marriot Hotel",Room.room_type,Room.price_per_night,Room.date_from,Room.date_to});
        return RoomsToSee;
    }
    virtual bool reserve(hotelCard* dataToreserveUpon){
        return 1;
    }


};

HiltonHotelAPI HiltonHotelAPI_instance ;

class HiltonHotelAPI_imp :public IHotel{
public:
    virtual std::vector<hotelsRoomsAvailable> queryRooms(hotelCard& queryInfo){
        const std::vector<HiltonRoom>& allRooms = HiltonHotelAPI_instance.SearchRooms(queryInfo.getCountry(),queryInfo.getCity(),queryInfo.getDateFrom(),queryInfo.getDateTo(),queryInfo.getAdults(),queryInfo.getChildren(),queryInfo.getNeededRooms());
        std::vector<hotelsRoomsAvailable> RoomsToSee;
        for (const HiltonRoom &Room :allRooms)
            RoomsToSee.push_back({"Hilton Hotel",Room.room_type,Room.price_per_night,Room.date_from,Room.date_to});
        return RoomsToSee;

    }
    virtual bool reserve(hotelCard* dataToreserveUpon){
        return 1;
    }


};





#endif // MY_HOTELS_IMPLEMENTATIONS_H_INCLUDED
