
//Description: Recursively find a path that touches all vacant spaces

using namespace std;

#include <iostream>
#include <fstream>

const int fieldSize = 7;
const int space = 32;

int endX, endY;

// function to recursively find a path that occupies all vacant spaces
// marks 1-9 or A-Z to spaces it travels on
// returns false if it cant travel anywhere else
// returns false if it reaches destination but did not mark all vacant spaces
// returns true if it reaches destination and marked all vacant spaces

bool findPath(char field[][fieldSize], int startX, int startY, int stepCounter, int vacantSpaces)
{
    // base cases
    // if at end and all vacant spaces are occupied then path found
    if (( (startX==endX) && (startY==endY) ) && (stepCounter == vacantSpaces))
        return true;

    // if at end but not all vacant spaces are occupied then back track
    if (( (startX==endX) && (startY==endY) ) && (stepCounter != vacantSpaces))
        return false;

    // if stepcounter exceeds 10 
    // skip the characters in between 9 and A
    int path = (stepCounter < 10) ? 48 : 55;

    // check up 
    if(startX-1 >= 0 && field[startX-1][startY] == space)
    {   
        // mark that space
        field[startX-1][startY] = stepCounter + path;

        // recursive call
        if(findPath(field, startX-1, startY, stepCounter+1, vacantSpaces))
            return true;

        // if it returned false then unmark that space
        field[startX-1][startY] = space;
    }

    // check down
    if(startX+1 < fieldSize && field[startX+1][startY] == space)
    {
        field[startX+1][startY] = stepCounter + path;

        if(findPath(field, startX+1, startY, stepCounter+1, vacantSpaces))
            return true;

        field[startX+1][startY] = space;        
    }

    // check left
    if(startY-1 >= 0 && field[startX][startY-1] == space)
    {
        field[startX][startY-1] = stepCounter + path;

        if(findPath(field, startX, startY-1, stepCounter+1, vacantSpaces))
            return true;

        field[startX][startY-1] = space;
    }

    // check right
    if(startY+1 < fieldSize && field[startX][startY+1] == space)
    {
        field[startX][startY+1] = stepCounter + path;

        if(findPath(field, startX, startY+1, stepCounter+1, vacantSpaces))
            return true;

        field[startX][startY+1] = space;
    }
    
    // if there is nowhere to travel return false (back track)
    return false;
}


// main will ask for a file, you may use the files provided in this folder
// reads the file and save it into a 2D array
// counts the amount of vacant spaces
// asks user for the starting position and end position of the path
// calls the recursive function 
// prints the array after it finds a path that travels through all vacant spaces


int main()
{   
    int vacantSpaces = 0;

    // attempt to open the file
    ifstream infile;
    string filename;

    while(true)
    {   
        cout<<"Enter config file: ";
        getline(cin, filename);
        cout<<endl;
        infile.open(filename.c_str());
        if(infile) break;
        cout<<"Invalid file!"<<endl;
    }

    // populate the array 
    char field[fieldSize][fieldSize];
    string line;
    
    for(int i = 0; i!=fieldSize; i++)
    {   
        getline(infile, line);
        for(int j = 0; j!=fieldSize; j++)
        {   
            // count all the vacant spaces
            // that the path can travel
            if(line[j] == space)
                vacantSpaces++;
            
            field[i][j] = line[j];
        }
    }
    
    // debug purposes
    //cout<<vacantSpaces<<endl;
    
    // ask for the starting and ending coordinates
    int startX, startY;

    cout<<"Please enter starting coordinates: ";
    cin>>startX>>startY;
    cout<<endl;

    // debug purposes
    //cout<<startX<<" "<<startY<<" "<<endl;

    cout<<"Please enter end coordinates: ";
    cin>>endX>>endY;
    cout<<endl;

    // debug purposes
    //cout<<endX<<" "<<endY<<" "<<endl;

    // start finding a path
    // mark the starting position with 0 then call the recursive function
    field[startX][startY] = '0';
    findPath(field, startX, startY, 1, vacantSpaces);
    
    // print the array
    for(int i=0; i<fieldSize; i++)
    {
        for(int j=0; j<fieldSize; j++)
            cout<<field[i][j]<<" ";
        
        cout<<endl;
    }
    
    return 0;
}

