/*
 * expedia_hotels_api.h
 *
 *  Created on: Sep 22, 2020
 *      Author: moustafa
 */

#ifndef EXPEDIA_HOTELS_API_H_
#define EXPEDIA_HOTELS_API_H_

class HiltonRoom {
public:
	string room_type;
	int available;
	double price_per_night;
	string date_from;
	string date_to;
};

class HiltonHotelAPI {
public:
	static vector<HiltonRoom> SearchRooms(string country, string city, string from_date, string to_date, int adults, int children, int needed_rooms) {
		vector<HiltonRoom> rooms;

		rooms.push_back( { "Interior View", 6, 200.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "City View", 3, 300.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Deluxe View", 8, 500.0, "29-01-2022", "10-02-2022" });

		return rooms;
	}
};

class MarriottFoundRoom {
public:
	string room_type;
	int available;
	double price_per_night;
	string date_from;
	string date_to;
};

class MarriottHotelAPI {
public:
	static vector<MarriottFoundRoom> FindRooms(string from_date, string to_date, string country, string city, int needed_rooms, int adults, int children) {
		vector<MarriottFoundRoom> rooms;

		rooms.push_back( { "City View", 8, 320.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Interior View", 8, 220.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Private View", 5, 600.0, "29-01-2022", "10-02-2022" });

		return rooms;
	}
};

#endif /* EXPEDIA_HOTELS_API_H_ */
