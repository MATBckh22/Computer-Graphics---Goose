#include <windows.h>
#include <GL/glut.h>
#include <cmath>

float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 5.0f; // Camera position
float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;                   // Rotation angles
float zoom = 1.0f;                                    // Zoom level


void drawSphereWithFlatBottom(float radius, int stacks, int slices, float cutoff) {
    float cutoffZ = radius * cos(cutoff * M_PI); // Calculate cut-off height in sphere's coordinate

    for (int i = 0; i <= stacks; ++i) {
        float theta1 = i * M_PI / stacks;
        float theta2 = (i + 1) * M_PI / stacks;

        // Calculate z for the current and next stack
        float z1 = radius * cos(theta1);
        float z2 = radius * cos(theta2);

        // Skip stacks that go below the cutoff
        if (z1 < cutoffZ) break;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float phi = j * 2 * M_PI / slices;

            // Vertex 1
            float x1 = radius * sin(theta1) * cos(phi);
            float y1 = radius * sin(theta1) * sin(phi);
            glNormal3f(x1, y1, z1); // Normal for lighting
            glVertex3f(x1, y1, z1);

            // Vertex 2
            float x2 = radius * sin(theta2) * cos(phi);
            float y2 = radius * sin(theta2) * sin(phi);
            glNormal3f(x2, y2, z2); // Normal for lighting
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }

    // Draw a flat cap at the cutoff level
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, -1); // Normal pointing downward
    glVertex3f(0.0f, 0.0f, cutoffZ); // Center of the cap
    for (int j = 0; j <= slices; ++j) {
        float phi = j * 2 * M_PI / slices;
        float x = radius * sin(cutoff * M_PI) * cos(phi);
        float y = radius * sin(cutoff * M_PI) * sin(phi);
        glVertex3f(x, y, cutoffZ);
    }
    glEnd();
}

void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPos[] = {0.0f, 5.0f, 5.0f, 1.0f};
    GLfloat lightAmb[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat lightDiff[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat lightSpec[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);

    GLfloat matAmb[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat matDiff[] = {0.5f, 0.5f, 1.0f, 1.0f};
    GLfloat matSpec[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat matShininess[] = {50.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Adjust the camera
    glTranslatef(0.0f, 0.0f, -cameraZ); // Zoom
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X-axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
    glScalef(0.8f*zoom, zoom, 0.55f*zoom);

    drawSphereWithFlatBottom(1.0f, 20, 50, 0.7f); // Sphere with flat bottom starting at 80% height

    glutSwapBuffers();
}

void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': cameraY += 0.1f; break; // Move up
    case 's': cameraY -= 0.1f; break; // Move down
    case 'a': cameraX -= 0.1f; break; // Move left
    case 'd': cameraX += 0.1f; break; // Move right
    case '+': zoom += 0.1f; break;    // Zoom in
    case '-': zoom -= 0.1f; break;
    case 'z': angleZ += 5.0f; break;
    case 'x': angleZ -= 5.0f; break;   // Zoom out
    }
    glutPostRedisplay();
}

// Keyboard input for special keys (arrow keys)
void handleSpecialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:    angleX -= 5.0f; break; // Rotate up
    case GLUT_KEY_DOWN:  angleX += 5.0f; break; // Rotate down
    case GLUT_KEY_LEFT:  angleY -= 5.0f; break; // Rotate left
    case GLUT_KEY_RIGHT: angleY += 5.0f; break; // Rotate right
    }
    glutPostRedisplay();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Sphere with Depth");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glutKeyboardFunc(handleKeyboard);    // Register keyboard input function
    glutSpecialFunc(handleSpecialKeys);  // Register special keys function
    initLighting();

    glutMainLoop();
    return 0;
}
