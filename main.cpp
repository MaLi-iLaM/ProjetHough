#include <iostream>
#include <cmath>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

#include "Image.hpp"
#include "Matrice.hpp"

#include "Point.hpp"


Image lirefichier ()
{
    std :: ifstream monfichier ("m1projetcpp2.ppm"); // Ouverture du fichier
    Image image;
    if (monfichier) // On s'assure que le fichier est bien ouvert
    {
        
        int compteur=0; // Le compteur ne tient pas compte des commentaires, et permet d'évoluer dans le code au rythme prédéfini.
        
        std :: string ligne; 
        while(getline(monfichier, ligne)) 
            {
                if (ligne[0] != '#')  // On ignore les commentaire du fichier ppm
                {
                    if (compteur == 0)
                    {
                        // Récupération du numéro de variante
                        
                        image.qualite = ligne; 

                    }
                    else
                    {
                        if (compteur == 1)
                        {           
                           
                            std :: array<int,2> resolution;
                            std::string parseNum;
                            std::stringstream streamLigne(ligne);
                            int res=0;
                            while(std::getline(streamLigne,parseNum,' '))
                            {
                                resolution[res] = std::stoi(parseNum);
                                res++;
                            } 
                            image.ligne = resolution[0];
                            image.colonne = resolution[1];
                            
                        }
                    else
                    {
                        if (compteur==2)
                        {
                            // Récupération de la valeur maximale
                            image.valmax = std :: stoi(ligne);
                        }
                        else  // Si le compteur vaut 3
                        {  
                            // On initialise une matrice 3D avec la valeur 0
                            std :: array<int,3>  vecteur;
                            std :: vector<std :: array<int,3> > intermediaire (image.colonne, vecteur)  ;
                            image.image = std :: vector<std :: vector< std:: array<int,3>>>  (image.ligne,intermediaire) ;
                            
                            // On boucle sur la largeur de l'image, sa hauteur, et pour chaque composante de la couleur    
                            for (int i = 0;i<image.ligne;i++)
                            { 
                                for (int j =0; j< image.colonne; j++)
                                {
                                    for (int k=0; k<3;k++) // Boucle sur la couleur
                                    {
                                        // On affecte la valeur récupérée dans l'image
                                        image.image[i][j][k] = stoi (ligne);  // Cette ligne est en premier, car la première valeur a été récupérée dans la condition du while
                                        getline(monfichier,ligne); 
                                    }
                                }

                            }
                            return image; // On retourne l'image 
                        }
                    }
                }
                compteur ++;

            }

        }
    }
    std :: cout << "Attention, il y a eu une erreur." ;
    return image ; 
}

std ::vector<Point> Houghnormale(std ::vector<Point> vecpoints)
{
    int N = 60;
    Matrice buffer(N,N);
    for (unsigned int i= 0; i< vecpoints.size(); i++) // On boucle sur tous les points différents du fond, ceux qu'on nous a transmis
    {
        for ( int j=0; j<N/2; j++) // On boucle sur une fenetre près établie
        {
                
            if (vecpoints[i].x * j + vecpoints[i].y>(-N/2 )&& vecpoints[i].x * j + vecpoints[i].y<N/2) // on trace la droite et on s'intéresse aux points dans la fenetre
            {
                buffer.mat[j+N/2][vecpoints[i].x * j + vecpoints[i].y+N/2] ++; // On incrémente chaque point sur une droite
            }
        }
    }
    float min = 0; 
    std ::vector<Point> vec;
    Point coormax;
    for (int i=0 ; i<N; i++)
    {
        for (int j=0;j<N;j++)
        {
                
            if (min<buffer.mat[i][j]) // On retient tous les points qui sont traversés par une droite
            {
                
                coormax.x = i -N/2;
                coormax.y = j-N/2;
                vec.push_back(coormax); // On l'ajoute à notre tableau de points final
            }
        }
    }
    return vec;
}


int main ()
{
    Image A;    
    std :: vector<Point> vec, res;
    
    A = lirefichier();

    vec = A.donnerdroites();
    res = Houghnormale(vec);

    A.Doublons(res);
    A.ecrire_fichier();

    return 0;
}