// Randomly generate numbers between a min and max for user to guess.


// header files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constants
#define MIN 1
#define MAX 1000

// function protype
void guessGame(void); 
bool isCorrect(int guess, int answer); 

int main(void) {
    //
   //srand(time(0));
    printf("Hello Lae ");
    
   // function being called
   guessGame();
} // end main



// 
void guessGame(void) {
    
    // variables
   int response =0;
   int guess = 0;

   // do while loop for game
   do {

      // random number generator
      int answer = 1 + rand() % MAX;

      // display
      printf("I have a number between %d and %d.\n", MIN, MAX);

      // display
      puts("Can you guess my number?\n" 
           "Please type your first guess.");

      // get guess ?
      printf("%s", "? ");
      

      // get guess ?
      scanf("%d", &guess);

      // repeat until guess is correct
      while (!isCorrect(guess, answer)) {
         scanf("%d", &guess);
      }


      puts("\nExcellent! You guessed the number!\n"
         "Would you like to play again?");
      printf("%s", "Please type (1=yes, 2=no)? ");
      scanf("%d", &response);
      puts("");

   } while (response == 1);
} // end function guessGame

// checks if guess is correct
bool isCorrect(int guess, int answer) {

    // variable
    bool correct = false;

   // checks if guess is correct
   if (guess == answer) {
      correct = true;
   }

   // if guess is to low or to high, display 
   if (guess < answer) {
      printf( "%s", "Too low. Try again.\n? " );
   }
   else {
      printf( "%s", "Too high. Try again.\n? " );
   }

   return correct;
} // end function isCorrect





/**************************************************************************
 * (C) Copyright 1992-2012 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/
