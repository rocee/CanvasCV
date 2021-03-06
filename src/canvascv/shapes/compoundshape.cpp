#include "canvascv/colors.h"
#include "handle.h"
#include "compoundshape.h"

#include <algorithm>

using namespace std;
using namespace cv;

namespace canvascv
{

void CompoundShape::draw(Mat &canvas)
{
    if (visible)
    {
        for (auto &shape : shapes)
        {
            if (shape->getVisible())
            {
                shape->draw(canvas);
            }
        }
    }
}

bool CompoundShape::mousePressed(const Point &pos, bool onCreate)
{
    if (visible)
    {
        // delegate to active
        if (active.get())
        {
            if (! active->mousePressed(pos, onCreate))
            {
                active->lostFocus();
                active.reset();
//                return false;
            } else {
                return true;
            }
        }

        // try to set active
        for (auto &shape : shapes)
        {
            if (shape->mousePressed(pos))
            {
                active = shape;
                return true;
            }
        }
    }
    return false;
}

bool CompoundShape::mouseMoved(const Point &pos)
{
    if (visible)
    {
        if (active.get())
        {
            return active->mouseMoved(pos);
        }
    }
    return false;
}

bool CompoundShape::mouseReleased(const Point &pos)
{
    if (visible)
    {
        if (active.get())
        {
            if (! active->mouseReleased(pos))
            {
                active->lostFocus();
                active.reset();
                return false;
            }
            return true;
        }
    }
    return false;
}

void CompoundShape::setOutlineColor(const Scalar &value)
{
    Shape::setOutlineColor(value);
    for (auto &shape : shapes)
    {
        if (shape->getType() != Handle::type)
        {
            shape->setOutlineColor(value);
        }
    }
}

void CompoundShape::setFillColor(const Scalar &value)
{
    Shape::setFillColor(value);
    for (auto &shape : shapes)
    {
        if (shape->getType() != Handle::type)
        {
            shape->setFillColor(value);
        }
    }
}

void CompoundShape::setThickness(int value)
{
    Shape::setThickness(value);
    for (auto &shape : shapes)
    {
        if (shape->getType() != Handle::type)
        {
            shape->setThickness(value);
        }
    }
}

void CompoundShape::setLineType(int value)
{
    Shape::setLineType(value);
    for (auto &shape : shapes)
    {
        shape->setLineType(value);
    }
}

void CompoundShape::setLocked(bool value)
{
    Shape::setLocked(value);
    for (auto &shape : shapes)
    {
        shape->setLocked(value);
    }
}

void CompoundShape::setVisible(bool value)
{
    Shape::setVisible(value);
    for (auto &shape : shapes)
    {
        shape->setVisible(value);
    }
}

shared_ptr<Shape> CompoundShape::getShape(int id)
{
    for (auto &shape : shapes)
    {
        if (shape->getId() == id)
        {
            return shape;
        }
        shared_ptr<Shape> subShape = shape->getShape(id);
        if (subShape.get())
        {
            return subShape;
        }
    }
    return nullptr;
}

void CompoundShape::translate(const Point &offset)
{
    if (active.get() && active->getType() == Handle::type)
    {
        active->translate(offset);
    }
    else
    {
        for (auto &shape : shapes)
        {
            shape->translate(offset);
        }
    }
}

bool CompoundShape::rmvShape(Shape *shape)
{
    auto i = find_if(shapes.begin(),shapes.end(),[shape](const shared_ptr<Shape> &item)->bool
    {
        return item.get() == shape;
    }
    );
    if (i != shapes.end())
    {
        if (active.get() == shape)
        {
            active->lostFocus();
            active.reset();
        }
        shapes.erase(i);
        return true;
    }
    return false;
}

void CompoundShape::writeInternals(FileStorage &fs) const
{
    Shape::writeInternals(fs);
    fs << "shapes" << "[";
    for (auto &shape : shapes)
    {
        fs << *shape;
    }
    fs << "]";
}

void CompoundShape::readInternals(const FileNode &node)
{
    Shape::readInternals(node);
    active.reset();
    shapes.clear();
    FileNode n = node["shapes"];
    FileNodeIterator it = n.begin(), it_end = n.end();
    list<Shape*> shapesTmp;
    for (; it != it_end; )
    { // ++it is done automatically by "it >> shape"
        Shape *shape = 0;
        it >> shape;
        assert(shape != 0);
        shapes.push_back(shared_ptr<Shape>(shape));
        shapesTmp.push_back(shape);
    }
    list<Shape*>::const_iterator i = shapesTmp.begin();
    reloadPointers(shapesTmp, i);
}

void CompoundShape::setReady()
{
    Shape::setReady();
    for (auto &shape : shapes)
    {
        shape->setReady();
    }
}

bool CompoundShape::keyPressed(int &key)
{
    if (active.get())
    {
        if (! active->keyPressed(key))
        {
            active->lostFocus();
            active.reset();
            return false;
        }
    }
    return true;
}

void CompoundShape::lostFocus()
{
    if (! isReady())
    {
        setDeleted();
    }
    else
    {
        for (auto &shape : shapes)
        {
            shape->lostFocus();
        }
    }
}

const string &CompoundShape::getCreateStatusMsg() const
{
   static const string msg = "Click to set point position. ESC to cancel.";
   return msg;
}

const string &CompoundShape::getEditStatusMsg() const
{
   static const string msg = "Drag with mouse to move shape.\nDrag handles to modify shape.\n";
   return msg;
}

void CompoundShape::setActive(Shape *shape)
{
    auto i = find_if(shapes.begin(),
                     shapes.end(),
                     [shape](const shared_ptr<Shape> &item)->bool
    {
        return item.get() == shape;
    });
    if (i != shapes.end())
    {
        if (active.get())
        {
            active->lostFocus();
        }
        active = *i;
    }
}

Shape *CompoundShape::getActive()
{
   return active.get();
}

}
