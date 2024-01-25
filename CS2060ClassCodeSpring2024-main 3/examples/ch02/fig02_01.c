// fig02_01.c
// A first program in C.
#include <stdio.h>

// function main begins program execution 
int main(void) {
   //printf("Welcome to C!\n");
    int length;
    int width;
    int area;
    int scanfReturn;
    
    
    printf("%s","Enter the length: ");
    scanfReturn = scanf("%d", &length);
    getchar(); // clear buffer
    
    // get valid length input
    while (scanfReturn != 1) {
        printf("%s","Enter an integer for length: ");
        scanfReturn = scanf("%d", &length);
        getchar(); // clear buffer
        
    }
    
    // get width input
    printf("%s","Enter the width: ");
    scanf("%d", &width);
    
    area = length * width;
    
    printf("Length: %d , Width: %d, Area: %d\n", length, width, area);
    
    // get average of length & width
    double average = (double)(length * width) / 2;
    
    // display to 1 decimal
    printf("Average: %.1f", average);
    printf("\n");
    
    return 0;
    
} // end function main





/**************************************************************************
 * (C) Copyright 1992-2021 by Deitel & Associates, Inc. and               *
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
 *************************************************************************/
