#include"Image.hpp"

double Norme(double x, double y) 
{
    return sqrt(abs(x- y));
}

void Image ::  afficheImage() // Fonction particulièrement utile pour le débug, peu dans le programme final.
{
    for (int i=0; i<ligne; i++)
    {
        for (int j=0;j<colonne; j++)
        {
            std:: cout<< " (";
            for (int k=0; k<3; k++)
            {
                if (k!= 2)
                std :: cout << image[i][j][k]<<", ";
                else
                std :: cout << image[i][j][k]<< ") ";
            }
        }
        std::cout << std :: endl;
    }
}

std::vector<Point> Image :: donnerdroites () // Permet de récupérer les points de couleurs. Renvoie un tableau avec les coefficients directeurs pret pour la transformée de Hough.
{
    std::vector<Point> pntdroites;

    for (int i=0; i<ligne ; i++) 
    {
        for (int j=0;j<colonne; j++) 
        {
            // Si la couleur est noire ou blanche, le pixel est considéré comme le fond de l'image, on ne s'en soucie pas.
            if (((image[i][j][0]==image[i][j][1])&&(image[i][j][1]==image[i][j][2]))&&(image[i][j][0]==0|| image[i][j][0]==255))
            {
                // On se trouve dans le fond
            }
            else // Dans le cas contraire, on retient le point pour le mettre dans un tableau.
            {
                Point P{(float)-i, (float) j};
                pntdroites.push_back(P);
                
            }
                
        }
    }
    return pntdroites;
}

void Image ::Doublons ( std :: vector<Point> res) // Supprime les doublons des droites avant de les créer.
{
    // La fonction est très spécifique à l'image m1projetcpp2.ppm

    // Pour chaque 'groupe' de droite, on a récupéré les différents groupe de droites
    for (int i=0 ; i<res.size(); i++) 
    {   
        std::vector<Point> vec_doublons;
        if (res[i].x == 0) 
        {
            do 
            {
                vec_doublons.push_back(res[i]);
                i ++;

            }while (res[i].y+1 == res[i+1].y);
        }
        else 
        {
            do 
            {
                vec_doublons.push_back(res[i]);
                i ++;

            }while (res[i].y+1 == res[i+1].y || res[i].x+1 == res[i+1].x);
        }

        // On calcule la moyenne pour chaque groupe
        float somme_x = 0.0;
        float somme_y = 0.0;
        for (int j = 0 ; j<vec_doublons.size(); j++)
        {
            somme_x = somme_x + vec_doublons[j].x;
            somme_y = somme_y + vec_doublons[j].y;
        }
        
        float point_x = somme_x / vec_doublons.size();
        float point_y = somme_y / vec_doublons.size();

        Point point;
        point.x = point_x;
        point.y = point_y;

        this->dessiner_ligne(point);
    }

}


void Image :: dessiner_ligne(Point point) // Dessine des lignes sur l'image.

{
    float m =point.x; // point.x est le coefficient directeur de la droite 
    float p = point.y; // point.y est l'ordonée à l'origine


    if (abs(m)<=1)
    {
        for(int j = 0; j < colonne; j++) 
        {
            if (((int)(m*j+p)<=ligne-1)&&((int)(m*j+p)>=0)) // pour eviter que la droite "dépasse" l'image
            {
                
                for (int k=0;k<3;k++)
                {
                    image[(int)(m*j+p)][j][k] = (int)(m*j+p);                     
                }
            }
            
        }
    }
    if (abs(m)>1)
    {
        for(int i = 0; i < ligne; i++) 
        {
            if (((int)((i-p)/m)<=colonne-1)&&((int)((i-p)/m)>=0)) // pour eviter que la droite "depasse" l'image
            {
                //std::cout<< (int)((i-p)/m) << " "<< ((i-p)/m)<< " " << Norme((int)((i-p)/m),((i-p)/m))*255<< " "<< (1-Norme((int)((i-p)/m),((i-p)/m)))*255<< " ";
                for (int k=0;k<3;k ++)
                {
                    image[i][(int)((i-p)/m)][k] = (int)((i-p)/m);
                }
            }
            
        }
    }
    
} 


// La fonction suivante est presque la meme, elle écrit des segments avec l'anti-aliasing.
// Elle ne tourne pas bien, nous avons préféré conserver l'ancienne

/* 
void Image :: dessiner_ligne(Point point, Point bornesup, Point borneinf)
// point.x est le coefficient directeur de la droite 
// point.y est l'ordonée à l'origine
{
    float m =point.x;
    float p = point.y;
    int xA = - bornesup.x;
    int yA = bornesup.y;
    int xB = - borneinf.x;
    int yB = -borneinf.y;


    if (abs(m)<=1)
    {
        for(int j = yA ; j < yB ; j++) 
        {
            if (((int)(m*j+p)<=xB-1)&&((int)(m*j+p)>=xA)) // pour eviter que la droite "depasse" l'image
            {

                for (int k=0;k<3;k++)
                {
                    image[(int)(m*j+p)][j][k] = Norme((int)(m*j+p),m*j+p)*255;                     
                }
            }
            if (((int)(m*j+p)+1<=xB-1)&&((int)(m*j+p)+1>=xA)) // pour eviter que la droite "depasse" l'image
            { 
                for (int k=0;k<3;k++)
                {
                    image[(int)(m*j+p)+1][j][k] = (1-Norme((int)(m*j+p),m*j+p))*255;      // Colorisation du pixel en dessous         
                }
            }
        }
    }
    if (abs(m)>1)
    {
        for(int i = xA; i < xB; i++) 
        {
            if (((int)((i-p)/m)<=yB-1)&&((int)((i-p)/m)>=yA)) // pour eviter que la droite "depasse" l'image
            {
                for (int k=0;k<3;k ++)
                {
                    image[i][(int)((i-p)/m)][k] = Norme((int)((i-p)/m),((i-p)/m))*255;
                }
            }
            if (((int)((i-p)/m)+1<=yB-1)&&((int)((i-p)/m)+1>=yA)) // pour eviter que la droite "depasse" l'image
            { 
                for (int k=0;k<3;k ++)
                {
                    image[i][(int)((i-p)/m)+1][k] = (1-Norme((int)((i-p)/m),((i-p)/m)))*255;                    
                }
            }
        }
    }
    
} */ 


void Image :: ecrire_fichier()
{
    
    std::ofstream fichier("image_rendue.ppm", std::ios::binary);

    // En-tête de l'image
    fichier << qualite;
    fichier << "\n# resolution\n";
    fichier << ligne;
    fichier << " ";
    fichier << colonne;
    fichier << "\n# avec 255 comme val max\n255\n# debut de l image\n";
    
    // Pixels de l'image
    
    for (int i = 0; i < ligne; i++)
    {
        for (int j = 0; j < colonne; j++)
        {
            for (int k = 0; k < 3; k++) 
            {
                fichier << image[i][j][k];
                fichier << "\n";
            }
        }
            
    }

    fichier.close();
}
