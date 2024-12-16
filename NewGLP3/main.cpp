#include <windows.h>
#include <GL/glut.h>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int defaultWing(int openValue);
float angleH  = M_PI/2;
float height = 2.0f;
float height1 = 2.0f;
float height2 = 2.0f;               // Rotation angles
float zoom = 7.0f;                                    // Zoom level
int open = 1;
bool moving = true;
bool moving2 = true;
int maxAngle = 83;
int wingAngle = defaultWing(open);
float placed = 0.53f;

int defaultWing(int openValue) {
    if (openValue == 0) {return 0;}
    else return maxAngle;
}

GLuint texture, texture2;
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

    stbi_image_free(data);  // Free image data after creating texture
    return textureID;
}

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

void draw3DQuarterOval(float radiusX, float radiusY, float height, int segments) {
    float halfHeight = height / 2.0f;

    // Top face (1/4 oval)
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 1.0f, 0.0f); // Normal for lighting
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
    glNormal3f(0.0f, -1.0f, 0.0f); // Normal for lighting
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
    gluLookAt(zoom*sin(angleH), height, zoom*cos(angleH),
              0.0, 1.0, 0.0,
              0.0, 1.0, 0.0);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
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
            drawWings();
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
                drawWings();
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
    glutSwapBuffers();
}

void handleKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'Z':
    case 'z':
        if (zoom < 10.0f) zoom += 0.1f;
        break;
    case 'X':
    case 'x':
        if (zoom > 4.0f) zoom -= 0.1f;
        break;
    case 27:
        exit(0);
        break;
    default:
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
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        height1 = height2 = 2.0f;
        if(open == 0) {open = 1;}
        else {open = 0;}
        moving = true;
        glutTimerFunc(6, openWings, open);
    }
}

// Keyboard input for special keys (arrow keys)
void handleSpecialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_DOWN:
        if (height >= -6.0f) {height -= 0.2f;}
        break; // Rotate up
    case GLUT_KEY_UP:
        if (height <= 6.0f) {height += 0.2f;}
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

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    stbi_set_flip_vertically_on_load(true);
    /*
    Remember to change the document name path into your version...
    */
    texture = loadTexture("C:\\Users\\kenho\\Documents\\Programming Practice\\TestGL\\UI.jpg");
    texture2 = loadTexture("C:\\Users\\kenho\\Documents\\Programming Practice\\TestGL\\PhoneUI.jpg");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Sphere with Depth");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    init();
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glutKeyboardFunc(handleKeyboard);    // Register keyboard input function
    glutSpecialFunc(handleSpecialKeys);  // Register special keys function
    glutMouseFunc(handleMouse);
    glutTimerFunc(6, openWings, open);
    glutMainLoop();
    return 0;
}
