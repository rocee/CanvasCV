#include "canvascv/canvas.h"

// These are used to create widgets
#include "canvascv/widgets/radiobuttons.h"

#include <iostream>
#include <iterator>

#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;
using namespace canvascv;

int main(int argc, char **argv)
{
    --argc;
    ++argv;
    Mat image;
    if (argc)
    {
        Mat orig = imread(argv[0]);
        if (orig.empty())
        {
            Canvas::fatal(string("Cannot load image ") + argv[0], -1);
        }
        if (orig.cols > 1024)
        {
            double ratio = 1024. / orig.cols;
            cv::resize(orig, image, Size(), ratio, ratio);
        }
        else
        {
            image = orig;
        }
    }
    else
    {
        Canvas::fatal("Must get a path to an image as a parameter" , -1);
    }

    Canvas c("Canvas", image.size());
    c.enableScreenText();
    Widget::CBUserSelection cb = [&c](Widget *w, int index) {
        RadioButtons *rb = (RadioButtons*)w;
        c.setScreenText(CCV_STR("User selected option '" << index << "': '" << rb->getTextAt(index) << "'\n"));
        switch (index)
        {
        case 0:
            w->setOutlineColor(Colors::Blue);
            break;
        case 1:
            w->setOutlineColor(Colors::Green);
            break;
        case 2:
            w->setOutlineColor(Colors::Red);
            break;
        }
    };

    auto radioButtons = RadioButtons::create(c, {
                                                 "Blue",  // index 0
                                                 "Green", // index 1
                                                 "Red",   // index 2
                                                 "Exit"   // index 3
                                             }, 0, cb,
                                             Point(image.cols / 2., image.rows / 2.));
    radioButtons->setOutlineColor(Colors::Blue);

    namedWindow("Canvas", WINDOW_AUTOSIZE);
    c.setMouseCallback(); // optional for mouse usage see also (example_selectbox.cpp)

    int key = 0;
    int delay = 1000/25; // we use a delay for polling the radioButtons
    Mat out; // keeping it out of the loop is a little more efficient
    while (radioButtons->getSelection() != 3 && key != 'q')
    {
        c.redrawOn(image, out);
        imshow("Canvas", out);
        key = c.waitKeyEx(delay); // GUI and callbacks happen here
    }

    destroyAllWindows();
    return 0;
}
