//
//  snow_iter01.c
//  CS2060CProject
//
//  Created by lael Snow on 2/14/24.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>


// used to generate random number of minutes based on number of miles
#define MIN_RAND_MINUTES_FACTOR 1.2
#define MAX_RAND_MINUTES_FACTOR 1.5
// sentinel value to end rider mode
#define SENTINEL_VALUE -1


// function prototypes
double getValidDouble(int min, int max, int sentinel);
double calculateFare(double base, double minuteCost, double mileCost, double minRate, double miles, int minutes);
void printFare(int count, double miles, int minutes, double fare);


int main(int argc, const char * argv[]) {
    // inItialize variables
       //min and max miles range
       int minMiles = 1;
       int maxMiles = 100;
       //example ride calculation values
       double baseFare = 1.8;
       double costPerMinute = .25;
       double costPerMile = 1.2;
       double minFlatRate = 20.0;
    
        int rideCount = 1;
        double miles;
        double rideFare;
        int minutes;
    
        double totalMiles = 0;
        int totalMinutes = 0;
        double totalFare = 0;
    
    
    // seed for the random generator with current time
    srand((unsigned int) time(NULL));
    
    
    puts("Welcome to the UCCS Ride Share. We can only provide services for rides from 1 to 100.\n");
    
    int sentinelInput = 0; // flag to track if the sentineal value is entered
    
    while(!sentinelInput) {
        puts("Enter the number of miles to your destination: ");
        miles = getValidDouble(minMiles, maxMiles, SENTINEL_VALUE);
        if(miles == SENTINEL_VALUE) {
            // SET FLAG TO INDICATE THE SENTINEL VALUE IS ENTERED
            sentinelInput = 1;
            
        } else {
            // calculate random number of mins from miles
            int minMinutes = (int)(MIN_RAND_MINUTES_FACTOR * miles);
            int maxMinutes = (int)(MAX_RAND_MINUTES_FACTOR * miles);
            minutes = rand() % (maxMinutes - minMinutes + 1) + minMinutes;
            
            // calculate ride fare
            rideFare = calculateFare(baseFare, costPerMinute, costPerMile, minFlatRate, miles, minutes);
            
            // Add ride details to total
                totalMiles += miles;
                totalMinutes += minutes;
                totalFare += rideFare;
            
            // print ride fare details
            printFare(rideCount, miles, minutes, rideFare);
            rideCount++;
            
            
        }
        
    } // end of while
    
    puts("\nUCCS Ride Share Business Summary\n");
    // print summary
    puts("\nUCCS Ride Share Business Summary\n");
        printf("Total number of rides: %d\n", rideCount - 1);
        printf("Total miles: %.2f\n", totalMiles);
        printf("Total minutes: %d\n", totalMinutes);
        printf("Total fare: $%.2f\n", totalFare);
    
    
    return 0;
} // end of main

// functions

double getValidDouble(int min, int max, int sentinel) {
    double value;
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
