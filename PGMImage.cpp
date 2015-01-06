#include "PGMImage.h"

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace std;

PGMImage::PGMImage()
{
    //ctor
}

PGMImage::PGMImage(string pathToImage)
{
    ifstream fin(pathToImage.c_str());

    string fileType;
    getline(fin, fileType);
    if(fileType != "P5" && fileType != "P2") {
        throw invalid_argument("Invalid PGM image type: " + fileType);
    }

    string dimensions;
    getline(fin, dimensions);

    istringstream iss(dimensions);
    iss >> numCols >> numRows;

    data = new int[numRows*numCols];

    string maxValStr;
    getline(fin, maxValStr);
    iss.str(maxValStr);

    int maxVal = atoi(maxValStr.c_str());

    if(fileType == "P2") {
        int ii = 0;
        while(fin.good()) {
            string line;
            getline(fin, line);

            istringstream iss2(line);
            string val;
            while(iss2 >> val) {
                data[ii] = atoi(val.c_str());
                ii++;
            }
        }
    }
    else { // P5
        int ii = 0;

        unsigned char *c = new unsigned char(numRows*numCols);
        unsigned char *index = c;
        while(fin.good()) {
            char lo;
            fin.get(lo);
            data[ii] = (unsigned char)lo;
            *index = (unsigned char) lo;
            index++;
            ii++;
        }

        for (int jj = 0; jj < numRows*numCols; jj++) {
            data[jj] = (int)c[jj];
        }
    }

    fin.close();
}

int *PGMImage::getData()
{
    return data;
}

void PGMImage::printData()
{
    for(int ii = 0; ii < numRows*numCols; ii++) {
        cout << data[ii] << " ";
    }
    cout << endl;
}

PGMImage::~PGMImage()
{
    delete [] data;
}
