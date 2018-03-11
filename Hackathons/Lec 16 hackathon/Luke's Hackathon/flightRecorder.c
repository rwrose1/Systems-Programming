//Imported libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//Typedef'd structure(s)
typedef struct flight{
    char AirlineCodeAndFlightNumber [8]; //AAA1234 + '/0', size, the code for the airline and its flight number, can hold an array up to a size of 8
    char OriginAirportCode[4]; //JFK + '/0', origin airport code, can hold an array up to size of 4
    char DestinationAirportCode[4]; //ORL + '/0'//, the code for the destination airport, can hold an array up to a size of 4
    char DepartureDayOfWeek[4]; //WED + '/0', departure day of the week, can hold an array up to a size of 4
    char DepartureMonth[4]; //JAN + '/0'// departure day of the month, can hold an array up to a size of 4
    int DepartureDay;// an int value, for the which date of the month that the departure occurs
    char DepartureTime[6]; //10:00 + '/0'// departure time of the flight/ holds an array up to a size of 6
    int DepartureYear;// an int value that, for which year the departure occurs
} flight;

typedef struct originAirport{
    char OriginAirportCode[4]; //JFK + '/0', origin airport code, can hold an array up to size of 4
    int count;// int value that holds the count
} originAirport;


//Prototypes
long fileSize(FILE * file);
int checkIfContains(char fileNames[100][4], int numFiles, char name[4]);

/*
Main function, takes parameters for the standard command line arguments, returns data to stdout when required, otherwise main completes the following tasks based on user input:
	(a) Create a binary file to store info about files. You may assume the user won't input info for more than 100 flights
	(b) Read input from user (i.e., create a menu) to implement the following functionality
	(c) Read and print info about all flight records in the file
	(d) Count number of airlines for a given airport
	(e) Print the number of inbound flights for airport x
	(f) Print the number of inbound flights for each airport
	(g) Print a sorted list of origin airports based on the number of outbound flights
	(h) Print a list of origin airports that have at least 2 flights that have a departure time earlier than noon
*/

int main( int argc, const char* argv[] )
{
    int flag = 1; //Flag for user input
    int sizeOfFlight = sizeof(flight); //sizeof the flight's data
    int sizeOfTotalFlight = sizeOfFlight + 8; //plus 8 for whitespace

    printf("The size of one flight is: %d.\n", sizeOfFlight);
    printf("The size of one flight including 8 1-byte spaces is: %d.\n", sizeOfTotalFlight);

    //(a) Create a binary file to store info about up to 100 flights from a txt file
    FILE * flightData;

    //(b) Read input from user (i.e., create a menu)
    printf("\nThe possible commands are as follows: \n0 to end; \n1 to store info; \n2 to print info; \n3 to count airlines; \n4 to print inbound flights at airport x; \n5 to print inbound flights for all airports; \n6 to print sorted list of origin airports; \n7 to print origin airports with at least 2 flights with departures before noon.\n");
    printf("Your input: ");
    int input; //user input

    while(flag){
        fflush(stdin); scanf("%d", &input);// clears the output buffer, and asks the user for input
		// if an input of 0 is entered, the program will end
        if(input == 0){
            //End
            printf("\nThe program will end.");
            flag = 0;
        }
        else if(input == 1){// if input is 1 it will create a binary file for the flight info

            flight tempFlight; //A temporary flight struct
		
	    //temp variables for each symbol in struct of flight
            char tempAirlineCodeAndFlightNumber [8]; //AAA1234 + '/0'
            char tempOriginAirportCode[4]; //JFK + '/0'
            char tempDestinationAirportCode[4]; //ORL + '/0'
            char tempDepartureDayOfWeek[4]; //WED + '/0'
            char tempDepartureMonth[4]; //JAN + '/0'
            int tempDepartureDay;
            char tempDepartureTime[6]; //10:00 + '/0'
            int tempDepartureYear;
		
            int length; //length int for length of input strings

            printf("\nThe program will take a flight to add here.\n");
            printf("Please enter airline code and flight number: ");
            fflush(stdin); scanf("%s", tempAirlineCodeAndFlightNumber);// clears the output buffer, asks for user input, user will enter an airline code and flight number.
            length = strlen(tempAirlineCodeAndFlightNumber) + 1;// size of the airline code and flight number
            if (length > 8){// if the length is greater than 8, notifies user about an error
                fprintf(stderr, "The supplied string is too large.\n");
                exit(-1);
            }
            strcpy(tempFlight.AirlineCodeAndFlightNumber, tempAirlineCodeAndFlightNumber);// copies the tempAirlineCodeAndFlightNumber into the location of Airline code and flight number in temp flight
            printf("Please enter Origin Airport Code: ");
            fflush(stdin); scanf("%s", tempOriginAirportCode);//clears the output buffer, asks the user for to enter the origin airport code
            length = strlen(tempOriginAirportCode) + 1;
            if (length > 8){// if the length is greater than 8, notifies user about an error
                fprintf(stderr, "The supplied string is too large.\n");
                exit(-1);
            }
            strcpy(tempFlight.OriginAirportCode, tempOriginAirportCode);// copies the temp origin airport code, into the location of origin airport code in tempflight

            printf("Please enter Destination Airport Code: ");
            fflush(stdin); scanf("%s", tempDestinationAirportCode);//clears the output buffer, asks the user for to enter the destination airport code
            length = strlen(tempDestinationAirportCode) + 1;
            if (length > 8){// if the length is greater than 8, notifies user about an error
                fprintf(stderr, "The supplied string is too large.\n");
                exit(-1);
            }
            strcpy(tempFlight.DestinationAirportCode, tempDestinationAirportCode);// copies the the temp destination airport code, into the location of destination airport code in tempflight

            printf("Please enter departure day of week: ");
            fflush(stdin); scanf("%s", tempDepartureDayOfWeek);//clears the output buffer, asks the user for to enter the departure day of the week
            if (length > 8){// if the length is greater than 8, notifies user about an error
                fprintf(stderr, "The supplied string is too large.\n");
                exit(-1);
            }
            strcpy(tempFlight.DepartureDayOfWeek, tempDepartureDayOfWeek); //copies the temp destination airport code, into the location of destination airport code in tempflight

            printf("Please enter departure month: ");
            fflush(stdin); scanf("%s", tempDepartureMonth);//clears the output buffer, asks the user for to enter the departure month
            length = strlen(tempDepartureMonth) + 1;
            if (length > 8){// if the length is greater than 8, notifies user about an error
                fprintf(stderr, "The supplied string is too large.\n");
                exit(-1);
            }
            strcpy(tempFlight.DepartureMonth, tempDepartureMonth);//copies the tempDepartureMonth , into the location of departure month in tempflight

            printf("Please enter departure day: ");
            fflush(stdin); scanf("%d", &tempDepartureDay);//clears the output buffer, asks the user for to enter the departure day
            tempFlight.DepartureDay = tempDepartureDay;// take the temp departure day and set that equal to the location of departure day in tempflight

            printf("Please enter departure time: ");
            fflush(stdin); scanf("%s", tempDepartureTime);//clears the output buffer, asks the user for to enter the departure day
            length = strlen(tempDepartureTime) + 1;
            if (length > 8){// if the length is greater than 8, notifies user about an error
                fprintf(stderr, "The supplied string is too large.\n");
                exit(-1);
            }
            strcpy(tempFlight.DepartureTime, tempDepartureTime);//copies the tempDepartureTime , into the location of departure time in tempflight

            printf("Please enter departure year: ");
            fflush(stdin); scanf("%d", &tempDepartureYear); //clears the output buffer, asks the user for to enter the departure year
            tempFlight.DepartureYear = tempDepartureYear;// set the value of tempDepartureYear equal to the location of departure year in tempflight
			
			//CHECK
			FILE * flightDataRead;// file pointer for the flight data that is being read
			if ((flightDataRead = fopen("flightData.bin", "rb")) != NULL) {// checks if the file pointer being opened for reading to a binary file is not null

                long archiveSize = fileSize(flightData);// the total size of the archive containing all of the flight data
				int numOfFlights = archiveSize / sizeof(flight);// value of the number of the flights, 
				
				int i = 0;// intializes the starting count to zero
				for (i; i < numOfFlights; i++){// looping
					flight tempFlightRead; //another temp flight struct
					fread(&tempFlightRead, sizeof(tempFlight), 1, flightData);// reads the content from flightData into the tempFlightRecord

					// checks each attribute in the struct to see if they contain the same value, if they do, the program terminates, and prints an errors
					if (strcmp(tempFlightRead.AirlineCodeAndFlightNumber, tempFlight.AirlineCodeAndFlightNumber) == 0) {
						if (strcmp(tempFlightRead.OriginAirportCode, tempFlight.OriginAirportCode) == 0) {
							if (strcmp(tempFlightRead.DestinationAirportCode, tempFlight.DestinationAirportCode) == 0) {
								if (strcmp(tempFlightRead.DepartureDayOfWeek, tempFlight.DepartureDayOfWeek) == 0) {
									if (strcmp(tempFlightRead.DepartureMonth, tempFlight.DepartureMonth) == 0) {
										if (tempFlightRead.DepartureDay == tempFlight.DepartureDay) {
											if (strcmp(tempFlightRead.DepartureTime, tempFlight.DepartureTime) == 0) {
												if (tempFlightRead.DepartureYear, tempFlight.DepartureYear) {
													fprintf(stderr, "\nInputed the same flight, exiting now.\n");
													exit(-1);
												}
											}
										}
									}
								}
							}
						}
					}
					
				}

				fclose(flightDataRead);// closes the file pointer
				//End Check
			
			}
			
            flightData = fopen("flightData.bin", "ab");// opens the .bin file for appending to a binary file
            
            long archiveSize = fileSize(flightData);// value of the total size of the archive containing the content stored in flight data
            int numOfFlights = archiveSize / sizeof(flight);// value of the number of flight
            printf("Number of flights: %ld/%ld = %d.\n", archiveSize, sizeof(flight), numOfFlights);

            if (numOfFlights > 100){// if the total number of flights entered is greater than 100, terminates and prints an error
                fprintf(stderr, "There cannot be more than 100 flights in the archive.");
                exit(-1);
            }

			rewind(flightData);// sets the file postion back to the beginning of the file
			
			// prints the values of the user inputed data for the attributes of a flight.
            printf("\nThe values of the newly created flight:\n");
            printf("AirlineCodeAndFlightNumber: \"%s\".\n", tempFlight.AirlineCodeAndFlightNumber);
            printf("OriginAirportCode: \"%s\".\n", tempFlight.OriginAirportCode);
            printf("DestinationAirportCode: \"%s\".\n", tempFlight.DestinationAirportCode);
            printf("DepartureDayOfWeek: \"%s\".\n", tempFlight.DepartureDayOfWeek);
            printf("DepartureMonth: \"%s\".\n", tempFlight.DepartureMonth);
            printf("DepartureDay: \"%d\".\n", tempFlight.DepartureDay);
            printf("DepartureTime: \"%s\".\n", tempFlight.DepartureTime);
            printf("DepartureYear: \"%d\".\n", tempFlight.DepartureYear);

            fwrite(&tempFlight, sizeof(flight), 1, flightData);// writes the content in flight data to tempflight

            fclose(flightData);//close the file pointer
            printf("\nYour input: ");
        }
        else if(input == 2){// if the user enters 2, read and print info about all flight records in the file
          
			flightData = fopen("flightData.bin", "rb");// opens the .bin file for reading to a binary file

            long archiveSize = fileSize(flightData);// value of the total size of the archive containing the content stored in flight data
            int numOfFlights = archiveSize / sizeof(flight);// value of the number of flight
            printf("Number of flights: %ld/%ld = %d.\n", archiveSize, sizeof(flight), numOfFlights);

            rewind(flightData);// sets the file position to the beginning of the file

            int i = 0; //count variable
            for (i; i < numOfFlights; i++){// looping
                flight tempFlight; //another temp flight struct
                fread(&tempFlight, sizeof(tempFlight), 1, flightData);// reads the data from flightData into tempFlight

                printf("\nFlight #%d:\n", i+1);
                printf("AirlineCodeAndFlightNumber: \"%s\".\n", tempFlight.AirlineCodeAndFlightNumber);
                printf("OriginAirportCode: \"%s\".\n", tempFlight.OriginAirportCode);
                printf("DestinationAirportCode: \"%s\".\n", tempFlight.DestinationAirportCode);
                printf("DepartureDayOfWeek: \"%s\".\n", tempFlight.DepartureDayOfWeek);
                printf("DepartureMonth: \"%s\".\n", tempFlight.DepartureMonth);
                printf("DepartureDay: \"%d\".\n", tempFlight.DepartureDay);
                printf("DepartureTime: \"%s\".\n", tempFlight.DepartureTime);
                printf("DepartureYear: \"%d\".\n", tempFlight.DepartureYear);
            }

            fclose(flightData);// closing the file pointer
            printf("\nYour input: ");
        }
        else if(input == 3){//if the user, inputs 3, it counts number of airlines for a given airport
           
			
			flightData = fopen("flightData.bin", "rb");// opens the .bin file for reading to 

            long archiveSize = fileSize(flightData);// value of the total size of the archive containing the content stored in flight data
            int numOfFlights = archiveSize / sizeof(flight), count = 0;// value of the number of flight
			char airport[4];// char data type, holds an array of size 4
            printf("Number of flights: %ld/%ld = %d.\n", archiveSize, sizeof(flight), numOfFlights);

            if (numOfFlights > 100){// if the number of flights inputted is greater than 100, terminate and print error message
                fprintf(stderr, "There cannot be more than 100 flights in the archive.");
                exit(-1);
            }
			
			printf("\nEnter the airport you would like to count: ");
			
			fflush(stdin); scanf("%s", airport);//clears the output buffer, asks the user for to enter the airport code that they would like to count
			printf("\nYour input: \"%s\"\n", airport);
			
            rewind(flightData);// sets the file position back to the beginning of the file.

            int i = 0; //count variable
            for (i; i < numOfFlights; i++){//looping
                
				flight tempFlight; //another temp flight struct
                fread(&tempFlight, sizeof(tempFlight), 1, flightData);// reads the content of flightdata into tempflight
				
				/*compare the to see if the user inputted airport code matches with either the origin airport code or the destination airport
				if they do increment the count
				*/
				if ((strcmp(airport, tempFlight.DestinationAirportCode) == 0) || (strcmp(airport, tempFlight.OriginAirportCode) == 0)) {
					count++;
				}
				
            }
			
			printf("The number of airlines for a given airport is : \"%d\".\n", count);// prints the number of airlines ar the specified airport

            fclose(flightData);// closing the file pointer
            printf("\nYour input: ");
			
        }
        else if(input == 4){// if the user enters 4, print the number of inbound flights for airport x
           
			flightData = fopen("flightData.bin", "rb");// opens the .bin file for reading to 

            long archiveSize = fileSize(flightData);// value of the total size of the archive containing the content stored in flight data
            int numOfFlights = archiveSize / sizeof(flight), count = 0;// value of the number of flights
			char airport[4];// char data type, holds an array of size 4
            printf("Number of flights: %ld/%ld = %d.\n", archiveSize, sizeof(flight), numOfFlights);
			
			printf("\nEnter the airport you would like to count: ");
			
			fflush(stdin); scanf("%s", airport);// clears the output buffer, and asks the user to enter an airport to count
			printf("\nYour input: \"%s\"\n", airport);
			
            rewind(flightData);//sets the file postion back to the beginning of the file

            int i = 0; //count variable
            for (i; i < numOfFlights; i++){//looping
                
				flight tempFlight; //another temp flight struct
                fread(&tempFlight, sizeof(tempFlight), 1, flightData);// reads the contents of flight data into tempflight
				
				// compares the destination airport code with the user inputted airport code and see if they match, if they do increment the count
				if ((strcmp(airport, tempFlight.DestinationAirportCode) == 0)) {

					count++;
				}
				
            }
			
			printf("The number of airlines for a given airport is : \"%d\".\n", count);// print the number airlines at the specified airport

            fclose(flightData);// closing the file pointer
            printf("\nYour input: ");

        }
        else if(input == 5){// if the user enters 5, print the number of inbound flights for each airport
            

            //Loop through every flight, looking for new DESTINATION airports
            //Adding them to an inorder array of strings
            //Incrementing a array list at that index
            flightData = fopen("flightData.bin", "rb");// opens the .bin file for reading to binary
            
            long archiveSize = fileSize(flightData);// value of the total size of the archive containing the content stored in flight data
            int numOfFlights = archiveSize / sizeof(flight);// value of the number of flights
            printf("Number of flights: %ld/%ld = %d.\n", archiveSize, sizeof(flight), numOfFlights);

            char destinations[100][4];/// two dimension array that holds up 100 flights, with each airport code not exceeding a size of 4
            //Loop through the array initializing to empty vals
            int x = 0; //count variable
            for (x; x < 100; x ++){
                strcpy(destinations[x], "\0\0\0\0");
            }

            int destinationCounts[100];// max size of the destination airports
            for (x = 0; x < 100; x ++){
                destinationCounts[x] = 0;
            }  

            rewind(flightData);// sets the file postion back to the beginning of the file

            int i = 0; int index = 0; int tempIndex = 0;
            for (i; i < numOfFlights; i++){
                flight tempFlight; //another temp flight struct
                fread(&tempFlight, sizeof(tempFlight), 1, flightData);// reads the contents of flight data into tempflight

                //int checkIfContains(char ** fileNames, int numFiles, char * name)
                if((tempIndex = checkIfContains(destinations, 100, tempFlight.DestinationAirportCode)) == -1){
                    //Does not exist in array
                    strcpy(destinations[index], tempFlight.DestinationAirportCode);// copies the destination airport code in tempflight, into the specified index of destinations
                    destinationCounts[index] += 1;
                    index ++;// increments the count of the index
                }
                else{
                    //Exists in array
                    destinationCounts[tempIndex] += 1;
                }
            }

            fclose(flightData);// closing the file pointer

            printf("\nThe number of inbound flights for each airport:\n");
            //Print
            i  =  0;
            while((strcmp(destinations[i], "\0\0\0\0") != 0) && (i < 100)){
                printf("Airport: %s; Number of inbound flights: %d.\n", destinations[i], destinationCounts[i]);
                i++;
            }

            printf("\nYour input: ");
        }
        else if(input == 6){
            //if the user enters 6, print a sorted list of origin airports based on the number of outbound flights, using bubble sort
            flightData = fopen("flightData.bin", "rb");// opens the .bin file for reading to binary

            long archiveSize = fileSize(flightData);// value of the total size of the archive containing the content stored in flight data
            int numOfFlights = archiveSize / sizeof(flight);// value of the number of flights
            printf("Number of flights: %ld/%ld = %d.\n", archiveSize, sizeof(flight), numOfFlights);

            //Initializes everything 
            originAirport originAirports[100];
            int x = 0; //count variable
            for (x; x < 100; x++){//looping
                strcpy(originAirports[x].OriginAirportCode, "\0\0\0\0");
                originAirports[x].count = 0;
            }

            rewind(flightData);

            //Loop for the number of flights in the archive
            int i = 0, index = 0; //count and index variable
            int ifContainsFlag = 0; //flag if the supplied string is contained already
            for (i; i < numOfFlights; i++){
                flight tempFlight; //another temp flight struct
                fread(&tempFlight, sizeof(tempFlight), 1, flightData);
                char tempOriginAirportCode[4];
                strcpy(tempOriginAirportCode, tempFlight.OriginAirportCode);
                
                ifContainsFlag = 0;

                //Loop through array comparing the origin code of the current flight to current origin code
                int x = 0; //count variable
                for(x; x < 100; x++) {
                    if (strcmp(originAirports[x].OriginAirportCode, tempOriginAirportCode) == 0) {                      
                        ifContainsFlag = 1;
                        originAirports[x].count++;
                        break;
                    }
                }

                //Adds a struct if it is not already existing
                if(ifContainsFlag == 0) {
                    strcpy(originAirports[index].OriginAirportCode, tempOriginAirportCode);
                    originAirports[index].count++;
                    index++;
                }                    
            }

            originAirport tempOrigin; //temp originAirport struct 
            
            int z; //count variable
            for (x = 0; x < index - 1; x ++){
                for (z = 0; z < index - x - 1; z++){
                    if (originAirports[z].count > originAirports[z+1].count){
                        //Swap
                        tempOrigin.count = originAirports[z].count;
                        strcpy(tempOrigin.OriginAirportCode, originAirports[z].OriginAirportCode);

                        originAirports[z].count = originAirports[z+1].count;
                        strcpy(originAirports[z].OriginAirportCode, originAirports[z+1].OriginAirportCode);

                        originAirports[z+1].count = tempOrigin.count;
                        strcpy(originAirports[z+1].OriginAirportCode, tempOrigin.OriginAirportCode);

                    }
                }
            }
            
            printf("Index: %d.\n", index);// prints the value of the index
            //return 0;

            for(x = 0; x < index; x++){
                printf("Origin airport: %s; Number of outbound flights: %d.\n", originAirports[x].OriginAirportCode, originAirports[x].count);
            }

            fclose(flightData);// closing the file pointer
            printf("\nYour input: ");

        }
        else if(input == 7){
            //if users enters 7, print a list of origin airports that have at least 2 flights that have a departure time earlier than noon

            //Loop through every flight, looking for new DESTINATION airports
            //Adding them to an inorder array of strings
            //Incrementing a array list at that index
            flightData = fopen("flightData.bin", "rb");// opens the .bin file for reading to binary
            
            long archiveSize = fileSize(flightData);// value of the total size of the archive containing the content stored in flight data
            int numOfFlights = archiveSize / sizeof(flight);// value of the number of flights
            printf("Number of flights: %ld/%ld = %d.\n", archiveSize, sizeof(flight), numOfFlights);

            char destinations[100][4]; //array of string to hold destination names
            //Loop through the array initializing to empty vals
            int x = 0; //count variable
            for (x; x < 100; x ++){
                strcpy(destinations[x], "\0\0\0\0");
            }

            int destinationCounts[100]; //arraylist to hold destination counts
            for (x = 0; x < 100; x ++){
                destinationCounts[x] = 0;
            }  

            rewind(flightData);// setting the file postion back to the beginning of the file.

	    //variable for count, index, and a tempindex in the numofflights
            int i = 0; int index = 0; int tempIndex = 0;
            for (i; i < numOfFlights; i++){//looping
                flight tempFlight; //another temp flight struct
                fread(&tempFlight, sizeof(tempFlight), 1, flightData);// reads the contents of flight data into tempflight
				if (strcmp(tempFlight.DepartureTime, "12:00") < 0) {// compares to the departure time in tempflight to see if it is earlier than 12:00
					//int checkIfContains(char ** fileNames, int numFiles, char * name)
					if((tempIndex = checkIfContains(destinations, 100, tempFlight.DestinationAirportCode)) == -1){
						//Does not exist in array
						strcpy(destinations[index], tempFlight.DestinationAirportCode);
						destinationCounts[index] += 1;
						index ++;
					}
					else{
						//Exists in array
						destinationCounts[tempIndex] += 1;
					}
				}
            }

            fclose(flightData);//closing file pointer

            //Print
            i  =  0; //count variable
            while((strcmp(destinations[i], "\0\0\0\0") != 0) && (i < 100)){
                if (destinationCounts[i] >= 2) {
					printf("Airport: %s; Number of inbound flights: %d.\n", destinations[i], destinationCounts[i]);
				}
				i++;
            }

            printf("\nYour input: ");
            
        }
        else{
            //End
            printf("\nThe program will end.\n");
            flag = 0;
        }
    }
}

/*
  This function finds file size by seeking all the way to the end on the file, then telling the long
  position the position of the end character. This position is the size of the file in bytes. It only takes,
  one argument, which is the FILE type needed to point to.
*/
long fileSize(FILE * file){
    //Position: the variable to be returned, and the position of the end character.
    unsigned long endPosition = 0; 
    unsigned long startPosition = 0;

    fflush(file); //Flush the buffer
    startPosition = ftell(file); //Record the start pos.

	// if it is null, and error is printed and terminates
    if (file == NULL){
        fprintf(stderr, "Error opening file in fileSize().\n");
        return(-1);
    }

    fseek(file, 0, SEEK_END);// sets the file position of the stream to the given offset

    endPosition = ftell(file);// ftell returns the current file postion of the given stream, and that is the value of position.

    fseek(file,startPosition,SEEK_SET); //return to start position

    return endPosition;// returns the position of the file offset
}

/*
    This function loops through entire array, and if name is == fileNames the function returns the index, else it returns -1;
    For parameters, this functions takes the string array of file names, the number of files, and the name to use in comparisons.
*/
int checkIfContains(char fileNames[100][4], int numFiles, char name[4]) {
	//i for loop
	int i;
  //This loops through the number of files supplied, comparing the string at the index with name
  //returning the location (index) of the correct file name.
	for (i = 0; i < numFiles; i++) {
		if (strcmp(fileNames[i], name) == 0) {
			//printf("\n index Given : %d", i);
			return i;
		}
	}

  //If nothing else it returns -1
	return -1;
}
