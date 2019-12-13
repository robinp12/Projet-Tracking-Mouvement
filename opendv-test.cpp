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

    if (!vid.isOpened())  // si ça ne fonctionne pas, quitter le programme
    {
        cout << "Can't get this file" << endl;
        return -1;
    }

    int posX = -1;
    int posY = -1;

    // avoir une image temporaire de la vidéo
    Mat fraTP;
    vid.read(fraTP);

    //Créer une nouvelle image de même taille
    Mat imgLines = Mat::zeros(fraTP.size(), CV_8UC3);

    while (true)
    {
        Mat fraOrgn;
        Mat imgHSV;
        Mat newVid;
        
         cvtColor(fraOrgn, imgHSV, COLOR_BGR2HSV); //convertir la frame de BGR en HSV

        

        inRange(imgHSV, Scalar(hueB, satB, valB), Scalar(hueH, satH, valH), newVid); //Threshold l'image

        bool okayV = vid.read(fraOrgn); // lire une nouvelle frame de la vidéo



        if (!okayV) //si ça ne fonctionne pas stopper la boucle
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }
        

        //trouver le centre de la masse
        Moments masse = moments(newVid);

        double dM01 = masse.m01;
        double dM10 = masse.m10;
        double areaComplete = masse.m00;
 
        if (zoneTot > 10000)
        {
            //Noter la position de la cible
            int varX = dM10 / zoneTot;
            int varY = dM01 / zoneTot;

            if (posX >= 0 && posY >= 0 && posX >= 0 && posY >= 0)
            {
                //tracer une ligne rouge qui va de la dernière position à la position actuelle
                line(imgLines, Point(posX, posY), Point(posX, posY), Scalar(0, 0, 255), 2);
            }

            varX = varX;
            varY = varY;
        
        }
        

        

        imshow("Thresholded Vid", newVid); //monter l'image treshold

        fraOrgn = fraOrgn + imgLines;
        imshow("Original", fraOrgn); //montrer l'image de base avec la ligne

        if (waitKey(30) == 27) //commande pour recevoir "esc" et quitter
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
    }

    return 0;

}
