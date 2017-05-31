#ifndef COLORS_H
#define COLORS_H

#include <opencv2/opencv.hpp>

namespace canvascv
{

class Colors
{
public:
    // Middle colors colors (middle
    //  in RGB color codes chart)
    static const cv::Scalar BLUE;
    static const cv::Scalar GREEN;
    static const cv::Scalar RED;
    static const cv::Scalar WHITE;
    static const cv::Scalar BLACK;

    // P1 colors are lighter colors (Plus1 after middle
    //  in RGB color codes chart)
    static const cv::Scalar P1_GRAY;
    static const cv::Scalar P1_PINK;
    static const cv::Scalar P1_LPINK;
    static const cv::Scalar P1_PURPLE;
    static const cv::Scalar P1_BLUE;
    static const cv::Scalar P1_LBLUE;
    static const cv::Scalar P1_CYAN;
    static const cv::Scalar P1_LCYAN;
    static const cv::Scalar P1_GREEN;
    static const cv::Scalar P1_LGREEN;
    static const cv::Scalar P1_YELLOW;
    static const cv::Scalar P1_ORANGE;
    static const cv::Scalar P1_RED;
};

}

#endif // COLORS_H
