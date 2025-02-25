#ifndef GRAPHICSITEMRESIZER_H
#define GRAPHICSITEMRESIZER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPen>
#include <QGraphicsView>

class GraphicsItemResizer : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit GraphicsItemResizer(QGraphicsItem *parent = nullptr);
    ~GraphicsItemResizer();

    inline QBrush brush() const;
    void setBrush(const QBrush &brush);

    inline QPen pen() const;
    void setPen(const QPen &pen);

    inline QSizeF minSize() const;
    void setMinSize(const QSizeF &minSize);

    inline QSizeF targetSize() const;

    bool handlersIgnoreTransformations() const;
    // If true, handler items ignore all transformations e.g. zooming the view etc
    void setHandlersIgnoreTransformations(bool ignore);

public slots:
    void setTargetSize(const QSizeF &size);

signals:
    void targetRectChanged(const QRectF &rect);
    void resizerLostFocus();

    // QGraphicsItem interface
public:
    virtual void focusOutEvent(QFocusEvent *ev) override;
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    class HandleItem;

    void updateHandleItemPositions();
    void updateDimensions(QSizeF newSize);
    void updateTargetRect(const QRectF &rect);

    QList<HandleItem *> mHandleItems;
    QPen mPen;
    QBrush mBrush;
    QSizeF mTargetSize;
    QSizeF mMinSize;
    QRectF mBounds;

    bool mHandlersIgnoreTransformations = false;
};

QBrush GraphicsItemResizer::brush() const
{
    return mBrush;
}

QPen GraphicsItemResizer::pen() const
{
    return mPen;
}

QSizeF GraphicsItemResizer::minSize() const
{
    return mMinSize;
}

QSizeF GraphicsItemResizer::targetSize() const
{
    return mTargetSize;
}

#endif // GRAPHICSITEMRESIZER_H
