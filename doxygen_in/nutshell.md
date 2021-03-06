Usage in a nutshell {#nutshell}
===================
~~~~~~~{.cpp}
#include <opencv2/highgui.hpp>

#include <canvascv/canvas.h>
#include <canvascv/colors.h>
#include <canvascv/widgets/msgbox.h>

using namespace std;
using namespace cv;
using namespace canvascv;

int main()
{
    Mat image(600, 800, CV_8UC3);
    image = Colors::White;

    Canvas c("Canvas", image.size());

    namedWindow("Canvas",
                WINDOW_AUTOSIZE); // diable mouse resize since resizing
                                  // the window will stretch the widgets

    c.setMouseCallback(); // optional for mouse usage (see also example_selectbox.cpp)

    auto msgBox = MsgBox::create(c, "Do you really want to do that?", {"Yes", "No"});

    int delay = 1000/25; // if using a polling API we need a delay
    int key = -1;
    Mat out;
    do
    {
        c.redrawOn(image, out);
        imshow("Canvas", out);
        key = c.waitKeyEx(delay);
    } while (msgBox->getUserSelection() == -1);
    cout << "user choose option with index " << msgBox->getUserSelection() << endl;

    return 0;
}
~~~~~~~

