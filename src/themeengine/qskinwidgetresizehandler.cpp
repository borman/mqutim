#include "qskinwidgetresizehandler.h"

#include "qframe.h"
#include "qapplication.h"
#include "qdesktopwidget.h"
#include "qcursor.h"
#include "qsizegrip.h"
#include "qevent.h"
#if defined(Q_WS_WIN)
#include "qt_windows.h"
#endif
#include "qdebug.h"
#define RANGE 4
// #ifdef WIN32
// #include <private/qlayoutengine_p.h>
#ifndef qSmartMinSize
QSize qSmartMinSize(const QWidget * wid)
{
    QWidgetItem i(const_cast<QWidget *>(wid));
    QWidget *w = ((QWidgetItem *)&i)->widget();
 
    QSize s(0, 0);
     QSize msh(w->minimumSizeHint());
     QSize sh(w->sizeHint());

     if (w->sizePolicy().horizontalPolicy() != QSizePolicy::Ignored) {
         if (w->sizePolicy().horizontalPolicy() & QSizePolicy::ShrinkFlag)
             s.setWidth(msh.width());
         else
             s.setWidth(qMax(sh.width(), msh.width()));
     }
 
     if (w->sizePolicy().verticalPolicy() != QSizePolicy::Ignored) {
         if (w->sizePolicy().verticalPolicy() & QSizePolicy::ShrinkFlag) {
            s.setHeight(msh.height());
         } else {
             s.setHeight(qMax(sh.height(), msh.height()));
        }
     }
 
     s = s.boundedTo(w->maximumSize());
     QSize min = w->minimumSize();
     if (min.width() > 0)
         s.setWidth(min.width());
     if (min.height() > 0)
         s.setHeight(min.height());
     return s.expandedTo(QSize(0,0));
}
#endif
static bool resizeHorizontalDirectionFixed = false;
static bool resizeVerticalDirectionFixed = false;

QSkinWidgetResizeHandler::QSkinWidgetResizeHandler(QSkinObject * skobj, QWidget *parent, QWidget *cw)
    : QObject(parent), widget(parent), childWidget(cw ? cw : parent),
      fw(0), extrahei(0), buttonDown(false), moveResizeMode(false), sizeprotect(true), movingEnabled(true)
{
	obj = skobj;
	widgetType = 0;
    mode = Nowhere;
    widget->setMouseTracking(true);
    //QFrame *frame = qobject_cast<QFrame*>(widget);
	range = skobj->customFrameWidth()/2;
	if(skobj->customFrameWidth()/2 < 5)
		range = skobj->customFrameWidth();
    activeForMove = activeForResize = true;
    widget->installEventFilter(this);
}

void QSkinWidgetResizeHandler::setActive(Action ac, bool b)
{
    if (ac & Move)
        activeForMove = b;
    if (ac & Resize)
        activeForResize = b;

    if (!isActive())
        setMouseCursor(Nowhere);
}

bool QSkinWidgetResizeHandler::isActive(Action ac) const
{
    bool b = false;
    if (ac & Move) b = activeForMove;
    if (ac & Resize) b |= activeForResize;

    return b;
}

bool QSkinWidgetResizeHandler::eventFilter(QObject *o, QEvent *ee)
{
    if (!isActive()
        || (ee->type() != QEvent::MouseButtonPress
            && ee->type() != QEvent::MouseButtonRelease
            && ee->type() != QEvent::MouseMove
            && ee->type() != QEvent::KeyPress
            && ee->type() != QEvent::ShortcutOverride)
        )
        return false;

    Q_ASSERT(o == widget);
    QWidget *w = widget;
    if (QApplication::activePopupWidget()) {
        if (buttonDown && ee->type() == QEvent::MouseButtonRelease)
            buttonDown = false;
        return false;
    }

    QMouseEvent *e = (QMouseEvent*)ee;
    switch (e->type()) {
    case QEvent::MouseButtonPress: {
        if (w->isMaximized())
            break;
        if (!widget->rect().contains(widget->mapFromGlobal(e->globalPos())))
    		return false;
        if (e->button() == Qt::LeftButton) {
#if defined(Q_WS_X11)
            /*
               Implicit grabs do not stop the X server from changing
               the cursor in children, which looks *really* bad when
               doing resizingk, so we grab the cursor. Note that we do
               not do this on Windows since double clicks are lost due
               to the grab (see change 198463).
            */
            if (e->spontaneous())

#endif // Q_WS_X11
			
	    obj->mousePressEvent(static_cast<QMouseEvent*>(ee));
            buttonDown = false;
            emit activate();
            bool me = movingEnabled;
            movingEnabled = (me && o == widget);
            mouseMoveEvent(e);
            movingEnabled = me;
            buttonDown = true;
            moveOffset = widget->mapFromGlobal(e->globalPos());
            invertedMoveOffset = widget->rect().bottomRight() - moveOffset;
            if (mode == Center) {
                if (movingEnabled)
                    return true;
            } else {
		return true;
            }
        }
    } break;
    case QEvent::MouseButtonRelease:
        if (w->isMaximized())
            break;
        if (e->button() == Qt::LeftButton) {
            moveResizeMode = false;
            buttonDown = false;
            widget->releaseMouse();
            widget->releaseKeyboard();
            if (mode == Center) {
                if (movingEnabled)
                    return true;
            } else {
                return true;
            }
        }
        break;
    case QEvent::MouseMove: {
        if (w->isMaximized())
            break;
        buttonDown = buttonDown && (e->buttons() & Qt::LeftButton); // safety, state machine broken!
        bool me = movingEnabled;
        movingEnabled = (me && o == widget && (buttonDown || moveResizeMode));
        mouseMoveEvent(e);
        movingEnabled = me;
        if (mode == Center) {
            if (movingEnabled)
                return true;
        } else {
            return true;
        }
    } break;
    case QEvent::KeyPress:
        keyPressEvent((QKeyEvent*)e);
        break;
    case QEvent::ShortcutOverride:
        if (buttonDown) {
            ((QKeyEvent*)ee)->accept();
            return true;
        }
        break;
    default:
        break;
    }
	
    return false;
}

void QSkinWidgetResizeHandler::mouseMoveEvent(QMouseEvent *e)
{
    
	QPoint pos = widget->mapFromGlobal(e->globalPos());
    if (!moveResizeMode && !buttonDown) {
        if (pos.y() <= range && pos.x() <= range)
            mode = TopLeft;
        else if (pos.y() >= widget->height()-range && pos.x() >= widget->width()-range)
            mode = BottomRight;
        else if (pos.y() >= widget->height()-range && pos.x() <= range)
            mode = BottomLeft;
        else if (pos.y() <= range && pos.x() >= widget->width()-range)
            mode = TopRight;
        else if (pos.y() <= range)
            mode = Top;
        else if (pos.y() >= widget->height()-range)
            mode = Bottom;
        else if (pos.x() <= range)
            mode = Left;
        else if ( pos.x() >= widget->width()-range)
            mode = Right;
        else if (widget->rect().contains(pos))
            mode = Center;
        else
            mode = Nowhere;

        if (widget->isMinimized() || !isActive(Resize))
            mode = Center;
#ifndef QT_NO_CURSOR
        setMouseCursor(mode);
#endif
        return;
    }

    if (mode == Center && !movingEnabled)
        return;

    if (widget->testAttribute(Qt::WA_WState_ConfigPending))
        return;


    QPoint globalPos = (!widget->isWindow() && widget->parentWidget()) ?
                       widget->parentWidget()->mapFromGlobal(e->globalPos()) : e->globalPos();
    if (!widget->isWindow() && !widget->parentWidget()->rect().contains(globalPos)) {

        if (globalPos.x() < 0)
            globalPos.rx() = 0;
        if (globalPos.y() < 0)
            globalPos.ry() = 0;
        if (sizeprotect && globalPos.x() > widget->parentWidget()->width())
            globalPos.rx() = widget->parentWidget()->width();
        if (sizeprotect && globalPos.y() > widget->parentWidget()->height())
            globalPos.ry() = widget->parentWidget()->height();
    }

    QPoint p = globalPos + invertedMoveOffset;
    QPoint pp;
	
	#if defined(Q_OS_WIN32)
		pp = globalPos - moveOffset + QPoint(0,-24);
	#else
		pp = globalPos - moveOffset;
	#endif
	
#ifdef Q_WS_X11
    // Workaround for window managers which refuse to move a tool window partially offscreen.
    QRect desktop = qApp->desktop()->availableGeometry(widget);
    pp.rx() = qMax(pp.x(), desktop.left());
    pp.ry() = qMax(pp.y(), desktop.top());
    p.rx() = qMin(p.x(), desktop.right());
    p.ry() = qMin(p.y(), desktop.bottom());

#endif

    QSize ms = qSmartMinSize(childWidget);
    int mw = ms.width();
    int mh = ms.height();
    if (childWidget != widget) {
        mw += 2 * fw;
        mh += 2 * fw + extrahei;
    }

    QSize maxsize(childWidget->maximumSize());
    if (childWidget != widget)
        maxsize += QSize(2 * fw, 2 * fw + extrahei);
    QSize mpsize(widget->geometry().right() - pp.x() + 1,
                  widget->geometry().bottom() - pp.y() + 1);
    mpsize = mpsize.expandedTo(widget->minimumSize()).expandedTo(QSize(mw, mh))
                    .boundedTo(maxsize);
    QPoint mp(widget->geometry().right() - mpsize.width() + 1,
               widget->geometry().bottom() - mpsize.height() + 1);

    QRect geom = widget->geometry();

    switch (mode) {
    case TopLeft:
        geom = QRect(mp, widget->geometry().bottomRight()) ;
        break;
    case BottomRight:
        geom = QRect(widget->geometry().topLeft(), p) ;
        break;
    case BottomLeft:
        geom = QRect(QPoint(mp.x(), widget->geometry().y()), QPoint(widget->geometry().right(), p.y())) ;
        break;
    case TopRight:
        geom = QRect(QPoint(widget->geometry().x(), mp.y()), QPoint(p.x(), widget->geometry().bottom())) ;
        break;
    case Top:
        geom = QRect(QPoint(widget->geometry().left(), mp.y()), widget->geometry().bottomRight()) ;
        break;
    case Bottom:
        geom = QRect(widget->geometry().topLeft(), QPoint(widget->geometry().right(), p.y())) ;
        break;
    case Left:
        geom = QRect(QPoint(mp.x(), widget->geometry().top()), widget->geometry().bottomRight()) ;
        break;
    case Right:
        geom = QRect(widget->geometry().topLeft(), QPoint(p.x(), widget->geometry().bottom())) ;
        break;
    case Center:
        geom.moveTopLeft(pp);
        break;
    default:
        break;
    }

    geom = QRect(geom.topLeft(),
                  geom.size().expandedTo(widget->minimumSize())
                             .expandedTo(QSize(mw, mh))
                             .boundedTo(maxsize));

    if (geom != widget->geometry() &&
        (widget->isWindow() || widget->parentWidget()->rect().intersects(geom))) {
        if (mode == Center)
            widget->move(geom.topLeft());
        else
            widget->setGeometry(geom);
    }

    QApplication::syncX();
}

void QSkinWidgetResizeHandler::setMouseCursor(MousePosition m)
{
#ifdef QT_NO_CURSOR
    Q_UNUSED(m);
#else
    QObjectList children = widget->children();
    for (int i = 0; i < children.size(); ++i) {
        if (QWidget *w = qobject_cast<QWidget*>(children.at(i))) {
            if (!w->testAttribute(Qt::WA_SetCursor) && !w->inherits("QWorkspaceTitleBar")) {
                w->setCursor(Qt::ArrowCursor);
            }
        }
    }

    switch (m) {
    case TopLeft:
    case BottomRight:
        widget->setCursor(Qt::SizeFDiagCursor);
        break;
    case BottomLeft:
    case TopRight:
        widget->setCursor(Qt::SizeBDiagCursor);
        break;
    case Top:
    case Bottom:
        widget->setCursor(Qt::SizeVerCursor);
        break;
    case Left:
    case Right:
        widget->setCursor(Qt::SizeHorCursor);
        break;
    default:
        widget->setCursor(Qt::ArrowCursor);
        break;
    }
#endif // QT_NO_CURSOR
}

void QSkinWidgetResizeHandler::keyPressEvent(QKeyEvent * e)
{
    if (!isMove() && !isResize())
        return;
    bool is_control = e->modifiers() & Qt::ControlModifier;
    int delta = is_control?1:8;
    QPoint pos = QCursor::pos();
    switch (e->key()) {
    case Qt::Key_Left:
        pos.rx() -= delta;
        if (pos.x() <= QApplication::desktop()->geometry().left()) {
            if (mode == TopLeft || mode == BottomLeft) {
                moveOffset.rx() += delta;
                invertedMoveOffset.rx() += delta;
            } else {
                moveOffset.rx() -= delta;
                invertedMoveOffset.rx() -= delta;
            }
        }
        if (isResize() && !resizeHorizontalDirectionFixed) {
            resizeHorizontalDirectionFixed = true;
            if (mode == BottomRight)
                mode = BottomLeft;
            else if (mode == TopRight)
                mode = TopLeft;
#ifndef QT_NO_CURSOR
            setMouseCursor(mode);
            widget->grabMouse(widget->cursor());
#else
            widget->grabMouse();
#endif
        }
        break;
    case Qt::Key_Right:
        pos.rx() += delta;
        if (pos.x() >= QApplication::desktop()->geometry().right()) {
            if (mode == TopRight || mode == BottomRight) {
                moveOffset.rx() += delta;
                invertedMoveOffset.rx() += delta;
            } else {
                moveOffset.rx() -= delta;
                invertedMoveOffset.rx() -= delta;
            }
        }
        if (isResize() && !resizeHorizontalDirectionFixed) {
            resizeHorizontalDirectionFixed = true;
            if (mode == BottomLeft)
                mode = BottomRight;
            else if (mode == TopLeft)
                mode = TopRight;
#ifndef QT_NO_CURSOR
            setMouseCursor(mode);
            widget->grabMouse(widget->cursor());
#else
            widget->grabMouse();
#endif
        }
        break;
    case Qt::Key_Up:
        pos.ry() -= delta;
        if (pos.y() <= QApplication::desktop()->geometry().top()) {
            if (mode == TopLeft || mode == TopRight) {
                moveOffset.ry() += delta;
                invertedMoveOffset.ry() += delta;
            } else {
                moveOffset.ry() -= delta;
                invertedMoveOffset.ry() -= delta;
            }
        }
        if (isResize() && !resizeVerticalDirectionFixed) {
            resizeVerticalDirectionFixed = true;
            if (mode == BottomLeft)
                mode = TopLeft;
            else if (mode == BottomRight)
                mode = TopRight;
#ifndef QT_NO_CURSOR
            setMouseCursor(mode);
            widget->grabMouse(widget->cursor());
#else
            widget->grabMouse();
#endif
        }
        break;
    case Qt::Key_Down:
        pos.ry() += delta;
        if (pos.y() >= QApplication::desktop()->geometry().bottom()) {
            if (mode == BottomLeft || mode == BottomRight) {
                moveOffset.ry() += delta;
                invertedMoveOffset.ry() += delta;
            } else {
                moveOffset.ry() -= delta;
                invertedMoveOffset.ry() -= delta;
            }
        }
        if (isResize() && !resizeVerticalDirectionFixed) {
            resizeVerticalDirectionFixed = true;
            if (mode == TopLeft)
                mode = BottomLeft;
            else if (mode == TopRight)
                mode = BottomRight;
#ifndef QT_NO_CURSOR
            setMouseCursor(mode);
            widget->grabMouse(widget->cursor());
#else
            widget->grabMouse();
#endif
        }
        break;
    case Qt::Key_Space:
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_Escape:
        moveResizeMode = false;
        widget->releaseMouse();
        widget->releaseKeyboard();
        buttonDown = false;
        break;
    default:
        return;
    }
    QCursor::setPos(pos);
}


void QSkinWidgetResizeHandler::doResize()
{
    if (!activeForResize)
        return;

    moveResizeMode = true;
    moveOffset = widget->mapFromGlobal(QCursor::pos());
    if (moveOffset.x() < widget->width()/2) {
        if (moveOffset.y() < widget->height()/2)
            mode = TopLeft;
        else
            mode = BottomLeft;
    } else {
        if (moveOffset.y() < widget->height()/2)
            mode = TopRight;
        else
            mode = BottomRight;
    }
    invertedMoveOffset = widget->rect().bottomRight() - moveOffset;
#ifndef QT_NO_CURSOR
    setMouseCursor(mode);
    widget->grabMouse(widget->cursor() );
#else
    widget->grabMouse();
#endif
    widget->grabKeyboard();
    resizeHorizontalDirectionFixed = false;
    resizeVerticalDirectionFixed = false;
}

void QSkinWidgetResizeHandler::doMove()
{
    if (!activeForMove)
        return;

    mode = Center;
    moveResizeMode = true;
    moveOffset = widget->mapFromGlobal(QCursor::pos());
    invertedMoveOffset = widget->rect().bottomRight() - moveOffset;
#ifndef QT_NO_CURSOR
    widget->grabMouse(Qt::SizeAllCursor);
#else
    widget->grabMouse();
#endif
    widget->grabKeyboard();
}

