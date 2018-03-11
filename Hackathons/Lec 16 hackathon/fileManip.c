#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"


flight * readFlight(FILE * archive) {
	
	flight * tempFlight = malloc(sizeof(flight));
	
	fread(tempFlight.AirlineCodeAndFlightNumber, sizeof(char), 8, archive);
	fseek(archive, 1, SEEK_CUR);
	fread(tempFlight.OriginAirportCode, sizeof(char), 3, archive);
	fseek(archive, 1, SEEK_CUR);
	fread(tempFlight.DestinationAirportCode, sizeof(char), 3, archive);
	fseek(archive, 1, SEEK_CUR);
	fread(tempFlight.DepartureDayOfWeek, sizeof(char), 3, archive);
	fseek(archive, 1, SEEK_CUR);
	fread(tempFlight.DepartureMonth, sizeof(char), 3, archive);
	fseek(archive, 1, SEEK_CUR);
	fread(tempFlight.DepartureDay, sizeof(int), 1, archive);
	fseek(archive, 1, SEEK_CUR);
	fread(tempFlight.DepartureTime, sizeof(char), 5, archive);
	fseek(archive, 1, SEEK_CUR);
	fread(tempFlight.DepartureYear, sizeof(int), 1, archive);
	fseek(archive, 1, SEEK_CUR);
	
	return tempFlight;
}