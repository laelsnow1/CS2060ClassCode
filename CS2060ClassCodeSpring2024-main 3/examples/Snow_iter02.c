//
//  Snow_iter02.c
//  CS2060CProject
//
//  Created by lael Snow on 3/7/24.
//

///#include "Snow_iter02.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <float.h>


// max length for string
#define STRING_LENGTH 80
// 2 dimensional array storage amounts for rows and columns for survey data
#define SURVEY_RIDER_ROWS 5
#define SURVEY_CATEGORIES 3
// login and sentinel values
#define CORRECT_ID "id1"
#define CORRECT_PASSCODE "ABCD"
#define LOGIN_MAX_ATTEMPTS 4
#define SENTINAL_VALUE -1
#define MAX_SET_UP 50.0
#define MIN_SET_UP 0.1
// used to generate random number of minutes based on number of miles
#define MIN_RAND_MINUTES_FACTOR 1.2
#define MAX_RAND_MINUTES_FACTOR 1.5
// min miles and max miles
#define MIN_MILES 1
#define MAX_MILES 100
#define MIN_FLATRATE 20

const char *surveyCategories[SURVEY_CATEGORIES] = {"Safety", "Cleanliness", "Comfort"};


// structure to hold ride share business info
typedef struct RideShareInfo {
    float baseFare;
    float costPerMinute;
    float costPerMile;
    float minFlatRate;
    char organizationName[STRING_LENGTH];
    unsigned int rentalSurvey[SURVEY_RIDER_ROWS][SURVEY_CATEGORIES];
    unsigned int surveyCount;
    double miles;
    int minutes;
    int ridersCount;
    int totalMiles;
    double totalFare;
    double totalMinutes;
    double rideFare;
    
} rideShare;

// function prototypes
bool adminLogin(void); // good
bool scanDouble (const char *buffer, double *output);
void fgetsRemoveNewLine(char *stringPtr); // good  need
int calculateRandomNumber(int min, int max); // need
void setUpRideShare (rideShare *rideSharePtr);
double getValidDouble(double min, double max);
void displayRideShareRatings(unsigned int *surveyCount, const unsigned int survey[][SURVEY_CATEGORIES], rideShare *rideSharePtr);
void getRideShareRatings(unsigned int survey[][SURVEY_CATEGORIES], unsigned int *surveyCount, size_t total_categories);
void ridersMode(rideShare *rideSharePtr);
double calculateFare(rideShare *rideSharePtr); // need
void getRatings(unsigned int rentalSurvey[][SURVEY_CATEGORIES ], unsigned int *ridersCount, const char *surveyCategories[]);
void printFare(rideShare *rideSharePtr); // need
double getValidInput(char *setup, double min, double max);
double getValidDoubleSentinel(int min, int max, int sentinel); // for miles  need
char getValidYN(void); // need







int main(int argc, const char * argv[]) {
    
    // seed for the random generator with current time
       srand((unsigned int) time(NULL));
    
    rideShare rideShareInfo;
    
    
    

    // STEP 1:
    // 1.1 get valid id and pw
    if(adminLogin()) { // if success go to user story 2
        printf("Login Successful\n\n");
        
        //User Story2: Admin RideShare Set up
        setUpRideShare(&rideShareInfo);
        
        
        // 2.1 - 2.6 get info, name, and rideshare details
        ridersMode(&rideShareInfo);
        
        /*
        puts("\nSetup RideShare Info: ");
        
        baseFare = getValidInput("Enter Base Fare: ", MIN_SET_UP, MAX_SET_UP);
        costPerMin = getValidInput("Enter Cost Per Min: ", MIN_SET_UP, MAX_SET_UP);
        costPerMile = getValidInput ("Enter Cost Per Mile: ", MIN_SET_UP, MAX_SET_UP);
        minFlatRate = getValidInput("Enter Min Flat Rate: ", MIN_SET_UP, MAX_SET_UP);
        
        // Get Ride Share Organizaion Name
        puts("\nEnter your RideShare Organization Name");
        getchar();
        fgets(rideShareName, STRING_LENGTH, stdin);

        
        // Display Rideshare details
        printInfo(rideShareName, baseFare, costPerMin, costPerMile, minFlatRate);
        
    } else {
        printf("Exiting RideShare\n");
        // end program
        return 0;
         */
    }
    
    
    
    // User Story 3 Rider Mode
    
    //3.1 display & display ride share rating collections so far
    
    // ZERO SURVEYS TO BEGIN WITH
    
    printf("Welcome to the %s. We can only provide services for rides from 1 to 100 miles.", rideShareInfo.organizationName);
    puts("");
    displayRideShareRatings(&rideShareInfo.surveyCount, rideShareInfo.rentalSurvey, &rideShareInfo);
   // displayRideShareInfo(rideShareName, surveyCategories, SURVEY_CATEGORIES, 4);
    
  
    // Prompt
    printf("Do you want to request a ride from %s \n", rideShareInfo.organizationName);
    
    char choice = getValidYN();
    if (choice == 'n') {
        // go back to 3.1
        displayRideShareRatings(&rideShareInfo.surveyCount, rideShareInfo.rentalSurvey , &rideShareInfo);
       // displayRideShareInfo(rideShareName, surveyCategories, SURVEY_CATEGORIES, 4);
    } else { //'y'
        // go to 3.3
       
        
        
        /*        puts("Enter the number of miles to your destination: ");
        rideShareInfo.miles = getValidDoubleSentinel(MIN_MILES, MAX_MILES, SENTINAL_VALUE);
        if(rideShareInfo.miles == SENTINAL_VALUE) {
            if(adminLogin() == 1) {
                puts("Admin shutdown. Exiting RideShare Mode");
                // go to user story 4.1
                
            } else {
                // go to 3.1
                 displayRideShareRatings(rideShareInfo.surveyCount, rideShareInfo.rentalSurvey , &rideShareInfo);
                //displayRideShareInfo(rideShareName, surveyCategories, SURVEY_CATEGORIES, 4);
            }
            
            
            
        } else { // if correct miles entered,
            // calculate random number of mins from miles
                        int minMinutes = (int)(MIN_RAND_MINUTES_FACTOR * rideShareInfo.miles);
                        int maxMinutes = (int)(MAX_RAND_MINUTES_FACTOR * rideShareInfo.miles);
                            
                        minutes = calculateRandomNumber(minMinutes, maxMinutes);
            
                        // minutes = rand() % (maxMinutes - minMinutes + 1) + minMinutes;
                        
                        // calculate ride fare
                        rideFare = calculateFare(baseFare, costPerMin, costPerMile, minFlatRate, miles, minutes);
                        
                        // Add ride details to total
                            totalMiles += miles;
                            totalMinutes += minutes;
                            totalFare += rideFare;
                        
                        // print ride fare details
                        printFare(rideCount, miles, minutes, rideFare);
                        rideCount++;
                        
            // go to 3.4
            puts("Do you want to rate your rideshare experience?");
            char expeirence = getValidYN();
            if(expeirence == 'n') {
                puts("Thanks for Riding with us");
                // go back to 3.1
                displayRideShareInfo(rideShareName, surveyCategories, SURVEY_CATEGORIES, 4);
            } else {
                // get ratings
                getRatings(rideShareInfo.rentalSurvey, &rentersCount,surveyCategories);
                
                // go back to 3.1
                displayRideShareInfo(rideShareName, surveyCategories, SURVEY_CATEGORIES, 4);
                
            }
                    }
         */
        }
        
        
    
    
 
    
    

}// end of main
    

// functions

void printInfo(char string[], double baseFare,double costPerMin, double costPerMile, double minFlatRate){
    printf("\n%s", string);
    printf("baseFare = $ %.2lf\n", baseFare);
    printf("costPerMinute = $ %.2lf\n", costPerMin);
    printf("costPerMile = $ %.2lf\n", costPerMile);
    printf("minFlatRate = $ %.2lf\n", minFlatRate);
    
    puts("\nExiting Admin Mode\n");
}

double getValidDoubleSentinel(int min, int max, int sentinel) {
    double value = 0.0;
    int validInput = 0; // flag to track if input is valid
    
    while(!validInput) {
        if (scanf("%lf", &value) != 1) {
            puts("Error: You did not enter a number.\n");
            while(getchar() != '\n'); // clear buffer
            
        } else if (value == sentinel) {
            validInput = 1; // set flag to indicate valid input
            
        } else if (value < min || value > max) {
            printf("Error: Not within %d and %d miles.\n", min, max);
            
        } else {
            validInput = 1; // set flag to indicate valid input
        }
        
    } // end of while
    return value;
    
} // end of getValidDouble

bool adminLogin(void){
    
    char userId[STRING_LENGTH];
    char userPw[STRING_LENGTH];
    
    int counter = 1;
    int validInput = 0;
    
    puts("Admin Login:");
       
        
    while (!validInput) {
            puts("Enter your Admin ID:");
            fgets(userId,STRING_LENGTH, stdin);
            
            fgetsRemoveNewLine(userId);
            // userId[strcspn(userId, "\n")] = '\0'; // remove trailing newline !!

            puts("\nEnter your Admin password");
            fgets(userPw,STRING_LENGTH, stdin);
        
            fgetsRemoveNewLine(userPw);
            //userPw[strcspn(userPw, "\n")] = '\0'; // remove trailing newline !!
            
            if (strcmp(userId, CORRECT_ID) == 0 && strcmp(userPw, CORRECT_PASSCODE) == 0) {
                validInput = 1;
            } else {
                if (counter < 4) {
                    puts("Error, incorrect ID or PW");
                    counter++;
                } else {
                    puts("Exiting Rideshare");
                    return false; // Exit the program
                }
            }
        }
        
    return true; // succesful login
}

void fgetsRemoveNewLine(char *stringPtr) {
    
    // get the length of the string being passed
    size_t strLength = strlen(stringPtr);
    
    if (strLength > 0 && stringPtr[strLength-1] == '\n') {
        stringPtr [strLength-1] = '\0';
    }
    
    
} // end of newline func

int calculateRandomNumber(int min, int max){
    int random;
    
    srand((unsigned int) time(NULL)); // seed
    
    return random = rand() % (max - min + 1) + min;
   
}
double getValidDouble(double min, double max){
    
    double value = 0.0;
    int validInput = 0; // flag to track if input is valid
    
    while(!validInput) {
        if (scanf("%lf", &value) != 1) {
            puts("Error: You did not enter a number.\n");
            while(getchar() != '\n'); // clear buffer

            
        } else if (value < min || value > max) {
            printf("Error: Enter a number from %.2lf to %.2lf.\n", min, max);
            
        } else {
            validInput = 1; // set flag to indicate valid input
        }
        
    } // end of while
    return value;
    
}

void setUpRideShare (rideShare *rideSharePtr){
    
    printf("Set up rideshare information\n");
    
    printf("Enter the RideShare Organization Name:\n ");
    fgets(rideSharePtr -> organizationName, STRING_LENGTH, stdin);
    fgetsRemoveNewLine(rideSharePtr -> organizationName);
    
    printf("Enter the base fare: ");
    rideSharePtr -> baseFare = getValidDouble(MIN_SET_UP, MAX_SET_UP);
    
    
    printf("Enter the cost per minute: ");
    rideSharePtr -> costPerMinute = getValidDouble(MIN_SET_UP, MAX_SET_UP);
    
    printf("Enter the cost per mile: ");
    rideSharePtr -> costPerMile = getValidDouble(MIN_SET_UP, MAX_SET_UP);
    
    printf("Enter the minimum flat rate: ");
    rideSharePtr -> minFlatRate = getValidDouble(MIN_SET_UP, MAX_SET_UP);
    
    // Initialize surveyCount to zero
    rideSharePtr->surveyCount = 0;
    
    // display ride share details
    printf("\nRideshare details");
    printf("%s", rideSharePtr -> organizationName);
    printf("Base fare: %.2f\n", rideSharePtr -> baseFare);
    printf("Cost Per Minute: %.2f\n", rideSharePtr -> costPerMinute);
    printf("Cost Per Mile: %.2f\n", rideSharePtr -> costPerMile);
    printf("Minimum flat rate: %.2f\n", rideSharePtr -> minFlatRate);
    printf("Exiting Admin Mode\n\n");
}


double getValidInput(char *setup, double min, double max){
    int validInput = 0;
    double value = 0.0;
    
    while (!validInput) {
            printf("%s", setup);
            if (scanf("%lf", &value) != 1 || value < min || value > max) {
                printf("Error, Enter a valid number from %.1lf to %.1lf\n", min, max);
                while (getchar() != '\n'); // Clear input buffer
            } else {
                validInput = 1; // Set validInput to true to exit the loop
            }
        }
        
        return value;
}
void printCategories(const char *categories[], size_t totalCategories){
    //loop to display each category horizontally
        printf("%s", "Rating Categories:\t");
        for (size_t surveyCategory = 0; surveyCategory < totalCategories; ++surveyCategory)
        {
            printf("\t%zu.%s\t", surveyCategory+1, categories[surveyCategory]);
        }
        puts(""); // start new line of output
    }

void printSurveyResults (int rentalSurvey[][SURVEY_CATEGORIES ], int rentersCount) {
    
    for(size_t i = 0; i < rentersCount; i++ ){
        printf("Survey %lu:\t", i + 1);
        
        for(size_t j = 0; j < SURVEY_CATEGORIES ; j++){
            printf("%d\t\t", rentalSurvey[i][j]);
        }
        printf("\n");
    }
    
}
// couldnt get to work in enough time 
char getValidYN(void){
    char input [2]; // enough space for a char and null
    int validInput = 0;
    
    while(!validInput){
        puts("Enter y or n");
        //input = getchar();
        fgets(&input[0], sizeof(input), stdin);
        
       // fgetsRemoveNewLine(input);
        
        // Clear input buffer
        //int c;
       // while ((c= getchar()) != '\n' && c != EOF);
        

        // convert to lower case
        input[0] = tolower(input[0]);
        fgetsRemoveNewLine(input);
        
        if(input[0] == 'n'|| input[0] == 'y'){
            
            validInput = 1;
            
        } else {
            
            puts("You did not enter a y or n.\n");
        }
        
        
    } // end of while
    return input[0];
}

double calculateFare(rideShare *rideSharePtr) {
    
    rideSharePtr -> rideFare = rideSharePtr -> baseFare + (rideSharePtr -> costPerMinute * rideSharePtr ->minutes) + (rideSharePtr -> costPerMile * rideSharePtr -> miles);
    
    if (rideSharePtr -> rideFare < MIN_FLATRATE) {
        return MIN_FLATRATE;
    } else {
        return rideSharePtr -> rideFare;
    }
    
} // end of calculateFare

// surveycount, miles minutes, ridefare
void printFare(rideShare *rideSharePtr) {
    printf("\nCurrent Ride Information\n");
    printf("Rider\tNumber of Miles\tNumber of Minutes\tRide Fare Amount\n");
    printf("%d\t%.1f\t\t%d\t\t\t$%.2f\n", rideSharePtr -> surveyCount, rideSharePtr -> miles, rideSharePtr -> minutes, rideSharePtr -> rideFare);
    
} // end of printFare


//3.1



bool scanDouble (const char *buffer, double *output) {
    
    // declare  end pointer
    char *endPtr;
    errno = 0; // reset errno
    
    // convert the buffer string to a double
    double dblTest = strtod(buffer, &endPtr);
    
    // check for errors
    if(endPtr == buffer){
        fprintf(stderr, "%s: not a valid double\n", buffer);
        return false;
    } else if ('\0' != *endPtr) {
        fprintf(stderr, "%s: extra characters at end of input: %s\n", buffer, endPtr);
        return false;
    } else if ((dblTest == DBL_MAX || dblTest == DBL_MIN) && errno == ERANGE) {
        fprintf(stderr, "%s: out of range of type double\n", buffer);
        return false;
    } else {
        *output = dblTest;
        printf("%lf is a valid double\n", *output);
        return true;
    }
}
void displayRideShareRatings(unsigned int *surveyCount, const unsigned int survey[][SURVEY_CATEGORIES], rideShare *rideSharePtr) {
    printf("%s Ratings\n", rideSharePtr -> organizationName);
       
       if (*surveyCount == 0) {
           puts("No Ratings Currently");
       } else {
           printf("Survey\t");
           for (size_t j = 0; j < SURVEY_CATEGORIES; j++) {
               printf("%s\t", surveyCategories[j]);
           }
           printf("\n");
           
           for (size_t i = 0; i < *surveyCount; i++) {
               printf("%zu\t", i + 1);
               for (size_t j = 0; j < SURVEY_CATEGORIES; j++) {
                   printf("%u\t", survey[i][j]);
               }
               printf("\n");
           }
       }
} // displayRideShareRatings

// couldnt get to work in enough time
void getRideShareRatings(unsigned int survey[][SURVEY_CATEGORIES], unsigned int *surveyCount, size_t total_categories) {
    
    for(size_t categories = 0; categories < total_categories; categories++) {
      
        for(size_t categories = 0; categories < total_categories; categories++) {
            double rating;
            bool validInput = false;
            do {
                printf("Enter your rating for %s (1-5): ", surveyCategories[categories]);
                if (!scanDouble("", &rating)) {
                    printf("Invalid input. Please enter a number between 1 and 5.\n");
                } else if (rating < 1.0 || rating > 5.0) {
                    printf("Invalid rating. Please enter a number between 1 and 5.\n");
                } else {
                    validInput = true;
                }
            } while (!validInput); // Loop until valid input is provided

            survey[*surveyCount][categories] = (unsigned int)rating;
            (*surveyCount)++;
        }
   
    }
    
    puts("");
    
} // getRideShareRatings

void ridersMode(rideShare *rideSharePtr){
    
    //3.1
    displayRideShareRatings(&(rideSharePtr->surveyCount), rideSharePtr->rentalSurvey, rideSharePtr);
    
    printf("Do you want to request a ride from %s " , rideSharePtr -> organizationName);
    getValidYN();
    
    if(getValidYN() == 'n') {
        displayRideShareRatings(&(rideSharePtr->surveyCount), rideSharePtr->rentalSurvey, rideSharePtr);
        
    } else {
        //3.3
        
        puts("Enter the number of miles to your destination: ");
        rideSharePtr-> miles = getValidDoubleSentinel(MIN_MILES, MAX_MILES, SENTINAL_VALUE);
        if(rideSharePtr-> miles == SENTINAL_VALUE) {
            bool loginStatus = adminLogin();
            if(loginStatus == true) {
                puts("Admin Shutdown");
                // go to 4.1 display report
            }
            
        } else {
            
            int minMinutes = (int)(MIN_RAND_MINUTES_FACTOR * rideSharePtr-> miles);
            int maxMinutes = (int)(MAX_RAND_MINUTES_FACTOR * rideSharePtr-> miles);
            
            rideSharePtr-> minutes = calculateRandomNumber(minMinutes, maxMinutes);
            
            calculateFare(rideSharePtr);
            printFare (rideSharePtr);
            
            
            // increment totals
            rideSharePtr -> totalMiles += rideSharePtr -> miles;
            rideSharePtr -> totalMinutes += rideSharePtr -> minutes;
            rideSharePtr -> totalFare += rideSharePtr -> rideFare;
            
            // 3.4 get ratings
            puts("Do you want to rate your rideShare experience?");
            if(getValidYN() == 'n') {
                puts("Thanks for riding with us");
                //3.1
                displayRideShareRatings(&(rideSharePtr->surveyCount), rideSharePtr->rentalSurvey, rideSharePtr);
                
            } else {
                getRideShareRatings(rideSharePtr->rentalSurvey, &(rideSharePtr->surveyCount), SURVEY_CATEGORIES);
                //3.1
                displayRideShareRatings(&(rideSharePtr->surveyCount), rideSharePtr->rentalSurvey, rideSharePtr);
                
            }

        }
        
        
        
    }
    
    
}
                                    

