//
// Created by caoth on 29/03/2023.
//

#ifndef PROJET_QCM_OPENCV_H
#define PROJET_QCM_OPENCV_H

#endif //PROJET_QCM_OPENCV_H


#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

double angle( Point pt1, Point pt2, Point pt0 );

void localiserCarre( const Mat& , std::vector<std::vector<Point> >&);

void IdentificationReponse(const Mat&, std::vector<std::vector<Point> >&, std::vector<std::vector<int>>&);

void constructReponse(const Mat&, std::vector<std::vector<int>>&);

void findSquares( const Mat& image, std::vector<std::vector<Point> >& squares );
//void stockerPancarte();

int Trouvercouleur(Mat &);

void ParcourirCarre(Mat &, char carton[26], Point, Point, int , int);
