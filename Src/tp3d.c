#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "graphique.h"
#include "touches.h"

/* dimensions initiales de la fen�tre d'affichage */
#define LARGEUR  256
#define HAUTEUR  256

/**
 * Fonction d'initialisation des param�tres d'affichage
 */
static void init_screen(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 50.0);

    glViewport(0, 0, LARGEUR, HAUTEUR);

    // initialisation des transformations g�om�triques
    trans_axeZ = -5;
    angle_rotY = angle_rotX = angle_rotZ = 0;
}

static void init_eclairage() {
    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    //GLfloat coeff[] = {0.2, 0.2, 0.2, 1.0};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, coeff);

    GLfloat coeffLight0[] = {0.1,0.1,0.1,1.0};
    glLightfv(GL_LIGHT0,GL_AMBIENT, coeffLight0);

    /* éclairage LIGHT0 géré dans la fonction dessiner*/

    //éclairage Light 1
    GLfloat coeffAmb[] = {0.1,0.1,0.1,1.0};
    GLfloat coeffIDS[] = {1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT1, GL_SPECULAR, coeffIDS);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, coeffIDS);
    glLightfv(GL_LIGHT1, GL_AMBIENT, coeffAmb);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 6.0f);

    GLfloat light2_position[] = {0.0, 2.0, 0.0, 1.0};
    GLfloat light2_direction[] = {0, -1.0, 0};
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_direction);



}

/**
 * Fonction principale qui cr�e et initialise la fen�tre
 * d'affichage et lance la boucle d'affichage Glut.
 * @param argc le nombre d'argument sur la ligne de commande
 * @param argv une table de cha�ne de caract�res contenant chacun
 * des arguments de la ligne de commande.
 */
int main(int argc, char *argv[]) {

    glutInit(&argc, argv);

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(LARGEUR, HAUTEUR);

    glutInitDisplayMode(GLUT_DEPTH);

    glutCreateWindow(argv[0]);

    /* choix de la fonction de rafraichissement */
    glutDisplayFunc(dessiner);
    /* choix de la fonction de redimensionnement de la fen�tre */
    glutReshapeFunc(retailler);
    /* choix des fonctions de gestion des �v�nements clavier */
    glutKeyboardFunc(gerer_clavier);
    glutSpecialUpFunc(gerer_clavier_special);

    init_screen();
    init_eclairage();

    // activer l'�limination des parties cach�es
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();


    return 0;
}


