#include <GL/glut.h>
#include <windows.h>
#include <math.h>

int window_width = 1500;
int window_height = 800;


void chickenObject(int x, int y, int radius){
    int num_segments = 100;
    int cx = 0, cy = 0;
    glBegin(GL_LINE_LOOP);
    float r = 0.1;
    for (int ii = 0; ii < num_segments; ii++)   {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex2f(x + cx, y + cy);//output vertex
    }
    glEnd();
}

void lines (){
    // X axis
    glColor3f(0.0f, 1.0f, 0.0f);


    //Y axis


}


void ground (){
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-1.0f, -1.0f); // bottom left
        glVertex2f(-1.0f, -0.5f); // top left
        glVertex2f(1.0f, -0.5f); // top right
        glVertex2f(1.0f, -1.0f); // bottom right
    glEnd();

}

void keyInput(){


}

void display(){
    glClearColor(0.0f, 6.0f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ground();
    chickenObject(100, 100, 50);

    glutSwapBuffers();

}


int main(int argc, char **argv){
    glutInit(&argc, argv);  // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Chicken Game");

    glutDisplayFunc(display); //display
    //glutReshapeFunc(); //reshape function
    //glutKeyboardFunc(keyInput);
    //glutSpecialFunc(specialKeyInput);



    glutMainLoop();
    return 0;
}
