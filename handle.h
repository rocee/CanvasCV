#ifndef HANDLE_H
#define HANDLE_H

#include "shape.h"
#include "shapefactory.h"

#include <opencv2/opencv.hpp>
#include <functional>
#include <list>

namespace canvasvc
{

class Handle : public Shape
{
public:
    typedef std::function<void(const cv::Point &)> PosChangedCB;
    typedef std::list<PosChangedCB>::iterator CBID;

    Handle(const cv::Point &pos)
        : pt(pos),
          allowSetPos(true)
    {
        thickness = 3;
        outlineColor = Colors::RED;
        fillColor = Colors::RED;
    }

    // force compiler to generate default cctor inspite of the ctor
    //  we defined above
    Handle(const Handle &) = default;

    ~Handle();

    virtual void draw(cv::Mat &canvas);
    virtual bool mousePressed(const cv::Point &pos, bool = false);
    virtual bool mouseMoved(const cv::Point &pos);
    virtual bool mouseReleased(const cv::Point &pos);
    virtual bool isAtPos(const cv::Point &pos)
    {
        return isPoint(pos);
    }
    virtual std::list<Handle *> getConnectionTargets();
    virtual const char *getType() const {
        return "Handle";
    }
    virtual void lostFocus();

    const cv::Point &operator()() const {
        return pt;
    }

    void setPos(const cv::Point &pos, bool notify = true)
    {
        if (allowSetPos)
        {
            pt = pos;
            if (notify)
            {
                broadcastPosChanged(pos);
            }
        }
    }

    int getRadius() const
    {
        return thickness;
    }

    CBID addPosChangedCB(PosChangedCB cb)
    {
        posChangedCBs.push_back(cb);
        return --posChangedCBs.end();
    }

    void delPosChangedCB(const CBID &id)
    {
        posChangedCBs.erase(id);
    }

    void connect(Handle &other);
    void disconnect(Handle &other);


protected:
    virtual void writeInternals(cv::FileStorage &fs) const;
    virtual void readInternals(const cv::FileNode &node);

private:

    void connectedFrom(Handle &other);
    void disconnectFrom(Handle &other);

    bool isPoint(const cv::Point &pos, int threshold=3)
    {
        threshold += thickness/2;
        return abs(pos.x - pt.x) <= threshold &&
                abs(pos.y - pt.y) <= threshold;
    }

    void broadcastPosChanged(const cv::Point& pos);

    std::list<PosChangedCB> posChangedCBs;
    std::map<Handle*, CBID> connectedHandles;
    cv::Point pt;
    bool allowSetPos;
};

}

#endif // HANDLE_H


