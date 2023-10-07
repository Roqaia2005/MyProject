
// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:				ImgProccesing.cpp
// Last Modification Date:	xx/xx/xxxx
// Author1 and ID and Group:	Roqaia Hassan Hassan , ID:20220129
// Author2 and ID and Group:	Fatima Atef ,ID:
// Author3 and ID and Group:	Tasnim Gomaa Anter ,ID:20220089
// Teaching Assistant:		xxxxx xxxxx
// Purpose:..........


#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char grayImage[SIZE][SIZE];
unsigned char darkImage[SIZE][SIZE];
unsigned char lightImage[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char mergedImage[SIZE][SIZE];
unsigned char black_white_image[SIZE][SIZE]; //black and white
unsigned char flippedImg[SIZE][SIZE];


void loadGrayImage ();
void loadImage1 ();
void loadImage2 ();
void saveBlackWhite ();
void saveMergedImage ();
void saveFlippedImage ();
void darken();
void lighten();
void choose();
void saveDarkImg ();
void saveLightImg ();




void BlackAndWhite (); //filter1
void flip();//filter 4
void merge(); //filter3


int main()
{
    while(true){
        cout<<"Please select a filter to apply or 0 to exit:";
        int filter;cin>>filter;
        if(filter==0){
            break;
        }
        else{

            switch (filter) {

                case 0:
                    break;
                case 1: // filter 1 black and white
                    loadGrayImage();
                    BlackAndWhite();
                    saveBlackWhite();
                    showGSBMP(black_white_image);
                    break;
                case 3:  //filter 3 merge images

                    loadImage1();
                    loadImage2();
                    merge();
                    saveMergedImage();
                    showGSBMP(mergedImage);
                    break;
                case 4: //filter 4 flip image
                    loadGrayImage();
                    flip();
                    saveFlippedImage();
                    showGSBMP(flippedImg);
                    break;
                case 6: //filter 6 lighten or darken
                    loadGrayImage();
                    choose();
                    break;



                default:
                    cout<<"Invalid filter";

            }

        }


    }





  return 0;
}

//_________________________________________

void loadGrayImage () { // function to load gray image we will make change on it
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, grayImage);
}
//_________________________________________
// filter 1 convert grayscale image to black_white_image
void BlackAndWhite() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            black_white_image[i][j]=grayImage[i][j];
            if (grayImage[i][j] > 110) {

                black_white_image[i][j] = 255; // white
            } else {
                black_white_image[i][j] = 0; // black
            }
        }
    }
}
//--------------------------------------------------------
void saveBlackWhite () { // function to save image after convert it to black_white_image
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,black_white_image);

}

// function to load first image to merge with another image
void loadImage1 () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image1);
}
// function to load second image to merge with first image
void loadImage2() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Please enter name of image file to merge with:  : ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);



}
// merge filter which take average of the two images I want to merge
void merge(){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){      //we make nested loop that loop over every pixel

            mergedImage[i][j] = (image1[i][j]+image2[i][j])/2; //we make summation between two images and divide it by 2 make them blending
        }
    }
}



//-----------------------------------------------
// function to save merged image
void saveMergedImage () {
        char imageFileName[100];

        // Get gray scale image target file name
        cout << "Enter the target image file name: ";
        cin >> imageFileName;

        // Add to it .bmp extension and load image
        strcat (imageFileName, ".bmp");

        writeGSBMP(imageFileName,mergedImage);

}


//-----------------------------------------

void flip(){
    char mode ;
    cout<<"Flip (h)orizontally or (v)ertically ?";
    cin>>mode;
    if(mode=='H'|| mode=='h'){
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){

                flippedImg[i][j]=grayImage[SIZE-i][j];

            }
        }


    }
    else if(mode=='V'||mode=='v'){

        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                flippedImg[i][j]=grayImage[i][SIZE-j];

            }
        }

    }
    else{
        cout<<" Invalid mode";
    }

}
void saveFlippedImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,flippedImg);

}

//--------------------------------------------------------------------------------
void darken(){//darken filter it make the image darker to 50%
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            //we make nested loop that loop over every pixel
            darkImage[i][j]=grayImage[i][j]/2; //to make image darker we will reduce it to its half to reach its darker mode
        }
    }

}
void lighten() {//darken filter it make the image lighter to 50%
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {            //we make nested loop that loop over every pixel

            lightImage[i][j]= grayImage[i][j]+(255-grayImage[i][j])/2;// we make this equation to reach to the highest light for the image
        }

    }
}


void choose(){ //function choose that help user to choose what change he wants to make in image
    char type;
    cout<<"Do you want to (d)arken or (l)ighten?(enter one character d or l)"<<"\n";
    cin>>type;//the user will enter char d or l to choose the change he wants
    if(type=='d'){
        darken();
        saveDarkImg();
        showGSBMP(darkImage);
    }
    else if(type=='l'){
        lighten();
        saveLightImg();
        showGSBMP(lightImage);
    }
}

void saveDarkImg () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,darkImage);

}
void saveLightImg () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");

    writeGSBMP(imageFileName,lightImage);

}












