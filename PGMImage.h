#ifndef PGMIMAGE_H
#define PGMIMAGE_H

#include <string>

class PGMImage
{
    public:
        PGMImage(std::string pathToImage);
        int *getData();
        void printData();
        ~PGMImage();
    protected:
    private:
        PGMImage();

        int numRows;
        int numCols;
        int *data = NULL;
};

#endif // PGMIMAGE_H
