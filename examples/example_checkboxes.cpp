#include "canvas.h"

// **Optional
// These are used to create widgets
#include "widgets/checkboxes.h"

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
            cerr << "Cannot load image " << argv[0] << endl;
            return -1;
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
        cout << "Must get a path to an image as a parameter" << endl;
        return -1;
    }

    Canvas c(image.size());
    c.enableScreenText();
    c.setScreenText("Nothing selected");
    Widget::CBUserSelection cb = [&c](Widget *w, int index) {
        stringstream s;
        CheckBoxes *boxes = (CheckBoxes*)w;
        s << "User selected option '" << index << "': '" << boxes->getTextAt(index) << "'\n";
        for (int i = 0; i < boxes->size(); ++i)
            s << "Option '" << boxes->getTextAt(i) << "' is " << boxes->isChecked(i) << "\n";
        c.setScreenText(s.str());
    };

    CheckBoxes::create(c, {
                           "One",  // index 0
                           "Two", // index 1
                           "Three",   // index 2
                           "Four"   // index 3
                       }, cb,
                       Point(image.cols / 2., image.rows / 2.));

    namedWindow("Canvas", WINDOW_AUTOSIZE);
    c.setMouseCallback("Canvas"); // optional for mouse usage see also (example_selectbox.cpp)

    int delay = 1000/25;
    int key = 0;
    Mat out; // keeping it out of the loop is a little more efficient
    while (key != 'q')
    {
        c.redrawOn(image, out);
        imshow("Canvas", out);
        key = waitKeyEx(delay); // GUI and callbacks happen here
    }

    destroyAllWindows();
    return 0;
}
