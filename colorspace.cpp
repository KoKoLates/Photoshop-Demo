#include "colorspace.h"

ColorSpace::ColorSpace(QWidget *parent, const Mat &image) : QWidget(parent)
{
    src = image;
}

void ColorSpace::TypeChanged()
{
    QRadioButton *button = qobject_cast<QRadioButton*>(sender());
    if(button == gray) type = GRAY;
    else if(button == hsv) type = HSV;
    else if(button == hsl) type = HSL;
    else type = YCRCB;

    color();
}

void ColorSpace::color()
{
    dst = src.clone();
    switch (type) {
    case ColorSpace::GRAY:
        cvtColor(dst, dst, COLOR_BGR2GRAY);
        break;

    case ColorSpace::HSV:
        cvtColor(dst, dst, COLOR_BGR2HSV);
        break;

    case ColorSpace::HSL:
        cvtColor(dst, dst, COLOR_BGR2HLS);
        break;

    case ColorSpace::YCRCB:
        cvtColor(dst, dst, COLOR_BGR2YCrCb);
        break;

    default:
        return;
    }
    imshow("Preview", dst);
}

void ColorSpace::rejected()
{
    switch (type) {
    case ColorSpace::GRAY:
        gray->setAutoExclusive(false);
        gray->setChecked(false);
        gray->setAutoExclusive(true);
        break;

    case ColorSpace::HSV:
        hsv->setAutoExclusive(false);
        hsv->setChecked(false);
        hsv->setAutoExclusive(true);
        break;

    case ColorSpace::HSL:
        hsl->setAutoExclusive(false);
        hsl->setChecked(false);
        hsl->setAutoExclusive(true);
        break;

    case ColorSpace::YCRCB:
        ycrcb->setAutoExclusive(false);
        ycrcb->setChecked(false);
        ycrcb->setAutoExclusive(true);
        break;

    default:
        return;
    }
}
