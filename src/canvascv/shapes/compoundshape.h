#ifndef COMPOUNDSHAPE_H
#define COMPOUNDSHAPE_H

#include "shape.h"
#include "shapefactory.h"
#include "canvascv/colors.h"

#include <list>
#include <memory>

namespace canvascv
{

/**
 * @brief The CompoundShape class
 * 
 * A utility class used by shapes which are the
 * combination of other shapes
 */
class CompoundShape : public Shape
{
public:

    virtual void setOutlineColor(const cv::Scalar &value);
    virtual void setFillColor(const cv::Scalar &value);
    virtual void setThickness(int value);
    virtual void setLineType(int value);
    virtual void setLocked(bool value);
    virtual void setVisible(bool value);

    virtual std::shared_ptr<Shape> getShape(int id);

    virtual void translate(const cv::Point &offset);
protected:
    virtual ~CompoundShape() {} // force inheritance

    virtual void reloadPointers(const std::list<Shape*> &, std::list<Shape*>::const_iterator &)
    {}

    virtual void draw(cv::Mat &canvas);
    virtual bool mousePressed(const cv::Point &pos, bool onCreate = false);
    virtual bool mouseMoved(const cv::Point &pos);
    virtual bool mouseReleased(const cv::Point &pos);

    virtual bool keyPressed(int &key);
    virtual void lostFocus();

    virtual const string &getCreateStatusMsg() const;
    virtual const string &getEditStatusMsg() const;

    void setActive(Shape* shape);
    Shape* getActive();

    template <class T>
    T* addShape(cv::Point pos);

    bool rmvShape(Shape *shape);

    virtual void writeInternals(cv::FileStorage &fs) const;
    virtual void readInternals(const cv::FileNode &node);

    virtual void setReady();

private:
    std::shared_ptr<Shape> active;
    std::list<std::shared_ptr<Shape>> shapes;
};

template <class T> inline
T* CompoundShape::addShape(cv::Point pos)
{
    T *ret = dynamic_cast<T*>(ShapeFactoryT<T>::newShape(pos));
    shapes.push_back(std::shared_ptr<Shape>(ret));
    return ret;
}

}

#endif // COMPOUNDSHAPE_H
