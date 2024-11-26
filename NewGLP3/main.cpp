#include <windows.h>
#include <GL/glut.h>
#include <cmath>

float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 5.0f; // Camera position
float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;                   // Rotation angles
float zoom = 1.0f;                                    // Zoom level

void drawPartialTorus(float innerRadius, float outerRadiusX, float outerRadiusY, int sides, int rings, float startAngle, float sweepAngle) {
    float ringDelta = 2.0f * M_PI / rings;       // Angle between each ring
    float sideDelta = 2.0f * M_PI / sides;      // Angle between each side
    float endAngle = startAngle + sweepAngle; // Calculate the end angle

    for (float ringAngle = startAngle; ringAngle < endAngle; ringAngle += ringDelta) {
        glBegin(GL_QUAD_STRIP);
        for (int side = 0; side <= sides; ++side) {
            float sideAngle = side * sideDelta;

            // Compute vertices for the current ring
            float x0 = (outerRadiusX + innerRadius * cos(sideAngle)) * cos(ringAngle);
            float y0 = (outerRadiusY + innerRadius * cos(sideAngle)) * sin(ringAngle);
            float z0 = innerRadius * sin(sideAngle);

            // Compute vertices for the next ring
            float x1 = (outerRadiusX + innerRadius * cos(sideAngle)) * cos(ringAngle + ringDelta);
            float y1 = (outerRadiusY + innerRadius * cos(sideAngle)) * sin(ringAngle + ringDelta);
            float z1 = innerRadius * sin(sideAngle);

            // Define two points of the quad strip
            glVertex3f(x0, y0, z0);
            glVertex3f(x1, y1, z1);
        }
        glEnd();
    }
}

void drawSector(float cX, float cY, float cZ, float rX, float rY, float Cbegin, float rad, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(cX, cY, cZ);
    for (int i = 0; i <= segments; ++i) {
        float angle = Cbegin + (rad * i / segments);
        float x = cX + rX * cos(angle);
        float y = cY + rY * sin(angle);
        glVertex3f(x, y, cZ);
    }
    glEnd();
}

void drawWings() {
    glutSolidTorus(0.08f, 0.5f, 30, 30);
    GLUquadric* quad = gluNewQuadric();
    glPushMatrix();
    {
        glTranslatef(0.0f, 0.0f, 0.08f);
        drawSector(0.0f, 0.5f, 0.0f, 1.9f, 1.0f, -M_PI/2, M_PI/2, 50);
        glTranslatef(0.0f, 0.0f, 0.005f);
        gluDisk(quad, 0.0, 0.5f, 30, 30);
        glTranslatef(0.0f, 0.0f, -0.165f);
        drawSector(0.0f, 0.5f, 0.0f, 1.9f, 1.0f, -M_PI/2, M_PI/2, 50);
         glTranslatef(0.0f, 0.0f, -0.005f);
        gluDisk(quad, 0.0, 0.5f, 30, 30);
    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0.0f, 0.5f, 0.0f);
        drawPartialTorus(0.08f, 1.9f, 1.0f, 30, 100, -M_PI/2, M_PI/2-0.08f);
    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(0.0f, 0.5f, 0.0f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        gluCylinder(quad, 0.08f, 0.08f, 2.1f, 30, 30);
        glPushMatrix();
        {
            glTranslatef(0.0f, -0.21f, 1.5f);
            glPushMatrix();
            {
                gluCylinder(quad, 0.08f, 0.13f, 0.5f, 30, 30);
                glTranslatef(0.0f, 0.0f, 0.5f);
                glutSolidSphere(0.13f, 30, 30);
            }glPopMatrix();
            glTranslatef(0.0f, -0.23f, -0.1f);
            glPushMatrix();
            {
                gluCylinder(quad, 0.08f, 0.13f, 0.5f, 30, 30);
                glTranslatef(0.0f, 0.0f, 0.5f);
                glutSolidSphere(0.13f, 30, 30);
            }glPopMatrix();
            glTranslatef(0.0f, -0.23f, -0.2f);
            glPushMatrix();
            {
                gluCylinder(quad, 0.08f, 0.13f, 0.5f, 30, 30);
                glTranslatef(0.0f, 0.0f, 0.5f);
                glutSolidSphere(0.13f, 30, 30);
            }glPopMatrix();
            glTranslatef(0.0f, -0.18f, -0.4f);
            glPushMatrix();
            {
                glRotatef(5, 0.4f, 0.0f, 0.0f);
                gluCylinder(quad, 0.08f, 0.13f, 0.6f, 30, 30);
                glTranslatef(0.0f, 0.0f, 0.6f);
                glutSolidSphere(0.13f, 30, 30);
            }glPopMatrix();
            glTranslatef(0.0f, -0.15f, -0.8f);
            glPushMatrix();
            {
                glRotatef(5, 0.4f, 0.0f, 0.0f);
                gluCylinder(quad, 0.08f, 0.13f, 1.0f, 30, 30);
                glTranslatef(0.0f, 0.0f, 1.0f);
                glutSolidSphere(0.13f, 30, 30);
            }glPopMatrix();
        }glPopMatrix();
    }glPopMatrix();
}

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

void setupLighting() {
    GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat light_diffuse[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {10.0, 10.0, 10.0, 1.0};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void setupMaterial() {
    GLfloat mat_ambient[] = {0.1, 0.1, 0.1, 0.2};
    GLfloat mat_diffuse[] = {0.4, 0.4, 0.4, 0.2};
    GLfloat mat_specular[] = {0.7, 0.7, 0.7, 0.2};
    GLfloat mat_shininess[] = {50.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    setupLighting();
    //setupMaterial();
    // Adjust the camera
    glTranslatef(0.0f, 0.0f, -cameraZ); // Zoom
    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X-axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y-axis
    glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
    glPushMatrix();
    {
        glScalef(0.8f*zoom, zoom, 0.55f*zoom);
        drawSphereWithFlatBottom(1.2f, 20, 50, 0.7f);
    }glPopMatrix(); // Sphere with flat bottom starting at 80% height
    glPushMatrix();
    {
        glTranslatef(1.05f, 0.3f, 0.5f);
        glPushMatrix();
        {
            glRotatef(90, 1.0f, 0.0f, 0.0f);
            glRotatef(-90, 0.0f, 1.0f, 0.0f);
            glRotatef(70, 0.0f, 0.0f, 1.0f);
            drawWings();
        }glPopMatrix();
        glPushMatrix();
        {
            glTranslatef(0.0f, 0.0f, -0.4f);
            glRotatef(90, 1.0f, 0.0f , 0.0f);
            drawPartialTorus(0.1f, 0.4f, 0.4f, 30, 30, -3*M_PI/2, 2*M_PI/3);
        }
        glPopMatrix();
    }glPopMatrix();
    glPushMatrix();
    {
        glTranslatef(-1.05f, 0.3f, 0.5f);
        glPushMatrix();
        {
            glRotatef(90, 1.0f, 0.0f, 0.0f);
            glRotatef(-90, 0.0f, 1.0f, 0.0f);
            glRotatef(70, 0.0f, 0.0f, 1.0f);
            drawWings();
        }glPopMatrix();
        glPushMatrix();
        {
            glTranslatef(0.0f, 0.0f, -0.4f);
            glRotatef(90, 1.0f, 0.0f , 0.0f);
            drawPartialTorus(0.1f, 0.4f, 0.4f, 30, 30, -M_PI/6, 2*M_PI/3);
        }
        glPopMatrix();
    }glPopMatrix();
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


    glutMainLoop();
    return 0;
}
