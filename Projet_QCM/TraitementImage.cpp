//
// Created by caoth on 29/03/2023.
//

#include "TraitementImage.h"
/*****************************************************************************************
Nom :
	Calcul d'angle
Role :
	Calcul d'angle à partir de trois points (trigonométrie)
Parametres passes :
	3 variables de types Point

Valeur renvoyee :

    double renvoie la valeur de l'angle calculé
******************************************************************************************/
double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);

}

/*****************************************************************************************
Nom :
	LocaliserCarre

Role :
	Permet de localiser les carrés blancs des cartons dans la photo prise

Parametres passes :

	const Mat& image : l'adresse d'une image sur laquelle travaillé
    std::vector<std::vector<Point> >& squares: conteneur de conteneur contenant des variables de type Point (conteneur de polygone)
Valeur renvoyee :
	-
******************************************************************************************/

void localiserCarre( const Mat& image, std::vector<std::vector<Point> >& squares ){

    Mat img_gray;
    cvtColor(image, img_gray, COLOR_BGR2GRAY);
    //met l'image en gris
    //threshhold = niveau de seuil
    Mat thresh;
    //met l'image en noir et blanc en appliquant le seuillage
    // si la valeur du pixel > 150, les pixels deviennent blanches, sinon le reste < 150 deviennent noirs
    threshold(img_gray,thresh,150,255,THRESH_BINARY);
    //imshow("tresh",thresh);
    //waitKey(0);


    std::vector<std::vector<Point>> contours;

    std::vector<Vec4i> hierarchy;
    //trouve les différents contours sur l'image
    findContours(thresh, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);
    //polylines(image, contours,true, Scalar (0,255,0), 2 ,LINE_AA);
    //imshow("contours",image);
    //waitKey(0);


    std::vector<Point> approx;
    for (int i=0; i <contours.size();i++){

        //approxPolyDP() -> trouve approximativement des courbes polygonales en fonction de la précision donnée
        // contourArea() -> calcul une zone de contour, retourne un nombre
        // arcLenght() -> calcul un périmètre ou une longueur de courbe, retourne un nombre
        //fabs() -> calcul d'un nombre absolu
        //isContourConvex()  -> vérifie si c'est convex
        approxPolyDP(contours[i],approx, arcLength(contours[i],true)*0.02,true);
        //std::cout<<contourArea(approx)<<std::endl;
        if (approx.size()==4 && fabs(contourArea(approx))>1000 && fabs(contourArea(approx))<7000 && isContourConvex(approx)){

            double maxCos =0;

            for (int j = 2; j<5; j++ ){
                //calcul de l'angle
                double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                maxCos = MAX(maxCos,cosine);

            }

            if (maxCos < 0.3){
                // si l'angle est égal à environ 90°
                squares.push_back(approx);


            }

        }
    }

}

/*****************************************************************************************
Nom :
	IdentificationReponse

Role :
	Permet de localiser les cartons de l'image puis construit les différents réponses à partir des cartons

Parametres passes :

	const Mat& image : l'adresse d'une image sur laquelle travaillé
    std::vector<std::vector<Point> >& squares: l'adresse conteneur de conteneur contenant des variables de type Point (conteneur de polygone)
    std::vector<std::vector <int>> a carton : l'adresse conteneur des réponses de chaque élève contenant eux même des 0 et des 1 représentant le nombre de carré blanc et noir dans le carton
 Valeur renvoyee :
	- rien
******************************************************************************************/


void IdentificationReponse(const Mat& image, std::vector<std::vector<Point> >& squares, std::vector<std::vector<int>> & carton){
    Mat copy=image.clone();
    //std::cout<<squares.size()<<std::endl;
    //std::cout<<squares[0].size()<<std::endl;
    for (int i =0; i<squares.size();i++){
        //std::cout<<squares[i]<<std::endl;
        //Les points formant le carré
        Point a=squares[i][0];
        //Point b=squares[i][1];
        Point c=squares[i][2];
        //Point d=squares[i][3];

        Point ecart;
        //calcul de la distance entre le point A et le point C
        ecart.x=c.x-a.x;
        ecart.y=c.y-a.y;

        // déplacement des coordonnées de a et c
        a.x=a.x-(ecart.x*2.4);
        a.y=a.y-(ecart.y*2.4);

        //b.x=b.x-(ecart.x*2.2);
        //b.y=b.y+(ecart.y*2.2);

        c.x=c.x+(ecart.x*2.4);
        c.y=c.y+(ecart.y*2.4);

        //d.x=d.x-(ecart.x*2.2);
        //d.y=d.y-(ecart.y*2.2);

        //int largeur =fabs(c.x-a.x);
        //int hauteur =fabs(a.y-c.y);

        // largeur et hauteur approximative du carton
        int largeur =fabs(c.x-a.x);
        int hauteur =fabs(a.y-c.y);

        //std::cout<<a<<std::endl;
        //std::cout<<c<<std::endl;
        //std::cout<<largeur<<std::endl;
        //std::cout<<hauteur<<std::endl;

        //création du rectangle permmetant de rogner l'image
        Rect rect(a.x,a.y,largeur,hauteur);

        Mat rogne=image(rect);
        //liste_pancarte.push_back(rogne);
        //imshow("rogne",rogne);
        //rectangle(copy, a,c,Scalar (255,0,0),1,LINE_AA);
        //imshow("trouver pancarte",copy);
        //waitKey(0);
        constructReponse(rogne,carton);


    }

}

/*****************************************************************************************
Nom :
	constructReponse

Role :
	Permet de construire les réponses à partie d'un carton isolé au préalable

Parametres passes :

	const Mat& image : l'adresse d'une image sur laquelle travaillé
    std::vector<std::vector <int>> a carton : l'adresse conteneur des réponses de chaque élève contenant eux même des 0 et des 1 représentant le nombre de carré blanc et noir dans le carton
 Valeur renvoyee :
	-
******************************************************************************************/

void constructReponse(const Mat & image, std::vector<std::vector<int>> & reponse) {

    //Ce portion de code est similaire à celui de localiserCarre()
    Mat image_copy = image.clone();
    std::vector<std::vector<Point> > squares;
    localiserCarre(image, squares);
    //std::cout << squares[0] << std::endl;

    //polylines(image_copy, squares, true, Scalar(0, 255, 0), 2, LINE_AA);
    //imshow("isole", image);
    //waitKey(0);

    std::vector<int> carton; // conteneur des 0 et 1 du carton (conteneur de carré noir et blanc)

    Point ecart;
    Point depart;
    Point a = squares[0][0];
    //Point b=squares[0][1];
    Point c = squares[0][2];
    //Point d=squares[0][3];

    //calcul de la distance entre le point A et le point B
    ecart.x = c.x - a.x;
    ecart.y = c.y - a.y;
    //déplace le point a en haut et vers le côté droit du carton
    a.x = a.x - (ecart.x * 2);
    a.y = a.y - (ecart.y * 2);

    //b.x=b.x-(ecart.x*2);
    //b.y=b.y-(ecart.y*2);
    //déplace le point c en bas et vers le côté gauche du carton
    c.x = c.x - (ecart.x * 2);
    c.y = c.y - (ecart.y * 2);

    depart = a; //position initiale d'un des points du carton
    //std::cout<<depart<<std::en0dl;
    int largeur = fabs(c.x - a.x);
    int hauteur = fabs(a.y - c.y);

    for (int r=0; r<5;r++) {

        for (int i =0; i < 5; i++) {

            Rect rect(a.x, a.y, largeur, hauteur);//image comprenant qu'une partie du carton (un carré blanc/noir)
            Mat rogne = image(rect);//image contenant un carré noir/blanc du carton
            Mat img_gray;
            cvtColor(rogne, img_gray, COLOR_BGR2GRAY);
            //Application du binary threshholding, mettre l'image en noir et blanc
            //threshhold = niveau de seuil
            Mat thresh;
            // si la valeur du pixel > 150, les pixels deviennent blanches, sinon le reste < 150 deviennent noirs
            threshold(img_gray, thresh, 150, 255, THRESH_BINARY);
            //imshow("carre", thresh);
            //waitKey(0);
            int CouleurCarre = Trouvercouleur(thresh);//trouve la couleur d'un des carrés du carton
            carton.push_back(CouleurCarre);//ajout de 1 ou 0 dans le vector

            a.x += ecart.x; // déplace le point A en horizontale, ce qui permet de passer au carré suivant



        }

        a= depart;
        a.y+=ecart.y;
        depart.y+=ecart.y;
        //déplace verticalment le point a, ce qui permet de passer à la ligne suivante de carré du carton



    }

    reponse.push_back(carton);// ajoute la réponse dans un conteneur


}

/*****************************************************************************************
Nom :
    constructReponse

Role :
    Permet de trouver la couleur d'un carré d'un carton

Parametres passes :

    const Mat& image : l'adresse d'une image sur laquelle travaillé (un carré d'un carton)

Valeur renvoyee :
    -int : 1 si le carré est blanc, sinon 0 si le carré est noir
******************************************************************************************/

int Trouvercouleur(Mat &img) {

    int nbPnoir = 0;//nb de pixel noir dans le carré
    int nbPblanc = 0;//nb de pixel blanc dans le carré
    Scalar intensity;//Variable prenant la valeur RGB du pixel
    for (int r = 0; r < img.rows; r++) {

        for (int c = 0; c < img.cols; c++) {

            Scalar intensity = img.at<uchar>(r, c);
            //std::cout<<intensity.val[0]<<std::endl;
            if (intensity.val[0] == 255) { //vérifie si le pixel est blanc

                nbPblanc += 1;

            } else {
                nbPnoir += 1; //sinon le pixel est noir
            }

        }
        //std::cout << nbPnoir << std::endl;
        //std::cout << nbPblanc << std::endl;

    }

    char CarreCouleur;
    if (nbPnoir > nbPblanc) { // on détermine la couleur du carré en vérifiant si il y a plus de pixel noir ou de pixel blanc

        CarreCouleur = 0;

    } else {
        CarreCouleur = 1;
    }

    return CarreCouleur;

}


