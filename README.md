# What This Project About (Expect Nothing Wow !)
It's a console program similar to Expedia website for reserving a whole itinerary that includes flights, hotels, cars and more.

This project is meant to be an implementaion on my knowledge about the OOP paradigm in my journey of learning OOP concepts from [Dr.mostafa Saad's course](https://www.udemy.com/course/cpp-4skills/) it's foucsed on the runtime polymorphism concept, So I tried hard to make the code generic as possible for future feature adding by following the interfaces made (you can check the UML for more explaination)


# UML Diagram (Check The [PDF](https://github.com/assem2002/ExpediaWebsite/blob/1f293ea77a948186e68d2fc821433d8f7bfa95b5/UML%20Digram%20PDF.pdf))
Check out the UML diagram for clearer understanding of the nature to my OO design.

![image](https://github.com/assem2002/ExpediaWebsite/blob/e306ea0004271229860f5e637515234403c43abd/UML%20Digram.png)


# How To Use It
You can simply download the [exe](https://github.com/assem2002/ExpediaWebsite/blob/e306ea0004271229860f5e637515234403c43abd/Expedia_Project.exe)  file and run it (Dummy User-> username:assem00,password:0000).

if exe doesn't work, You can download the files and just compile the main.cpp file using g++ compiler.

The program has friendly-console interface instructions to make you go along with the program such as :

**Login/Signup menu:**

this menu provide login and signup methods. it checks for existing users and gives the proper action to take by using simple looping and if conditions on the existing user data.

![image](https://github.com/assem2002/ExpediaWebsite/blob/e306ea0004271229860f5e637515234403c43abd/ScreenShots/Program%20Start.png)

**Make An itinerary (Flights & Hotel Room for now)**

This function has the most complex part of the program as it make queries on several services such as hotels and flights and for each service you can query a specific reservation from your own choice and the program would call every API it has access to then query for your flight specific choice or room choice and display every possible choice from the various APIs (absolutely the data returned are dummy as I got no real working APIs they're made by the course instructor for the purpose of learning).

I had to make quering on every service very generic, so I made a  simple unified object to use it for making query request on the various APIs (Check UML PDF).

![image](https://github.com/assem2002/ExpediaWebsite/blob/e306ea0004271229860f5e637515234403c43abd/ScreenShots/Make%20An%20Itinerary.png)

![image](https://github.com/assem2002/ExpediaWebsite/blob/e306ea0004271229860f5e637515234403c43abd/ScreenShots/Add%20A%20Flight.png)

![image](https://github.com/assem2002/ExpediaWebsite/blob/e306ea0004271229860f5e637515234403c43abd/ScreenShots/Add%20A%20Hotel%20.png)

**check out your itineraries**

![image](https://github.com/assem2002/ExpediaWebsite/blob/e306ea0004271229860f5e637515234403c43abd/ScreenShots/View%20All%20Itineraries.png)

**Credit Card API**

You can add payment cards when you signup or when you check out from the itinerary you just made.

I tried to make a genreic code (Interface for the credit cards for later new-card-providors adding) as the cards withdraw methods gets done throught APIs provided by the company of the card.

![image](https://github.com/assem2002/ExpediaWebsite/blob/e306ea0004271229860f5e637515234403c43abd/ScreenShots/Pay%20For%20Itinerary.png)

![image](https://github.com/assem2002/ExpediaWebsite/blob/e306ea0004271229860f5e637515234403c43abd/ScreenShots/Add%20A%20Card.png)


# Features
- Create New Users
- Query About Rooms from Various Hotel
- Query About Flights From Various FAirLines
- Add Flight To Itinerary
- Add Hotel Room To Itinerary 
- Pay using Various Credit Cards
- Check Your Itinerary Reservations

  
# How to Extend Code

Code extending is the whole purpose of this program as you can do the following :

- Add new Airline just by following the interface named "IFlight" and making the needed local API for querying and reserving the flights, then add an instance of it in the vector named allAirlines.
- Add new Hotel just by following the interface named "IHotel" and making the need local API for querying and reserving the hotel rooms, then add an instance of it in the vector named allHotels.
- Add a whole new service by implementing the needed object for transfering the data (Service dependant object) with a mandtory inheritance from the "Reservation class" which is resposible for handling the data and reservation at time of checking out (Probably not the best way for handling the issue, but fine for now ).
- Add new card Providor by following the interface named "IPayment" and then add it to the factory object.


# Difficulties Faced
- Design Issues
  - The generic code made required from me deep thinking about my choices to make it clear code and easy to extend and maintain.
  - Tried to avoid unnecessary copies so I had to think twice before passing by refernce or doing a memory allocation.
  - Data hiding was a nightmare for me to choose who to hide and who not and who gets setter method and who gets getter method (some objects all of its members are public just for the sake of simplicity).
- Dealing with Json objects/strings creditcard info in C++ was little challenging.
- Could happen a memory leak if the program got interrupted by mistake or not used correctly.
- If happened to add a refund feature in the itineraries, there could be difficulties though the APIs now don't provide this feature.
