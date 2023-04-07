>Le sujet :

Le but du projet est de réussir à detecter des segments de droite au sein d'une image.

Pour cela, on utilisera la transformée de Hough qui à un point associe une droite.
En effet un point (a,b) de l'espace (x,y) sera associée à la droite d'équation p=am+b de l'espace (m,p).
De cette façon, deux points alignés dans l'espace (x,y) corresponderont à deux droites sécantes dans l'espace (m,p).
Ainsi nous allons pouvoir créer un buffer d'accumulation que nous allons incrémenter chaque fois qu'une droite passera par un de ses points.
Nous pourrons ensuite chercher les cases du buffer ayant le plus grand score.
Ce point sera donc le point d'intersection (ma,mp) du maximum de droite dans l'espace (m,p).
De la même façon qu'un point de (x,y) associe une droite en  (m,p), ce point (ma,mp) nous permettra de récupérer une droite dans l'espace (x,y).

Cette méthode n'étant pas la plus optimale, il faudra passer ensuite en représentation polaire.


> Structure du code 

Le code est réparti en un Main et trois structures : Point, Matrice et Image.
Les 3 structures ont une fonction d'affichage qui nous a été utile pour le débuguage.
Image contient les fonctions donnerdroites, dessiner_ligne, doublons et ecrire_fichier.
Ainsi le Main n'a que les fonctions lirefichier et HoughNormale.

>Travail réalisé :

Nous avons commencé par créer la fonction lirefichier() qui renvoie une Image depuis le fichier .ppm
Nous obtenons donc une Image [i][j][k] où i,j correspondent aux coordonnées d'un pixel et k={0,1,2} correspond à la couleur de ce pixel dans le système RVB.

Ensuite nous avons créé la fonction donnerdroites qui permet de récupérer les pixels à traiter.
En effet, il n'est pas pertinent de travailler sur les points du fond.
On considère que le fond ne peut être que noir (Image [i][j][k]=0 pour tout k) ou blanc (Image [i][j][k]=0 pour tout k)
La fonction donnerpoints nous donne la pente et l'ordonnée à l'origine des droites formées par la transformée de Hough.
Elle renvoie donc un vecteur de Point.

Ensuite, nous avons crée la fonction Houghnormale qui renvoie aussi un vecteur de Point.
Celle-çi crée donc le buffer d'accumulation qui va s'incrémenter comme expliqué plus haut.
Puis on récupère les coordonnées des points du buffer ayant le meilleur score ce qui nous donne les nouvelles coordonnées des droites à tracer.

Ensuite on supprime les doublons inutiles grâce à la fonctions doublons.

Enfin on trace les droites grâce aux fonctions dessinerligne et écrirefichier.


>Ce qui a été essayé et qui n'a pas abouti mais qui a été laissé en commentaire:

Dans la fonction dessinerligne de la structure Image, on a essayé de ne tracer que des segments de droite. L'anti-aliasing a aussi été laissé en commentaire car pas optimal au niveau de l'affichage.

>Comment se servir du code développé :

Dans main.cpp,  il faut changer le nom du fichier .ppm au sein de la fonction lirefichier()
Dans la structure Image, dans la fonction écrirefichier il est possible de modifier le nom de la nouvelle image qui sera créee avec les droites detectées.
Ensuite dans le terminal, il faut compiler toutes les structures ainsi que le main avec la commande suivante :
g++ -Wall -std=c++17 -o Hough Image.cpp Matrice.cpp Point.cpp  Main.cpp


