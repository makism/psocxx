#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include "camera.h"

int window;
CCamera Camera;

#include "psocxx.hpp"
using namespace psocxx;
namespace psocxx {
float Particle::EvaluateCallback(const Vector* v)
{
    float x = (*v)[0];
    float y = (*v)[1];

//     return  20 + x*x + y*y - 10 * (cos(2 * PI * x) + cos(2 * PI * y));
//     return -(0.2f / (4*(x*x) + y*y));
    return x*x + y*y;
}
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


    // Define a 2 dimentional space.
    s->ConfigureSpace(2, -1.0f, 1.0f);
    // Pass the parameters (omega, phi_p, phi_g).
    s->SetParameters(0.01f, 0.1f, 0.01f);
    // Create inital particles.
    s->Init();
}

void ReSizeGLScene(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,10000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void DrawNet(GLfloat size, GLint LinesX, GLint LinesZ)
{
    glBegin(GL_LINES);
    for (int xc = 0; xc < LinesX; xc++)
    {
        glVertex3f( -size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
                    0.0,
                    size / 2.0);
        glVertex3f( -size / 2.0 + xc / (GLfloat)(LinesX-1)*size,
                    0.0,
                    size / -2.0);
    }
    for (int zc = 0; zc < LinesX; zc++)
    {
        glVertex3f( size / 2.0,
                    0.0,
                    -size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
        glVertex3f( size / -2.0,
                    0.0,
                    -size / 2.0 + zc / (GLfloat)(LinesZ-1)*size);
    }
    glEnd();
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    Camera.Render();

    // Draw the axis
    GLfloat size = 2.0;
    GLint LinesX = 30;
    GLint LinesZ = 30;
    
    GLfloat halfsize = size / 2.0;
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    glTranslatef(0.0,-halfsize ,0.0);
    DrawNet(size,LinesX,LinesZ);
    glTranslatef(0.0,size,0.0);
    DrawNet(size,LinesX,LinesZ);
    glPopMatrix();
    glColor3f(0.0,0.0,1.0);
    glPushMatrix();
    glTranslatef(-halfsize,0.0,0.0);    
    glRotatef(90.0,0.0,0.0,halfsize);
    DrawNet(size,LinesX,LinesZ);
    glTranslatef(0.0,-size,0.0);
    DrawNet(size,LinesX,LinesZ);
    glPopMatrix();
    glColor3f(1.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(0.0,0.0,-halfsize);    
    glRotatef(90.0,halfsize,0.0,0.0);
    DrawNet(size,LinesX,LinesZ);
    glTranslatef(0.0,size,0.0);
    DrawNet(size,LinesX,LinesZ);
    glPopMatrix();
    
    
    // Draw the function.
    glPointSize(2.0);
    glBegin(GL_POINTS);
    for (float x=-1.0f; x<1.0f; x+=0.005f) {
        for (float y=-1.0f; y<1.0f; y+=0.005f) {
//             float z = 0 + x*x + y*y - 1 * cos(2 * PI * x) - 1 * cos(2 * PI * y);
//             float z = 0.2f / (4*(x*x) + y*y);
            float z = x*x + y*y;

            float* colors = Helpers::JetColorspace::Convert(z);
            glColor3f(colors[0], colors[1], colors[2]);
            glVertex3f(x, z, y);

            delete colors;
        }
    }
    glEnd();
    glFinish();


    // Draw particles and tails.
    glPointSize(2.0);
    glBegin(GL_POINTS);
    for (int i=0; i<s->NumberOfParticles(); i++) {
        Particle* p = s->Particles()->at(i);

        glColor3f (1.0f, 1.0f, 1.0f);
        glVertex3f(p->Position()->Points()->at(0), p->Fitness(), p->Position()->Points()->at(1));

        // Draw the tails.
        glBegin(GL_LINES);
        glVertex3f(p->Position()->Points()->at(0), p->Fitness(), p->Position()->Points()->at(1));
        for (int t=0; t<p->Tail()->size(); t++) {
            Vector* v = p->Tail()->at(t);
            glVertex3f(v->Points()->at(0), v->Points()->at(1), v->Points()->at(2));
        }
        glEnd();
        glFinish();
    }
    glEnd();
    glFinish();
 
    glutSwapBuffers();


    // Step one iteration.
    s->Step();
}

void KeyDown(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:        //ESC
        glutDestroyWindow(window);
        delete s;

        break;
    case 'a':
        Camera.RotateY(5.0);
        Display();
        break;
    case 'd':
        Camera.RotateY(-5.0);
        Display();
        break;
    case 'w':
        Camera.MoveForward( -0.1 ) ;
        Display();
        break;
    case 's':
        Camera.MoveForward( 0.1 ) ;
        Display();
        break;
    case 'x':
        Camera.RotateX(5.0);
        Display();
        break;
    case 'y':
        Camera.RotateX(-5.0);
        Display();
        break;
    case 'c':
        Camera.StrafeRight(-0.1);
        Display();
        break;
    case 'v':
        Camera.StrafeRight(0.1);
        Display();
        break;
    case 'f':
        Camera.MoveUpward(-0.3);
        Display();
        break;
    case 'r':
        Camera.MoveUpward(0.3);
        Display();
        break;

    case 'm':
        Camera.RotateZ(-5.0);
        Display();
        break;
    case 'n':
        Camera.RotateZ(5.0);
        Display();
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
    Camera.Move( F3dVector(0.0, 0.0, 3.0 ));
    Camera.MoveForward( 1.0 );
    glutDisplayFunc(&Display);
    glutReshapeFunc(&ReSizeGLScene);
    glutKeyboardFunc(&KeyDown);
    InitGL(640, 480);

    glutMainLoop();

    return 0;
}
