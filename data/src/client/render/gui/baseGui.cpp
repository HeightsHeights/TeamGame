#include "./baseGui.h"

BaseGui::BaseGui()
{
}
void BaseGui::draw(Vector2f pos)
{
    glBindTexture(GL_TEXTURE_2D, texId);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.3f, 0.3f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.3f, -0.3f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(0.3f, -0.3f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.3f, 0.3f, 0.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}
void BaseGui::bindTexture()
{
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}