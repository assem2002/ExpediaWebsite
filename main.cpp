#include <iostream>
#include<vector>
#include "Ireservations.h"
#include "My_Flights_Implementations.h"
#include "My_Hotels_Implementations.h"
#include "My_Payments_Implementations.h"
#include "user.h"
#include "AccountAccess.h"
//make a vector of pointer to all the APIs i have built.
candianAPI_imp f1;
TurkishAirline_imp f2;
std::vector<IMyflights*> allAirLines {&f1,&f2};

HiltonHotelAPI_imp hotel1;
marriottHotelAPI_imp hotel2;
std::vector<IHotel*> allHotels {&hotel1,&hotel2};
#include "ItineraryMaker.h"




void main_flow(){
    bool loggedIn = 0; //Indication that we're in some account right now.
    bool programOn = 1;
    while(programOn){
        accountAccess accInstance;
        user* currentUser = accInstance.start();
        loggedIn = 1;
        //Main Menu in the Program.
        while(loggedIn){
            std::cout<<"\n\nMenu:\n";
            std::cout<<"\n    1)View Profile";
            std::cout<<"\n    2)Make Itinerary";
            std::cout<<"\n    3)List My Itineraries";
            std::cout<<"\n    4)LogOut";
            std::cout<<"\n    5)Terminate Program";
            std::cout<<"\nEnter Your Choice : ";
            int meunChoice;
            std::cin>>meunChoice;
            std::cin. ignore(1000,'\n');

            switch(meunChoice){
                case 5:
                    {
                        programOn=0;
                        loggedIn =0;
                        for (auto & itinerary:currentUser->myItineraries){
                            for (auto &singleReservation :itinerary){
                                delete singleReservation;
                            }
                        }
                    }
                    break;
                case 4:
                    loggedIn = 0;
                    break;
                case 1:
                    currentUser->viewProfile();
                    break;
                case 3:
                    viewItineraries(currentUser);
                    break;
                case 2:
                    {
                        makeItinerary temp(currentUser);
                        temp.start();
                        break;
                    }
                default:
                    std::cout<<"Wrong Choice";
                    break;

            }

        }


    }

}


int main()
{
    allUsers.push_back({"assem@gmail.com","assem","0000","assem00"});
    allUsers[0].allCards.push_back({"assem","kfs","123456789","10-10-2023","Credit Card",111,1});
    main_flow();
    return 0;
}
