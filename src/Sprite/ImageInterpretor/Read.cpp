#include "../../../include/Sprite/ImageInterpretor.hpp"

void Motor2D::ImageInterpretor::readImage(const char *fileName) {
    // I need it with SDL but I don't know how to do it
    sf::Image image;
    image.loadFromFile(fileName);
    this->m_WidthImage = image.getSize().x;
    this->m_HeightImage = image.getSize().y;
    this->m_Tab2DPixel = Tab2D_Create<Motor2D::Pixel *>(this->m_WidthImage, this->m_HeightImage);
    Tab2D_InitPointer(this->m_Tab2DPixel);
    for (int y = 0; y < image.getSize().y; y++) {
        for (int x = 0; x < image.getSize().x; x++) {
            this->putPixelValue(&image, x, y);
        }
    }
}

Uint32 Motor2D::ImageInterpretor::getPixel(SDL_Surface *surface, int x, int y) {
    Uint32 *pixels = (Uint32 *) surface->pixels;
    return pixels[(y * surface->w) + x];
}

void Motor2D::ImageInterpretor::putPixelValue(SDL_Surface *surface, int x, int y) {
    SDL_Color color = {0, 0, 0, 0};
    Motor2D::Pixel pixel(this->m_Renderer, x, y, color);
    Tab2D_Set(this->m_Tab2DPixel, x, y, &pixel);
}

void Motor2D::ImageInterpretor::putPixelValue(sf::Image *image, int x, int y) {
    sf::Color colorPixel = image->getPixel(x, y);
    SDL_Color color = {colorPixel.r, colorPixel.g, colorPixel.b, colorPixel.a};
    if (colorPixel.a != 0) {
        Tab2D_Set(this->m_Tab2DPixel, x, y,
                  new Motor2D::Pixel(this->m_Renderer, x, y, color));
    }
}