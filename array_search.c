// Author: Isaiah Vogt
// Author email: ivogt@csu.fullerton.edu
// CPSC 223C-1
// Due Date: 02/21/2024 11:59pm
//
// Program Name: Array Search for Character Frequency in a File:
// This program demonstrates the use of the C language's file opening, reading, and writing methods, file pointer capacities,
// and input/output functionality. The program asks the user for a file to search for. Then, the program opens the file and
// copies the contents of the file to an array of char, taking heed of the proper size to allocate. The program calculates the
// number of characters and then asks the user to input string(s) to find the position of. The user can type `control + d` to
// terminate the program.
// Files in this program: array_search.c, r.sh
// Date of last update: 2024-Feb-20
// Status: Finished. The program was tested extensively with no errors in 11.1.0ubuntu4.
//
// Compile: gcc -c -Wall -m64 -no-pie -fno-pie -o search.o array_search.c -std=c2x
// Link: gcc -m64 -no-pie -fno-pie -o search.out search.o -std=c2x
//
// OS developed on: 11.1.0ubuntu4
// OS developed on: 11.1.04ubuntu4

#include <stdio.h> //sizeof, stdin, fgets, printf, fseek, fopen, fgetc, fclose
#include <string.h> //strlen, strncmp

int main(int argc, char* argv[])
{
    //string of user file-input
    char get_file[64];

    //size of user file-input
    unsigned int index = 0;

    //used to insert each char into array of file contents
    unsigned int temp_file_pointer = 0;

    printf("Please enter the name of your file: ");

    //retrieve user input for file
    fgets(get_file, 64, stdin);
    
    //removes last byte of user input
    get_file[strlen(get_file) - 1] = '\0';

    //check for valid input and ask user for another input if not found
    while(!fopen( get_file, "r" )){
        printf("Sorry. File was not found. Try again.\n");
        printf("Please enter the name of your file: ");
        fgets(get_file, 64, stdin);
        get_file[strlen(get_file) - 1] = '\0';

    }
    //open file for reading
    FILE *fp = fopen( get_file, "r" );
    printf("The file has been opened with read permission.\n");

    //move file pointer to the end of the file for getting size
    fseek( fp, 0, SEEK_END );

    //copy position of file pointer to file_size to allocate to new array
    long file_size = ftell( fp );

    //move file pointer to the beginning of the file
    fseek(fp, 0, SEEK_SET);

    //array storing file contents and add null terminator at end
    char file_contents[file_size + 1];

    //eliminate white space using fgetc from get_file by copying file contents to one-dimensional array
    while( EOF != ( temp_file_pointer = fgetc( fp ) ) )
    {
        file_contents[index] = temp_file_pointer;
        index++;
    }

    //add null terminator
    file_contents[index] = '\0';

    //close get_file
    fclose(fp);

    //number of chars in file
    printf( "The file contains %li characters.\n", strlen( file_contents ) );

    //confirmation of copying of file contents to user
    printf( "The file has been copied to a one-dimensional array\n" );

    //buffer for user search input
    char buffer[strlen(file_contents)];

    //stores index of searched char found in file_contents
    int locations[strlen(file_contents)];

    //index to char in locations array
    unsigned int locations_index = 0;
    for( ;; )
    {
        printf( "\nEnter a string to find or enter cntl+d to terminate: ");

        //<cntl + d> points to end of file, if it is inputted, it is stored in res and if equal to EOF,
        //break the loop and end the program
        int res = scanf( "%s", buffer );
        if( res == EOF ) break;

        //the length of the buffer can be ommitted from the number of searched chars
        //since it would be found regardless.
        //not omitting the buffer length would accomplish nothing and is costlier.
        for( int i = 0; i <= ( strlen( file_contents ) - strlen( buffer ) ); i++ )
        {
            //on each iteration, shorten the length of the file contents by iterating forward
            //and compare to the buffer. strlen( buffer ) ensures that only the length of the buffer
            //is being read
            //strncmp returns 0 if there is a match
            if( strncmp( file_contents + i, buffer, strlen( buffer ) ) == 0 )
            {
                //store the indexes of the occurrence of the buffer
                locations[locations_index] = i;
                //iterate the index for further searches
                locations_index++;
            }
        
        }
        //display the word
        printf("%s was found at positions: ", buffer);
        
        // if locations_index is zero, then it was not iterated and no occurrences were found
        //use continue to allow for another user input for a searched char
        if( locations_index == 0 )
        {
            printf("none");
            continue;
        }
        
        //print index(s) of found char
        for( unsigned int i = 0; i < locations_index; i++ )
        {
            printf( "%u ", locations[i]);
        }

        //reset locations_index to 0 for further user input
        locations_index = 0;

        //clear buffer for invalid user input
        scanf("%*[^\n]");
    }

    //nice message
    printf("\nThank you for using this search program.\n\nHave a good day. We hope you enjoyed the string search.\nCome back any time for more searching. Bye\n");

    return 0;
}