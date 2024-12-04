#include <windows.h>
#include <GL/glut.h>
#include <cmath>

float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 5.0f; // Camera position
float angleH  = 0.0f;
int angleV = 0;               // Rotation angles
float zoom = 7.0f;                                    // Zoom level

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

void drawNeckWithStackedSpheres() {
    /*
    curved neck with spheres stacking each other
    */
    int numSpheres = 200;        // Number of spheres in the neck
    float baseRadius = 0.3f;    // Radius of the largest sphere at the base
    float tipRadius = 0.1f;     // Radius of the smallest sphere at the tip
    float neckLength = 1.5f;    // Total length of the neck
    float neckCurve = 0.7f;     // Degree of the curve

    glPushMatrix();
    {
        // Translate to the starting position of the neck
        glTranslatef(0.0f, 0.5f, 0.3f);

        for (int i = 0; i <= numSpheres; ++i) {
            float t = (float)i / numSpheres;   // Parametric value [0, 1]
            float angle = t * M_PI * neckCurve; // Curve angle for the sphere

            // Compute neck curve points
            float x = 0.0f;                     // Neck is centered in x
            float y = neckLength * t;           // Linear progression along the length
            float z = neckLength * sin(angle);  // Curve in the z direction

            // Compute radius for this sphere (linear tapering)
            float radius = baseRadius + t * (tipRadius - baseRadius);

            // Place the sphere
            glPushMatrix();
            {
                glTranslatef(x, y, z);
                glutSolidSphere(radius, 20, 20);
            }
            glPopMatrix();
        }

        // Draw the head at the end of the neck
        glTranslatef(0.0f, neckLength, neckLength * sin(M_PI * neckCurve));
        glutSolidSphere(tipRadius * 1.5f, 30, 30); // Goose's head
    }
    glPopMatrix();
}

//tail (lighting bug)
void drawTailWithTaperedTriangles() {
    int numTriangles = 2000;      // Number of stacked triangles to create the tail
    float baseWidth = 0.8f;     // Width of the base of the tail (widest point)
    float tipWidth = 0.2f;      // Width at the tip of the tail (smallest point)
    float baseThickness = 0.5f; // Thickness at the base of the tail
    float tipThickness = 0.05f; // Thickness at the tip of the tail
    float tailLength = 1.2f;    // Total length of the tail

    glPushMatrix();
    {
        // Position the tail at the back of the body
        glTranslatef(0.0f, -1.7f, 0.5f); // Adjust these values as needed for correct positioning
        glRotatef(-180.0f, 0.0f, 1.0f, 0.0f); // Rotate the tail slightly upwards
        glRotatef(30.0f, 1.0f, 0.0f, 0.0f);

        // Stack triangles with decreasing thickness along the length of the tail
        for (int i = 0; i < numTriangles; ++i) {
            float t = (float)i / numTriangles;  // Parametric value [0, 1] for progression
            float currentWidth = baseWidth + t * (tipWidth - baseWidth);  // Linearly interpolate width
            float currentHeight = tailLength * (1 - t);  // Linearly decrease height along the length
            float currentThickness = baseThickness + t * (tipThickness - baseThickness);  // Linearly decrease thickness

            // Draw each thick triangle as a prism
            glPushMatrix();
            {
                glTranslatef(0.0f, currentHeight, 0.0f);  // Move each triangle upwards

                glBegin(GL_QUADS);

                // Front face of the triangle
                glVertex3f(0.0f, 0.3f * t, currentThickness / 2.0f);               // Top point (front)
                glVertex3f(-currentWidth / 2.0f, 0.0f, currentThickness / 2.0f);    // Bottom-left point (front)
                glVertex3f(currentWidth / 2.0f, 0.0f, currentThickness / 2.0f);     // Bottom-right point (front)

                // Back face of the triangle
                glVertex3f(0.0f, 0.3f * t, -currentThickness / 2.0f);              // Top point (back)
                glVertex3f(-currentWidth / 2.0f, 0.0f, -currentThickness / 2.0f);   // Bottom-left point (back)
                glVertex3f(currentWidth / 2.0f, 0.0f, -currentThickness / 2.0f);    // Bottom-right point (back)

                glEnd();

                // Draw connecting edges between the front and back faces to create thickness
                glBegin(GL_QUADS);

                // Left side connecting quad
                glVertex3f(-currentWidth / 2.0f, 0.0f, currentThickness / 2.0f);    // Bottom-left (front)
                glVertex3f(-currentWidth / 2.0f, 0.0f, -currentThickness / 2.0f);   // Bottom-left (back)
                glVertex3f(0.0f, 0.3f * t, -currentThickness / 2.0f);               // Top (back)
                glVertex3f(0.0f, 0.3f * t, currentThickness / 2.0f);                // Top (front)

                // Right side connecting quad
                glVertex3f(currentWidth / 2.0f, 0.0f, currentThickness / 2.0f);     // Bottom-right (front)
                glVertex3f(currentWidth / 2.0f, 0.0f, -currentThickness / 2.0f);    // Bottom-right (back)
                glVertex3f(0.0f, 0.3f * t, -currentThickness / 2.0f);               // Top (back)
                glVertex3f(0.0f, 0.3f * t, currentThickness / 2.0f);                // Top (front)

                // Bottom side connecting quad
                glVertex3f(-currentWidth / 2.0f, 0.0f, currentThickness / 2.0f);    // Bottom-left (front)
                glVertex3f(-currentWidth / 2.0f, 0.0f, -currentThickness / 2.0f);   // Bottom-left (back)
                glVertex3f(currentWidth / 2.0f, 0.0f, -currentThickness / 2.0f);    // Bottom-right (back)
                glVertex3f(currentWidth / 2.0f, 0.0f, currentThickness / 2.0f);     // Bottom-right (front)

                glEnd();
            }
            glPopMatrix();
        }
    }
    glPopMatrix();
}

//partially fixed lighting but not satisfied
/*
void drawTailWithTaperedTriangles() {
    int numTriangles = 20;      // Number of stacked triangles to create the tail
    float baseWidth = 0.8f;     // Width of the base of the tail (widest point)
    float tipWidth = 0.2f;      // Width at the tip of the tail (smallest point)
    float baseThickness = 0.2f; // Thickness at the base of the tail
    float tipThickness = 0.05f; // Thickness at the tip of the tail
    float tailLength = 1.2f;    // Total length of the tail

    glPushMatrix();
    {
        // Position the tail at the back of the body
        glTranslatef(0.0f, -1.0f, -0.8f); // Adjust these values as needed for correct positioning
        glRotatef(-30.0f, 1.0f, 0.0f, 0.0f); // Rotate the tail slightly upwards

        // Stack triangles with decreasing thickness along the length of the tail
        for (int i = 0; i < numTriangles; ++i) {
            float t = (float)i / numTriangles;  // Parametric value [0, 1] for progression
            float currentWidth = baseWidth + t * (tipWidth - baseWidth);  // Linearly interpolate width
            float currentHeight = tailLength * (1 - t);  // Linearly decrease height along the length
            float currentThickness = baseThickness + t * (tipThickness - baseThickness);  // Linearly decrease thickness

            // Draw each thick triangle as a prism
            glPushMatrix();
            {
                glTranslatef(0.0f, currentHeight, 0.0f);  // Move each triangle upwards

                glBegin(GL_QUADS);

                // Front face of the triangle
                glNormal3f(0.0f, 0.0f, 1.0f); // Normal pointing towards the viewer
                glVertex3f(0.0f, 0.3f * t, currentThickness / 2.0f);               // Top point (front)
                glVertex3f(-currentWidth / 2.0f, 0.0f, currentThickness / 2.0f);    // Bottom-left point (front)
                glVertex3f(currentWidth / 2.0f, 0.0f, currentThickness / 2.0f);     // Bottom-right point (front)

                // Back face of the triangle
                glNormal3f(0.0f, 0.0f, -1.0f); // Normal pointing away from the viewer
                glVertex3f(0.0f, 0.3f * t, -currentThickness / 2.0f);              // Top point (back)
                glVertex3f(-currentWidth / 2.0f, 0.0f, -currentThickness / 2.0f);   // Bottom-left point (back)
                glVertex3f(currentWidth / 2.0f, 0.0f, -currentThickness / 2.0f);    // Bottom-right point (back)

                glEnd();

                // Draw connecting edges between the front and back faces to create thickness
                glBegin(GL_QUADS);

                // Left side connecting quad
                glNormal3f(-1.0f, 0.0f, 0.0f); // Normal pointing left
                glVertex3f(-currentWidth / 2.0f, 0.0f, currentThickness / 2.0f);    // Bottom-left (front)
                glVertex3f(-currentWidth / 2.0f, 0.0f, -currentThickness / 2.0f);   // Bottom-left (back)
                glVertex3f(0.0f, 0.3f * t, -currentThickness / 2.0f);               // Top (back)
                glVertex3f(0.0f, 0.3f * t, currentThickness / 2.0f);                // Top (front)

                // Right side connecting quad
                glNormal3f(1.0f, 0.0f, 0.0f); // Normal pointing right
                glVertex3f(currentWidth / 2.0f, 0.0f, currentThickness / 2.0f);     // Bottom-right (front)
                glVertex3f(currentWidth / 2.0f, 0.0f, -currentThickness / 2.0f);    // Bottom-right (back)
                glVertex3f(0.0f, 0.3f * t, -currentThickness / 2.0f);               // Top (back)
                glVertex3f(0.0f, 0.3f * t, currentThickness / 2.0f);                // Top (front)

                // Bottom side connecting quad
                glNormal3f(0.0f, -1.0f, 0.0f); // Normal pointing downward
                glVertex3f(-currentWidth / 2.0f, 0.0f, currentThickness / 2.0f);    // Bottom-left (front)
                glVertex3f(-currentWidth / 2.0f, 0.0f, -currentThickness / 2.0f);   // Bottom-left (back)
                glVertex3f(currentWidth / 2.0f, 0.0f, -currentThickness / 2.0f);    // Bottom-right (back)
                glVertex3f(currentWidth / 2.0f, 0.0f, currentThickness / 2.0f);     // Bottom-right (front)

                glEnd();
            }
            glPopMatrix();
        }
    }
    glPopMatrix();
}
*/

void drawSphereWithFlatBottom(float radiusX, float radiusY, float radiusZ, int slices, int stacks, float cutoff) {
    float cutoffY = radiusY * cos(cutoff * M_PI); // Calculate cut-off height in sphere's coordinate

    // Draw the main part of the sphere
    for (int i = 0; i <= stacks; ++i) {
        float theta1 = i * M_PI / stacks;
        float theta2 = (i + 1) * M_PI / stacks;

        // Calculate y for the current and next stack
        float y1 = radiusY * cos(theta1);
        float y2 = radiusY * cos(theta2);

        // Skip stacks that go below the cutoff
        if (y1 < cutoffY) break;

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float phi = j * 2 * M_PI / slices;

            // Vertex 1
            float x1 = radiusX * sin(theta1) * cos(phi);
            float z1 = radiusZ * sin(theta1) * sin(phi);
            glNormal3f(x1, y1, z1); // Normal for lighting
            glVertex3f(x1, y1, z1);

            // Vertex 2
            float x2 = radiusX * sin(theta2) * cos(phi);
            float z2 = radiusZ * sin(theta2) * sin(phi);
            glNormal3f(x2, y2, z2); // Normal for lighting
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }

    // Draw the bottom cap
    glBegin(GL_TRIANGLE_FAN);
    // Center of the disc
    glNormal3f(0.0f, -1.0f, 0.0f); // Normal pointing downward
    glVertex3f(0.0f, cutoffY, 0.0f);
    for (int j = 0; j <= slices; ++j) {
        float phi = j * 2 * M_PI / slices;
        float x = 1.45*radiusX * sin(M_PI - cutoff) * cos(phi);
        float z = 1.45*radiusZ * sin(M_PI - cutoff) * sin(phi);
        glNormal3f(x, cutoffY, z); // Normal for the edge
        glVertex3f(x, cutoffY, z);
    }
    glEnd();
}

void setupLighting() {
    GLfloat light_ambient[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[] = {0.7, 0.7, 0.7, 1.0};
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
    GLfloat mat_ambient[] = {0.4, 0.4, 0.4, 0.2};
    GLfloat mat_diffuse[] = {0.7, 0.7, 0.7, 0.2};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 0.2};
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
    setupMaterial();
    // Adjust the camera
    gluLookAt(zoom*sin(angleH), 4.0, zoom*cos(angleH),
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    glRotatef(angleV, 0.0f, 1.0f, 0.0f);
    glPushMatrix();
    {
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        drawSphereWithFlatBottom(1.1f, 0.6f, 0.9f, 36, 36, 0.67f);
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

    glPushMatrix();
    {
        drawNeckWithStackedSpheres();
    }
    glPopMatrix();

    glPushMatrix();
    {
        drawTailWithTaperedTriangles();
    }
    glPopMatrix();

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
    }
    glutPostRedisplay();
}

// Keyboard input for special keys (arrow keys)
void handleSpecialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        if (angleV >= -75) {angleV -= 3;}
        break; // Rotate up
    case GLUT_KEY_DOWN:
        if (angleV <= 75) {angleV += 3;}
        break; // Rotate down
    case GLUT_KEY_LEFT:
        angleH -= 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        angleH += 0.1f;
        break;
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
