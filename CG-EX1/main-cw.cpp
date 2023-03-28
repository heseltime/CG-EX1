/* Title: Computergrafik und Bildverarbeitung
* Author : Christian Wesesslintner s2110307044
* Stundenaufwand 35h
* ------------------------------------------------------------------------ - */


#include "GL/freeglut.h"
#include "math.h"
#include <stdio.h>
#define AREA_SIDE_LENGTH 40
#define CENTERX glutGet(GLUT_WINDOW_WIDTH) / 2 
#define CENTERY glutGet(GLUT_WINDOW_HEIGHT) / 2


int windowid; // the identifier of the GLUT window

//40 x 40 px is one field
int area[AREA_SIDE_LENGTH][AREA_SIDE_LENGTH]{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,1,1,0,0,0,0,0,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,1,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


//GLfloat matrot[][4] = {          // a rotation matrix
//  { 0.707f, 0.707f, 0.0f, 0.0f}, // it performs a rotation around z
//  {-0.707f, 0.707f, 0.0f, 0.0f}, // in 45 degrees
//  { 0.0f,   0.0f,   1.0f, 0.0f},
//  { 0.0f,   0.0f,   0.0f, 1.0f}
//};
//
//GLfloat mattrans[][4] = {        // a translation matrix
//  { 1.0f, 0.0f,  0.0f, 0.0f},    // it performs a translation along the
//  { 0.0f, 1.0f,  0.0f, 0.0f},    // x-axis of 0.5 units and along
//  { 0.0f, 0.0f,  1.0f, 0.0f},    // the z-axis of -1.5 units
//  { 0.5f, 0.0f, -1.5f, 1.0f}
//};

// Navigation variables - required for TASK 5
//GLfloat navX = 0.0f;
//GLfloat navZ = 5.0f;

// Angle for cube rotation - required for TASK 6
GLfloat angleCube = 0.0f;        //angle for cube1

// Camera motion variables - required for HOMEOWRK HELPER
GLdouble angle = 0.0f;          // angle of rotation for the camera direction
GLdouble lx = -0.7f, lz = -1.0f; // actual vector representing the camera's
// direction
GLdouble x = 40.0f, z = 25.0f;    // XZ position of the camera


//Taken from http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/w
void processSpecialKeys(int key, int xcoor, int ycoor) {
    float fraction = 0.1f;

    switch (key) {
    case GLUT_KEY_LEFT:
        angle -= 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_RIGHT:
        angle += 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_UP:
        x += lx * fraction;
        z += lz * fraction;
        break;
    case GLUT_KEY_DOWN:
        x -= lx * fraction;
        z -= lz * fraction;
        break;
    }
}
/* Here we have an example to draw a bit nicer with our limited OpenGL
   knowledge. First filled objects are drawn in black, at a smaller size.
   Then the same object outlines are drawn in full size full size. Both
   will be compared in the depth buffer and the front outlines will
   remain. */
void drawObjectAlt(void) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPushMatrix(); //set where to start the current object transformations  
    glRotatef(angleCube, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0); //change cube1 to black
    glScalef(0.99, 0.99, 0.99);
    glutSolidCube(0.5);
    glTranslatef(0, 0.5, 0); //move cube1 to the right
    glScalef(0.99, 0.99, 0.99);
    glutSolidSphere(0.25f, 20, 20);
    glPopMatrix();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPushMatrix(); //set where to start the current object transformations  
    glRotatef(angleCube, 0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0); //change cube1 to Green
    glutSolidCube(0.5);
    glTranslatef(0, 0.5, 0); //move cube1 to the right
    glutSolidSphere(0.25f, 20, 20);
    glPopMatrix();
}

/* This is the keyboard function which is used to react on keyboard input.
   It has to be registered as a callback in glutKeyboardFunc. Once a key is
   pressed it will be invoked and the keycode as well as the current mouse
   coordinates relative to the window origin are passed.
   It acts on our FPS controls 'WASD' and the escape key. A simple output
   to the keypress is printed in the console in case of 'WASD'. In case of
   ESC the window is destroyed and the application is terminated. */
void keyboard(unsigned char key, int xcoor, int ycoor) {
    float fraction = 0.2f;
    switch (key) {
    case 'a':
        x -= 0.1f * cos(angle);
        z -= 0.1f * sin(angle);
        break;
    case 'd':
        //x += 0.1f; // TASK 5
        x += 0.1f * cos(angle);
        z += 0.1f * sin(angle);
        break;
    case 'w':
        x += lx * fraction;
        z += lz * fraction;
        break;
    case 's':
        x -= lx * fraction;
        z -= lz * fraction;
        break;
    case 27: // escape key
        glutDestroyWindow(windowid);
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void drawSnowman() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // body-ground
    glTranslatef(0, 0, 0);
    glColor3f(1, 1, 1);
    glPushMatrix();
    glutSolidSphere(1, 20, 20);
    glPopMatrix();

    // body-middle
    glTranslatef(0, 1, 0);
    glColor3f(1, 1, 1);
    glPushMatrix();
    glutSolidSphere(0.7, 20, 20);
    glPopMatrix();

    // body-top
    glTranslatef(0, 0.8, 0);
    glColor3f(1, 1, 1);
    glPushMatrix();
    glutSolidSphere(0.5, 20, 20);
    glPopMatrix();

    // nose
    glTranslatef(0, 0, 0.2);
    glColor3f(1, 0, 0);
    glPushMatrix();
    glutSolidCone(0.1, 1, 20, 20);
    glPopMatrix();

    // left arm 1
    glTranslatef(-0.5, -0.5, 0);
    glColor3f(0, 0, 0);
    glPushMatrix();
    glRotatef(270, 0, 1, 0);
    glRotatef(60, 1, 0, 0);
    glutSolidCylinder(0.05, 0.9, 20, 20);
    glPopMatrix();

    // left arm 2
    glTranslatef(-0.41, -0.70, 0);
    glColor3f(0, 0, 0);
    glPushMatrix();
    glutSolidCylinder(0.05, 1.2, 20, 20);
    glPopMatrix();

    // reset left arm both parts
    glTranslatef(0.91, 1.2, 0);

    // right arm 1
    glTranslatef(0.5, -0.5, 0);
    glColor3f(0, 0, 0);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glRotatef(60, 1, 0, 0);
    glutSolidCylinder(0.05, 0.9, 20, 20);
    glPopMatrix();

    // right arm 2
    glTranslatef(0.41, -0.70, 0);
    glColor3f(0, 0, 0);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glRotatef(-45, 1, 0, 0);
    glutSolidCylinder(0.05, 1.2, 20, 20);
    glPopMatrix();

} /* drawSnowman */

void mouseMovement(int xcoor, int ycoor) {
    printf("mouse coords: lx: %f, ly: %f\n", lx, lz);
    printf("mouse coords: xcoor: %d, ycoor: %d\n", xcoor, ycoor);

    static bool mouse_warped = false;

    if (mouse_warped) {
        mouse_warped = false;
        return;
    }

    if (xcoor < CENTERX) {
        angle -= 0.02f;
        lx = sin(angle);
        lz = -cos(angle);
    }
    else if (xcoor > CENTERY) {
        angle += 0.02f;
        lx = sin(angle);
        lz = -cos(angle);
    }

    glutWarpPointer((CENTERX), (CENTERY));
    mouse_warped = true;
}


/* This function should be called when the window is resized. It has to be
   registered as a callback in glutReshapeFunc. The function sets up the
   correct perspective projection. Don't worry about it we will not go into
   detail but we need it for correct perspective 3D rendering. */
void reshapeFunc(int xwidth, int yheight) {
    if (yheight == 0 || xwidth == 0) return;  // Nothing is visible, return

    glMatrixMode(GL_PROJECTION); // Set a new projection matrix
    glLoadIdentity();
    // Angle of view: 40 degrees
    // Near clipping plane distance: 0.5
    // Far clipping plane distance: 20.0
    gluPerspective(40.0f, (GLdouble)xwidth / (GLdouble)yheight, 0.5f, 120.0f);
    glViewport(0, 0, xwidth, yheight);  // Use the whole window for rendering
}

/* This is our first display function it will be used for drawing a 2D
   triangle. The background is set to black and cleared, the current drawing
   colour is set and the vertices of the triangle are defined. At the end the
   buffers are flipped. */
void renderPrimitives(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set background colour to black 
    glClear(GL_COLOR_BUFFER_BIT);         // clear the colour buffer

    glColor3f(0.1f, 0.2f, 0.3f);        // set the colour to grey
    glBegin(GL_TRIANGLES);              // drawing using triangles
    glVertex3f(0.0f, 1.0f, 0.0f);      // top
    glVertex3f(-1.0f, -1.0f, 0.0f);    // bottom left
    glVertex3f(1.0f, -1.0f, 0.0f);    // bottom right
    glEnd();                            // finished drawing the triangle

    /* Example 1 - Slide 5 */
    glColor3f(1.0f, 0.0f, 0.0f);        // red
    glBegin(GL_QUADS);                  // drawing using quads
    glVertex2f(-0.5f, -0.5f);          // bottom left
    glVertex2f(0.5f, -0.5f);          // bottom right
    glVertex2f(0.5f, 0.5f);            // top right
    glVertex2f(-0.5f, 0.5f);          // top left
    glEnd();

    /* Example 2 - Slide 5 */
    glBegin(GL_QUADS);                  // drawing using quads
    glColor3f(1.0f, 0.0f, 0.0f);      // red
    glVertex2f(-0.5f, -0.5f);          // bottom left
    glColor3f(0.0f, 1.0f, 0.0f);      // green
    glVertex2f(0.5f, -0.5f);          // bottom right
    glColor3f(0.0f, 0.0f, 1.0f);      // blue
    glVertex2f(0.5f, 0.5f);            // top right
    glColor3f(1.0f, 1.0f, 0.0f);      // yellow
    glVertex2f(-0.5f, 0.5f);          // top left
    glEnd();

    // TASK 1:
    glColor3f(1.0f, 1.0f, 0.0f);  // yellow
    glBegin(GL_POLYGON);          // these vertices form a closed polygon
    glVertex2f(0.4f, 0.2f);
    glVertex2f(0.6f, 0.2f);
    glVertex2f(0.7f, 0.4f);
    glVertex2f(0.6f, 0.6f);
    glVertex2f(0.4f, 0.6f);
    glVertex2f(0.3f, 0.4f);
    glEnd();
    glutSwapBuffers();
}


/* This function will be used for composited objects and will be called from a
   display function. */
void drawObject(void) { // TASK 4:
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPushMatrix(); //set where to start the current object transformations  
    glRotatef(angleCube, 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);    // change cube1 to green
    glutSolidCube(0.5f);            // cube
    glTranslatef(0.0f, 0.5f, 0.0f); // move cube1 to the top
    glutSolidSphere(0.25f, 40, 40); // sphere
    glPopMatrix();
}

/* This function will replace the previous display function and will be used
   for scene setup. */
void render3DScene(void) {
    glMatrixMode(GL_MODELVIEW);    // set the ModelView Matrix for scene setup
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glColor3f(0.0f, 1.0f, 0.0f);  // green
    glTranslatef(0.0f, 0.0f, -1.5f);
    glRotatef(45, 1.0f, 0.0f, 0.0f);
    glutSolidCube(0.5f);

    // TASK 2:
    glutSolidSphere(0.1f, 20, 20);
    glutSolidTorus(0.6f, 1.4f, 20, 20);

    //glutSwapBuffers();
}

void drawFloor() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    glColor3f(0.150, 0.150, 0.150);
    glVertex3f(-AREA_SIDE_LENGTH, 0, -AREA_SIDE_LENGTH);
    glVertex3f(-AREA_SIDE_LENGTH, 0, AREA_SIDE_LENGTH);
    glVertex3f(AREA_SIDE_LENGTH, 0, AREA_SIDE_LENGTH);
    glVertex3f(AREA_SIDE_LENGTH, 0, -AREA_SIDE_LENGTH);
    glEnd();
}

void drawWall() {
    glPushMatrix();
    for (size_t i = 0; i < 4; i++) {
        //glPushMatrix();
        glTranslatef(0, 0.5, 0);

        // line solid cube
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(0, 0, 0);
        glScalef(1.0, 1.0, 1.0);
        glutSolidCube(1);

        // solid cube
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glColor3f(0.128, 0.100, 0.60);
        glScalef(0.99, 0.99, 0.99);
        glutSolidCube(1);
    }
    glTranslatef(0, -2.0f, 0);
    glPopMatrix();
}

void printLabyrinth() {
    for (size_t i = 0; i < AREA_SIDE_LENGTH; i++) {
        glTranslatef(1.0f, 0, 0);
        for (size_t j = 0; j < AREA_SIDE_LENGTH; j++) {
            glTranslatef(0, 0, 1.0);

            if (area[i][j] == 1) {
                drawWall();
            }
            else if (area[i][j] == 2) {

            }
        }
        glTranslatef(0, 0, -AREA_SIDE_LENGTH);
    }
}

/* This function will replace the previous display function and will be used
   for rendering a cube and playing with transformations. */
void renderCube(void) {
    glMatrixMode(GL_MODELVIEW);
    // glClear(GL_DEPTH_BUFFER_BIT); // Helper to be used with drawObjectAlt
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(x, 1.0f, z,            // camera position
      x + lx, 1.0f, z + lz,          // target position (at)
      0.0f, 1.0f, 0.0f);             // up vector

    glEnable(GL_DEPTH_TEST);


    glPushMatrix();
    glTranslatef(10, 0.25f, -5);
    drawFloor();
    glTranslatef(0, 0, 0);
    printLabyrinth();		

    glTranslatef(-10, 1, 10);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.3, 0.2, 0.1);
    glScalef(0.699, 0.699, 0.699);
    glutSolidOctahedron();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1, 1, 1);
    glScalef(1.0, 1.0, 1.0);
    glutSolidOctahedron();

    glTranslatef(0, 2, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.3, 0.0, 0.1);
    glScalef(0.7, 0.7, 0.7);
    glutSolidDodecahedron();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0, 0, 0);
    glScalef(1.0, 1.0, 1.0);
    glutSolidDodecahedron();




    glTranslatef(4, -2, 5);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.3, 0.0, 0.1);
    //glScalef(0.49, 0.49, 0.49);
    glutSolidTeapot(0.399);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0, 0, 0);
    //glScalef(0.5, 0.5, 0.5);
    glutSolidTeapot(0.4);

    glTranslatef(0, -0.6, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.3, 0.0, 0.1);
    glScalef(0.99, 0.99, 0.99);
    glutSolidCube(0.599);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0, 0, 0);
    glScalef(1.0, 1.0, 1.0);
    glutSolidCube(0.6);


    
    glPopMatrix();
    glTranslatef(0, 5, 0);
    glutSwapBuffers();
}


/* Called back when timer expired [NEW] */
void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(0, timer, 0); // next timer call milliseconds later
}

/* This function will registered as a callback with glutIdleFunc. Here it will
   be constantly called and perform updates to realise an animation. */
void idleFunc(void) {
    angleCube += 0.1f; // TASK 6:
    glutPostRedisplay();
}

/* This is our main method which will perform the setup of our first OpenGL
   window. The command line parameters will be passed but not used in the
   context of our application. Callbacks have been registered already and
   are prepared for future use during the lab. */
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(500, 500); // initial position of the window
    glutInitWindowSize(800, 600);     // initial size of the window
    //glClearDepth(1.0f);
    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    windowid = glutCreateWindow("Our Second OpenGL Window"); // create window
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glEnable(GL_DEPTH_TEST);       // Helper to be used with drawObjectAlt

    // register callbacks
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouseMovement);
    //glutDisplayFunc(renderPrimitives);// Part 1 - we simply render primitives
    //glutDisplayFunc(render3DScene);  // Part 2 - we start with 3D scene setup
    glutReshapeFunc(reshapeFunc);    // Part 2 - keep reshape for all 3D parts
    glutDisplayFunc(renderCube);     // Part 3 - we play with transformations 
    glutIdleFunc(idleFunc);
    glutTimerFunc(0, timer, 0);// Part 4 - we perform basic animation 
    glutSpecialFunc(processSpecialKeys); // HOMEWORK HELPER

    glutMainLoop(); // start the main loop of GLUT
    return 0;
}