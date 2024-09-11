//
// Created by Drew Smith on 4/30/21.
//
#include "graphics.h"
#include "rect.h"
#include "circle.h"
#include <iostream>
#include <vector>

GLdouble width, height;
int wd;
using namespace std;

Rect user;
Rect user2;
vector<unique_ptr<Shape>> ball;


const color skyBlue(77/255.0, 213/255.0, 240/255.0);
const color grassGreen(26/255.0, 176/255.0, 56/255.0);
const color white(1, 1, 1);
const color brickRed(201/255.0, 20/255.0, 20/255.0);
const color darkBlue(1/255.0, 110/255.0, 214/255.0);
const color purple(119/255.0, 11/255.0, 224/255.0);
const color black(0, 0, 0);
const color magenta(1, 0, 1);
const color orange(1, 163/255.0, 22/255.0);
const color cyan (0, 1, 1);

void init() {
    width = 750;
    height = 750;
    initUsers();
    initBall();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

// user init
void initUsers(){
    // make the player on the right and left
    user.setColor(white);
    user.setSize(10, 75);
    user.setCenter(25, height/2);

    user2.setColor(white);
    user2.setSize(10,75);
    user2.setCenter(730, height/2);
}

// init ball
void initBall(){
    // makes the game ball with random velocity
    ball.push_back(make_unique<Circle>(grassGreen, width/2, height/2, 9));
    dimensions dim = {18,18};
    point2D pt = {width/2, height/2};
    ball.push_back(make_unique<Rect>(white, pt, dim));
}

/* Handler for window-repaint event. Call back when the window first appears and
whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you're on a Mac running Catalina)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    /*
     * Draw here
     */
    if(user.getSC() == start){
        string message3 = "Welcome to 2 player Pong";
        glColor3f(1,1,1);
        point2D center3 = {355, 100};
        glRasterPos2i(center3.x - (4 * message3.length()), center3.y + 7);
        for (const char &letter : message3) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string message2 = "Using the arrow keys or w and s you will play to 7.";
        glColor3f(1,1,1);
        point2D center2 = {355, 370};
        glRasterPos2i(center2.x - (4 * message2.length()), center2.y + 7);
        for (const char &letter : message2) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }


        string message = "Press the space bar to begin.";
        glColor3f(1, 1, 1);
        point2D center = {355, 650};
        glRasterPos2i(center.x - (4 * message.length()), center.y + 7);
        for (const char &letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string message4 = "Press ESC to leave.";
        glColor3f(1, 1, 1);
        point2D center4 = {355, 675};
        glRasterPos2i(center4.x - (4 * message4.length()), center4.y + 7);
        for (const char &letter : message4) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    if(user.getSC() == game) {
        int sc2 = user2.getScore();
        string message4 = to_string(sc2);
        glColor3f(1, 1, 1);
        point2D center4 = {width/2 - 45, 15};
        glRasterPos2i(center4.x - (4 * message4.length()), center4.y + 7);
        for (const char &letter : message4) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        int sc1 = user.getScore();
        string message3 = to_string(sc1);
        glColor3f(1, 1, 1);
        point2D center3 = {width/2 + 45, 15};
        glRasterPos2i(center3.x - (4 * message3.length()), center3.y + 7);
        for (const char &letter : message3) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        user.draw();
        user2.draw();
        ball[0]->draw();
    }

    if(user.getSC() == win){
        string message2 = "User 1 wins. User2 better luck next time";
        glColor3f(1,1,1);
        point2D center2 = {355, 370};
        glRasterPos2i(center2.x - (4 * message2.length()), center2.y + 7);
        for (const char &letter : message2) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string message = "Press the space bar to begin.";
        glColor3f(1, 1, 1);
        point2D center = {355, 650};
        glRasterPos2i(center.x - (4 * message.length()), center.y + 7);
        for (const char &letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string message4 = "Press ESC to leave.";
        glColor3f(1, 1, 1);
        point2D center4 = {355, 675};
        glRasterPos2i(center4.x - (4 * message4.length()), center4.y + 7);
        for (const char &letter : message4) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    if(user.getSC() == loss){
        string message2 = "User 2 wins. User 1 better luck next time";
        glColor3f(1,1,1);
        point2D center2 = {355, 370};
        glRasterPos2i(center2.x - (4 * message2.length()), center2.y + 7);
        for (const char &letter : message2) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string message = "Press the space bar to begin.";
        glColor3f(1, 1, 1);
        point2D center = {355, 650};
        glRasterPos2i(center.x - (4 * message.length()), center.y + 7);
        for (const char &letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string message4 = "Press ESC to leave.";
        glColor3f(1, 1, 1);
        point2D center4 = {355, 675};
        glRasterPos2i(center4.x - (4 * message4.length()), center4.y + 7);
        for (const char &letter : message4) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }


    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y){
    if(key == 27){
        glutDestroyWindow(wd);
        exit(0);
    }
    if(key == 32){
        if(user.getSC() == start){
            user.setSC(game);
            // set ball at a random velocity direction
            ball[0]->setVelocity(rand() % 30 + (-15), rand() % 30 + (-15));
        } else if(user.getSC() == win || user.getSC() == loss || user.getSC() == game){
            user.setScore(0);
            user2.setScore(0);
            ball[0]->setVelocity(0,0);
            for(int i = 0; i < ball.size(); i++){
                ball[i]->setCenter(width/2, height/2);
            }
            user.setSC(start);
        }
    }
    if(key == 119){
        user.moveY(-15);
    }
    if(key == 115){
        user.moveY(15);
    }
    // up and down for left player will be w and s
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        // up and down for right player will be up and down arrow keys
        case GLUT_KEY_DOWN:
            user2.moveY(30);
            break;
        case GLUT_KEY_LEFT:
            // move user to the left

            break;
        case GLUT_KEY_RIGHT:
            // move user to the right

            break;
        case GLUT_KEY_UP:
            user2.moveY(-30);
            break;
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {

    glutPostRedisplay();
}

void timer(int dummy) {
    ball[0]->move(ball[0]->getXVelocity(), ball[0]->getYVelocity());
    ball[1]->move(ball[0]->getXVelocity(), ball[0]->getYVelocity());

    if(ball[1]->getLeftX() < 0){
        // score for player 1
        user.setScore(user.getScore()+1);
        // reset ball to center with random vel
        for(int i = 0; i < ball.size(); i++) {
            ball[i]->setCenter(width/2, height/2);
        }
        ball[0]->setVelocity(rand() % 30 + (-15), rand() % 30 + (-15));
    } else if(ball[1]->getRightX() > width){
        // score for player 2
        user2.setScore(user2.getScore()+1);
        // reset ball to center with random vel
        for(int i = 0; i < ball.size(); i++) {
            ball[i]->setCenter(width/2, height/2);
        }
        ball[0]->setVelocity(rand() % 30 + (-15), rand() % 30 + (-15));
    }
    if(ball[1]->getTopY() < 0){
        ball[0]->bounceY();
    } else if(ball[1]->getBottomY() > height){
        // only temp will swap to making this a loss but for testing purposses
        ball[0]->bounceY();
    }

    if (dynamic_cast<Rect&>(*ball[1]).isOverlapping(user)){
        ball[0]->bounceX();
    }
    if (dynamic_cast<Rect&>(*ball[1]).isOverlapping(user2)){
        ball[0]->bounceX();
    }
    if(user.getScore() == 7){
        user.setSC(win);
    }
    if(user2.getScore() == 7){
        user.setSC(loss);
    }

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Pong" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}


