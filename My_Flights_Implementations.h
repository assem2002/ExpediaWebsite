//interface for the various flights APIs for the sake of extesibility
#ifndef MY_FLIGHTS_IMPLEMENTATIONS_H_INCLUDED
#define MY_FLIGHTS_IMPLEMENTATIONS_H_INCLUDED
#include "expedia_flights_api.h" //Include All Flight APIs

class flightsQueryObj;
class flightAvailable;



// Interface for all flights APIs implementation for the sake of the extensibility when new airline gets added
class IMyflights{
private:
public:
   virtual std::vector<flightAvailable> qureyFlights(flightsQueryObj &query) = 0;
   virtual bool Reserve(flightsQueryObj* choosenFlight)  =0;

};





// Object to be Generic, so i can change the data entered from the user to the flight interface.
// i consider to be like a form that you fill when you search for a flight and then it's passed to the various functions as it's extremely generic.
class flightsQueryObj:public reservation{
private:
    std::string dateFrom;
    std::string dateTo;
    std::string countryFrom;
    std::string countryTo;
    int adults;
    int infants;
    int children;
    double Price;
    std::string AirLineName;
    IMyflights* IMyflightsPtr;

public:
    flightsQueryObj(std::string dateFrom,std::string dateTo,std::string countryFrom,std::string countryTo,int adults,int infants,int children):
        dateFrom(dateFrom),dateTo(dateTo),countryFrom(countryFrom),countryTo(countryTo),adults(adults),infants(infants),children(children)
        {}
    virtual void getInfo(){
        std::cout<<"\nAirline Reservation : "<<AirLineName<<"\n from "<<countryFrom<< " On "<<dateFrom;
        std::cout<<"\nTo "<<countryTo<<" On "<<dateTo;
        std::cout<<"\nAdults: "<<adults<<" Infants: "<<infants<<" Children: "<<children;
        std::cout<<"\nTotal Cost :"<<getCost();

    }
    double getPrice(){
        return Price;
    }
    virtual double getCost(){ //Ireservations implementation
        return Price;
    }
    void setPrice(double _price){
        Price =_price;
    }
    virtual bool reserveThisOne(){ //Ireservations implementation
        return IMyflightsPtr->Reserve(this);
    }
    const std::string& getDateFrom() const {
        return dateFrom;
    }
    const std::string& getDateTo() const {
        return dateTo;
    }
    const std::string& getCountryFrom() const {
        return countryFrom;
    }
    const std::string& getCountyTo() const {
        return countryTo;
    }
    const int& getAdults() const{
        return adults;
    }
    const int& getInfants() const {
        return infants;

    }
    const int& getChildren() const{
        return children;
    }

    //intended to return a bool so I can validate the data passed to the function (enhancing the code later)
    void setAirLineName(std::string AirLinenameNew){
        AirLineName = AirLinenameNew;
    }
    void setPtr(IMyflights* ptr){
        IMyflightsPtr = ptr;
    }
    bool setDateFrom(const std::string& dateFromPassed){
        dateFrom =dateFromPassed;
        return 1;
    }
    bool setDateTo(const std::string& dateToPassed){
        dateTo =dateToPassed;
        return 1;
    }
    bool setCountryFrom(const std::string& countryFromPassed){
        countryFrom =countryFromPassed;
        return 1;
    }
    bool setCountryTo(const std::string& countryToPassed){
        countryTo =countryToPassed;
        return 1;
    }
    bool setChildren(int numberOfChildren){
        children = numberOfChildren;
        return 1;
    }
    bool setInfants(int numberOfInfants){
        infants = numberOfInfants;
        return 1;
    }
    bool setAdults(int numberOfAdults){
        adults = numberOfAdults;
        return 1;
    }
    ~flightsQueryObj(){}

};

// object to contain info about the flights in specific airline (generic form to be handled from the interface)
class flightAvailable{
private:
public:
    std::string airlineName;
    double cost;
    std::string dateTimeFrom;
    std::string dateTimeTo;
    IMyflights* flighAirLinePtr =nullptr; // An empty pointer to the API Implementations (Put in whatever you want to be an indicator of what API this object belongs to.)
    flightAvailable() = default;
    flightAvailable(std::string airlineName , double cost , std::string dateTimeFrom, std::string dateTimeTo): //constructor for setting the object
        airlineName(airlineName), cost(cost) , dateTimeFrom(dateTimeFrom)  ,dateTimeTo(dateTimeTo){}


    void printFlightInfo(){
        std::cout<<"Airline : "<<airlineName<<" | cost :"<<cost<<" |Departure Date :"<<dateTimeFrom<<" |Arrival Date :"<<dateTimeTo<<std::endl;
    }
};



// IMPLEMENTATION ZONE . Expedia's Implementation Of Its Own Way Of Communicating With The Various Flight APIs.




AirCanadaOnlineAPI CanadaApi_Instance;
//my own implementation of the Canadian Airlines API
class candianAPI_imp: public IMyflights{
private:
public:
    virtual std::vector<flightAvailable> qureyFlights(flightsQueryObj &query){
        std::vector<AirCanadaFlight> allFlights = CanadaApi_Instance.GetFlights(query.getCountryFrom(),query.getDateFrom(),query.getCountyTo(),query.getDateTo(),query.getAdults(),query.getChildren());
        std::vector<flightAvailable> FlightsBack; // vector of general format of the flights to be handled from various part of the code
        for (AirCanadaFlight &singleFlightInfo : allFlights){
            flightAvailable newOne("AirCanda Airlines", singleFlightInfo.price,singleFlightInfo.date_time_from ,singleFlightInfo.date_time_to);
            FlightsBack.push_back(newOne);
        }
        return FlightsBack;
    }

    virtual bool Reserve(flightsQueryObj* chosenFlight){
        AirCanadaFlight obj;
        obj.date_time_from = chosenFlight->getDateFrom();
        obj.date_time_to = chosenFlight->getDateTo();
        obj.price = chosenFlight->getPrice();
        AirCanadaOnlineAPI ApiInstance;
        return ApiInstance.ReserveFlight(obj,AirCanadaCustomerInfo());//the customer Argument here is quite empty object (for the sake of project simplicity).
    }
    virtual ~candianAPI_imp(){}
};


//object of the Turkish api to make a request.
TurkishAirlinesOnlineAPI TurkishApi_Instance;

//My implementation of the Turkish Airlines API

class TurkishAirline_imp: public IMyflights{
public:

    virtual std::vector<flightAvailable> qureyFlights(flightsQueryObj &query){

        // required function to get flights ,supports GetAvailableFlights Function.
        TurkishApi_Instance.SetFromToInfo(query.getDateFrom(),query.getCountryFrom(),query.getDateTo(),query.getCountyTo());

        // required function to get flights ,supports GetAvailableFlights Function.
        TurkishApi_Instance.SetPassengersInfo(query.getInfants(),query.getChildren(),query.getAdults());

        //finally making a query request to the API.
        std::vector<TurkishFlight> allFlights = TurkishApi_Instance.GetAvailableFlights() ;

        std::vector<flightAvailable> FlightsBack ; // vector of my own generic object that holds data to be screened for user .

        //looping on returned vector from the API to convert it to my own generic object.
        for(TurkishFlight &singleFlightInfo : allFlights){
            flightAvailable newOne("Turkish Airlines", singleFlightInfo.cost,singleFlightInfo.datetime_from ,singleFlightInfo.datetime_to);
            FlightsBack.push_back(newOne);
        }

        return FlightsBack;
    }




    virtual bool Reserve(flightsQueryObj* chosenFlight){
        TurkishFlight obj; //create the API Object that hold the data; required for communicating with the API.

        //filing the object with the chosen flight to be reserved.
        obj.cost = chosenFlight->getPrice();
        obj.datetime_from = chosenFlight->getDateFrom();
        obj.datetime_to = chosenFlight->getDateTo();

        // creating a Turkish API object to make a reservation.
        TurkishAirlinesOnlineAPI APIInstance;
        return APIInstance.ReserveFlight(TurkishCustomerInfo(),obj);
    }
    virtual ~TurkishAirline_imp(){}

};




#endif // MY_FLIGHTS_IMPLEMENTATIONS_H_INCLUDED
