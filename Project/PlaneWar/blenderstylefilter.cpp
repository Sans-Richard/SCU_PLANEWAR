#include "blenderstylefilter.h"

#include <QImage>
#include <QPainter>
#include <QColor>
#include <QVector>

int BlenderStyleFilter::clampChannel(int value)
{
    if (value < 0) return 0;
    if (value > 255) return 255;
    return value;
}

QRgb BlenderStyleFilter::adjustColor(QRgb color, int brightness, double contrast, double saturation)
{
    QColor c(color);

    int r = c.red();
    int g = c.green();
    int b = c.blue();

    r += brightness;
    g += brightness;
    b += brightness;

    r = clampChannel(int((r - 128) * contrast + 128));
    g = clampChannel(int((g - 128) * contrast + 128));
    b = clampChannel(int((b - 128) * contrast + 128));

    const int grey = (r + g + b) / 3;
    r = clampChannel(int(r + (r - grey) * (saturation - 1.0)));
    g = clampChannel(int(g + (g - grey) * (saturation - 1.0)));
    b = clampChannel(int(b + (b - grey) * (saturation - 1.0)));

    return qRgba(r, g, b, c.alpha());
}

QImage BlenderStyleFilter::boxBlur(const QImage& image, int radius)
{
    if (radius <= 0) return image;

    QImage out = image;
    const int w = image.width();
    const int h = image.height();

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int r = 0, g = 0, b = 0, a = 0;
            int count = 0;

            for (int yy = -radius; yy <= radius; ++yy) {
                for (int xx = -radius; xx <= radius; ++xx) {
                    int nx = x + xx;
                    int ny = y + yy;
                    if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;

                    QColor c(image.pixel(nx, ny));
                    r += c.red();
                    g += c.green();
                    b += c.blue();
                    a += c.alpha();
                    ++count;
                }
            }

            if (count > 0) {
                QColor c;
                c.setRed(r / count);
                c.setGreen(g / count);
                c.setBlue(b / count);
                c.setAlpha(a / count);
                out.setPixelColor(x, y, c);
            }
        }
    }

    return out;
}

QPixmap BlenderStyleFilter::applyCompositeStyle(const QPixmap& pixmap,
                                               int brightness,
                                               double contrast,
                                               double saturation,
                                               int bloom,
                                               const QColor& tint)
{
    if (pixmap.isNull()) {
        return pixmap;
    }

    QImage img = pixmap.toImage();
    QImage processed = img.convertToFormat(QImage::Format_ARGB32);

    for (int y = 0; y < processed.height(); ++y) {
        for (int x = 0; x < processed.width(); ++x) {
            processed.setPixel(x, y,
                              adjustColor(processed.pixel(x, y), brightness, contrast, saturation));
        }
    }

    if (bloom > 0) {
        QImage glow = boxBlur(processed, bloom);
        QImage combined = processed.copy();

        QPainter painter(&combined);
        painter.setCompositionMode(QPainter::CompositionMode_Screen);
        painter.drawImage(0, 0, glow);
        painter.end();

        processed = combined;
    }

    if (tint.alpha() > 0) {
        QImage tinted = processed.copy();
        QPainter painter(&tinted);
        painter.setCompositionMode(QPainter::CompositionMode_Screen);
        painter.fillRect(0, 0, tinted.width(), tinted.height(), tint);
        painter.end();

        QPainter finalPainter(&processed);
        finalPainter.setCompositionMode(QPainter::CompositionMode_Screen);
        finalPainter.drawImage(0, 0, tinted);
        finalPainter.end();
    }

    return QPixmap::fromImage(processed);
}
