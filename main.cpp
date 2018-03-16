/*
 * main.cpp file
 * Author: Aryan Gupta
 * Date: 2/27/18
 * This program takes in up to 100 numbers or a filename that contains a list of numbers (ranging from 1-1000) 
 * seperated by spaces and adding them to a heap (to create a max heap) and then remove those numbers in order from the
 * heap and add them to the output.
 */

#include <iostream>
#include <cstring>
#include <limits>
#include <fstream>

using namespace std;

// function prototypes
void maxHeapify(int (&A)[100], int i, int elements);
void createMaxHeap(int (&A)[100], int elements);
void sort(int (&A)[100] , int elements);
void print(int A[100], int n, int start, int elements);

int main() {

  char option[10]; // stores if user wants to manually input or enter a filename
  bool validOption = false; // makes sure if user entered a valid option
  int numbers[100]; // array used for the heap
  
  ifstream inFile;
  
  // prompt user for a selection
  cout << "Do you want to manually input (type MANUAL) numbers or enter a filename (type FILE)? ";
  while(validOption == false) {
  cin.getline(option, 10);
  if(strcmp(option, "MANUAL") == 0) {
    validOption = true;
    int input = 0; // stores users input
    int count = 0; // keeps track of how many numbers have been added
    
    // tell user what to do
    cout << "You may now enter up to 100 numbers. The numbers must range from 1-1000 inclusive." << endl;
    cout << "Enter the number 10000 if you are done adding numbers." << endl;
    while(input != 10000) {
      // prompt user
      cout << "Enter a number: ";
      cin >> input;
      // if the user's input is not an integer
      if(cin.fail()) {
	cout << "Invalid input type. Please enter an integer." << endl;
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      // if the users input isn't within the range
      else if(input < 1 || input > 1000) {
	// check if user is done adding numbers
	if(input == 10000) {
	  cout << "Done adding to the list." << endl;
	  cout << "Printing List." << endl;
	}
	else {
	  cout << "The number you entered is not within the specified range (1-1000 inclusive)." << endl;
	}
      }
      // otherwise continue with the making of the heap
      else {
	numbers[count] = input; // store input to the array for heap
	count++; // add 1 to the number of numbers of entered here
	// if the user has entered more numbers than stated
	if(count > 100) {
	  cout << "You have already entered the max amount of number (100)." << endl;
	  cout << "Printing List." << endl;
	  input = 10000; // exits the input loop to print the list
	}
      }
    } // while(input != 10000)
    
    // print the list here
    sort(numbers, count);
    cout << "In order..." << endl;
    for(int i = count - 1; i >= 0; i--) {
      cout << numbers[i] << " ";
    }
    
  } // if(strcmp(option, "MANUAL") == 0)
  else if(strcmp(option, "FILE") == 0) {
    validOption = true;
    int elements = 0;
    
    cout << "Files: test.txt" << endl;
    char filename[100]; // stores the filename the user inputs
    char input[10000]; // for the numbers in the file
    
    // prompt user for a file
    cout << "Enter a filename: ";
    cin.getline(filename, 100);
    inFile.open(filename);
    while(!inFile) {
      cout << "The file you entered does not exist. Try Again: ";
      cin.getline(filename, 100);
    }
    inFile.getline(input, 10000);
    // split the file up by the spaces
    char* split;
    split = strtok(input, " ");
    while(split != NULL) {
      numbers[elements] = atoi(split);
      elements++;
      split = strtok(NULL, " ");
    }

    // MAX HEAP TAKING TIME!!!!!!!!!!!!
    sort(numbers, elements);
    cout << "In order..." << endl;
    for(int i = elements - 1; i >= 0; i--) {
      cout << numbers[i] << " ";
    }
  } // else if(strcmp(option, "FILE") == 0)
  // the user didn't input a valid option
  else {
    cout << "Enter a valid option (MANUAL or FILE): ";
    validOption = false;
  }
  } // while(validOption == false)
} // int main()

// functions

void maxHeapify(int (&A)[100], int i, int elements) {
  // children
  int left = (2 * i) + 1;
  int right = (2 * i) + 2;
  // keep track of parent-child
  int largest = i;
  if(left < elements && A[left] > A[i]) {
    largest = left;
  }
  if(right < elements && A[right] > A[largest]) {
    largest = right;
  }
  if(largest != i) {
    swap(A[i], A[largest]);
    maxHeapify(A, largest, elements);
  }
}

void createMaxHeap(int (&A)[100], int elements) {
  int size = elements;
  for(int i = (elements/2) - 1; i >= 0; i--) {
    maxHeapify(A, i, elements);
  }
}

void sort(int (&A)[100], int elements) {
  createMaxHeap(A, elements);
  cout << "Printing." << endl;
  print(A, 1, 0, elements);
  cout << "\n";
  for(int i = elements - 1; i >= 0; i--) {
    swap(A[0], A[i]);
    maxHeapify(A, 0, i);
  }
}

//
void print(int A[100], int n, int start, int elements) {
  for(int i = 0; i < n; i++) {
    if(!(start + i >= elements)) {
      cout << A[start + i] << "   ";
    }
    else {
      return;
    }
  }
  cout << "\n";
  print(A, n * 2, start + n, elements);
}
