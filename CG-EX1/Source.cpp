 /*---------------------------------------------------------------------------
 * Title: Maze/Ex 2 (HUE)
 * Objective: Follow the cat to find the cheese, escape the Maze.
 * Instructions: Click in vicinity of the cheese, 
 *      the pretend the cat is following you -- RUN!
 * BASED ON:
 * Title: Computer Graphics Lab 2 - Meshes and Transformations
 * Author: Christoph Anthes
 *------------------------------------------------------------------------- */
#include "GL/freeglut.h"
#include "math.h"
#include <stdio.h>

int windowid; // the identifier of the GLUT window

// Central Datastructure for the Maze: for Task 2
#define SIDE 30

// Camera motion variables - required for HOMEOWRK HELPER
GLdouble angle = 0.0f;          // angle of rotation for the camera direction
GLdouble lx = 0.0f, ly = 0.0f, lz = -1.0f; // actual vector representing the camera's
// direction
GLdouble x = (float)SIDE / 2, y = 1.0f, z = (float)SIDE / 2;    // XZ position of the camera

int maze[SIDE][SIDE]{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,0,0,1},
    {1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,1},
    {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
    {1,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
    {1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

#define _USE_MATH_DEFINES

/*
*/
//
// Actions (Task 1.4)
//

void jump_down(int val) {
    float fraction = 0.1f;
    y -= val * fraction;
}

void jump(int val) {
    float fraction = 0.1f;
    y += val * fraction;
    glutTimerFunc(500, jump_down, val);
}

bool is_occupied(float x, float z) {
    // map x/z coords to maze[SIDE = 30][SIDE = 30]
    // maze is drawn from the origin and made up of 1x1 cubes, so ...
    int maze_x = (int)x;
    int maze_z = (int)z;
    /* what is happening is:
    printf("maze_x is %d, maze_z is %d \n", maze_x, maze_z);
    printf("is wall? %d \n", maze[maze_x][maze_z]);*/
    return maze[maze_x][maze_z];
}

/*
*/
//Taken from http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/
// (template 2: Camera controls)
void processSpecialKeys(int key, int xcoor, int ycoor) {
    float fraction = 0.5f;

    /*
    */
    // 
    // BLOCKED DETECTION (TASK 2.1)
    // for back and forward movement, see below
    //
    float new_x = 0.0f;
    float new_z = 0.0f;

    switch (key) {
    case GLUT_KEY_LEFT:
        angle -= 0.05f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_RIGHT:
        angle += 0.05f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_UP:
        new_x = lx * fraction;
        new_z = lz * fraction;
        if (!is_occupied(x + new_x, z + new_z)) {
            x += new_x;
            z += new_z;
            // otherwise do nothing (maybe even rebuff <-- POSS. IMPROVEMENT)
        }
        break;
    case GLUT_KEY_DOWN:
        new_x = lx * fraction;
        new_z = lz * fraction;
        if (!is_occupied(x - new_x, z - new_z)) {
            x -= new_x;
            z -= new_z;
            // otherwise do nothing (maybe even rebuff <-- POSS. IMPROVEMENT)
        }
        break;
    }
}

/* 'WASD'-Movement, compare template */
void keyboard(unsigned char key, int xcoor, int ycoor) {
    float fraction = 0.5f;
    //printf("x is %f, z is %f \n", x, z);

    /*
    */
    // 
    // BLOCKED DETECTION (TASK 2.1)
    //
    float new_x = 0.0f;
    float new_z = 0.0f; // modulated by is_occupied boolean function

    switch (key) {
    case 'a':
        new_x = fraction * cos(angle);
        new_z = fraction * sin(angle); 
        if (!is_occupied(x-new_x, z-new_z)) {
            x -= new_x;
            z -= new_z; 
            // otherwise do nothing (maybe even rebuff <-- POSS. IMPROVEMENT)
        }
        break;
    case 'd':
        new_x = fraction * cos(angle);
        new_z = fraction * sin(angle); 
        if (!is_occupied(x + new_x, z + new_z)) {
            x += new_x;
            z += new_z;
            // otherwise do nothing (maybe even rebuff <-- POSS. IMPROVEMENT)
        }
        break;
    case 'w':
        new_x = lx * fraction;
        new_z = lz * fraction;
        if (!is_occupied(x + new_x, z + new_z)) {
            x += new_x;
            z += new_z;
            // otherwise do nothing (maybe even rebuff <-- POSS. IMPROVEMENT)
        }
        break;
    case 's':
        new_x = lx * fraction;
        new_z = lz * fraction;
        if (!is_occupied(x - new_x, z - new_z)) {
            x -= new_x;
            z -= new_z;
            // otherwise do nothing (maybe even rebuff <-- POSS. IMPROVEMENT)
        }
        break;
    /*
    */
    // 
    // JUMP FEATURE (TASK 1.4)
    //
    case ' ': 
        jump(25);
        break;
    case 27: // escape key
        glutDestroyWindow(windowid);
        exit(0);
        break;
    }
    //glutPostRedisplay();
}

// TASK 3(.0)
void mouse(int x, int y) {
    float fraction = 0.01f;

    // remeber coords
    static int lastXMousePosition, lastYMousePosition;
    static bool mouse_warped = false; 

    if (mouse_warped) {
        mouse_warped = false;
        return;
    }

    if (x < (glutGet(GLUT_WINDOW_WIDTH) / 2))
        angle -= fraction;
    else
        angle += fraction;

    lx = sin(angle);
    lz = -cos(angle);

    //glutPostRedisplay();

    lastXMousePosition = x;
    lastYMousePosition = y;

    glutWarpPointer((glutGet(GLUT_WINDOW_WIDTH) / 2), (glutGet(GLUT_WINDOW_HEIGHT) / 2));
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
    gluPerspective(40.0f, (GLdouble)xwidth / (GLdouble)yheight, 0.5f, 20.0f);
    glViewport(0, 0, xwidth, yheight);  // Use the whole window for rendering
}

/*
*/
//
// DRAW METHODS
//

// 
// MAZE
//

void drawFloor() {
    glTranslatef(SIDE / 2, 0, SIDE / 2); // position in the middle of the maze
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-SIDE/2, 0, -SIDE/2);
    glVertex3f(-SIDE/2, 0, SIDE/2);
    glVertex3f(SIDE/2, 0, SIDE/2);
    glVertex3f(SIDE/2, 0, -SIDE/2);
    glEnd();
    glTranslatef(-SIDE / 2, 0, -SIDE / 2); // position in the middle of the maze
}

void drawWall(int h) {
    glPushMatrix();
    glTranslatef(0, -1.0f, 0);
    for (size_t i = 0; i < h; i++) {
        glTranslatef(0, 1.0f, 0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glColor3f(0.12, 0.10, 0.55);
        glutSolidCube(1);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(1, 1, 1);
        glutSolidCube(1);
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glTranslatef(0, (float) -h, 0);
    glPopMatrix();
}

void drawMaze() {
    glTranslatef(-1.0f, 0, 0);
    for (int i = 0; i < SIDE; i++) {
        glTranslatef(1.0f, 0, 0); // scan x
        for (int j = 0; j < SIDE; j++) {
            glTranslatef(0, 0, 1.0); // scan z

            if (maze[i][j] == 1) {
                drawWall(3);
            }
        }
        glTranslatef(0, 0, -SIDE); // line back
    }
}


//
// MAZE CONTENT
//
// A cat from triangles/pytramids for ears and lines for whiskers follows.
// This is one cat but from two sets of objects (Aufgabe 1.1), each made of base objects:
//      The pyramids for ears from triangles
//      The whiskers made from 6 lines

void drawPyramid(float x, float y, float z, int s) {
    glTranslatef(x, y, z);

    glBegin(GL_TRIANGLES);           

    // Front
    glColor3f(s*1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, s*1.0f, 0.0f);
    glColor3f(0.0f, s*1.0f, 0.0f);     // Green
    glVertex3f(-s*1.0f, -s*1.0f, s*1.0f);
    glColor3f(0.0f, 0.0f, s*1.0f);     // Blue
    glVertex3f(s*1.0f, -s*1.0f, s*1.0f);

    // Right
    glColor3f(s*1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, s*1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, s*1.0f);     // Blue
    glVertex3f(1.0f, -s*1.0f, s*1.0f);
    glColor3f(0.0f, s*1.0f, 0.0f);     // Green
    glVertex3f(s*1.0f, -s*1.0f, -s*1.0f);

    // Back
    glColor3f(s*1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(0.0f, s*1.0f, 0.0f);
    glColor3f(0.0f, s*1.0f, 0.0f);     // Green
    glVertex3f(s*1.0f, -s*1.0f, -s*1.0f);
    glColor3f(0.0f, 0.0f, s*1.0f);     // Blue
    glVertex3f(-s*1.0f, -s*1.0f, -s*1.0f);

    // Left
    glColor3f(s*1.0f, 0.0f, 0.0f);       // Red
    glVertex3f(0.0f, s*1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, s*1.0f);       // Blue
    glVertex3f(-s*1.0f, -s*1.0f, -s*1.0f);
    glColor3f(0.0f, s*1.0f, 0.0f);       // Green
    glVertex3f(-s*1.0f, -s*1.0f, s*1.0f);

    glEnd();

    glTranslatef(-x, -y, -z);  // move back
}

void drawLine(float x, float y, float z, float xD, float yD, float zD, int s) { // second set of params are deltas
    glTranslatef(x, y, z);

    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(s*xD, s*yD, s*zD);
    glEnd();

    glTranslatef(-x, -y, -z);  // move back
}


void drawCat(float d) {
    // ears
    drawPyramid(-5.0f, 5.0f, d, 2);
    drawPyramid(5.0f, 5.0f, d, 2);

    // whiskers right
    drawLine(0.1f, 1.0f, d, 5.0f, 3.0f, 1.0f, 3); 
    drawLine(0.2f, 0.8f, d, 5.0f, 1.0f, 0.5f, 3); 
    drawLine(0.1f, 0.6f, d, 5.0f, -1.0f, 1.0f, 3); 

    // whiskers left
    drawLine(-0.1f, 1.0f, d, -5.0f, 3.0f, 1.0f, 3);
    drawLine(-0.2f, 0.8f, d, -5.0f, 1.0f, 0.5f, 3);
    drawLine(-0.1f, 0.6f, d, -5.0f, -1.0f, 1.0f, 3);

    // 
    // (it's an abstract cat.)
    //
}

//
// There is also a cirle/cylinder of cheese, using quad strip primitive
// (lots of vertices, for Augabe 1.2)

void drawCylinder(GLfloat radius,
    GLfloat height,
    GLubyte R,
    GLubyte G,
    GLubyte B)
{
    GLfloat x = 0.0;
    GLfloat y = 0.0;
    GLfloat angle = 0.0;
    GLfloat angle_stepsize = 0.1;

    /** Draw the tube */
    glColor3ub(R - 40, G - 40, B - 40);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while (angle < 2 * 3.14159265358979323846) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        glVertex3f(x, y, 0.0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R, G, B);
    glBegin(GL_POLYGON);
    angle = 0.0;
    while (angle < 2 * 3.14159265358979323846) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glVertex3f(x, y, height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
}

void drawCheese(int s) {
    drawCylinder(s * 1.0f, s * 1.0f, 254, 226, 62); // r, h, RGB for warm yellow
}

/* This function will replace the previous display function and will be used
   for rendering a cube and playing with transformations. */
void renderCube(void) {
    glMatrixMode(GL_MODELVIEW);
    // glClear(GL_DEPTH_BUFFER_BIT); // Helper to be used with drawObjectAlt
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    // TASK 5:

    //gluLookAt(navX, 0.0f, navZ,      // camera position
    //    navX, 0.0f, 0.0f,      // target position (at)
    //    0.0f, 1.0f, 0.0f);     // up vector

    /* HOMEWORK HELPER */
    gluLookAt(x, y, z,            // camera position
      x + lx, y + ly, z + lz,          // target position (at)
      0.0f, 1.0f, 0.0f);             // up vector (NO Y)

    // CALL DRAW METHODS
    // from origin
    drawFloor();
    drawMaze();

    // in the middle of the maze
    glTranslatef(-SIDE / 2, y, SIDE / 2);
    drawCat(-7.0); // TASK 1.1
    glTranslatef(SIDE / 2, y, -SIDE / 2);

    glTranslatef(-SIDE / 2, y - 2, SIDE / 2 - 3);
    drawCheese(1); // TASK 1.2
    glTranslatef(SIDE / 2, y - 2, -SIDE / 2 + 3);


    // TASK 4:
    //glTranslatef(0.0f, 0.0f, -5.0f);
    //glutSolidCube(0.5);
    //glTranslatef(-1.0f, 0.0f, 0.0f);
    //drawObject();
    // drawObjectAlt(); // Helper to be used with drawObjectAlt
    //glTranslatef(-1.0f, 0.0f, 0.0f);
    //drawObject();
    // drawObjectAlt(); // Helper to be used with drawObjectAltt
    //glTranslatef(0.0f, 1.0f, 0.0f);
    //drawObject();
    // drawObjectAlt(); // Helper to be used with drawObjectAlt

    glutSwapBuffers();
}

/* This function will registered as a callback with glutIdleFunc. Here it will
   be constantly called and perform updates to realise an animation. */
void idleFunc(void) {
    // IMPROVEMENT POSSIBILITY
    // if jump, count up to some height
    // if jump down, same

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
    windowid = glutCreateWindow("OpenGL Window"); // create window
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glEnable(GL_DEPTH_TEST);       // Helper to be used with drawObjectAlt

    // register callbacks
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouse);
    glutSetCursor(GLUT_CURSOR_NONE);
    glutReshapeFunc(reshapeFunc);    // Part 2 - keep reshape for all 3D parts
    glutDisplayFunc(renderCube);     // Part 3 - we play with transformations 
    glutIdleFunc(idleFunc);           // Part 4 - we perform basic animation 
    glutSpecialFunc(processSpecialKeys); // HOMEWORK HELPER

    glutMainLoop(); // start the main loop of GLUT
    return 0;
}