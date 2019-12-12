#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/videoio.hpp>



using namespace cv;
using namespace std;


//RNG rng(12345);


int main(int argc, char** argv)
{

    int hueB = 170;
    int hueH = 179;

    int satB = 110;
    int satH = 230;

    int valB = 60;
    int valH = 255;
    //int thresh = 100;
    //RNG rng(12345);
    VideoCapture vid("C:/Users/Gilles/source/repos/opendv-test/opendv-test/test.mp4");

    if (!vid.isOpened())  // if not success, exit program
    {
        cout << "Can't get this file" << endl;
        return -1;
    }

    int posX = -1;
    int posY = -1;

    //Capture a temporary image from the camera
    Mat fraTP;
    vid.read(fraTP);

    //Create a new iamage same size
    Mat imgLines = Mat::zeros(fraTP.size(), CV_8UC3);

    while (true)
    {
        Mat fraOrgn;


        bool bSuccess = vid.read(fraOrgn); // read a new frame from video



        if (!bSuccess) //if unsuccessful, stop the while()
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        Mat imgHSV;

        cvtColor(fraOrgn, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

        Mat newVid;

        inRange(imgHSV, Scalar(hueB, satB, valB), Scalar(hueH, satH, valH), newVid); //Threshold the image

        

        //Calculate the moments of the thresholded image
        Moments oMoments = moments(newVid);

        double dM01 = oMoments.m01;
        double dM10 = oMoments.m10;
        double areaComplete = oMoments.m00;

        // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
        if (areaComplete > 10000)
        {
            //Get the position of santa
            int posX = dM10 / areaComplete;
            int posY = dM01 / areaComplete;

            if (posX >= 0 && posY >= 0 && posX >= 0 && posY >= 0)
            {
                //Draw a red line from the previous point to the current point
                line(imgLines, Point(posX, posY), Point(posX, posY), Scalar(0, 0, 255), 2);
            }

            posX = posX;
            posY = posY;
        
        }
        

        

        imshow("Thresholded Vid", newVid); //show the thresholded image

        fraOrgn = fraOrgn + imgLines;
        imshow("Original", fraOrgn); //show the original image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
    }

    return 0;

}
