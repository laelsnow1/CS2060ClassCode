//
//  Snow_iter03.c
//  CS2060CProject
//
//  Created by lael Snow on 4/24/24.
//

#include "Snow_iter03.h"

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
#define CORRECT_PASSCODE "abcd"
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
typedef struct rideShare {
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
    struct rideShare *next;
    struct rideShare *head;
    struct rideShare *tail;
    
} rideShare;

// function prototypes
bool adminLogin(void); // good
bool scanDouble (const char *buffer, double *output);
void fgetsRemoveNewLine(char *stringPtr); // good  need
int calculateRandomNumber(int min, int max); // need
void setUpRideShare (rideShare *rideSharePtr);
double getValidDouble(double min, double max);
void displayRideShareRatings(unsigned int *surveyCount, const unsigned int survey[][SURVEY_CATEGORIES], rideShare *rideSharePtr);
void getRideShareRatings(unsigned int survey[][SURVEY_CATEGORIES], unsigned int *surveyCount,rideShare *rideSharePtr);
void ridersMode(rideShare *rideSharePtr);
double calculateFare(rideShare *rideSharePtr); // need
void getRatings(unsigned int rentalSurvey[][SURVEY_CATEGORIES ], unsigned int *ridersCount, const char *surveyCategories[]);
void printFare(rideShare *rideSharePtr); // need
double getValidInput(char *setup, double min, double max);
double getValidDoubleSentinel(int min, int max, int sentinel); // for miles  need
char getValidYN(void); // need
void displayRideShareDetails (const rideShare *rideSharePtr);
void writeSummaryToFile(rideShare *rideSharePtr);

void displayRideShareRatingsAlpha(rideShare *rideSharePtr);




int main(int argc, const char * argv[]) {
    
    // seed for the random generator with current time
       srand((unsigned int) time(NULL));
    
    
    rideShare rideShareInfo;
    
    
    rideShareInfo.head = NULL; // head pointer to NULL
    
    
    
    // 1.1 get valid id and pw
    if( adminLogin()) {
        printf("Login Successful\n\n");
        
        // user 2 admin Ride Share set up
        setUpRideShare(&rideShareInfo);
        
        // sort the rides alphabetically
        
        
    } else {
        printf("Exiting RideShare\n");
        // end program
        return 0;
    }
    
    // 3.1 display ride share name and ratings
   // displayRideShareRatingsAlpha(&rideShareInfo);
  
    // Rider mode
    ridersMode(&rideShareInfo);

    

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
    
    char addOrganization;
    
    do {
        
        rideShare *newRideInfo = (rideShare *)malloc(sizeof(rideShare)); // allocate enough memory
        if (newRideInfo == NULL) {
            printf("Memory FAILED!!");
            exit (EXIT_FAILURE); // exit?
        }
        
        printf("Enter the RideShare Organization Name:\n ");
        fgets(newRideInfo -> organizationName, STRING_LENGTH, stdin);
        fgetsRemoveNewLine(newRideInfo-> organizationName);
        
        printf("Enter the base fare: ");
        newRideInfo -> baseFare = getValidDouble(MIN_SET_UP, MAX_SET_UP);
        
        printf("Enter the cost per minute: ");
        newRideInfo -> costPerMinute = getValidDouble(MIN_SET_UP, MAX_SET_UP);
        
        printf("Enter the cost per mile: ");
        newRideInfo -> costPerMile = getValidDouble(MIN_SET_UP, MAX_SET_UP);
        
        printf("Enter the minimum flat rate: ");
        newRideInfo -> minFlatRate = getValidDouble(MIN_SET_UP, MAX_SET_UP);
        
        // Initialize surveyCount to zero
        newRideInfo ->surveyCount = 0;
        
        newRideInfo -> next = NULL;
        
        if(rideSharePtr -> head == NULL) {
            rideSharePtr ->head = newRideInfo;
            rideSharePtr -> tail = newRideInfo;
        } else {
            rideSharePtr ->tail->next = newRideInfo;
            rideSharePtr -> tail = newRideInfo;
            
        }
        puts("Do you want to add another rideshare");
        addOrganization = getValidYN();
        
        
    } while (addOrganization == 'y' ||addOrganization == 'Y');
    
    // display the ride share details for each organization
    rideShare *current = rideSharePtr ->head;
    while(current != NULL) {
        displayRideShareDetails(current);
        current = current -> next;
    }
    

}

void displayRideShareDetails (const rideShare *rideSharePtr) {
    
    printf("\nRideshare details\n");
       printf("%s", rideSharePtr->organizationName);
       printf("Base fare: %.2f\n", rideSharePtr->baseFare);
       printf("Cost Per Minute: %.2f\n", rideSharePtr->costPerMinute);
       printf("Cost Per Mile: %.2f\n", rideSharePtr->costPerMile);
       printf("Minimum flat rate: %.2f\n", rideSharePtr->minFlatRate);
       printf("Exiting Admin Mode\n\n");
    
    
} // end


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
    
    char validYesNo;
  
        do {
            puts("Please enter (y)es or (n)o:");
            
            validYesNo = getchar();
            while (getchar() != '\n');
            
            validYesNo = tolower(validYesNo);
            

        } while (validYesNo != 'y' && validYesNo != 'n');

        return  validYesNo;

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
   // Sort the linked list alphabetically by organization name
    
    
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

void getRideShareRatings(unsigned int survey[][SURVEY_CATEGORIES], unsigned int *surveyCount, rideShare *rideSharePtr) {
    puts("Do you want to rate your rideShare experience?");
    char rateChoice;
    
    do {
        rateChoice = getValidYN();
        if(rateChoice != 'y' && rateChoice != 'n') {
            printf("You did not enter a valid option. Please enter 'y' for yes or 'n' for no.\n");
            printf("Do you want to rate your rideshare experience? ");
        }
    } while (rateChoice != 'y' && rateChoice != 'n');
    
    
    if(rateChoice == 'y') {
        puts("Thanks for riding with us");
        //3.1 get ratings from the rider
        
        // increment the survey count
       // rideSharePtr -> surveyCount++;
        (*surveyCount)++;
        
        printf("Enter your ratings for the ride-sharing experience:\n");
        
        // Loop through each survey category
        for (size_t category = 0; category < SURVEY_CATEGORIES; category++) {
            unsigned int rating;
            bool validInput = false;
            
            // Keep prompting until a valid rating is provided
            do {
                printf("Rate %s (1-5): ", surveyCategories[category]);
                if (scanf("%u", &rating) != 1 || rating < 1 || rating > 5) {
                    printf("Invalid input. Please enter a number between 1 and 5.\n");
                    while (getchar() != '\n'); // Clear input buffer
                } else {
                    validInput = true;
                }
            } while (!validInput); // Loop until valid input is provided

            // Store the rating in the survey array
            survey[*surveyCount][category] = rating;
        }

        // Increment the survey count for specific organization
        //rideSharePtr -> surveyCount++;
        
        // go back to 3.1 for the next customer
        ridersMode(rideSharePtr);
       // displayRideShareRatingsAlpha(rideSharePtr);
        
    } else {
        printf("Thanks for riding with us. \n\n");
        // 3.1 display ride share name and ratings
        displayRideShareRatingsAlpha(rideSharePtr);
    }
    
    
    
    
    
} // end

void ridersMode(rideShare *rideSharePtr){
    
    
    
    // 3.1 display ride share name and ratings
    displayRideShareRatingsAlpha(rideSharePtr);
    
    //3.2 Enter the name of the Ride Share
    char rideChoice[STRING_LENGTH];
    bool found = false;
    
    do {
        printf("Enter the name of the Ride Share: ");
        fgets(rideChoice, STRING_LENGTH, stdin);
        fgetsRemoveNewLine(rideChoice);
        
        // Traverse the linked list to check if correct
        rideShare *current = rideSharePtr -> head;
        while (current != NULL) {
            if(strcmp(rideChoice, current -> organizationName) == 0) {
                found = true;
                // break ?
            }
            current = current -> next;
        }
        
        if(!found) {
            printf("Incorrect name try again\n\n");
            // 3.1 display ride share name and ratings
            displayRideShareRatingsAlpha(rideSharePtr);
            
        } else {
            // 3.3 Get the number of miles
            puts("Enter the number of miles to your destination: ");
            rideSharePtr-> miles = getValidDoubleSentinel(MIN_MILES, MAX_MILES, SENTINAL_VALUE);
            
            if(rideSharePtr-> miles == SENTINAL_VALUE) {
                // prompt for admin login if sentinel value is entered
                if( adminLogin()){
                    puts("Admin Shutdown");
                    
                    // go to 4.1 display report & shut down return;
                    writeSummaryToFile(rideSharePtr);
                }
                
            } else {
                // calculate minutes
                int minMinutes = (int)(MIN_RAND_MINUTES_FACTOR * rideSharePtr-> miles);
                int maxMinutes = (int)(MAX_RAND_MINUTES_FACTOR * rideSharePtr-> miles);
                
                rideSharePtr-> minutes = calculateRandomNumber(minMinutes, maxMinutes);
                
                // calculate ride fare
                calculateFare(rideSharePtr);
                
                // display ride faer charge
                printFare (rideSharePtr);
                
                
                // increment totals
                rideSharePtr -> totalMiles += rideSharePtr -> miles;
                rideSharePtr -> totalMinutes += rideSharePtr -> minutes;
                rideSharePtr -> totalFare += rideSharePtr -> rideFare;
                
                
                // 3.4 get ratings
                getRideShareRatings(rideSharePtr->rentalSurvey, &(rideSharePtr->surveyCount), rideSharePtr);
                
                //3.1  Display updated ratings
                displayRideShareRatingsAlpha(rideSharePtr);
                
            }
            
        }
    } while (!found);
        
    }
    
    
    
    void displayRideShareRatingsAlpha(rideShare *rideSharePtr) {
        
        // Sort the linked list alphabetically by organization name
        rideShare *current = rideSharePtr->head;
        rideShare *sorted = NULL;
        
        while (current != NULL) {
            rideShare *next = current->next;
            if (sorted == NULL || strcmp(current->organizationName, sorted->organizationName) < 0) {
                current->next = sorted;
                sorted = current;
            } else {
                rideShare *search = sorted;
                while (search->next != NULL && strcmp(search->next->organizationName, current->organizationName) < 0) {
                    search = search->next;
                }
                current->next = search->next;
                search->next = current;
            }
            current = next;
        }
        rideSharePtr->head = sorted;
        
        // Traverse the linked list and display the ratings for each ride share
        current = rideSharePtr->head;
        while (current != NULL) {
            printf("%s Ratings\n", current->organizationName);
            if (current->surveyCount == 0) {
                puts("No Ratings Currently\n\n");
            } else {
                printf("Survey\t");
                for (size_t j = 0; j < SURVEY_CATEGORIES; j++) {
                    printf("%s\t", surveyCategories[j]);
                }
                printf("\n");
                
                
                // dispay the survey ratings
                for (size_t i = 0; i < current->surveyCount; i++) {
                    printf("%zu\t", i + 1);
                    for (size_t j = 0; j < SURVEY_CATEGORIES; j++) {
                        printf("%u\t", current->rentalSurvey[i][j]);
                    }
                    printf("\n");
                }
            }
            // move to the next org. in  linked list
            current = current->next;
        }
    }

void writeSummaryToFile(rideShare *rideSharePtr){
    
    
    char fileName[STRING_LENGTH];
    FILE *filePtr;

       // Replace spaces in organization name with underscores for file name
       for (size_t i = 0; rideSharePtr->organizationName[i] != '\0'; i++) {
           if (rideSharePtr->organizationName[i] == ' ') {
               fileName[i] = '_';
           } else {
               fileName[i] = rideSharePtr->organizationName[i];
           }
       }
       fileName[strlen(rideSharePtr->organizationName)] = '\0';

       // Open file for writing
       filePtr = fopen(fileName, "w");
       if (filePtr == NULL) {
           printf("Error: Unable to create file.\n");
           return;
       }

       // Write summary header to file
       fprintf(filePtr, "[%s] Summary Report\n\n", rideSharePtr->organizationName);

       // Write ride summary to file
       fprintf(filePtr, "Rider\tNumber of Miles\tNumber of Minutes\tRide Fare Amount\n");
       fprintf(filePtr, "%d\t%.1f\t\t%d\t\t\t$%.2f\n", rideSharePtr->surveyCount, rideSharePtr->miles, rideSharePtr->minutes, rideSharePtr->rideFare);

       // Calculate and write average ratings to file
       fprintf(filePtr, "\nCategory Rating Averages\n");
       for (size_t i = 0; i < SURVEY_CATEGORIES; i++) {
           unsigned int sum = 0;
           for (size_t j = 0; j < rideSharePtr->surveyCount; j++) {
               sum += rideSharePtr->rentalSurvey[j][i];
           }
           double averageRating = (double)sum / rideSharePtr->surveyCount;
           fprintf(filePtr, "%zu. %s\t%.1f\n", i + 1, surveyCategories[i], averageRating);
       }

       fprintf(filePtr, "\nExiting RideShare Program\n");

       // Close file
       fclose(filePtr);
   }
