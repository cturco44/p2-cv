#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <cstring>
#include "Image.h"
#include "processing.h"

using namespace std;

int main( int argc, char**argv )
{
    assert(argc >= 4);
    
    //open file stream
    ifstream in;
    in.open(argv[1]);

    //check if open was successful
    if( !in.is_open())
    {
        cout <<"open failed" <<endl;
        exit(1);
    }

    //create new image
    Image *temp = new Image;
    Image_init(temp, in);

    //Convert cstrings to ints
    int width = atoi(argv[3]);
    int height = atoi(argv[4]);

    //Modify image
    seam_carve(temp,width,height);

    //Print out modified image
    ofstream out;
    out.open(argv[2]);
    Image_print(temp, out);
    
    //Close everything
    in.close();
    out.close();
    delete temp;

}