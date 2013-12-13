#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <time.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

#define num_of_categories 5 // Require number of categories
#define num_of_trains 2000 // max number of trains
#define num_of_trackgroups 15 // max number of track groups
#define typedGate std::pair<int, void*> // A0 B1 F5 P15 S18 T19 Y24
//typedef std::pair<int, int> reustPair;


/********************************* READING FILE METHODS ************************************/

// read resource name from pFile and return the first character of resource name minus 'A'

int resourceNumber;

static int readResourceName(FILE * pFile)
{
    char c,c0,c1;
    c0 = fgetc(pFile);
    while(true)
    {
        c1 = c;
        c = fgetc(pFile);
        if(c==';') break;
    }
    resourceNumber = c1-'0';
    return c0-'A';
}

// ignore the first line in pFile including the property names of the object
static void ignoreFirstLine(FILE * pFile)
{
    char mystring[200];
    if ( fgets (mystring , 200 , pFile) != NULL )
        puts ("Ignore the following line:");
    puts (mystring);
}


/*************************** Vector Operation ****************************************/

// Initialize a class T vector(using REFERENCE instead of POINTER) from a file exiting at path

template <class T>

void initVector(std::vector<T> &vec, std::string path)

{
    vec.clear();
    FILE * pFile = fopen (path.c_str(), "r");
    if (pFile == NULL) 
        perror ("Error opening file");
    else
    {
        std::cout << "\nTSET IS HERE\n";
        ignoreFirstLine(pFile);
        while(true)
        {
            if(feof(pFile))
            {
                std::cout << "It is EOF\n";
                break;
            }
            T t;
            t.setupFromFile(pFile);
            //       t.print();
            vec.push_back(t);
            //std::cout << "VEC SIZE is " << vec.size() << std::endl;
        }
        fclose (pFile);
    }
}
// Show vector storing primitives

template <class T>

void showPrimitiveVector(std::vector<T> &vec)

{
    typename std::vector<T>::iterator it;
    for(it = vec.begin(); it!=vec.end(); it++)
    {
        //std::cout << "Print a element in the vector\n";
        std::cout << (*it);
        std::cout << std::endl;
    }
}
// Show all the element in the class T vector(using REFERENCE instead of POINTER)

template <class T>

void showVector(std::vector<T> &vec)

{
    typename std::vector<T>::iterator it;
    for(it = vec.begin(); it!=vec.end(); it++)
    {
        //std::cout << "Print a element in the vector\n";
        (*it).print();
        std::cout << std::endl;
    }
}


template <class T>

void showPointerVector(std::vector<T> &vec)
{
    typename std::vector<T>::iterator it;
    for(it = vec.begin(); it!=vec.end(); it++)
    {
        //std::cout << "Print a element in the vector\n";
        (*it)->printBasicInfo();
    }
}

