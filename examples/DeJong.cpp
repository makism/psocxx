#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>

#include <boost/foreach.hpp>

#define ESCAPE 27
#define PAGE_UP 73
#define PAGE_DOWN 81
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define KEY_Q 113
#define KEY_A 97
int window;
float rot = 0.0f;
GLfloat xrot;
GLfloat yrot;
GLfloat xspeed;
GLfloat yspeed;
GLfloat walkbias = 0;
GLfloat walkbiasangle = 0;
GLfloat lookupdown = 0.0;
const float piover180 = 0.0174532925f;
float heading, xpos, zpos=5.0f;
GLfloat camx = 0, camy = 0, camz = 0;
GLfloat therotate;
GLfloat z=0.0f;

float rad(float angle)
{
    return angle * piover180;
}
float rX = 0.0f, rY = 0.0f, rZ = 0.0f, rA = 0.0f, rB = 0.0f, rC = 0.0f;
float rStep = 0.3f;
bool  keys[256];

const float PI = 3.1415926535897932384626433832795f;


#include "JetColorspace.hpp"
#include "psocxx.hpp"
using namespace psocxx;
float dejong(const vecf& v) {
    float x = v[0];
    float y = v[1];

    return x*x + y*y;
}
Swarm *s = new Swarm(30);


void InitGL(int Width, int Height)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);

    s->setFitnessCallback(dejong);
    // Define a 2 dimentional space.
    s->configureSpace(2, -1.0f, 1.0f);
    // Pass the parameters (omega, phi_p, phi_g).
    s->setParameters(0.01f, 0.1f, 0.01f);
    // Create inital particles.
    s->init();
}

void ReSizeGLScene(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,10000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
    glLoadIdentity();


    GLfloat x_m, y_m, z_m, u_m, v_m;
    GLfloat xtrans, ztrans, ytrans;
    GLfloat sceneroty;
    xtrans = -xpos;
    ztrans = -zpos;
    ytrans = -walkbias-0.25f;
    sceneroty = 360.0f - yrot;

    // Input?
    if (keys[(int)'w']) rX += rStep;
    if (keys[(int)'x']) rX -= rStep;
    if (keys[(int)'a']) rY += rStep;
    if (keys[(int)'d']) rY -= rStep;
    if (keys[(int)'q']) rZ += rStep;
    if (keys[(int)'e']) rZ -= rStep;
    if (keys[(int)'s']) rX = rY = rZ = 0.0;


    // Move, rotate the world.
    glRotatef(lookupdown, 1.0f, 0, 0);
    glRotatef(sceneroty, 0, 1.0f, 0);
    glTranslatef(xtrans, ytrans, ztrans);
    glRotatef(rX, 1, 0, 0);
    glRotatef(rY, 0, 1, 0);
    glRotatef(rZ, 0, 0, 1);


    // Draw the x,z,y axis.
    glBegin(GL_LINES);
    glColor4f(1,1,1,0);
    glVertex3f(-20, 0, 0);
    glVertex3f(+20, 0, 0);
    glVertex3f(0, +20, 0);
    glVertex3f(0, -20, 0);
    glVertex3f(0, 0, -20);
    glVertex3f(0, 0, +20);
    glEnd();


    // Draw the benchmark function.
    glPointSize(2.0);
    glBegin(GL_POINTS);
    for (float x=-1.0f; x<1.0f; x+=0.005f) {
        for (float y=-1.0f; y<1.0f; y+=0.005f) {
            float z = x*x + y*y;

            float* colors = JetColorspace::Convert(z);
            glColor3f(colors[0], colors[1], colors[2]);
            glVertex3f(x, z, y);

            delete colors;
        }
    }
    glEnd();
    glFinish();


    // Draw the particles and the tails.
    glPointSize(2.0);
    glBegin(GL_POINTS);
    BOOST_FOREACH(psocxx::Particle& p, s->particles())
    {
        vecf& position = p.position();

        glColor3f (1.0f, 1.0f, 1.0f);
        glVertex3f(position[0], p.fitness(), position[1]);
    }
    glEnd();
    glFinish();

    glutSwapBuffers();


    // Step one iteration.
    s->step();
}


void keyReleased(unsigned char key, int x, int y)
{
    usleep(100);

    keys[key] = false;
}

void keyPressed(unsigned char key, int x, int y)
{
    usleep(100);

    keys[key] = true;

    if (key == ESCAPE)
    {
        glutDestroyWindow(window);
        delete s;
        exit(0);
    }
}

void specialKeyPressed(int key, int x, int y)
{
    usleep(100);

    switch (key) {
        case GLUT_KEY_PAGE_UP: // tilt up
        z -= 0.2f;
        lookupdown -= 0.2f;
        break;

        case GLUT_KEY_PAGE_DOWN: // tilt down
        z += 0.2f;
        lookupdown += 1.0f;
        break;

        case GLUT_KEY_UP: // walk forward (bob head)
        xpos -= (float)sin(yrot*piover180) * 0.1f;
        zpos -= (float)cos(yrot*piover180) * 0.1f;
        if (walkbiasangle >= 359.0f)
            walkbiasangle = 0.0f;
        else
            walkbiasangle+= 10;
        walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
        break;

        case GLUT_KEY_DOWN: // walk back (bob head)
        xpos += (float)sin(yrot*piover180) * 0.1f;
        zpos += (float)cos(yrot*piover180) * 0.1f;
        if (walkbiasangle <= 1.0f)
            walkbiasangle = 359.0f;
        else
            walkbiasangle-= 10;
        walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
        break;

        case GLUT_KEY_LEFT: // look left
        yrot += 1.5f;
        break;

        case GLUT_KEY_RIGHT: // look right
        yrot -= 1.5f;
        break;

        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);

    window = glutCreateWindow("psocxx");

    glutDisplayFunc(&DrawGLScene);
    glutFullScreen();
    glutIdleFunc(&DrawGLScene);
    glutReshapeFunc(&ReSizeGLScene);
    glutKeyboardFunc(&keyPressed);
    glutKeyboardUpFunc(&keyReleased);
    glutSpecialFunc(&specialKeyPressed);
    InitGL(640, 480);

    glutMainLoop();

    return 0;
}
