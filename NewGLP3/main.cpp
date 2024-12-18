#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "D:/Downloads/stb_image.h"

float angleH  = 0.0f;
float height = 0.0f;               // Rotation angles
float height1 = 2.0f;
float height2 = 2.0f;
float zoom = 7.0f;                                    // Zoom level
int open = 1;
bool moving = true;
bool moving2 = true;
int maxAngle = 83;
float placed = 0.53f;

float wireLength = 0.0f;      // Current length of the wire
const float maxWireLength = 4.0f; // Maximum wire length
bool wireAnimating = false;   // Flag to indicate wire animation
float cubePosition = -5.2f;  // Position of the cube along the wire
bool charging = false;

// Brightness control variables
float lightBrightness = 0.3f; // Initial brightness (dim)
const float MAX_BRIGHTNESS = 0.8f;
const float MIN_BRIGHTNESS = 0.0f;

bool isFadingIn = false;   // Indicates if the light is fading in
bool isFadingOut = false;  // Indicates if the light is fading out

// Light state variable
bool lightOn = false; // Light is initially on

GLuint texture, texture2, groundTexture;
GLuint loadTexture(const char* filename) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
    if (!data) {
        printf("Failed to load image: %s\n", filename);
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                 channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Repeat horizontally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Repeat vertically

    stbi_image_free(data);  // Free image data after creating texture
    return textureID;
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    stbi_set_flip_vertically_on_load(true);
    /*
    Remember to change the document name path into your version...
    */
    texture = loadTexture("D:/Downloads/UI.jpg");
    texture2 = loadTexture("D:/Downloads/PhoneUI.jpg");
    groundTexture = loadTexture("D:/Downloads/wooden floor.jpg");
}

int defaultWing(int openValue) {
    if (openValue == 0) {return 0;}
    else return maxAngle;
}

int wingAngle = defaultWing(open);

void drawTablet() {
    glPushMatrix();
    {
        glBegin(GL_QUADS);
        {
            glColor3f(0.1f, 0.1f, 0.1f);
            glVertex3f(-0.6f, 0.4f, 0.01f);
            glVertex3f(-0.6f, -0.4f, 0.01f);
            glVertex3f(0.6f, -0.4f, 0.01f);
            glVertex3f(0.6f, 0.4f, 0.01f);

            glColor3f(0.9f, 0.9f, 0.9f);
            glVertex3f(-0.6f, 0.4f, -0.01f);
            glVertex3f(-0.6f, -0.4f, -0.01f);
            glVertex3f(-0.6f, -0.4f, 0.01f);
            glVertex3f(-0.6f, 0.4f, 0.01f);

            glVertex3f(0.6f, 0.4f, -0.01f);
            glVertex3f(0.6f, -0.4f, -0.01f);
            glVertex3f(0.6f, -0.4f, 0.01f);
            glVertex3f(0.6f, 0.4f, 0.01f);

            glVertex3f(0.6f, 0.4f, -0.01f);
            glVertex3f(-0.6f, 0.4f, -0.01f);
            glVertex3f(-0.6f, 0.4f, 0.01f);
            glVertex3f(0.6f, 0.4f, 0.01f);

            glVertex3f(0.6f, -0.4f, -0.01f);
            glVertex3f(-0.6f, -0.4f, -0.01f);
            glVertex3f(-0.6f, -0.4f, 0.01f);
            glVertex3f(0.6f, -0.4f, 0.01f);

            glColor3f(0.9f, 0.95f, 1.0f);
            glVertex3f(-0.6f, 0.4f, -0.01f);
            glColor3f(0.7f, 0.8f, 1.0f);
            glVertex3f(-0.6f, -0.4f, -0.01f);
            glColor3f(0.9f, 0.95f, 1.0f);
            glVertex3f(0.6f, -0.4f, -0.01f);
            glColor3f(0.7f, 0.8f, 1.0f);
            glVertex3f(0.6f, 0.4f, -0.01f);
        }
        glEnd();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glBegin(GL_QUADS);
        {
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.55f, -0.35f, 0.011f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(0.55f, -0.35f, 0.011f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(0.55f, 0.35f, 0.011f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.55f, 0.35f, 0.011f);
        }glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

void drawPhone() {
    glPushMatrix();
    {
        glBegin(GL_QUADS);
        {
            glColor3f(0.1f, 0.1f, 0.1f);
            glVertex3f(-0.2f, 0.4f, 0.01f);
            glVertex3f(-0.2f, -0.4f, 0.01f);
            glVertex3f(0.2f, -0.4f, 0.01f);
            glVertex3f(0.2f, 0.4f, 0.01f);

            glColor3f(0.9f, 0.9f, 0.9f);
            glVertex3f(-0.2f, 0.4f, -0.01f);
            glVertex3f(-0.2f, -0.4f, -0.01f);
            glVertex3f(-0.2f, -0.4f, 0.01f);
            glVertex3f(-0.2f, 0.4f, 0.01f);

            glVertex3f(0.2f, 0.4f, -0.01f);
            glVertex3f(0.2f, -0.4f, -0.01f);
            glVertex3f(0.2f, -0.4f, 0.01f);
            glVertex3f(0.2f, 0.4f, 0.01f);

            glVertex3f(0.2f, 0.4f, -0.01f);
            glVertex3f(-0.2f, 0.4f, -0.01f);
            glVertex3f(-0.2f, 0.4f, 0.01f);
            glVertex3f(0.2f, 0.4f, 0.01f);

            glVertex3f(0.2f, -0.4f, -0.01f);
            glVertex3f(-0.2f, -0.4f, -0.01f);
            glVertex3f(-0.2f, -0.4f, 0.01f);
            glVertex3f(0.2f, -0.4f, 0.01f);

            glColor3f(1.0f, 0.95f, 0.95f);
            glVertex3f(-0.2f, 0.4f, -0.01f);
            glColor3f(1.0f, 0.8f, 0.7f);
            glVertex3f(-0.2f, -0.4f, -0.01f);
            glColor3f(1.0f, 0.95f, 0.95f);
            glVertex3f(0.2f, -0.4f, -0.01f);
            glColor3f(1.0f, 0.8f, 0.7f);
            glVertex3f(0.2f, 0.4f, -0.01f);
        }
        glEnd();
        glEnable(GL_TEXTURE_2D);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBegin(GL_QUADS);
        {
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.18f, -0.38f, 0.011f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(0.18f, -0.38f, 0.011f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(0.18f, 0.38f, 0.011f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.18f, 0.38f, 0.011f);
        }glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    glPopMatrix();
}

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

            // compute normals (lighting)
            float nx = cos(sideAngle) * cos(ringAngle);
            float ny = cos(sideAngle) * sin(ringAngle);
            float nz = sin(sideAngle);

            // normalize the normal vector for proper lighting
            float length = sqrt(nx * nx + ny * ny + nz * nz);
            if (length != 0.0f) {
                nx /= length;
                ny /= length;
                nz /= length;
            }

            // Compute vertices for the next ring
            float x1 = (outerRadiusX + innerRadius * cos(sideAngle)) * cos(ringAngle + ringDelta);
            float y1 = (outerRadiusY + innerRadius * cos(sideAngle)) * sin(ringAngle + ringDelta);
            float z1 = innerRadius * sin(sideAngle);
            float nextRingAngle = ringAngle + ringDelta;

            // compute normals for the next ring
            float nxNext = cos(sideAngle) * cos(nextRingAngle);
            float nyNext = cos(sideAngle) * sin(nextRingAngle);
            float nzNext = sin(sideAngle);

            // normalize the normal vector
            float lengthNext = sqrt(nxNext * nxNext + nyNext * nyNext + nzNext * nzNext);
            if (lengthNext != 0.0f) {
                nxNext /= lengthNext;
                nyNext /= lengthNext;
                nzNext /= lengthNext;
            }

            // normalize and define two points of the quad strip
            glNormal3f(nx, ny, nz);
            glVertex3f(x0, y0, z0);

            glNormal3f(nxNext, nyNext, nzNext);
            glVertex3f(x1, y1, z1);
        }
        glEnd();
    }
}

void drawSector(float cX, float cY, float cZ, float rX, float rY, float Cbegin, float rad, int segments, bool isLeft) {

    GLfloat normalX = 0.0f;
    GLfloat normalY = 0.0f;
    GLfloat normalZ;
    if (isLeft){
        normalZ = 1.0f;
    }
    else{
        normalZ = -1.0f;
    }

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(cX, cY, cZ);
    for (int i = 0; i <= segments; ++i) {
        float angle = Cbegin + (rad * i / segments);
        float x = cX + rX * cos(angle);
        float y = cY + rY * sin(angle);
        glNormal3f(normalX, normalY, normalZ); // normal for each edge vertex
        glVertex3f(x, y, cZ);
    }
    glEnd();
}

void draw3DQuarterOval(float radiusX, float radiusY, float height, int segments) {
    float halfHeight = height / 2.0f;

    // Top face (1/4 oval)
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(-1.0f, 1.0f, 1.0f); // Normal for lighting
    glVertex3f(0.0f, halfHeight, 0.0f); // Center of the top face
    for (int i = 0; i <= segments / 4; ++i) { // 1/4 of the circle
        float angle = (M_PI / 2) * i / (segments / 4); // Quarter circle
        float x = radiusX * cos(angle);
        float z = radiusY * sin(angle);
        glVertex3f(x, halfHeight, z);
    }
    glEnd();

    // Bottom face (1/4 oval)
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(-1.0f, -1.0f, 1.0f); // Normal for lighting
    glVertex3f(0.0f, -halfHeight, 0.0f); // Center of the bottom face
    for (int i = 0; i <= segments / 4; ++i) { // 1/4 of the circle
        float angle = (M_PI / 2) * i / (segments / 4); // Quarter circle
        float x = radiusX * cos(angle);
        float z = radiusY * sin(angle);
        glVertex3f(x, -halfHeight, z);
    }
    glEnd();

    // Curved side faces (connect top and bottom 1/4 ovals)
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= segments / 4; ++i) { // 1/4 of the circle
        float angle = (M_PI / 2) * i / (segments / 4); // Quarter circle
        float x = radiusX * cos(angle);
        float z = radiusY * sin(angle);

        glNormal3f(x, 0.0f, z); // Normal for curved side
        glVertex3f(x, halfHeight, z);    // Top edge
        glVertex3f(x, -halfHeight, z);   // Bottom edge
    }
    glEnd();

    // Front face (vertical rectangle connecting top and bottom planes)
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f); // Normal pointing outward
    glVertex3f(radiusX, halfHeight, 0.0f); // Top-right corner
    glVertex3f(radiusX, -halfHeight, 0.0f); // Bottom-right corner
    glVertex3f(0.0f, -halfHeight, 0.0f); // Bottom-left corner
    glVertex3f(0.0f, halfHeight, 0.0f); // Top-left corner
    glEnd();

    // Back face (connect start of curve to top and bottom planes)
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, -1.0f); // Normal pointing backward
    glVertex3f(0.0f, halfHeight, 0.0f); // Top-left corner
    glVertex3f(0.0f, -halfHeight, 0.0f); // Bottom-left corner
    glVertex3f(0.0f, -halfHeight, radiusY); // Bottom-right corner (end of back face)
    glVertex3f(0.0f, halfHeight, radiusY); // Top-right corner (end of back face)
    glEnd();
}

void drawWings(bool isLeft) {
    glutSolidTorus(0.08f, 0.5f, 30, 30);
    GLUquadric* quad = gluNewQuadric();

    glPushMatrix();
    {
        glTranslatef(0.0f, 0.0f, 0.08f);
        drawSector(0.0f, 0.5f, 0.0f, 1.9f, 1.0f, -M_PI/2, M_PI/2, 50, isLeft);
        glTranslatef(0.0f, 0.0f, 0.005f);
        // right disk
        glPushMatrix();
        {
            glRotatef(180, 0.0, 1.0, 0.0);
            gluDisk(quad, 0.0, 0.5f, 30, 30);
        }
        glPopMatrix();
        glTranslatef(0.0f, 0.0f, -0.165f);
        drawSector(0.0f, 0.5f, 0.0f, 1.9f, 1.0f, -M_PI/2, M_PI/2, 50, isLeft);
        glTranslatef(0.0f, 0.0f, -0.005f);
        // left disk
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
            glRotatef(-90, 0.0, 1.0, 0.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            glTranslatef(2.1, 0.0, -0.11);
            draw3DQuarterOval(0.5f, 0.18f, 0.2f, 50);
        }
        glPopMatrix();
        glPushMatrix();
        {
            glTranslatef(0.0f, -0.21f, 1.5f);
            glPushMatrix();
            {
                gluCylinder(quad, 0.08f, 0.13f, 0.5f, 30, 30);
                glTranslatef(0.0f, 0.0f, 0.5f);
                glPushMatrix();
                {
                    glRotatef(-90, 0.0, 1.0, 0.0);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glTranslatef(-0.02, 0.0, -0.1);
                    draw3DQuarterOval(0.5f, 0.18f, 0.21f, 50);
                }
                glPopMatrix();
            }glPopMatrix();
            glTranslatef(0.0f, -0.23f, -0.1f);
            glPushMatrix();
            {
                gluCylinder(quad, 0.08f, 0.13f, 0.5f, 30, 30);
                glTranslatef(0.0f, 0.0f, 0.5f);
                glPushMatrix();
                {
                    glRotatef(-90, 0.0, 1.0, 0.0);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glTranslatef(-0.02, 0.0, -0.1);
                    draw3DQuarterOval(0.5f, 0.18f, 0.21f, 50);
                }
                glPopMatrix();
            }glPopMatrix();
            glTranslatef(0.0f, -0.23f, -0.2f);
            glPushMatrix();
            {
                gluCylinder(quad, 0.08f, 0.13f, 0.5f, 30, 30);
                glTranslatef(0.0f, 0.0f, 0.5f);
                glPushMatrix();
                {
                    glRotatef(-90, 0.0, 1.0, 0.0);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glTranslatef(-0.02, 0.0, -0.1);
                    draw3DQuarterOval(0.5f, 0.18f, 0.21f, 50);
                }
                glPopMatrix();
            }glPopMatrix();
            glTranslatef(0.0f, -0.18f, -0.4f);
            glPushMatrix();
            {
                glRotatef(5, 0.4f, 0.0f, 0.0f);
                gluCylinder(quad, 0.08f, 0.13f, 0.6f, 30, 30);
                glTranslatef(0.0f, 0.0f, 0.6f);
                glPushMatrix();
                {
                    glRotatef(-90, 0.0, 1.0, 0.0);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glTranslatef(-0.02, 0.0, -0.1);
                    draw3DQuarterOval(0.5f, 0.18f, 0.21f, 50);
                }
                glPopMatrix();
            }glPopMatrix();
            glTranslatef(0.0f, -0.15f, -0.8f);
            glPushMatrix();
            {
                glRotatef(5, 0.4f, 0.0f, 0.0f);
                gluCylinder(quad, 0.08f, 0.13f, 1.0f, 30, 30);
                glTranslatef(0.0f, 0.0f, 1.0f);
                glPushMatrix();
                {
                    glRotatef(-90, 0.0, 1.0, 0.0);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glTranslatef(-0.02, 0.0, -0.1);
                    draw3DQuarterOval(0.5f, 0.18f, 0.21f, 50);
                }
                glPopMatrix();
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
    float neckCurve = 0.5f;     // Degree of the curve

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

// tail
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

            // normal for vertex 1
            float nx1 = x1 / (radiusX * radiusX);
            float ny1 = y1 / (radiusY * radiusY);
            float nz1 = z1 / (radiusZ * radiusZ);

            // normalize normal vector
            float length1 = sqrt(nx1 * nx1 + ny1 * ny1 + nz1 * nz1);
            if (length1 != 0.0f) {
                nx1 /= length1;
                ny1 /= length1;
                nz1 /= length1;
            }

            glNormal3f(-nx1, -ny1, -nz1);
            glVertex3f(x1, y1, z1);

            // Vertex 2
            float x2 = radiusX * sin(theta2) * cos(phi);
            float z2 = radiusZ * sin(theta2) * sin(phi);

            // normal for vertex 2
            float nx2 = x2 / (radiusX * radiusX);
            float ny2 = y2 / (radiusY * radiusY);
            float nz2 = z2 / (radiusZ * radiusZ);

            // normalize normal vector
            float length2 = sqrt(nx2 * nx2 + ny2 * ny2 + nz2 * nz2);
            if (length2 != 0.0f) {
                nx2 /= length2;
                ny2 /= length2;
                nz2 /= length2;
            }

            glNormal3f(-nx2, -ny2, -nz2); // Set normal for lighting
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
        glNormal3f(0.0f, -1.0f, 0.0f); // Normal for the edge
        glVertex3f(x, cutoffY, z);
    }
    glEnd();
}

void drawGround() {
    float groundSize = 5.0f; // Size of the ground plane

    glEnable(GL_TEXTURE_2D); // Enable texturing
    glBindTexture(GL_TEXTURE_2D, groundTexture); // Bind the ground texture
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3f(1.0f, 1.0f, 1.0f); // Ensure the texture color is used

    glBegin(GL_QUADS);
    {
        // Define texture coordinates and vertices
        // Adjust the texture coordinates (e.g., multiply by a factor) to control tiling
        float tiling = 10.0f; // Number of times the texture repeats across the ground

        glNormal3f(0.0f, 0.0f, 1.0f);

        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-groundSize, -groundSize, -0.5f);

        glTexCoord2f(tiling, 0.0f);
        glVertex3f(-groundSize, groundSize, -0.5f);

        glTexCoord2f(tiling, tiling);
        glVertex3f(groundSize, groundSize, -0.5f);

        glTexCoord2f(0.0f, tiling);
        glVertex3f(groundSize, -groundSize, -0.5f);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D); // Disable texturing
}

void drawWalls() {
    // Enable lighting if not already enabled
    glEnable(GL_LIGHTING);

    // Set wall material so it reflects light well
    GLfloat wall_ambient[]  = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat wall_diffuse[]  = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat wall_specular[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat wall_shininess[] = {10.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, wall_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, wall_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, wall_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, wall_shininess);

    // Coordinates for walls
    float groundSize = 5.0f;  // same size as the ground
    float wallHeight = 3.0f;  // how high the walls go above the ground

    // Back wall: spanning x = -5 to x = 5 at y = 5
    // Normal points inward (towards negative Y)
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-groundSize,  groundSize, -0.5f);
    glVertex3f( groundSize,  groundSize, -0.5f);
    glVertex3f( groundSize,  groundSize, wallHeight);
    glVertex3f(-groundSize,  groundSize, wallHeight);
    glEnd();

    // Left wall: spanning y = -5 to y = 5 at x = -5
    // Normal points inward (towards positive X)
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-groundSize, -groundSize, -0.5f);
    glVertex3f(-groundSize,  groundSize, -0.5f);
    glVertex3f(-groundSize,  groundSize, wallHeight);
    glVertex3f(-groundSize, -groundSize, wallHeight);
    glEnd();

    // Right wall: spanning y = -5 to y = 5 at x = 5
    // Normal points inward (towards negative X)
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f( groundSize, -groundSize, -0.5f);
    glVertex3f( groundSize,  groundSize, -0.5f);
    glVertex3f( groundSize,  groundSize, wallHeight);
    glVertex3f( groundSize, -groundSize, wallHeight);
    glEnd();
}

void drawWire(float length) {
    GLUquadric* quad = gluNewQuadric();

    glPushMatrix();
    {
        glColor3f(0.7f, 0.7f, 0.7f); // Gray color for the wire
        glTranslatef(0.0f, -5.2f, -0.2f); // Start position of the wire near the tail
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Align the cylinder vertically
        gluCylinder(quad, 0.05f, 0.05f, length, 20, 20); // Dynamic length cylinder
    }
    glPopMatrix();

    glPushMatrix();
    {
        if (charging) glColor3f(0.0f, 0.8f, 0.0f); // green when charging
        else glColor3f(0.8f, 0.0f, 0.0f); // red when not in charge

        // Position the cube at the end of the wire
        glTranslatef(0.0f, cubePosition, -0.2f); // Move along the wire length
        glScalef(1.0f, 2.5f, 1.0f);
        glutSolidCube(0.15f); // Cube size 0.15
    }
    glPopMatrix();

    gluDeleteQuadric(quad);
}

void animateWire(int value) {
    if (wireAnimating && wireLength < maxWireLength) {
        wireLength += 0.05f; // Adjust speed of the wire animation
        cubePosition += 0.05f;
        glutPostRedisplay();
        glutTimerFunc(16, animateWire, 0); // Recur every ~16ms for 60 FPS
    } else {
        charging = true;
        wireAnimating = false; // Stop the animation when max length is reached
    }
}

void setupLighting() {
    if (lightOn) {
        // Set a low global ambient light for a softer overall lighting
        GLfloat global_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f}; // Very low ambient
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

        // Set up light properties based on current brightness
        GLfloat light_ambient[]  = {0.3f * lightBrightness, 0.25f * lightBrightness, 0.15f * lightBrightness, 1.0f}; // Warm ambient
        GLfloat light_diffuse[]  = {0.6f * lightBrightness, 0.5f * lightBrightness, 0.3f * lightBrightness, 1.0f}; // Warm diffuse
        GLfloat light_specular[] = {0.1f, 0.1f, 0.1f, 1.0f}; // Soft specular

        // Position the light at the object's location (assuming object is at origin)
        // light from below
        GLfloat light_position[] = {0.0f, 0.0f, -1.0f, 1.0f}; // Adjust Y and Z as needed

        // Attenuation factors for smoother light fall-off
        GLfloat light_constant_attenuation = 0.5f;
        GLfloat light_linear_attenuation = 0.05f;
        GLfloat light_quadratic_attenuation = 0.01f;

        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

        // Set attenuation
        glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, light_constant_attenuation);
        glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, light_linear_attenuation);
        glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, light_quadratic_attenuation);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    } else {
        // When light is off, set light0's ambient and diffuse to zero
        GLfloat light_ambient_off[]  = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat light_diffuse_off[]  = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat light_specular_off[] = {0.0f, 0.0f, 0.0f, 1.0f};

        glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_off);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse_off);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular_off);

        // Optionally, adjust global ambient if needed
        GLfloat global_ambient_off[] = {0.3f, 0.3f, 0.3f, 1.0f}; // Low ambient to render gray
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient_off);

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }
}

void setupMaterial() {
    if (lightOn) {
        // Set material properties with emission based on brightness
        GLfloat mat_ambient[]    = {0.4f, 0.35f, 0.3f, 1.0f}; // Slightly warmer ambient
        GLfloat mat_diffuse[]    = {0.7f, 0.65f, 0.6f, 1.0f}; // Slightly warmer diffuse
        GLfloat mat_specular[]   = {0.9f, 0.85f, 0.75f, 1.0f}; // Soft specular
        GLfloat mat_shininess[]  = {20.0f}; // Reduced shininess for softer highlights

        // Calculate emission color based on brightness (warm yellow)
        GLfloat mat_emission[]   = {0.3f * lightBrightness, 0.25f * lightBrightness, 0.1f * lightBrightness, 1.0f};

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    } else {
        // Set material to gray with 30% transparency
        GLfloat mat_ambient[]    = {0.8f, 0.8f, 0.8f, 0.9f}; // Gray ambient with alpha 0.7
        GLfloat mat_diffuse[]    = {0.8f, 0.8f, 0.8f, 0.9f}; // Gray diffuse with alpha 0.7
        GLfloat mat_specular[]   = {0.2f, 0.2f, 0.2f, 0.7f}; // Low specular with alpha 0.7
        GLfloat mat_shininess[]  = {10.0f}; // Low shininess for softer highlights

        // No emission when light is off
        GLfloat mat_emission[]   = {0.0f, 0.0f, 0.0f, 1.0f};

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
}

void setupAdditionalLights() {
    // Secondary light 1: Soft ambient light from above
    GLfloat light1_ambient[]  = {0.5f * lightBrightness, 0.45f * lightBrightness, 0.35f * lightBrightness, 1.0f}; // Warm ambient
    GLfloat light1_diffuse[]  = {0.6f * lightBrightness, 0.5f * lightBrightness, 0.3f * lightBrightness, 1.0f}; // Warm diffuse
    GLfloat light1_specular[] = {0.1f, 0.1f, 0.1f, 1.0f}; // Soft specular
    GLfloat light1_position[] = {0.0f, 0.0f, 1.0f, 1.0f}; // Above the scene

    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

    glEnable(GL_LIGHT1);

    // Secondary light 2: Soft ambient light from behind
    GLfloat light2_ambient[]  = {0.3f * lightBrightness, 0.25f * lightBrightness, 0.15f * lightBrightness, 1.0f}; // Warm ambient
    GLfloat light2_diffuse[]  = {0.6f * lightBrightness, 0.5f * lightBrightness, 0.3f * lightBrightness, 1.0f}; // Warm diffuse
    GLfloat light2_specular[] = {0.0f, 0.0f, 0.0f, 1.0f}; // Soft specular
    GLfloat light2_position[] = {0.0f, 0.0f, 0.2f, 1.0f}; // Behind the scene

    glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

    glEnable(GL_LIGHT2);
}

void setupFog() {
    GLfloat fogColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; // Soft gray fog
    glFogi(GL_FOG_MODE, GL_EXP2); // Exponential squared fog for a smooth density
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.05f); // Adjust density for desired softness
    glHint(GL_FOG_HINT, GL_DONT_CARE); // Let OpenGL choose the fog quality
    glEnable(GL_FOG);
}

void updateLightAnimation(int value) {
    const float brightnessStep = 0.02f; // Adjust step size for speed of animation

    if (isFadingIn) {
        lightBrightness += brightnessStep;
        if (lightBrightness >= MAX_BRIGHTNESS) {
            lightBrightness = MAX_BRIGHTNESS;
            lightOn = true;
            isFadingIn = false; // Animation complete
        } else {
            glutTimerFunc(16, updateLightAnimation, 0); // Continue fading in
        }
    }
    else if (isFadingOut) {
        lightBrightness -= brightnessStep;
        if (lightBrightness <= MIN_BRIGHTNESS) {
            lightBrightness = MIN_BRIGHTNESS;
            lightOn = false;
            isFadingOut = false; // Animation complete
        } else {
            glutTimerFunc(16, updateLightAnimation, 0); // Continue fading out
        }
    }

    setupLighting(); // Update lighting configuration with new brightness
    glutPostRedisplay(); // Redraw the scene with updated lighting
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Adjust the camera
    gluLookAt(zoom*sin(angleH), height, zoom*cos(angleH),
              0.0, 1.0, 0.0,
              0.0, 1.0, 0.0);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);

    // Enable blending for transparency when light is off
    if (!lightOn) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.1f); // Discard fragments with low alpha
    } else {
        glDisable(GL_BLEND);
        glDisable(GL_ALPHA_TEST);
    }

    // Setup lighting based on current state
    setupLighting();

    // Setup material based on current state
    setupMaterial();

    setupFog();
    setupAdditionalLights();
    drawGround();
    //drawWalls();

    //glRotatef(angleV, 0.0f, 1.0f, 0.0f);
    glPushMatrix();
    {
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        glRotatef(90, 0.0f, 1.0f, 0.0f);
        drawSphereWithFlatBottom(1.1f, 0.6f, 0.9f, 36, 36, 0.67f);
    }glPopMatrix(); // Sphere with flat bottom starting at 80% height

    glPushMatrix();
    {
        glTranslatef(0.9f, 0.3f, 0.3f);
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        glRotatef(-wingAngle, 0.0f, 0.0f, 1.0f);
        drawPartialTorus(0.1f, 0.4f, 0.4f, 30, 30, -3*M_PI/2, 5*M_PI/6);
        glPushMatrix();{
            glTranslatef(0.0f, 0.5f, 0.0f);
            glRotatef(-90, 0.0f, 1.0f, 0.0f);
            glRotatef(75, 0.0f, 0.0f, 1.0f);
            drawWings(true);
        }glPopMatrix();
    }glPopMatrix();

    glPushMatrix();
    {
        glRotatef(180, 0.0f, 0.0f, 1.0f);
        glPushMatrix();
        {
            glTranslatef(0.9f, -0.3f, 0.3f);
            glRotatef(90, 1.0f, 0.0f, 0.0f);
            glRotatef(-wingAngle, 0.0f, 0.0f, 1.0f);
            drawPartialTorus(0.1f, 0.4f, 0.4f, 30, 30, -3*M_PI/2, 5*M_PI/6);
            glPushMatrix();{
                glRotatef(180, 0.0f, 1.0f, 0.0f);
                glTranslatef(0.0f, 0.5f, 0.0f);
                glRotatef(-90, 0.0f, 1.0f, 0.0f);
                glRotatef(75, 0.0f, 0.0f, 1.0f);
                drawWings(false);
            }glPopMatrix();
        }glPopMatrix();
    }glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.0f, 0.3f, -0.05f);
        drawNeckWithStackedSpheres();
    }
    glPopMatrix();

    glPushMatrix();
    {
        drawTailWithTaperedTriangles();
    }
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glPushMatrix();
    {
        glRotatef(90, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, -1.15f);
        glScalef(3.3f, 3.3f, 3.3f);
        glPushMatrix();
        {
            glTranslatef(0.0f, height1, 0.0f); //lowest: 0.53f
            glRotatef(-25, 1.0f, 0.0f, 0.0f);
            drawTablet();
        }glPopMatrix();
        glPushMatrix();
        {
            glTranslatef(0.0f, height2, 0.0f);
            glRotatef(-25, 1.0f, 0.0f, 0.0f);
            drawPhone();
        }glPopMatrix();
    }
    glPopMatrix();

    if (!lightOn) {
        glDisable(GL_BLEND);
        glDisable(GL_ALPHA_TEST);
    }

    if (wireLength > 0.0f) {
            drawWire(wireLength);
        }

    glutSwapBuffers();
}

void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'z':
        if (zoom < 10.0f) zoom += 0.1f;
        break;    // Zoom in
    case 'x':
        if (zoom > 4.0f) zoom -= 0.1f;
        break;
    case 'o':
        // Toggle light on/off
        lightOn = !lightOn;
        glutPostRedisplay();
        break;
    case 'l': // Handle lighting animation
            if (!isFadingIn && !isFadingOut) { // Only respond if no animation is in progress
                if (lightOn && lightBrightness > MIN_BRIGHTNESS) {
                    isFadingOut = true; // Start fading out
                } else if (!lightOn && lightBrightness < MAX_BRIGHTNESS) {
                    isFadingIn = true; // Start fading in
                }
                glutTimerFunc(16, updateLightAnimation, 0); // Start the animation (~60 FPS)
            }
            break;
    }
    glutPostRedisplay();
}

void openWings(int value)
{
    if (moving == true)
    {
        if(value == 1 && wingAngle < maxAngle)
        {
            wingAngle += 1;
            glutPostRedisplay();
            glutTimerFunc(6, openWings, value);
        }
        else if(value == 1 && wingAngle >= maxAngle && height1 > placed)
        {
            height1 -= 0.01f;
            glutPostRedisplay();
            glutTimerFunc(6, openWings, value);
        }
        else if(value == 0 && wingAngle > 0)
        {
            wingAngle -= 1;
            glutPostRedisplay();
            glutTimerFunc(6, openWings, value);
        }
        else if(value == 0 && wingAngle <= 0 && height2 > placed)
        {
            height2 -= 0.01f;
            glutPostRedisplay();
            glutTimerFunc(6, openWings, value);
        }
        else { moving = false; }
    }
}

void handleMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        height1 = height2 = 2.0f;

        if (open == 0) {
            open = 1;
        } else {
            open = 0;
            wireAnimating = true;       // Start wire animation
            wireLength = 0.0f;          // Reset wire length
            cubePosition = -5.2f;
            charging = false;
            glutTimerFunc(16, animateWire, 0); // Start animation
        }

        moving = true;
        glutTimerFunc(6, openWings, open);
    }
}

// Keyboard input for special keys (arrow keys)
void handleSpecialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_DOWN:
        if (height >= -5.0f) {height -= 0.2f;}
        break; // Rotate up
    case GLUT_KEY_UP:
        if (height <= 5.0f) {height += 0.2f;}
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
    glEnable(GL_NORMALIZE);
    glutKeyboardFunc(handleKeyboard);    // Register keyboard input function
    glutSpecialFunc(handleSpecialKeys);  // Register special keys function
    glutMouseFunc(handleMouse);

    init();
    glutMainLoop();
    return 0;
}
