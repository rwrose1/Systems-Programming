#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct flight{
    char AirlineCodeAndFlightNumber [8]; //AAA123..
    char OriginAirportCode [3]; //JFK
    char DestinationAirportCode [3]; //ORL
    char DepartureDayOfWeek [3]; //Wed
    char DepartureMonth [3]; //Jan
    int DepartureDay;
    char DepartureTime [5]; //10:00
    int DepartureYear;
 } flight;

 #endif
