#include <GL/gl.h>
#include <GL/glut.h>

#include <windows.h>
#include <math.h>

#define PI 3.1416;

int window_width = 1500;
int window_height = 800;


void chickenObject(){
//    int num_segments = 100;
//    int cx = 0, cy = 0;
//    glBegin(GL_LINE_LOOP);
//    float r = 0.1;
//    for (int ii = 0; ii < num_segments; ii++)   {
//        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
//        float x = r * cosf(theta);//calculate the x component
//        float y = r * sinf(theta);//calculate the y component
//        glVertex2f(x + cx, y + cy);//output vertex
//    }
//    glEnd();


    glScalef(0.3f, 0.3f, 0.0f);
    glTranslatef(0.5f,-0.87f,0);

        float x, y;
	 int i;
	 GLfloat radius;
	 int triangleAmount = 100;
	 GLfloat twicePi = 2.0 * PI;



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

    glBegin(GL_LINES); //Kaki kiri
    glColor3ub(222,105,0);
        glVertex2f(-0.48f, -0.661f); // top left
        glVertex2f(-0.518f, -0.739f); // bottom left
        glVertex2f(-0.578f, -0.778f); // top right
        glVertex2f(-0.480f, -0.781f); // top right
    glEnd();

    glBegin(GL_LINES); //Kaki Kanan
    glColor3ub(222,105,0);
        glVertex2f(-0.301f, -0.655f); // top left
        glVertex2f(-0.221f, -0.755f); // bottom left
        glVertex2f(-0.246f, -0.8f); // top right
        glVertex2f(-0.157f, -0.768f); // top right
    glEnd();

    glBegin(GL_POLYGON); //PARUH
    glColor3ub(242,124,0);
        glVertex2f(-0.126f, -0.384f); // top right
        glVertex2f(-0.129f, -0.359f); // top left
        glVertex2f(0.1f, -0.35f); // bottom left
        glVertex2f(-0.051f, -0.369f); // top right
        glVertex2f(-0.126f, -0.384f); // top right
        glVertex2f(-0.06f, -0.399f); // top right
        glVertex2f(-0.098f, -0.430f); // top right
        glVertex2f(-0.126f, -0.420f); // top right
        glVertex2f(-0.126f, -0.384f); // top right

    glEnd();

    glBegin(GL_LINES); // MATA
    glColor3ub(28,28,28);
        glVertex2f(-0.240f, -0.338f); // top left
        glVertex2f(-0.2f, -0.3); // bottom left
        glVertex2f(-0.160f, -0.339f); // top right
        glEnd();


}





int xTranslation;


void timer(int value) {
   glutPostRedisplay();

   xTranslation += 0.005; // perubahan nilai pada sumbu x
   glutTimerFunc(1000/60, timer, 0);
}


void clouds(){
	 float x, y;
	 int i;
	 GLfloat radius;
	 int triangleAmount = 100;
	 GLfloat twicePi = 2.0 * PI;


     glTranslatef(0.5f,3.0f,0);
	 glBegin(GL_TRIANGLE_FAN);//awan1.1
        glColor3ub(255,255,255);
        x=-0.50;
        y=-0.20;
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
        y=0.22;
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
        y=-0.20;
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
        y=0.08;
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
        y=-0.20;
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
        y=-0.22;
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
        y=0.10;
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
        y=-0.25;
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
        y=-0.10;
        radius = 0.3;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();


    //matahari
    glBegin(GL_TRIANGLE_FAN);//matahari
        glColor3ub(255,255,0);
        x=-1.8;
        y=0.35;
        radius = 0.20;
        twicePi = 2.0 * PI;
        glVertex2f(x, y); // center of circle
        for(i = 0; i <= triangleAmount;i++) {
            glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)),y + (radius * sin(i * twicePi /triangleAmount)));
        }
    glEnd();


}



void lines (){
    // X axis
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINE);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(-1.0, 0.0f);
    glEnd;


    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(0.0f, -1.0f);
    glEnd;


    //Y axis

}


void ground (){
    glBegin(GL_QUADS);
    glColor3ub(101,206,25);
        glVertex2f(-1.0f, -1.0f); // bottom left
        glVertex2f(-1.0f, -0.5f); // top left
        glVertex2f(1.0f, -0.5f); // top right
        glVertex2f(1.0f, -1.0f); // bottom right
    glEnd();

}

/*
float rockPosX = 0.0f;
float rockSpeed = 0.01f;

void updateRockPosition() {
    // check if the rock has gone off the screen
    if (rockPosX < -1.0f) {
        rockPosX = 1.0f; // reset the position to the right edge of the screen
    } else {
        rockPosX -= rockSpeed; // move the rock to the left
    }
}
*/


void rockObject(){ // rock tinggal benerin titik lokasi (translasi)
    glLoadIdentity();
    glScalef(0.3f, 0.3f, 0.0f);
    glTranslatef(0.5f,-0.87f,0);
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
}

void keyInput(){

}

void display(){
    glLoadIdentity(); // harus pake ini biar ga scaling terus menerus
    glClearColor(0.28, 0.75, 0.9, 1.0);
    glColor3ub(173, 216, 230);

    glClear(GL_COLOR_BUFFER_BIT);
    lines(); //didn't work or I cannot see the lines
    ground();
    chickenObject();
    rockObject();
    //tes buat awan gerak
    glPushMatrix();
    glTranslatef(xTranslation, 0, 0); // tambahkan transalasi pada sumbu x
    clouds();
    glPopMatrix();



    glutSwapBuffers();

}
void resize(){
    glutReshapeWindow(1500, 800);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);  // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Chicken Game");

    glutDisplayFunc(display);//display
   glutTimerFunc(0, timer, 0); // memanggil fungsi timer, BUAT GERAK

    //glutReshapeWindow(window_width, window_height);
    //glutReshapeFunc(resize); //reshape function
    //glutKeyboardFunc(keyInput);
    //glutSpecialFunc(specialKeyInput);

    glutMainLoop();
    return 0;
}
