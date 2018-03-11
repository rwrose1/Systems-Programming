#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs.h"

/*
  char AirlineCodeAndFlightNumber [8]; //AAA123..
  char OriginAirportCode [3]; //JFK
  char DestinationAirportCode [3]; //ORL
  char DepartureDayOfWeek [3]; //Wed
  char DepartureMonth [3]; //Jan
  int DepartureDay;
  char DepartureTime [5]; //10:00
  int DepartureYear;
*/

flight * createFlight( char * AirlineCodeAndFlightNumber, char * OriginAirportCode, char * DestinationAirportCode, char * DepartureDayOfWeek, char * DepartureMonth, int DepartureDay, char * DepartureTime, int DepartureYear);

void storeInfo(flight tempFlight, FILE * flightdata);

int main( int argc, const char* argv[] )
{
  int flag = 1;
  int sizeOfFlight = sizeof(flight);

  printf("The size of one flight is: %d.", sizeOfFlight);
  //(a) Create a binary file to store info about up to 100 flights from a txt file
  FILE * flightData;
  flightData = fopen("flightData.bin", "wb");

  //(b) Read input from user (i.e., create a menu)
  printf("Please enter: 0 to end; 1 to store info; 2 to print info; 3 to count airlines; 4 to print inbound flights at airport x; 5 to print inbound flights for all airports; 6 to print sorted list of origin airports; 7 to print origin airports with at least 2 flights with departures before noon.\n");
  int input;

  while(flag){
    scanf("%d", &input);
    if(input == 0){
      printf("The program will end.");
      flag = 0;
    }
    else if(input == 1){
      char tempAirlineCodeAndFlightNumber [8]; //AAA123..
      char tempOriginAirportCode [3]; //JFK
      char tempDestinationAirportCode [3]; //ORL
      char tempDepartureDayOfWeek [3]; //Wed
      char tempDepartureMonth [3]; //Jan
      int tempDepartureDay;
      char tempDepartureTime [5]; //10:00
      int tempDepartureYear;

      printf("The program will take a flight to add here.\n");
      printf("Please enter airline code and flight number: ");
      scanf("%s", &tempAirlineCodeAndFlightNumber);

      printf("Please enter Origin Airport Code: ");
      scanf("%s", &tempOriginAirportCode);

      printf("Please enter Destination Airport Code: ");
      scanf("%s", &tempDestinationAirportCode);

      printf("Please enter departure day of week: ");
      scanf("%s", &tempDepartureDayOfWeek);

      printf("Please enter departure month: ");
      scanf("%s", &tempDepartureMonth);

      printf("Please enter departure day: ");
      scanf("%d", &tempDepartureDay);

      printf("Please enter departure time: ");
      scanf("%s", &tempDepartureTime);

      printf("Please enter departure year: ");
      scanf("%d", &tempDepartureYear);

      flight * tempFlight;
      tempFlight = malloc(sizeof(* tempFlight));
      tempFlight = createFlight(tempAirlineCodeAndFlightNumber, tempOriginAirportCode, tempDestinationAirportCode, tempDepartureDayOfWeek, tempDepartureMonth, tempDepartureDay, tempDepartureTime, tempDepartureYear);

      //storeInfo(tempFlight, flightdata);

    }
  }

  //(c) Read and print info about all flight records in the file
  //(d) Count number of airlines for a given airport
  //(e) Print the number of inbound flights for airport x
  //(f) Print the number of inbound flights for each airport
  //(g) Print a sorted list of origin airports based on the number of outbound flights
  //(h) Print a list of origin airports that have at least 2 flights that have a departure time earlier than noon

}

flight * createFlight( char * AirlineCodeAndFlightNumber, char * OriginAirportCode, char * DestinationAirportCode, char * DepartureDayOfWeek, char * DepartureMonth, int DepartureDay, char * DepartureTime, int DepartureYear) {

  flight * tempFlight = malloc(sizeof(flight));

  strcpy(tempFlight->AirlineCodeAndFlightNumber, AirlineCodeAndFlightNumber);
  strcpy(tempFlight->OriginAirportCode, OriginAirportCode);
  strcpy(tempFlight->DestinationAirportCode, DestinationAirportCode);
  strcpy(tempFlight->DepartureDayOfWeek, DepartureDayOfWeek);
  strcpy(tempFlight->DepartureMonth, DepartureMonth);
  strcpy(tempFlight->DepartureTime, DepartureTime);

  tempFlight->DepartureDay = DepartureDay;
  tempFlight->DepartureYear = DepartureYear;

  return tempFlight;
}
