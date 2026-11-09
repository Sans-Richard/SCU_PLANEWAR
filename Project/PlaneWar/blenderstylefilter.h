#ifndef BLENDERSTYLEFILTER_H
#define BLENDERSTYLEFILTER_H

#include <QPixmap>
#include <QImage>
#include <QColor>

class BlenderStyleFilter
{
public:
    static QPixmap applyCompositeStyle(const QPixmap& pixmap,
                                      int brightness = 18,
                                      double contrast = 1.20,
                                      double saturation = 1.15,
                                      int bloom = 6,
                                      const QColor& tint = QColor(40, 120, 255, 28));

private:
    static int clampChannel(int value);
    static QRgb adjustColor(QRgb color, int brightness, double contrast, double saturation);
    static QImage boxBlur(const QImage& image, int radius);
};

#endif // BLENDERSTYLEFILTER_H
