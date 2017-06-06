#ifndef VERTICALLAYOUT_H
#define VERTICALLAYOUT_H

#include "compoundwidget.h"
#include "layout.h"

namespace canvascv
{

class Canvas;

class VerticalLayout : public CompoundWidget, public Layout
{
public:

    VerticalLayout(const cv::Point &pos);

    static std::shared_ptr<VerticalLayout> newVerticalLayout(Canvas &c, cv::Point pos);

    virtual const char *getType() const;

    int getSpacing() const;
    void setSpacing(int value);

    virtual void recalc();
    virtual void addDirtyWidget(Widget *widget);
    virtual void addWidget(const std::shared_ptr<Widget> &widget);
    virtual bool rmvWidget(const std::shared_ptr<Widget> &widget);
    virtual Size getAllowedSize() const;

    void rmvWidget(int i);

    Widget *at(int index);

    static const char *type;
    bool getStretchX() const;
    void setStretchX(bool value);

    bool getStretchY() const;
    void setStretchY(bool value);

protected:

    virtual void writeInternals(FileStorage &fs) const;
    virtual void readInternals(const FileNode &node);

private:
    int spacing;
    bool stretchX;
    bool stretchY;
    std::vector<std::shared_ptr<Widget>> vertWidgets;
    bool duringDirtyHandling;
    std::list<Widget*> dirtyWidgets;
};

}

#endif // VERTICALLAYOUT_H
