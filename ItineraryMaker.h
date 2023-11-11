#ifndef ITINERARYMAKER_H_INCLUDED
#define ITINERARYMAKER_H_INCLUDED

void viewItineraries(user* currentUser){
    if (currentUser->myItineraries.empty()){
        std::cout<<"\n Sorry there's no itinerary made yet!!";
        return;
    }
    std::cout<<"\n*********************************************************";
    for (std::vector<reservation*> &Itinerary:currentUser->myItineraries){
            double totalItiteraryCost= 0;
        for (reservation* &signleReservation:Itinerary){
            signleReservation->getInfo();
            std::cout<<"\n\n";
            totalItiteraryCost += signleReservation->getCost();
        }
            std::cout<<"Total Itinerary Cost : "<<totalItiteraryCost;
            std::cout<<"\n*********************************************************";

    }
}


class makeItinerary{
private:
    user* currentUser;
    std::vector<reservation*> allReservations; //All Reservations made in this itinerary.
    bool doneItinerary=0; // ends the loop and go back to the main menu.
    inline bool done(){
        std::cout<<"\n would you like to add a payment method?";
        std::cout<<"\n1)Yes\n2)No";
        std::cout<<"\n Enter Your Choice : ";
        int addCard;
        std::cin>>addCard;
        std::cin.ignore(1000,'\n');
        if (addCard ==1) add_card(currentUser);
        int items =0;
        for (userInfoCard& card:currentUser->allCards) {
            std::cout<<"\n"<<++items<<" )";
            card.showCardInfo();
        }

        double cardChoice;
        std::cout<<"\nChoose a card 1-"<<items<<" : ";
        std::cin>>cardChoice;
        int totalCostToPay =0;
        for (reservation* singleReservation :allReservations){
            if (!singleReservation->reserveThisOne()){
                std::cout<<"\nInvalid Reservation,\nsomething Wrong happened!!";
                for(reservation* singleReservation :allReservations) delete singleReservation;
                doneItinerary =1;
                return 0;
                break;
            }
            totalCostToPay += singleReservation->getCost();
        }

        (currentUser->allCards[cardChoice-1]).pay(totalCostToPay);
        currentUser->myItineraries.push_back(allReservations);
        std::cout<<"\nReservations Done Successfully.";

        doneItinerary =1;
        return 1;

    }
    void cancel() {
        doneItinerary =1;
    }
    void addHotel(){
        //Declaration of local Variable to be passed to the form.
        std::string city;
        std::string country;
        std::string fromDate;
        std::string toDate;
        int children,adults;
        int neededRooms;
        int nights;

        //Asking the user to fill the form (Query Request)
        std::cout<<"\n\nEnter Country : ";
        std::getline(std::cin,country);
        std::cout<<"Enter city  :";
        std::getline(std::cin,city);
        std::cout<<"Enter From Date (MM-DD-YYYY) : ";
        std::getline(std::cin,fromDate);
        std::cout<<"Enter To Date (MM-DD-YYYY)  :";
        std::getline(std::cin,toDate);
        std::cout<<"Enter Number Of Adults Children (In The Same Previous Order) : " ;
        std::cin>>adults>>children;
        std::cin.ignore(10000,'\n');
        std::cout<<"Enter The Number Of Rooms Needed :";
        std::cin>>neededRooms;
        std::cin.ignore(10000,'\n');
        std::cout<<"Enter How Many nights needed : ";
        std::cin>>nights;
        std::cin.ignore(10000,'\n');
        hotelCard* hotelForm = new hotelCard(fromDate,toDate,country,city,adults,children,neededRooms,nights);
        std::vector<hotelsRoomsAvailable> hotelRoomsToDisplay;
        int items =0;
        for (IHotel* &hotelImp : allHotels){
            std::vector<hotelsRoomsAvailable> temp = hotelImp->queryRooms(*hotelForm);
            for(hotelsRoomsAvailable &singleRoom:temp){
                std::cout<<++items<<")";
                singleRoom.printHotelInfo();
                singleRoom.iHotelPtr = hotelImp;
                hotelRoomsToDisplay.push_back(singleRoom);
            }
        }
        int hotelChoice;
        while (true){ //dummy while loop as wrong choice here would make a hard crash to the program.
            std::cout<<"Choose From Range 1 - "<<items<<" : ";
            std::cin>>hotelChoice;
            if (hotelChoice>=1 || hotelChoice<=items)break;
        }
        hotelForm->setHotelName(hotelRoomsToDisplay[hotelChoice-1].hotelName);
        hotelForm->setPtr((hotelRoomsToDisplay[hotelChoice-1].iHotelPtr));
        hotelForm->setPrice(hotelRoomsToDisplay[hotelChoice-1].pricePerNight);
        allReservations.push_back(hotelForm);
    }




    void addFlight(){
        //Declaration of local Variable to be passed to the form.
        std::string countryFrom;
        std::string fromDate;
        std::string countryTo;
        std::string toDate;
        int children,infants,adults;

        //Asking the user to fill the form (Query Request)
        std::cout<<"\n\nEnter From Country : ";
        std::getline(std::cin,countryFrom);
        std::cout<<"Enter From Date (MM-DD-YYYY) : ";
        std::getline(std::cin,fromDate);
        std::cout<<"Enter To Country  :";
        std::getline(std::cin,countryTo);
        std::cout<<"Enter To Date (MM-DD-YYYY)  :";
        std::getline(std::cin,toDate);
        std::cout<<"Enter Number Of Adults Children Infants (In The Same Previous Order) : " ;
        std::cin>>adults>>children>>infants;

        flightsQueryObj* flightForm = new flightsQueryObj(fromDate,toDate,countryFrom,countryTo,adults,infants,children);
        //all flights returned from the various APIs
        std::vector<flightAvailable> FlightsToDisplay;

        //iterate over the "AllAirLines Vector decalred in the global scope".
        //iterations would make a query and get  a vector filled with flights and will be pushed back to the "flightsToDisplay Vector" To get selected from later.

        int items=0;
        for (IMyflights* &API_imp_ptr:allAirLines){
            std::vector<flightAvailable> Flights = API_imp_ptr->qureyFlights(*flightForm);
                for (flightAvailable &FlightInfo:Flights){
                    std::cout<<++items<<") ";
                    FlightInfo.printFlightInfo();
                    FlightInfo.flighAirLinePtr = API_imp_ptr;
                    FlightsToDisplay.push_back(FlightInfo);
                }
        }


        int flightChoice;
        while (true){ //dummy while loop as wrong choice here would make a hard crash to the program.
            std::cout<<"Choose From Range 1 - "<<items<<" : ";
            std::cin>>flightChoice;
            if (flightChoice>=1 || flightChoice<=items)break;
        }
        //filling the form with the related pointer of the flight implementation as checking out the itinerary would make reservation requests to the various APIs selected.
        flightForm->setAirLineName(FlightsToDisplay[flightChoice-1].airlineName) ;
        flightForm->setPtr(FlightsToDisplay[flightChoice-1].flighAirLinePtr);
        flightForm->setPrice(FlightsToDisplay[flightChoice-1].cost);
        allReservations.push_back(flightForm);

    }


public:

    makeItinerary(user* currentUser) :currentUser(currentUser){}
    void start(){
        while(!doneItinerary){
            std::cout<<"\nItinerary:\n";
            std::cout<<"\n    1)Add Flight";
            std::cout<<"\n    2)Add Hotel";
            std::cout<<"\n    3)Done";
            std::cout<<"\n    4)Cancel";
            std::cout<<"\nEnter Your Choice : ";
            int meunChoice;
            std::cin>>meunChoice;
            std::cin. ignore(1000,'\n');

            switch (meunChoice){
                case 1 :
                    addFlight();
                    break;
                case 2 :
                    addHotel();
                    break;
                case 3:
                    done();
                    break;
                case 4:
                    cancel();
                    break;
            }
        }

    }
};


#endif // ITINERARYMAKER_H_INCLUDED
