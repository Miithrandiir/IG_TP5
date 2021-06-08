#include <GL/glut.h>
#include "graphique.h"
// variables globales associées aux transformations géométrique

float trans_axeZ; // translation selon Oz
float angle_rotY; // angle de rotation autour de Oy
float angle_rotX; // angle de rotation autour de Ox
float angle_rotZ; // angle de rotation autour de Oz

void gerer_clavier_special(int touche, int x, int y) {
    switch (touche) {

        // touches liées à la rotation autour de Ox
        case GLUT_KEY_DOWN :
            angle_rotX += 10;
            break;
        case GLUT_KEY_UP :
            angle_rotX -= 10;
            break;

            // touches liées à la rotation autour de Oy
        case GLUT_KEY_LEFT :
            angle_rotY -= 10;
            break;
        case GLUT_KEY_RIGHT  :
            angle_rotY += 10;
            break;

            // touches liées à la rotation autour de Oz
        case GLUT_KEY_PAGE_DOWN :
            angle_rotZ -= 10;
            break;
        case GLUT_KEY_PAGE_UP :
            angle_rotZ += 10;
            break;

    }

    // redessiner avec les nouveaux paramètres
    glutPostRedisplay();

}

void gerer_clavier(unsigned char touche, int x, int y) {
    int valeur;
    GLfloat* param = (GLfloat*) malloc(4);
    GLfloat* paramAngle = (GLfloat*) malloc(1);
    switch (touche) {
        // touches liées à la translation selon Oz
        case '-' :
            trans_axeZ -= 1.0;
            break;
        case '+' :
            trans_axeZ += 1.0;
            break;
        case 'o':
            glIsEnabled(GL_LIGHTING) ? glDisable(GL_LIGHTING) : glEnable(GL_LIGHTING);
            break;
        case 'l':
            glGetIntegerv(GL_SHADE_MODEL, &valeur);

            (valeur == GL_SMOOTH) ? glShadeModel(GL_FLAT) : glShadeModel(GL_SMOOTH);
            break;
        case 's':
            if(coefShininess+1 <= 128) {
                coefShininess++;
            }
            break;
        case 'S':
            if(coefShininess-1 >=0) {
                coefShininess--;
            }
            break;
        case 'a':
            glGetLightfv(GL_LIGHT0, GL_DIFFUSE, param);
            param[0]+=0.1;
            param[1]+=0.1;
            param[2]+=0.1;
            glLightfv(GL_LIGHT0,GL_DIFFUSE, param);
            break;
        case 'd':
            glGetLightfv(GL_LIGHT0, GL_DIFFUSE, param);
            param[0]-=0.1;
            param[1]-=0.1;
            param[2]-=0.1;
            glLightfv(GL_LIGHT0,GL_DIFFUSE, param);
            break;
        case 'A':
            glGetLightfv(GL_LIGHT0, GL_SPECULAR, param);
            param[0]+=0.1;
            param[1]+=0.1;
            param[2]+=0.1;
            glLightfv(GL_LIGHT0,GL_SPECULAR, param);
            break;
        case 'D':
            glGetLightfv(GL_LIGHT0, GL_SPECULAR, param);
            param[0]-=0.1;
            param[1]-=0.1;
            param[2]-=0.1;
            glLightfv(GL_LIGHT0,GL_SPECULAR, param);
            break;
        case '<':
            glGetLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, paramAngle);
            (paramAngle[0]+1 <= 90) ? paramAngle[0]++ : paramAngle[0];
            glLightf(GL_LIGHT1,GL_SPOT_CUTOFF, paramAngle[0]);
            break;
        case '>':
            glGetLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, paramAngle);
            (paramAngle[0]-1 >= 0) ? paramAngle[0]-- : paramAngle[0];
            glLightf(GL_LIGHT1,GL_SPOT_CUTOFF, paramAngle[0]);
            break;
        case 'q' :
            exit(0);
            break;
    }
    free(param);
    free(paramAngle);
    // redessiner avec les nouveaux paramètres
    glutPostRedisplay();

}
