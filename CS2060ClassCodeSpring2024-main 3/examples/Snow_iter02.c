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

#define STRING_LENGTH 80
#define MAX_SET_UP 50.0
#define MIN_SET_UP 0.1
#define MAX_ATTEMPTS 4
#define ROWS 4
#define COLUMNS 2
#define SURVEY_CATEGORIES 3
// sentinel value to end rider mode
#define SENTINEL_VALUE -1

// used to generate random number of minutes based on number of miles
#define MIN_RAND_MINUTES_FACTOR 1.2
#define MAX_RAND_MINUTES_FACTOR 1.5

// function prototypes
double getValidInput(char *setup, double min, double max);
double getValidDouble(int min, int max, int sentinel); // for miles
int adminLogin(void);
char getValidYN(void);

//3.1 info
void displayRideShareInfo(const char *rideShareName, const char *surveyCategories[], size_t totalCategories, int rentersCount);

//displays the strings
void printCategories(const char *categories[], size_t totalCategories);

// print survey results
void printSurveyResults (int rentalSurvey[][COLUMNS], int rentersCount);

double calculateFare(double base, double minuteCost, double mileCost, double minRate, double miles, int minutes);
void printFare(int count, double miles, int minutes, double fare);


void printInfo(char string[], double baseFare,double costPerMin, double costPerMile, double minFlatRate);
void getRatings(int rentalSurvey[][COLUMNS], int rentersCount, const char *surveyCategories[]);




int main(int argc, const char * argv[]) {
    // seed for the random generator with current time
       srand((unsigned int) time(NULL));
    
    double baseFare;
    double costPerMin;
    double costPerMile;
    double minFlatRate;
    double rideFare;
    double totalMiles = 0;
    double totalFare = 0;
    
    int minutes;
    int miles;
    int totalMinutes = 0;
    //min and max miles range
    int minMiles = 1;
    int maxMiles = 100;
    int rideCount = 1;
    int rentersCount = 1;
    
    char rideShareName[SIZE];
    char *rideShareNamePtr = rideShareName;
    
    char id[SIZE];
    char pw[SIZE];
    
    char *idPtr = id;
    char *pwPtr = pw;
    
    //2D array for Renters and categories
    int rideShareSurvey [ROWS][COLUMNS];
    
    // 2D array for rental survey
    int rentalSurvey  [ROWS][COLUMNS];
    
    //1D array for category averages
    int categoryAverages [3];
    
    // This will allow you to iterate through an array of strings to display the survey categories.
    const char *surveyCategories[SURVEY_CATEGORIES] = {"Safety", "Cleanliness", "Comfort"};
    
    // PUT IN METHODS :
    
    
    // 1.1 get valid id and pw
    if(adminLogin() == 1) { // if success go to user story 2
        printf("Login Success");
        
        //User Story2: Admin RideShare Set up
        // 2.1 - 2.6 get info, name, and rideshare details
        puts("\nSetup RideShare Info: ");
        
        baseFare = getValidInput("Enter Base Fare: ", MIN_SET_UP, MAX_SET_UP);
        costPerMin = getValidInput("Enter Cost Per Min: ", MIN_SET_UP, MAX_SET_UP);
        costPerMile = getValidInput ("Enter Cost Per Mile: ", MIN_SET_UP, MAX_SET_UP);
        minFlatRate = getValidInput("Enter Min Flat Rate: ", MIN_SET_UP, MAX_SET_UP);
        
        // Get Ride Share Organizaion Name
        puts("\nEnter your RideShare Organization Name");
        getchar();
        fgets(rideShareName, SIZE, stdin);

        
        // Display Rideshare details
        printInfo(rideShareName, baseFare, costPerMin, costPerMile, minFlatRate);
        
    } else {
        printf("Exiting RideShare\n");
        // end program
        return 0;
    }
    
    
    
    // User Story 3 Rider Mode
    
    //3.1 display & display ride share rating collections so far
    displayRideShareInfo(rideShareName, surveyCategories, SURVEY_CATEGORIES, 4);
    
  
    // Prompt
    printf("Do you want to request a ride from %s \n", rideShareName);
    
    char choice = getValidYN();
    if (choice == 'n') {
        // go back to 3.1
        displayRideShareInfo(rideShareName, surveyCategories, SURVEY_CATEGORIES, 4);
    } else { //'y'
        // go to 3.3
        
        puts("Enter the number of miles to your destination: ");
        miles = getValidDouble(minMiles, maxMiles, SENTINEL_VALUE);
        if(miles == SENTINEL_VALUE) {
            if(adminLogin() == 1) {
                puts("Admin shutdown. Exiting RideShare Mode");
                // go to user story 4.1
                
            } else {
                // go to 3.1
                displayRideShareInfo(rideShareName, surveyCategories, SURVEY_CATEGORIES, 4);
            }
            
            
            
        } else { // if correct miles entered,
            // calculate random number of mins from miles
                        int minMinutes = (int)(MIN_RAND_MINUTES_FACTOR * miles);
                        int maxMinutes = (int)(MAX_RAND_MINUTES_FACTOR * miles);
                        minutes = rand() % (maxMinutes - minMinutes + 1) + minMinutes;
                        
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
                getRatings(rentalSurvey, rentersCount,surveyCategories);
                
                // go back to 3.1
                displayRideShareInfo(rideShareName, surveyCategories, SURVEY_CATEGORIES, 4);
                
            }
                    }
            
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

double getValidDouble(int min, int max, int sentinel) {
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

int adminLogin(void){
    
    char userId[] = [STRING_LENGTH];
    char userPw[] = [STRING_LENGTH];
    
    int counter = 1;
    int validInput = 0;
    
    puts("Admin Login");
       
        
    while (!validInput) {
            puts("Enter your Admin ID");
            fgets(id, SIZE, stdin);
            id[strcspn(id, "\n")] = '\0'; // remove trailing newline !!

            puts("Enter your Admin password");
            fgets(pw, SIZE, stdin);
            pw[strcspn(pw, "\n")] = '\0'; // remove trailing newline !!
            
            if (strcmp(id, correctID) == 0 && strcmp(pw, correctPW) == 0) {
                validInput = 1;
            } else {
                if (counter < 4) {
                    puts("Error, incorrect ID or PW");
                    counter++;
                } else {
                    puts("Exiting Rideshare");
                    return 0; // Exit the program
                }
            }
        }
        
    return validInput; // succesful login
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

void printSurveyResults (int rentalSurvey[][COLUMNS], int rentersCount) {
    
    for(size_t i = 0; i < rentersCount; i++ ){
        printf("Survey %lu:\t", i + 1);
        
        for(size_t j = 0; j < COLUMNS; j++){
            printf("%d\t\t", rentalSurvey[i][j]);
        }
        printf("\n");
    }
    
}

char getValidYN(void){
    char input = '\0';
    int validInput = 0;
    
    while(!validInput){
        puts("Enter y or n");
        input = getchar();
        
        // Clear input buffer
        while (getchar() != '\n');
        
        // convert to lower case
        input = tolower(input);
        
        if(input == 'n'|| input == 'y'){
            
            validInput = 1;
            
        } else {
            puts("You did not enter a y or n.\n");
        }
        
        
    } // end of while
    return input;
}
double calculateFare(double base, double minuteCost, double mileCost, double minRate, double miles, int minutes) {
    
    double rideFare = base + (minuteCost * minutes) + (mileCost * miles);
    
    if (rideFare < minRate) {
        return minRate;
    } else {
        return rideFare;
    }
    
} // end of calculateFare

void printFare(int count, double miles, int minutes, double fare) {
    printf("\nCurrent Ride Information\n");
    printf("Rider\tNumber of Miles\tNumber of Minutes\tRide Fare Amount\n");
    printf("%d\t%.1f\t\t%d\t\t\t$%.2f\n", count, miles, minutes, fare);
    
} // end of printFare

void getRatings(int rentalSurvey[][COLUMNS], int rentersCount, const char *surveyCategories[]) {
    
    puts("We want to know how your experience was on your ride today. Using the rating system 1 to 5 enter your rating for each category:");
    puts("enter your rating for each category 1. Safety                2.Cleanliness        3. Comfort");
    // iterate over each column
    for(size_t i = 0; i < SURVEY_CATEGORIES; i++) {
       
        // get input
        scanf("%d", &rentalSurvey[rentersCount][i]);
        int rating = 0;
        int validInput = 0;
        
        while(!validInput){
            printf("Enter your rating for %s", surveyCategories[i]);
            // Get input
                        if (scanf("%d", &rating) != 1 || rating < 1 || rating > 5) {
                            // Clear input buffer
                            while(getchar() != '\n');
                            
                            printf("Invalid input. Please enter a rating between 1 and 5.\n");
                        } else {
                            // Valid input, store in the survey array
                            rentalSurvey[rentersCount][i] = rating;
                            validInput = 1;// Exit the loop when valid input is entered
                        }
        }
    }
    
    
}

//3.1

void displayRideShareInfo(const char *rideShareName, const char *surveyCategories[], size_t totalCategories, int rentersCount) {
    printf("Welcome to the %s. We only provide services for rides from 1 to 100 miles\n", rideShareName);
    printCategories(surveyCategories, totalCategories);
    printSurveyResults(surveyCategories, rentersCount);
}
