#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "touches.h"

float coefShininess = 50.0f;
float subdivision = 1.0f;

static void sol(float dim) {
    GLfloat coefAmb[] = {0.9, 0.9, 0.9, 1.0};
    GLfloat coefSpec[] = {0.5, 0.5, 0.5, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, coefAmb);
    glMaterialfv(GL_FRONT, GL_SPECULAR, coefSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, coefShininess);

    float pas = dim / subdivision;
    float departX = -(dim / 2);
    float departZ = -departX;
    for (int i = 0; i < subdivision; i++) {
        for (int j = 0; j < subdivision; j++) {
            glBegin(GL_POLYGON);
            {
                float calcX = departX + pas * j;
                float calcZ = departZ - pas * i;
                glNormal3f(0, 1, 0);
                glVertex3f(calcX, 0, calcZ);
                glVertex3f(calcX + pas, 0, calcZ);
                glVertex3f(calcX + pas, 0, calcZ - pas);
                glVertex3f(calcX, 0, calcZ - pas);
            }
            glEnd();
        }
    }
}

/**
 * Fonction permettant de dessiner une th�i�re centr�e sur l'origine
 * du rep�re de taille dim
 */

static void laTeapot(float dim) {

    GLfloat coefAmb[] = {0.2, 0.2, 0.9, 1.0};
    GLfloat coefSpec[] = {0.5, 0.5, 0.5, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, coefAmb);
    glMaterialfv(GL_FRONT, GL_SPECULAR, coefSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, coefShininess);
    // couleur par d�faut de l'objet
    glColor3f(0.0, 0.0, 1.0);
    glutSolidTeapot(dim);
}

/** 
 * Fonction permettant de dessiner le rep�re du monde sous 
 * forme d'une croix 3D.
 * @param dim la taille de la ligne repr�sentant un demi-axe.
 */

static void repere(float dim) {

    glBegin(GL_LINES);

    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-dim, 0.0, 0.0);
    glVertex3f(dim, 0.0, 0.0);
    glVertex3f(0.0, -dim, 0.0);
    glVertex3f(0.0, dim, 0.0);
    glVertex3f(0.0, 0.0, -dim);
    glVertex3f(0.0, 0.0, dim);

    glEnd();
}

/**
 * Fonction permettant de recalculer la zone d'affichage
 * en cas de modification de la fen�tre qui la contient.
 * @param largeur la nouvelle largeur en pixel de la fen�tre
 * @param hauteur la nouvelle hauteur en pixel de la fen�tre
 */

void retailler(GLsizei largeur, GLsizei hauteur) {
    int xbas, ybas, taille;

    // d�terminer, si la fen�tre est rectangulaire, si il
    // faut r�duire la zone d'affichge en hauteur ou en largeur
    if (largeur < hauteur) {// fen�tre rectangulaire verticale
        // on prend toute la largeur pour l'affichage
        xbas = 0;
        taille = largeur;
        // on calcule la hauteur des bandes "noires" en haut et en bas
        ybas = (hauteur - largeur) / 2;
    } else {// fen�tre rectangulaire horizontale
        // on calcule la largeur des bandes "noires" � droite et � gauche
        xbas = (largeur - hauteur) / 2;
        // on prend toute la largeur
        taille = hauteur;
        ybas = 0;
    }
    // redimensionner la zone d'affichage
    glViewport(xbas, ybas, taille, taille);
    // redessiner
    glutPostRedisplay();

}

/**
 * Fonction utilis�e pour afficher le monde 3D � visualiser. Cette fonction
 * sera appel�e � chaque fois qu'un "rafraichissement" de la fen�tre
 * d'affichage sera n�cessaire.
 */

void dessiner(void) {
    /* effacer l'ecran */
    glClearColor(0.0, 0.0, 0.0, 1.0);

    /* raz de la fenetre avec la couleur de fond */
    /* et raz du tampon de profondeur */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // transformation du rep�re global
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, trans_axeZ);
    glRotatef(angle_rotY, 0, 1, 0);
    glRotatef(angle_rotX, 1, 0, 0);
    glRotatef(angle_rotZ, 0, 0, 1);

    GLfloat light0_position[] = {10.0, 10.0, -3.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    GLfloat light2_position[] = {0.0, 2.0, 0.0, 1.0};
    GLfloat light2_direction[] = {0, -1.0, 0};
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_direction);


    /* dessin des objets */
    repere(2.0);
    //laTeapot(2.0);
    sol(2.0);

    glFlush();
    return;

}
