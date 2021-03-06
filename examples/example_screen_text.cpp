#include "canvascv/canvas.h"

#include <iostream>

#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;
using namespace canvascv;

static string gHelpMsg =
"Usage:\n"
"=====\n"
"h: toggle usage message\n"
"*: toggle canvas on/off\n"
"q: exit";

void help(Canvas &c)
{
    static bool showHelp = true;
    if (showHelp)
    {
        cout << gHelpMsg << endl;
        c.setScreenText(gHelpMsg);
    }
    else
    {
        c.setScreenText("");
    }
    showHelp = ! showHelp;
}

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

    // Enabling on screen text with changes from defaults
    c.enableScreenText(Colors::Black, // fg
                       Colors::Green, // bg
                       0.6);          // font scale
    help(c);

    namedWindow("Canvas",
                WINDOW_AUTOSIZE); // disable mouse resize since resizing
                                  // the window will stretch the widgets

    int key = 0;
    Mat out; // keeping it out of the loop is a little more efficient
    do
    {
        switch (key)
        {
        case 'h':
            help(c);
            break;
        case '*':
            c.setOn(! c.getOn());
            break;
        }

        c.redrawOn(image, out);

        imshow("Canvas", out);

        key = c.waitKeyEx(); // GUI and callbacks happen here

    } while (key != 'q');

    destroyAllWindows();
    return 0;
}
