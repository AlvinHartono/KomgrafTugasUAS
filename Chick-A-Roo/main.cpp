#include <GL/gl.h>
#include <GL/glut.h>

#include <windows.h>
#include <math.h>
#include <string>
#include <iostream>
#define PI 3.1416;

//DEKLARASI VARIABLE
bool jump = false;
bool restart = false;
int window_width = 1500;
int window_height = 800;

float x_position = 1.0;
float y_position = -0.2;

float rockPosX = 4.0;
float rockPosY = -0.55;
float rockSpeed = 0.05;

float cloudPosX = 0.5;
float cloudSpeed = 0.001;
int state = 1;

int score = 0;
int scoreUpdate = 1;
float distanceY = 0;
float distanceX = 0;
float jumpHeight = 0.06;

void displayPoin();
void update(int value);
void chickenObject();
void timer(int value);
void clouds();
void ground();
void coup1();
void coup2();
void fence();
void rockObject();
void rumput();
void display();
void keyboard(unsigned char key, int x, int y);
void WelcomeDisplay();
void GameOver();

void keyboard(unsigned char key, int x, int y) {
    if (key == ' ') {
        rockSpeed = 0.05;
        glutDisplayFunc(display);
        glutPostOverlayRedisplay();
        if(!jump){
                // If spacebar is pressed, initiate a jump
        jump = true;
        y_position += 0.0;
        }
    } else if (key == 'r') {
        if(!restart){

        score = 0;
        scoreUpdate = 1;
        rockPosX = 4.0;
        rockPosY = -0.55;
        rockSpeed = 0.05;
        cloudPosX = 0.5;
        cloudSpeed = 0.001;
        distanceY = 0;
        distanceX = 0;
        jumpHeight = 0.06;
        glutDisplayFunc(display);
        glutPostOverlayRedisplay();
        }
    }
}

void displayPoin(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.95, 0.8);
    glVertex2f(-0.75, 0.8);
    glVertex2f(-0.75, 1.0);
    glVertex2f(-0.95, 1.0);
    glEnd();


    glColor3f(1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glRasterPos2f(-0.9, 0.9);
    std::string text = "Score: " + std::to_string(score);


    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glFlush();
}

void update(int value) {
    score+= scoreUpdate;
    if (jump) { // If jump is initiated, move the dinosaur up
        y_position += jumpHeight;
        if (y_position > 1.3) { // If the dinosaur has reached the peak of the jump, start falling down
            jump = false;
        }
    }
    else { // If jump is not initiated, move the dinosaur down
        y_position -= jumpHeight;
        if (y_position < 0.0) { // If the dinosaur has reached the ground, reset its position
            y_position = 0.0;
        }
    }
    if (rockPosX <= -4.0f) {
        rockPosX = 4.0f; // Reset the position to the right edge of the screen
    } else {
        rockPosX -= rockSpeed; // Move the rock to the left
    }

    distanceX =  rockPosX - x_position;
    distanceY = rockPosY - y_position;

    if((distanceX - 0.0) < -0.8 && (distanceX - 0.0) > -1.0 && abs(distanceY - (-0.55)) < 0.001){
        scoreUpdate = 0;
        rockSpeed = 0;
        jumpHeight = 0;
        glutDisplayFunc(GameOver);
        glutPostOverlayRedisplay();
    }
   switch(state){
    case 1:
        if(cloudPosX<9)
            cloudPosX+= cloudSpeed;
        else
            state =-1;

        break;
    case -1:
        if(cloudPosX>-9)
            cloudPosX-= cloudSpeed;
        else
            state =1;
        break;
    }

    glutPostRedisplay(); // Call the display function to update the screen
    glutTimerFunc(25, update, 0); // Call the update function again after 25 milliseconds
}

void chickenObject(){

    glLoadIdentity();

    glLineWidth(10.0f);
     float x, y;
	 int i;
	 GLfloat radius;
	 int triangleAmount = 100;
	 GLfloat twicePi = 2.0 * PI;
    glScalef(0.5f, 0.5f, 0.0f);
    glTranslatef(0.5f,y_position,0);

    glBegin(GL_TRIANGLE_FAN);//outline ayam
        glColor3ub(230,174,37);
        x= -0.4;
        y=-0.4;

        radius = 0.31;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();

    glBegin(GL_LINES); //Kaki kiri
    glColor3ub(222,105,0);
        glVertex2f(-0.48f, -0.661f); // top left
        glVertex2f(-0.518f, -0.78f); // bottom left
        glVertex2f(-0.535f, -0.78f); // top right
        glVertex2f(-0.43f, -0.781f); // top right
    glEnd();

    glBegin(GL_LINES); //Kaki Kanan
    glColor3ub(222,105,0);
        glVertex2f(-0.301f, -0.655f); // top left
        glVertex2f(-0.221f, -0.78f); // bottom left
        glVertex2f(-0.246f, -0.78f); // top right
        glVertex2f(-0.157f, -0.78f); // top right
    glEnd();



	 glBegin(GL_TRIANGLE_FAN);
        glColor3ub(255,236,2);
        x= -0.4;
        y=-0.4;

        radius = 0.3;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();

    glBegin(GL_POLYGON); //Chicken Comb (jambul)
    glColor3ub(255, 87, 51);
        glVertex2f(-0.576f, -0.190f); // top left
        glVertex2f(-0.501f, -0.039); // bottom left
        glVertex2f(-0.45f, -0.1f); // top right
        glVertex2f(-0.4f, 0.0f); // bottom right
        glVertex2f(-0.35f, -0.1f); // bottom right
        glVertex2f(-0.274f, 0.0f); // bottom right
        glVertex2f(-0.231f, -0.184f); // bottom right
        glVertex2f(-0.576f, -0.190f); // top left
        glEnd();

    glBegin(GL_POLYGON); //Chicken Wing (sayap)
    glColor3ub(254,206,0);
        glVertex2f(-0.339f, -0.398f); // top left
        glVertex2f(-0.4f, -0.3f); // bottom left
        glVertex2f(-0.479f, -0.267f); // top right
        glVertex2f(-0.560f, -0.317f); // bottom right
        glVertex2f(-0.501f, -0.341f); // bottom right
        glVertex2f(-0.64f, -0.361f); // bottom right
        glVertex2f(-0.524f, -0.416f); // bottom right
        glVertex2f(-0.458f, -0.443f); // top left
        glVertex2f(-0.38f, -0.441f); // top left
        glVertex2f(-0.339f, -0.398f); // top left
        glEnd();

    glBegin(GL_POLYGON); //PARUH
    glColor3ub(242,124,0);
        glVertex2f(-0.136f, -0.394f); // top right
        glVertex2f(-0.129f, -0.36f); // top left
        glVertex2f(-0.1f, -0.35f); // bottom left
        glVertex2f(-0.051f, -0.37f); // top right
        glVertex2f(-0.126f, -0.394f); // top right
        glVertex2f(-0.06f, -0.4f); // top right
        glVertex2f(-0.098f, -0.440f); // top right
        glVertex2f(-0.126f, -0.430f); // top right
        glVertex2f(-0.126f, -0.394f); // top right

    glEnd();

    /*glBegin(GL_LINES); // MATA
    glColor3ub(28,28,28);
        glVertex2f(-0.240f, -0.338f); // top left
        glVertex2f(-0.2f, -0.3); // bottom left
        glVertex2f(-0.160f, -0.339f); // top right
        glEnd();*/

	glBegin(GL_TRIANGLE_FAN);//mata
        glColor3ub(28,28,28);
        x= -0.2;
        y=-0.32;
        radius = 0.03;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();

    	glBegin(GL_TRIANGLE_FAN);//pipi
        glColor3ub(254,206,0);
        x= -0.26;
        y=-0.4;
        radius = 0.03;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();

}

void clouds(){
	 float x, y;
	 int i;
	 GLfloat radius;
	 int triangleAmount = 100;
	 GLfloat twicePi = 2.0 * PI;

     glTranslatef(cloudPosX,-0.2f,0);
	 glBegin(GL_TRIANGLE_FAN);//awan1.1
        glColor3ub(255,255,255);
        x=-0.50;
        y=3.3;
        radius = 0.3;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();


    glBegin(GL_TRIANGLE_FAN);//awan1.2
        glColor3ub(255,255,255);
        x=-0.20;
        y=3.72;
        radius = 0.32;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();


    glBegin(GL_TRIANGLE_FAN);//awan1.3
        glColor3ub(255,255,255);
        x=-0.13;
        y=3.3;
        radius = 0.30;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();



    glBegin(GL_TRIANGLE_FAN);//awan1.4
        glColor3ub(255,255,255);
        x=0.18;
        y=3.58;
        radius = 0.32;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();



    glBegin(GL_TRIANGLE_FAN);//awan1.5
        glColor3ub(255,255,255);
        x=0.38;
        y=3.3;
        radius = 0.32;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();



    //awan 2
    glBegin(GL_TRIANGLE_FAN);//awan2.1
        glColor3ub(255,255,255);
        x=-3.8;
        y=3.2;
        radius = 0.3;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();



    glBegin(GL_TRIANGLE_FAN);//awan2.2
        glColor3ub(255,255,255);
        x=-3.5;
        y=3.52;
        radius = 0.3;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();



    glBegin(GL_TRIANGLE_FAN);//awan2.3
        glColor3ub(255,255,255);
        x=-3.3;
        y=3.2;
        radius = 0.3;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();


    glBegin(GL_TRIANGLE_FAN);//awan2.4
        glColor3ub(255,255,255);
        x=-3.0;
        y=3.32;
        radius = 0.3;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();
}

void ground (){
    glLineWidth(3.0f);

    glLoadIdentity();
    glBegin(GL_QUADS);
    glColor3ub(101,206,25);
        glVertex2f(-1.0f, -1.0f); // bottom left
        glVertex2f(-1.0f, -0.4f); // top left
        glVertex2f(1.0f, -0.4f); // top right
        glVertex2f(1.0f, -1.0f); // bottom right
    glEnd();

     glBegin(GL_LINES);
    glColor3ub(54,100,31);
        glVertex2f(-1.0f, -1.0f); // bottom left
        glVertex2f(-1.0f, -0.4f); // top left
        glVertex2f(1.0f, -0.4f); // top right
        glVertex2f(-1.0f, -0.4f); // top left
        glVertex2f(1.0f, -1.0f); // bottom right
    glEnd();

}

void coup1 (){
     glLoadIdentity();
    glTranslatef(0.05f,0.0,0.0);
     glLineWidth(5.0f);
    //atap
    glBegin(GL_POLYGON);
    glColor3ub(187,48,39);
        glVertex2f(-0.45f, 0.05f); // bottom right M
        glVertex2f(-0.45f, 0.1f); // bottom right P
        glVertex2f(-0.65f, 0.3f); // top center
        glVertex2f(-0.85f, 0.1f); // bottom left O
        glVertex2f(-0.85f, 0.05f); // bottom left K
        glVertex2f(-0.65f, 0.25f); // bottom center
        glVertex2f(-0.45f, 0.05f); // bottom right M
    glEnd();


    //kotak utama
    glBegin(GL_POLYGON);
    glColor3ub(251,172,42);
        glVertex2f(-0.5f, -0.3f); // bottom right
        glVertex2f(-0.5f, 0.1f); // top right
        glVertex2f(-0.8f, 0.1f); // top left
        glVertex2f(-0.8f, -0.3f); // bottom left
    glEnd();

    //segitiga atap
    glBegin(GL_POLYGON);
    glColor3ub(251,172,42);
        glVertex2f(-0.5f, 0.1f); // top right
        glVertex2f(-0.65f, 0.25f); // center
        glVertex2f(-0.8f, 0.1f); // top left
    glEnd();

     //segitiga atap
    glBegin(GL_LINES);
    glColor3ub(200,130,28);
        glVertex2f(-0.5f, 0.1f); // top right
        glVertex2f(-0.65f, 0.25f); // center
        glVertex2f(-0.8f, 0.1f); // top left
        glVertex2f(-0.65f, 0.25f); // center
    glEnd();


     //pintu
    glBegin(GL_POLYGON);
    glColor3ub(93,44,13);
        glVertex2f(-0.72f, -0.3f); // btm left
        glVertex2f(-0.72f, -0.06f); // top left
        glVertex2f(-0.58f, -0.06f); // top right
        glVertex2f(-0.58f, -0.3f); // btm right

    glEnd();

    //pintu
    glBegin(GL_LINES);
    glColor3ub(134,63,17);
        glVertex2f(-0.72f, -0.3f); // btm left
        glVertex2f(-0.72f, -0.06f); // top left
        glVertex2f(-0.58f, -0.06f); // top right
        glVertex2f(-0.58f, -0.3f); // btm right

    glEnd();

     //jendela atas
    glBegin(GL_POLYGON);
    glColor3ub(93,44,13);
        glVertex2f(-0.7f, 0.14f); // top left
        glVertex2f(-0.7f, 0.08f); // btm left
        glVertex2f(-0.6f, 0.08f); // btm right
        glVertex2f(-0.6f, 0.14f); // top right

    glEnd();

     glBegin(GL_LINES);
    glColor3ub(134,63,17);
        glVertex2f(-0.7f, 0.14f); // top left
        glVertex2f(-0.7f, 0.08f); // btm left
        glVertex2f(-0.6f, 0.08f); // btm right
        glVertex2f(-0.6f, 0.14f); // top right

    glEnd();


     //tatakan bawah
    glBegin(GL_POLYGON);
    glColor3ub(187,48,39);
        glVertex2f(-0.84f, -0.3f); // top left
        glVertex2f(-0.84f, -0.34f); // btm left
        glVertex2f(-0.46f, -0.34f); // btm right
        glVertex2f(-0.46f, -0.3f); // top right

    glEnd();

     //tatakan kiri
    glBegin(GL_POLYGON);
    glColor3ub(143,65,30);
        glVertex2f(-0.77f, -0.34f); // top left
        glVertex2f(-0.82f, -0.4f); // btm left
        glVertex2f(-0.77f, -0.4f); // btm right
        glVertex2f(-0.72f, -0.34f); // top right

    glEnd();

      //tatakan kanan
    glBegin(GL_POLYGON);
    glColor3ub(143,65,30);
        glVertex2f(-0.58f, -0.34f); // top left
        glVertex2f(-0.52f, -0.4f); // btm left
        glVertex2f(-0.48f, -0.4f); // btm right
        glVertex2f(-0.53f, -0.34f); // top right

    glEnd();

}

void coup2 (){
     glLoadIdentity();
    glTranslatef(1.37f,0.0,0.0);
     glLineWidth(5.0f);
    //atap
    glBegin(GL_POLYGON);
    glColor3ub(187,48,39);
        glVertex2f(-0.45f, 0.05f); // bottom right M
        glVertex2f(-0.45f, 0.1f); // bottom right P
        glVertex2f(-0.65f, 0.3f); // top center
        glVertex2f(-0.85f, 0.1f); // bottom left O
        glVertex2f(-0.85f, 0.05f); // bottom left K
        glVertex2f(-0.65f, 0.25f); // bottom center
        glVertex2f(-0.45f, 0.05f); // bottom right M
    glEnd();


    //kotak utama
    glBegin(GL_POLYGON);
    glColor3ub(251,172,42);
        glVertex2f(-0.5f, -0.3f); // bottom right
        glVertex2f(-0.5f, 0.1f); // top right
        glVertex2f(-0.8f, 0.1f); // top left
        glVertex2f(-0.8f, -0.3f); // bottom left
    glEnd();

    //segitiga atap
    glBegin(GL_POLYGON);
    glColor3ub(251,172,42);
        glVertex2f(-0.5f, 0.1f); // top right
        glVertex2f(-0.65f, 0.25f); // top right
        glVertex2f(-0.8f, 0.1f); // top left
    glEnd();

    //segitiga atap
    glBegin(GL_LINES);
    glColor3ub(200,130,28);
        glVertex2f(-0.5f, 0.1f); // top right
        glVertex2f(-0.65f, 0.25f); // center
        glVertex2f(-0.8f, 0.1f); // top left
        glVertex2f(-0.65f, 0.25f); // center
    glEnd();

     //pintu
    glBegin(GL_POLYGON);
    glColor3ub(93,44,13);
        glVertex2f(-0.72f, -0.3f); // btm left
        glVertex2f(-0.72f, -0.06f); // top left
        glVertex2f(-0.58f, -0.06f); // top right
        glVertex2f(-0.58f, -0.3f); // btm right

    glEnd();

     //pintu
    glBegin(GL_LINES);
    glColor3ub(134,63,17);
        glVertex2f(-0.72f, -0.3f); // btm left
        glVertex2f(-0.72f, -0.06f); // top left
        glVertex2f(-0.58f, -0.06f); // top right
        glVertex2f(-0.58f, -0.3f); // btm right

    glEnd();

     //jendela atas
    glBegin(GL_POLYGON);
    glColor3ub(93,44,13);
        glVertex2f(-0.7f, 0.14f); // top left
        glVertex2f(-0.7f, 0.08f); // btm left
        glVertex2f(-0.6f, 0.08f); // btm right
        glVertex2f(-0.6f, 0.14f); // top right

    glEnd();

      glBegin(GL_LINES);
    glColor3ub(134,63,17);
        glVertex2f(-0.7f, 0.14f); // top left
        glVertex2f(-0.7f, 0.08f); // btm left
        glVertex2f(-0.6f, 0.08f); // btm right
        glVertex2f(-0.6f, 0.14f); // top right

    glEnd();

     //tatakan bawah
    glBegin(GL_POLYGON);
    glColor3ub(187,48,39);
        glVertex2f(-0.84f, -0.3f); // top left
        glVertex2f(-0.84f, -0.34f); // btm left
        glVertex2f(-0.46f, -0.34f); // btm right
        glVertex2f(-0.46f, -0.3f); // top right

    glEnd();



     //tatakan kiri
    glBegin(GL_POLYGON);
    glColor3ub(143,65,30);
        glVertex2f(-0.77f, -0.34f); // top left
        glVertex2f(-0.82f, -0.4f); // btm left
        glVertex2f(-0.77f, -0.4f); // btm right
        glVertex2f(-0.72f, -0.34f); // top right

    glEnd();


      //tatakan kanan
    glBegin(GL_POLYGON);
    glColor3ub(143,65,30);
        glVertex2f(-0.58f, -0.34f); // top left
        glVertex2f(-0.52f, -0.4f); // btm left
        glVertex2f(-0.48f, -0.4f); // btm right
        glVertex2f(-0.53f, -0.34f); // top right

    glEnd();


}

void fence (){

     glLoadIdentity();

    glLineWidth(2.0f);

    glBegin(GL_POLYGON); //middle
    glColor3ub(198,133,65);
    //glColor3ub(181,126,77);
        glVertex2f(1.0f, -0.25f); // bottom left
        glVertex2f(1.0f, -0.15f); // top left
        glVertex2f(-1.0f, -0.15f); // top right
        glVertex2f(-1.0f, -0.25f); // bottom right
    glEnd();

    //lines
    glBegin(GL_LINES);

    glColor3ub(82,23,3);
    //glColor3ub(202,157,115);
        //glVertex2f(1.0f, -0.35f); // bottom left
        glVertex2f(1.0f, -0.25f); // top left
        glVertex2f(-1.0f, -0.25f); // top right
        //glVertex2f(-1.0f, -0.35f); // bottom right

    glEnd();


    glBegin(GL_POLYGON);
    glColor3ub(181,126,77);
    //glColor3ub(202,157,115);
        glVertex2f(0.9f, -0.4f); // bottom left
        glVertex2f(0.9f, -0.0f); // top left
        glVertex2f(1.0f, -0.0f); // top right
        glVertex2f(1.0f, -0.4f); // bottom right
    glEnd();

    //lines
     glBegin(GL_LINES);
    glColor3ub(82,23,3);
    //glColor3ub(202,157,115);
        glVertex2f(0.9f, -0.0f); // top left
         glVertex2f(0.9f, -0.4f); // bottom left
        glVertex2f(1.0f, -0.0f); // top right
        glVertex2f(1.0f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON);
     glColor3ub(181,126,77);
    // glColor3ub(202,157,115);
        glVertex2f(0.7f, -0.4f); // bottom left
        glVertex2f(0.7f, -0.0f); // top left
        glVertex2f(0.8f, -0.0f); // top right
        glVertex2f(0.8f, -0.4f); // bottom right
    glEnd();

    //lines
     glBegin(GL_LINES);
    glColor3ub(82,23,3);
    //glColor3ub(202,157,115);
        glVertex2f(0.7f, -0.4f); // bottom left
        glVertex2f(0.7f, -0.0f); // top left
        glVertex2f(0.8f, -0.0f); // top right
        glVertex2f(0.8f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON);
     glColor3ub(181,126,77);
     //glColor3ub(202,157,115);
        glVertex2f(0.5f, -0.4f); // bottom left
        glVertex2f(0.5f, -0.0f); // top left
        glVertex2f(0.6f, -0.0f); // top right
        glVertex2f(0.6f, -0.4f); // bottom right
    glEnd();

        //lines
     glBegin(GL_LINES);
    glColor3ub(82,23,3);
    //glColor3ub(202,157,115);
        glVertex2f(0.5f, -0.4f); // bottom left
        glVertex2f(0.5f, -0.0f); // top left
        glVertex2f(0.6f, -0.0f); // top right
        glVertex2f(0.6f, -0.4f); // bottom right
    glEnd();


    glBegin(GL_POLYGON);
     glColor3ub(181,126,77);
     //glColor3ub(202,157,115);
        glVertex2f(0.3f, -0.4f); // bottom left
        glVertex2f(0.3f, -0.0f); // top left
        glVertex2f(0.4f, -0.0f); // top right
        glVertex2f(0.4f, -0.4f); // bottom right
    glEnd();

      //lines
     glBegin(GL_LINES);
    glColor3ub(82,23,3);
    //glColor3ub(202,157,115);
        glVertex2f(0.3f, -0.4f); // bottom left
        glVertex2f(0.3f, -0.0f); // top left
        glVertex2f(0.4f, -0.0f); // top right
        glVertex2f(0.4f, -0.4f); // bottom right
    glEnd();


    glBegin(GL_POLYGON);
    glColor3ub(181,126,77);
    //glColor3ub(202,157,115);
        glVertex2f(0.1f, -0.4f); // bottom left
        glVertex2f(0.1f, -0.0f); // top left
        glVertex2f(0.2f, -0.0f); // top right
        glVertex2f(0.2f, -0.4f); // bottom right
    glEnd();

    //lines
     glBegin(GL_LINES);
    glColor3ub(82,23,3);
    //glColor3ub(202,157,115);
        glVertex2f(0.1f, -0.4f); // bottom left
        glVertex2f(0.1f, -0.0f); // top left
        glVertex2f(0.2f, -0.0f); // top right
        glVertex2f(0.2f, -0.4f); // bottom right
    glEnd();


    glBegin(GL_POLYGON);
   glColor3ub(181,126,77);
   //glColor3ub(202,157,115);
        glVertex2f(-0.1f, -0.4f); // bottom left
        glVertex2f(-0.1f, -0.0f); // top left
        glVertex2f(0.0f, -0.0f); // top right
        glVertex2f(0.0f, -0.4f); // bottom right
    glEnd();

     //lines
     glBegin(GL_LINES);
    glColor3ub(82,23,3);
    //glColor3ub(202,157,115);
        glVertex2f(-0.1f, -0.4f); // bottom left
        glVertex2f(-0.1f, -0.0f); // top left
        glVertex2f(0.0f, -0.0f); // top right
        glVertex2f(0.0f, -0.4f); // bottom right
    glEnd();


    glBegin(GL_POLYGON);
    glColor3ub(181,126,77);
     //glColor3ub(202,157,115);
        glVertex2f(-0.3f, -0.4f); // bottom left
        glVertex2f(-0.3f, -0.0f); // top left
        glVertex2f(-0.2f, -0.0f); // top right
        glVertex2f(-0.2f, -0.4f); // bottom right
    glEnd();

    //lines
     glBegin(GL_LINES);
    glColor3ub(82,23,3);
    //glColor3ub(202,157,115);
       glVertex2f(-0.3f, -0.4f); // bottom left
        glVertex2f(-0.3f, -0.0f); // top left
        glVertex2f(-0.2f, -0.0f); // top right
        glVertex2f(-0.2f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(181,126,77);
    //glColor3ub(202,157,115);
        glVertex2f(-0.5f, -0.4f); // bottom left
        glVertex2f(-0.5f, -0.0f); // top left
        glVertex2f(-0.4f, -0.0f); // top right
        glVertex2f(-0.4f, -0.4f); // bottom right
    glEnd();

     //lines
     glBegin(GL_LINES);
    glColor3ub(82,23,3);
    //glColor3ub(202,157,115);
       glVertex2f(-0.5f, -0.4f); // bottom left
        glVertex2f(-0.5f, -0.0f); // top left
        glVertex2f(-0.4f, -0.0f); // top right
        glVertex2f(-0.4f, -0.4f); // bottom right
    glEnd();


    glBegin(GL_POLYGON);
    glColor3ub(181,126,77);
    //glColor3ub(202,157,115);
        glVertex2f(-0.7f, -0.4f); // bottom left
        glVertex2f(-0.7f, -0.0f); // top left
        glVertex2f(-0.6f, -0.0f); // top right
        glVertex2f(-0.6f, -0.4f); // bottom right
    glEnd();

     //lines
     glBegin(GL_LINES);
    glColor3ub(82,23,3);
    //glColor3ub(202,157,115);
       glVertex2f(-0.7f, -0.4f); // bottom left
        glVertex2f(-0.7f, -0.0f); // top left
        glVertex2f(-0.6f, -0.0f); // top right
        glVertex2f(-0.6f, -0.4f); // bottom right
    glEnd();


     glBegin(GL_POLYGON);
  glColor3ub(181,126,77);
  //glColor3ub(202,157,115);
        glVertex2f(-0.9f, -0.4f); // bottom left
        glVertex2f(-0.9f, -0.0f); // top left
        glVertex2f(-0.8f, -0.0f); // top right
        glVertex2f(-0.8f, -0.4f); // bottom right
    glEnd();

      //lines
     glBegin(GL_LINES);
    glColor3ub(82,23,3);
    //glColor3ub(202,157,115);
       glVertex2f(-0.9f, -0.4f); // bottom left
        glVertex2f(-0.9f, -0.0f); // top left
        glVertex2f(-0.8f, -0.0f); // top right
        glVertex2f(-0.8f, -0.4f); // bottom right
    glEnd();
}

void rockObject(){

    glLineWidth(3.0f);

    glLoadIdentity();
    glScalef(0.3f, 0.3f, 0.0f);
    glTranslatef(rockPosX,rockPosY,0);
    glBegin(GL_POLYGON);
    glColor3ub(178,185,195);
        glVertex2f(0.220f, -0.8f);
        glVertex2f(0.237f, -0.756f);
        glVertex2f(0.259f, -0.719f);
        glVertex2f(0.297f, -0.685f);
        glVertex2f(0.360f, -0.682f);
        glVertex2f(0.419f, -0.699f);
        glVertex2f(0.442f, -0.731f);
        glVertex2f(0.297f, -0.685f);
        glVertex2f(0.478f, -0.741f);
        glVertex2f(0.5f, -0.7f);
        glVertex2f(0.527f, -0.660f);
        glVertex2f(0.561f, -0.621f);
        glVertex2f(0.6f, -0.6f);
        glVertex2f(0.656f, -0.578f);
        glVertex2f(0.708f, -0.578f);
        glVertex2f(0.754, -0.606f);
        glVertex2f(0.787f, -0.643f);
        glVertex2f(0.821f, -0.689f);
        glVertex2f(0.836f, -0.738f);
        glVertex2f(0.842f, -0.8);
        glVertex2f(0.220f, -0.8f);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(153,151,149);
        glVertex2f(0.220f, -0.8f);
        glVertex2f(0.237f, -0.756f);
        glVertex2f(0.259f, -0.719f);
        glVertex2f(0.297f, -0.685f);
        glVertex2f(0.360f, -0.682f);
        glVertex2f(0.419f, -0.699f);
        glVertex2f(0.442f, -0.731f);
        glVertex2f(0.297f, -0.685f);
        glVertex2f(0.478f, -0.741f);
        glVertex2f(0.5f, -0.7f);
        glVertex2f(0.527f, -0.660f);
        glVertex2f(0.561f, -0.621f);
        glVertex2f(0.6f, -0.6f);
        glVertex2f(0.656f, -0.578f);
        glVertex2f(0.708f, -0.578f);
        glVertex2f(0.754, -0.606f);
        glVertex2f(0.787f, -0.643f);
        glVertex2f(0.821f, -0.689f);
        glVertex2f(0.836f, -0.738f);
        glVertex2f(0.842f, -0.8);
        glVertex2f(0.220f, -0.8f);
    glEnd();
}

void rumput (){

    //glLoadIdentity();

	glBegin(GL_POLYGON); //1
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-1.0f, -0.4f); // bottom left
        glVertex2f(-0.97, -0.27f); // center
        glVertex2f(-0.95f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //2
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.95f, -0.4f); // bottom left
        glVertex2f(-0.93, -0.30f); // center
        glVertex2f(-0.9f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //3
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.9f, -0.4f); // bottom left
        glVertex2f(-0.87, -0.25f); // center
        glVertex2f(-0.85f, -0.4f); // bottom right
    glEnd();


    glBegin(GL_POLYGON); //4
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.85f, -0.4f); // bottom left
        glVertex2f(-0.84f, -0.28f); // center
        glVertex2f(-0.82f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //5
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.82f, -0.4f); // bottom left
        glVertex2f(-0.78f, -0.26f); // center
        glVertex2f(-0.77f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //6
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.77f, -0.4f); // bottom left
        glVertex2f(-0.75f, -0.3f); // center
        glVertex2f(-0.73f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //7
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.73f, -0.4f); // bottom left
        glVertex2f(-0.72f, -0.24f); // center
        glVertex2f(-0.68f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //8
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.68f, -0.4f); // bottom left
        glVertex2f(-0.66f, -0.27f); // center
        glVertex2f(-0.64f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //8
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.64f, -0.4f); // bottom left
        glVertex2f(-0.63f, -0.3f); // center
        glVertex2f(-0.6f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //9
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.6f, -0.4f); // bottom left
        glVertex2f(-0.58f, -0.24f); // center
        glVertex2f(-0.56f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //10
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.56f, -0.4f); // bottom left
        glVertex2f(-0.55f, -0.28f); // center
        glVertex2f(-0.53f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //11
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.53f, -0.4f); // bottom left
        glVertex2f(-0.5f, -0.27f); // center
        glVertex2f(-0.47f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //12
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.47f, -0.4f); // bottom left
        glVertex2f(-0.47f, -0.25f); // center
        glVertex2f(-0.43f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //13
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.43f, -0.4f); // bottom left
        glVertex2f(-0.4f, -0.27f); // center
        glVertex2f(-0.4f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //14
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.43f, -0.4f); // bottom left
        glVertex2f(-0.4f, -0.27f); // center
        glVertex2f(-0.4f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //15
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.4f, -0.4f); // bottom left
        glVertex2f(-0.38f, -0.29f); // center
        glVertex2f(-0.36f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //16
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.36f, -0.4f); // bottom left
        glVertex2f(-0.34f, -0.26f); // center
        glVertex2f(-0.32f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //17
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.32f, -0.4f); // bottom left
        glVertex2f(-0.31f, -0.27f); // center
        glVertex2f(-0.3f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //18
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.3f, -0.4f); // bottom left
        glVertex2f(-0.28f, -0.27f); // center
        glVertex2f(-0.26f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //19
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.26f, -0.4f); // bottom left
        glVertex2f(-0.26f, -0.30f); // center
        glVertex2f(-0.23f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //20
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.23f, -0.4f); // bottom left
        glVertex2f(-0.22f, -0.28f); // center
        glVertex2f(-0.2f, -0.4f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //21
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.2f, -0.4f); // bottom left
        glVertex2f(-0.18f, -0.26f); // center
        glVertex2f(-0.16f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //22
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.16f, -0.40f); // bottom left
        glVertex2f(-0.16f, -0.28f); // center
        glVertex2f(-0.13f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //23
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.13f, -0.40f); // bottom left
        glVertex2f(-0.11f, -0.27f); // center
        glVertex2f(-0.07f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //24
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.07f, -0.40f); // bottom left
        glVertex2f(-0.07f, -0.29f); // center
        glVertex2f(-0.04f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //25
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(-0.04f, -0.40f); // bottom left
        glVertex2f(-0.03f, -0.32f); // center
        glVertex2f(0.0f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //26
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.0f, -0.40f); // bottom left
        glVertex2f(0.009f, -0.28f); // center
        glVertex2f(0.03f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //27
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.03f, -0.40f); // bottom left
        glVertex2f(0.03f, -0.29f); // center
        glVertex2f(0.06f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //28
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.06f, -0.40f); // bottom left
        glVertex2f(0.08f, -0.28f); // center
        glVertex2f(0.1f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //29
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.1f, -0.40f); // bottom left
        glVertex2f(0.12f, -0.30f); // center
        glVertex2f(0.13f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //30
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.13f, -0.40f); // bottom left
        glVertex2f(0.15f, -0.27f); // center
        glVertex2f(0.18f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //31
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.18f, -0.40f); // bottom left
        glVertex2f(0.17f, -0.28f); // center
        glVertex2f(0.23f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //32
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.23f, -0.40f); // bottom left
        glVertex2f(0.23f, -0.29f); // center
        glVertex2f(0.26f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //33
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.26f, -0.40f); // bottom left
        glVertex2f(0.27f, -0.27f); // center
        glVertex2f(0.3f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //34
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.3f, -0.40f); // bottom left
        glVertex2f(0.3f, -0.3f); // center
        glVertex2f(0.33f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //35
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.33f, -0.40f); // bottom left
        glVertex2f(0.34f, -0.27f); // center
        glVertex2f(0.36f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //36
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.36f, -0.40f); // bottom left
        glVertex2f(0.37f, -0.30f); // center
        glVertex2f(0.4f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //37
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.4f, -0.40f); // bottom left
        glVertex2f(0.4f, -0.27f); // center
        glVertex2f(0.43f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //38
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.43f, -0.40f); // bottom left
        glVertex2f(0.46f, -0.31f); // center
        glVertex2f(0.47f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //39
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.47f, -0.40f); // bottom left
        glVertex2f(0.50f, -0.29f); // center
        glVertex2f(0.52f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //40
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.52f, -0.40f); // bottom left
        glVertex2f(0.53f, -0.28f); // center
        glVertex2f(0.56f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //41
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.56f, -0.40f); // bottom left
        glVertex2f(0.56f, -0.31f); // center
        glVertex2f(0.6f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //42
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.6f, -0.40f); // bottom left
        glVertex2f(0.62f, -0.28f); // center
        glVertex2f(0.64f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //43
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.64f, -0.40f); // bottom left
        glVertex2f(0.64f, -0.29f); // center
        glVertex2f(0.68f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //44
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.68f, -0.40f); // bottom left
        glVertex2f(0.7f, -0.3f); // center
        glVertex2f(0.73f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //44
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.73f, -0.40f); // bottom left
        glVertex2f(0.74f, -0.27f); // center
        glVertex2f(0.77f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //45
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.77f, -0.40f); // bottom left
        glVertex2f(0.76f, -0.30f); // center
        glVertex2f(0.8f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //46
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.8f, -0.40f); // bottom left
        glVertex2f(0.82f, -0.27f); // center
        glVertex2f(0.83f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //47
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.83f, -0.40f); // bottom left
        glVertex2f(0.85f, -0.31f); // center
        glVertex2f(0.88f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //48
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.88f, -0.40f); // bottom left
        glVertex2f(0.87f, -0.27f); // center
        glVertex2f(0.92f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //49
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.92f, -0.40f); // bottom left
        glVertex2f(0.93f, -0.30f); // center
        glVertex2f(0.98f, -0.40f); // bottom right
    glEnd();

    glBegin(GL_POLYGON); //50
    glColor3ub(51,121,0);
    //glColor3ub(181,126,77);
        glVertex2f(0.98f, -0.40f); // bottom left
        glVertex2f(1.0f, -0.28f); // center
        glVertex2f(1.0f, -0.40f); // bottom right
        glEnd();
}

void display(){
    glLoadIdentity();
    glClearColor(0.28, 0.75, 0.9, 1.0);
    glColor3ub(173, 216, 230);

    glClear(GL_COLOR_BUFFER_BIT);
    displayPoin();

    ground();
    coup1();
    coup2();
    fence();
    rumput();


    chickenObject();
    rockObject();
    clouds();

    glPushMatrix();
    glPopMatrix();
    glutSwapBuffers();

}

void GameOver(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1, 0, 0);
    glRasterPos3f(-1.25, 1.5, 0);
    std::string text = "GAME OVER "; // GAME OVER
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glRasterPos3f(-1.15, 0.25, 0);
    std::string text1 = "Score: " + std::to_string(score);
    for (char c : text1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glRasterPos3f(-1.3, 0, 0);
    std::string text3 = "Press r to restart";


    for (char c : text3) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }


    glutSwapBuffers();
}

void WelcomeDisplay(){
    rockSpeed = 0;
    glLoadIdentity();
    glClearColor(0.28, 0.75, 0.9, 1.0);
    glColor3ub(173, 216, 230);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 0, 0);

    glRasterPos3f(-0.10, 0.5, 0);
    std::string text = "Chick-A-Roo"; // GAME NAME
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glRasterPos3f(-0.175, 0, 0);
    std::string text2 = "Press SPACEBAR to start";
    for (char c : text2) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }

    glutSwapBuffers();
}


int main(int argc, char **argv){
    glutInit(&argc, argv);  // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Chicken Game");

    glutTimerFunc(0, update, 0);

    glutKeyboardFunc(keyboard); //keyboard input

    glutDisplayFunc(WelcomeDisplay);//display
   	glutTimerFunc(0, update, 0); // memanggil fungsi timer, BUAT GERAK

    glutKeyboardFunc(keyboard);

    //glutSpecialFunc(specialKeyInput);

    glutReshapeFunc([](int width, int height) {
        glutReshapeWindow(window_width, window_height);
    });
    glutMainLoop();
    return 0;
}
