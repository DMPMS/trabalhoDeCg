#ifndef OUTROS
#define OUTROS

void eixos()
{
    // EIXO x
    glBegin(GL_LINES);

    glColor3ub(255, 0, 255);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);

    glColor3ub(255, 0, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    glEnd();

    // EIXO y
    glBegin(GL_LINES);

    glColor3ub(255, 255, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);

    glColor3ub(0, 255, 0);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    glEnd();

    // EIXO z
    glBegin(GL_LINES);

    glColor3ub(0, 255, 255);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);

    glColor3ub(0, 0, 255);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);

    glEnd();
}

#endif
