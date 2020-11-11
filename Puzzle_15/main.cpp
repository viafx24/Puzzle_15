#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

int main()
{
    RenderWindow app(VideoMode(256,256), "15-Puzzle!");
    app.setFramerateLimit(60);

    Texture t;
    t.loadFromFile("images/15.png");
 
    int w = 64; // taille d'un carré de chiffre
    int grid[6][6] = {0};
    Sprite sprite[20];

    // cette boucle permet essentiellement de récupérer la case que l'on souhaite dans sprite

    
    int n=0;
    for (int i=0;i<4;i++)
     for (int j=0;j<4;j++)
      {
        n++;
        sprite[n].setTexture(t);
        sprite[n].setTextureRect( IntRect(i*w,j*w,w,w) );
        grid[i+1][j+1]=n;// mais également de  placer les valeurs de n dans la grid de 1 à 16.
      }

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

               if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left)
                  {
                    // un point à noter: on ne deplace pas par drag and drop: 
                    // une fois cliqué, la case n'a qu'une seul possibilité et s'y rend toute seule!
                     Vector2i pos = Mouse::getPosition(app);

                     // avec des deux lignes on saura sur quel case est positionné la souris
                     int x = pos.x/w + 1;
                     int y = pos.y/w + 1;

                     // au debut deplacement en x et y initialisé à zero
                     int dx=0;
                     int dy=0;

                     // on regarde si une des cases adjacentes est la case vide (16)
                     // une fois determiné cette dernière, on initialise une vitesse de deplacement
                     // en haut, à gauche, en bas, à droite en fonction de l'emplacement de la case vide
                     if (grid[x+1][y]==16) {dx=1; dy=0;};// on ajoutera 1 à x
                     if (grid[x][y+1]==16) {dx=0; dy=1;}; // on ajoutera 1 à y
                     if (grid[x][y-1]==16) {dx=0; dy=-1;}; // on retranchera 1 à y
                     if (grid[x-1][y]==16) {dx=-1;dy=0;};// on retranchera 1 à x


                     // On récupère la valeur de la case où est positionné la souris 
                     // et on la stocke dans la variable n
                     int n = grid[x][y];

                     // on passe la case actuelle à 16 (vide)
                     grid[x][y] = 16;
                     // on passe la case ciblé pour le deplacement
                     grid[x+dx][y+dy] = n;

                     //animation
                     // on deplace immédiatement le sprite 16 sans encore montrer le résultat
                     // le signe - vient du fait que la case 16 prend la place opposé de la case de qui "bouge"
                     sprite[16].move(-dx*w,-dy*w);
                     float speed=3;

                     // c'est là qu'a lieu l'animation
                     // w=64 ; speed =3 donc environ 20 iteration de 3 pixels ( 0.3sec?)
                     for (int i=0;i<w;i+=speed)
                     {sprite[n].move(speed*dx,speed*dy);
                     // on ne redessine que nos deux sprites mais seule le sprite cible doit bouger lentement
                     // on dessine le sprite 16 car il faut voir le fond blanc de suite derrière la case qui bouge.
                      app.draw(sprite[16]);
                      app.draw(sprite[n]);
                      app.display(); }
                  }

        }


        // on redessine constamment tout les sprites pour la mise à jour 
        // ca peut sembler bizarre mais c'est apparement la bonne manière de faire.
       app.clear(Color::White);
       for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
         {
            int n = grid[i+1][j+1];
            sprite[n].setPosition(i*w,j*w);
            app.draw(sprite[n]);
          }

        app.display();
    }

    return 0;
}
