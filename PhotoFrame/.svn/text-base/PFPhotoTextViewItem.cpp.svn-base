/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include "PFPhotoTextViewItem.h"
#include "photoframe.h"
#include "PFPhotoEditScene.h"

/*********************************************************/
//TextItem related
/*********************************************************/
#define DEFAULT_MAR_W 300
#define DEFAULT_MAR_H 64
#define MIN_HW 48
#define RADIUS 2.5
#define RIGHT_RAT 10

const QString biresPath = ":/PhotoFrame/Resources/images/buildinui/";

TextViewItem::TextViewItem(bool print_item, PhotoFrame* pMainFrame, QGraphicsItem *parent)
    :QGraphicsItem(parent), _pMainFrame(pMainFrame),_mv_d(0,0),_pTextitem(NULL)
{
    text = QString("");
    text_horalign = HorLeftAlig;
    text_veralign = VerTopAlig;

    text_font_ratio = 1.0;

    calItemRect(QRectF(0,0,DEFAULT_MAR_W,DEFAULT_MAR_H));
    rot_angle = 0;

    print_text_item = print_item;

    item_shadow = false;

    mm_style = MMN;
    b_leftbtn_dwn = false;

    setFlag( QGraphicsItem::ItemIsSelectable );
    setFlag( QGraphicsItem::ItemIsMovable );
    setAcceptHoverEvents(true);

    rotate_cur = QCursor(QPixmap(QString(biresPath+"/curs/rotate.png")));

    _pTextitem = new QGraphicsTextItem();
    _pTextitem->setParentItem(this);
    _pTextitem->setAcceptHoverEvents(false);
    _pTextitem->setPos(0,0);
    _pTextitem->setTextWidth(DEFAULT_MAR_W);
}

TextViewItem::~TextViewItem()
{
    //do nth
}


void TextViewItem::setText(const QString &txt)
{
    text = txt;

    _pTextitem->setHtml(text);
    //_pTextitem->setHtml("abcd");
    _pTextitem->update();
}

void TextViewItem::setShadow(bool s)
{
    item_shadow = s;

    QGraphicsDropShadowEffect* gdse =  (QGraphicsDropShadowEffect*)_pTextitem->graphicsEffect();
    if( gdse == 0 )
    {
        gdse = new QGraphicsDropShadowEffect(_pTextitem);
        gdse->setOffset(SHADOW_OFFSET, SHADOW_OFFSET);
        gdse->setBlurRadius(SHADOW_BLUR);
        _pTextitem->setGraphicsEffect(gdse);
    }

    if( item_shadow )
    {
        gdse->setBlurRadius(SHADOW_BLUR);
        gdse->setOffset(SHADOW_OFFSET, SHADOW_OFFSET);
    }
    else
    {
        gdse->setBlurRadius(0.0);
        gdse->setOffset(0,0);
    }
    _pTextitem->update();
}

void TextViewItem::setHorAlignment(HorAlignment ha)
{
    text_horalign = ha;

    QTextDocument* doc = _pTextitem->document();
    QTextOption op = doc->defaultTextOption();
    if( ha == HorLeftAlig )
    {
        op.setAlignment(Qt::AlignLeft);
    }
    else if( ha == HorCenterAlig )
    {
        op.setAlignment(Qt::AlignHCenter);
    }
    else if( ha == HorRightAlig )
    {
        op.setAlignment(Qt::AlignRight);
    }
    doc->setDefaultTextOption(op);

    _pTextitem->update();
}

void TextViewItem::setVerAlignment(VerAlignment va)
{
    text_veralign = va;

    QRectF rect = _pTextitem->boundingRect();

    if( rect.height() >= item_rect.height() )//the text is full of the item_rect
        return;


    qreal pos_y = 0.0;
    if( va == VerTopAlig )
    {
        pos_y = item_rect.y();
    }
    else if( va == VerCenterAlig )
    {
        pos_y = item_rect.y() + item_rect.height()/2.0 - rect.height()/2.0;
    }
    else if( va == VerBottomAlig )
    {
        pos_y = item_rect.y() + item_rect.height() - rect.height();
    }
    _pTextitem->setPos(_pTextitem->pos().x(), pos_y);

    _pTextitem->update();
}

QPainterPath TextViewItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

QRectF TextViewItem::boundingRect() const
{
    qreal adjust = RADIUS;
    QRectF rect(item_rect.x() - 2*adjust, item_rect.y() - 2*adjust,
                item_rect.width() + 4*adjust + RIGHT_RAT*RADIUS, item_rect.height() + 4*adjust);
    return rect;
}

static QString replaceFont(const QString& input, qreal ratio)
{
    qDebug() << "The input <<< " << input;
    QString res("");
    QString pat("font-size:");

    int last_pos = 0;
    int cur_pos = 0;

    do{
        cur_pos = input.indexOf(pat, last_pos);

        if( cur_pos == -1 )
        {
            res += input.mid(last_pos);
            break;
        }
        else
        {
            res += input.mid(last_pos, cur_pos-last_pos);
            res += pat;
            cur_pos += pat.length();
            QString fs("");
            while(input[cur_pos].isDigit() || input[cur_pos] == '.')
            {
                fs += input[cur_pos++];
            }
            res += QString("%1").arg((int)(fs.toDouble()*ratio));

            last_pos = cur_pos;
        }
    }while(1);

    qDebug() << "The output <<<" << res;
    return res;
}

void TextViewItem::setFontViewRatio(qreal fontratio)
{
    text_font_ratio = fontratio;

    QString txt = replaceFont(text, fontratio);

    _pTextitem->setHtml(txt);
    //_pTextitem->setHtml("abcd");
    _pTextitem->update();
}

void TextViewItem::setWidthHeight(int width, int height)
{
    calItemRect(QRectF(0,0,width,height));

    this->update();
}

void TextViewItem::reload()
{
    rot_angle = _txtitm->getRotate();
    item_shadow = _txtitm->isShadowEnable();
    QString cnt;
    _txtitm->getContent(cnt);
    setText(cnt);
    this->rrotate(rot_angle);
    setShadow(_txtitm->isShadowEnable());

    int align = 0;
    align = _txtitm->getAlign();
    HorAlignment haligninview;
    switch ( align & PmTextItm::ALIGN_HMASK )
    {
    case PmTextItm::ALIGN_CENTER:
        haligninview = HorCenterAlig;
        break;
    case PmTextItm::ALIGN_RIGHT:
        haligninview = HorRightAlig;
        break;
    case PmTextItm::ALIGN_LEFT:
    default:
        haligninview = HorLeftAlig;
    }
    this->setHorAlignment(haligninview);

    VerAlignment verigninview;
    switch ( align & PmTextItm::ALIGN_VMASK )
    {
    case PmTextItm::ALIGN_TOP:
        verigninview = VerTopAlig;
        break;
    case PmTextItm::ALIGN_VCENTER:
        verigninview = VerCenterAlig;
        break;
    case PmTextItm::ALIGN_BOTTOM:
    default:
        verigninview = VerBottomAlig;
    }
    this->setVerAlignment(verigninview);

    this->update();
}


void TextViewItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    //qDebug() << "The paint pos is: " << this->pos();
    if ( this->isSelected() )
    {
        //first draw the boundary
        QPen pen;
        pen.setColor(Qt::gray);
        pen.setStyle(Qt::DotLine);
        pen.setWidth(0);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(item_rect);

        //second draw the scale hits
        pen.setColor(Qt::black);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(0);
        painter->setPen(pen);
        painter->setBrush(Qt::green);
        for(int i = 0; i < 8; i++)
        {
            painter->drawRect(dragRects[i]);
        }

        //third draw the rotate hit
        painter->setBrush(Qt::red);
        painter->drawEllipse(rotateRect);
    }
    else if( !print_text_item )
    {
        //paint 4 corner
        QPen pen;
        pen.setColor(Qt::gray);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(0);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);

        QVector<QLineF> lines;

        qreal len = RADIUS*2;
        QPointF p1 = item_rect.topLeft();
        QPointF p2 = p1 + QPointF(len, 0.0);
        lines.push_back(QLineF(p1,p2));
        p2 = p1 + QPointF(0.0, len);
        lines.push_back(QLineF(p1,p2));

        p1 = item_rect.topRight();
        p2 = p1 - QPointF(len, 0.0);
        lines.push_back(QLineF(p1,p2));
        p2 = p1 + QPointF(0.0, len);
        lines.push_back(QLineF(p1,p2));

        p1 = item_rect.bottomRight();
        p2 = p1 - QPointF(len, 0.0);
        lines.push_back(QLineF(p1,p2));
        p2 = p1 - QPointF(0.0, len);
        lines.push_back(QLineF(p1,p2));

        p1 = item_rect.bottomLeft();
        p2 = p1 + QPointF(len, 0.0);
        lines.push_back(QLineF(p1,p2));
        p2 = p1 - QPointF(0.0, len);
        lines.push_back(QLineF(p1,p2));

        painter->drawLines(lines);
    }

#if 0
    if( this->isSelected() )
    {
        QStyleOptionGraphicsItem op(*option);
        op.state &= ~(QStyle::State_Selected|QStyle::State_HasFocus);
        _pTextitem->paint(painter, &op, widget);
    }
    else
    {
        _pTextitem->paint(painter, option, widget);
    }
#endif
}

void TextViewItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if( event->button() != Qt::LeftButton )
    {
        b_leftbtn_dwn = false;
        return;
    }

    PFPhotoEditScene *pEditScene = dynamic_cast<PFPhotoEditScene*>(this->scene());
    if ( pEditScene )
    {
        pEditScene->selectItm(NULL, this);
    }

    b_leftbtn_dwn = true;

    if( mm_style == MMN )
    {
        return;
    }

    _mv_d = QPoint(0,0);

    QPointF pos = this->pos();
    QRectF itmrct = item_rect.translated(pos.x(), pos.y());

    if( mm_style >= MM0 && mm_style <= MM7 )
    {
        _pMainFrame->OnResizeTextBox(itmrct);
    }
    else if( mm_style == MMR )
    {
        _pMainFrame->OnRotateTextBox(itmrct, rot_angle);
    }
    else if( mm_style == MMT )
    {
        _pMainFrame->OnMvTextBox(itmrct);
    }
   // setCursor(mouse_curs[(int)mm_style]);
}

void TextViewItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{   

    if( !b_leftbtn_dwn )
    {
        //d = QPointF();
        return;
    }

    if( !this->isSelected() )
    {
       // d = QPointF();
        return;
    }

    if( mm_style == MMN )
    {
       // d = QPointF();
        return;
    }

    QPoint dd = event->screenPos() - event->lastScreenPos();
    _mv_d += dd;

    bool need_update = false;
    do{
        if( mm_style == MM0 )
        {
            if( (qAbs(_mv_d.x()) >= MOUSEMV_THRES || qAbs(_mv_d.y()) >= MOUSEMV_THRES) &&
                (_mv_d.x()*_mv_d.y()>0) &&
                ((item_rect.width() - _mv_d.x() >= MIN_HW) && (item_rect.height() - _mv_d.y() >= MIN_HW)) )
            {
                _pTextitem->moveBy(_mv_d.x(), _mv_d.y());

                item_rect.adjust(_mv_d.x(), _mv_d.y(), 0, 0);

                need_update = true;
            }
        }
        else if( mm_style == MM1 )
        {
            if( qAbs(_mv_d.y()) >= MOUSEMV_THRES &&
                item_rect.adjusted(0, _mv_d.y(), 0, 0).height() >= MIN_HW )
            {
                _pTextitem->moveBy(0, _mv_d.y());

                item_rect.adjust(0, _mv_d.y(), 0, 0);

                need_update = true;
            }
        }
        else if( mm_style == MM2 )
        {
            if( (qAbs(_mv_d.x()) >= MOUSEMV_THRES || qAbs(_mv_d.y()) >= MOUSEMV_THRES) &&
                (_mv_d.x()*_mv_d.y()<0) &&
                ((item_rect.width() + _mv_d.x() >= MIN_HW)&&(item_rect.height() - _mv_d.y() >= MIN_HW)) )
            {
                _pTextitem->moveBy(-_mv_d.x(), _mv_d.y());

                item_rect.adjust(-_mv_d.x(), _mv_d.y(), 0, 0);
                need_update = true;
            }
        }
        else if( mm_style == MM3 )
        {
            if( qAbs(_mv_d.x()) >= MOUSEMV_THRES &&
                item_rect.adjusted(0, 0, _mv_d.x(), 0).width() >= MIN_HW )
            {
                item_rect.adjust(0, 0, _mv_d.x(), 0);
                need_update = true;
            }
        }
        else if( mm_style == MM4 )
        {
            if( (qAbs(_mv_d.x()) >= MOUSEMV_THRES || qAbs(_mv_d.y()) >= MOUSEMV_THRES) &&
                (_mv_d.x()*_mv_d.y()>0) &&
                    ((item_rect.width() + _mv_d.x() >= MIN_HW)&&(item_rect.height() + _mv_d.y() >= MIN_HW)) )
            {
                item_rect.adjust(0, 0, _mv_d.x(), _mv_d.y());
                need_update = true;
            }
        }
        else if( mm_style == MM5 )
        {
            if( qAbs(_mv_d.y()) >= MOUSEMV_THRES &&
                item_rect.adjusted(0,0,0,_mv_d.y()).height() >= MIN_HW )
            {
                item_rect.adjust(0, 0, 0, _mv_d.y());
                need_update = true;
            }
        }
        else if( mm_style == MM6 )
        {
            if( (qAbs(_mv_d.x()) >= MOUSEMV_THRES || qAbs(_mv_d.y()) >= MOUSEMV_THRES) &&
                (_mv_d.x()*_mv_d.y()<0) &&
                    ((item_rect.width() - _mv_d.x() >= MIN_HW)&&(item_rect.height() + _mv_d.y() >= MIN_HW)) )
            {
                _pTextitem->moveBy(_mv_d.x(), -_mv_d.y());

                item_rect.adjust(_mv_d.x(), -_mv_d.y(), 0, 0);
                need_update = true;
            }
        }
        else if( mm_style == MM7 )
        {
            if( qAbs(_mv_d.x()) >= MOUSEMV_THRES &&
                item_rect.adjusted(_mv_d.x(), 0, 0, 0).width() >= MIN_HW )
            {
                _pTextitem->moveBy(_mv_d.x(), 0);

                item_rect.adjust(_mv_d.x(), 0, 0, 0);
                need_update = true;
            }
        }
        else if( mm_style == MMR )
        {
            if( qAbs(_mv_d.x()) >= MOUSEMV_THRES || qAbs(_mv_d.y()) >= MOUSEMV_THRES )
            {
                QPointF a1(0.0,0.0);
                QPointF a2(1.0,0.0);
                a1 = this->mapToScene(a1);
                a2 = this->mapToScene(a2);
                QPointF a0(a1.x()+_mv_d.x(), a1.y()+_mv_d.y());
                qreal res = (a2.x()-a1.x())*(a0.y()-a1.y())-(a2.y()-a1.y())*(a0.x()-a1.x());

                if( res > 0.0 )
                {
                    rot_angle += 2;
                    this->rrotate(rot_angle);
                    need_update = true;
                }
                else
                {
                    rot_angle -= 2;
                    this->rrotate(rot_angle);
                    need_update = true;
                }
            }
        }
        else if( mm_style == MMT )
        {
            if( qAbs(_mv_d.x()) >= MOUSEMV_THRES || qAbs(_mv_d.y()) >= MOUSEMV_THRES )
            {
                this->ttranslate(_mv_d.x(),_mv_d.y());
                need_update = true;
            }
        }

        if( need_update && mm_style >= MM0 && mm_style <= MM7 )
        {
            calItemRect(item_rect);
        }
    }while(0);

    if( need_update )
    {
        QPointF pos = this->pos();
        QRectF itmrct = item_rect.translated(pos.x(), pos.y());

        if( mm_style >= MM0 && mm_style <= MM7 )
        {
            _pMainFrame->OnResizeTextBox(itmrct);
        }
        else if( mm_style == MMR )
        {
            _pMainFrame->OnRotateTextBox(itmrct, rot_angle);
        }
        else if( mm_style == MMT )
        {
            _pMainFrame->OnMvTextBox(itmrct);
        }

        // this->scene()->update();//not call this->update, because it maybe smaller
        _mv_d = QPoint();
    }
}

void TextViewItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    b_leftbtn_dwn = false;

    if( mm_style == MMN )
    {
        //do nth
        return;
    }

    QPointF pos = this->pos();
    QRectF itmrct = item_rect.translated(pos.x(), pos.y());

    if( mm_style >= MM0 && mm_style <= MM7 )
    {
        _pMainFrame->OnResizeTextBox(itmrct);
    }
    else if( mm_style == MMR )
    {
        _pMainFrame->OnRotateTextBox(itmrct, rot_angle);
    }
    else if( mm_style == MMT )
    {
        _pMainFrame->OnMvTextBox(itmrct);
    }

    //setCursor(mouse_curs[(int)mm_style]);
}

void TextViewItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
}

void TextViewItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    static QCursor mouse_curs[] = {
        Qt::SizeFDiagCursor,
        Qt::SizeVerCursor,
        Qt::SizeBDiagCursor,
        Qt::SizeHorCursor,
        Qt::SizeFDiagCursor,
        Qt::SizeVerCursor,
        Qt::SizeBDiagCursor,
        Qt::SizeHorCursor,
        rotate_cur, //rotate
        Qt::OpenHandCursor, //translate
        Qt::ArrowCursor //normal one
    };

    if( b_leftbtn_dwn )
        return;

    if( !this->isSelected() )
        return;

    do{
        QPointF pnt = event->pos();
        bool hit = false;
        qreal adjust = RADIUS;

        for(int i = 0; i < 8; i++)
        {
            if( dragRects[i].adjusted(-adjust,-adjust,adjust,adjust).contains(pnt) )
            {
                mm_style = MouseMovStyle(i);
                hit = true;
                break;
            }
        }
        if( hit )
            break;

        if( rotateRect.adjusted(-adjust,-adjust,adjust,adjust).contains(pnt) )
        {
            mm_style = MMR;
            hit = true;
            break;
        }

        if( item_rect.contains(pnt) )
        {
            mm_style = MMT;
            hit = true;
            break;
        }

        if( !hit )
        {
            mm_style = MMN;
        }
    }while(0);

    setCursor(mouse_curs[(int)mm_style]);
}

void TextViewItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
}

/*******************Private Part of TextItem***************************/
void TextViewItem::calItemRect(const QRectF& rect)
{
    prepareGeometryChange();

    item_rect = rect;

    qreal dia = 2*RADIUS;

    dragRects[0] = QRectF(item_rect.x()-(dia/2.0), item_rect.y()-(dia/2.0), dia, dia);
    dragRects[1] = dragRects[0].translated(item_rect.width()/2, 0);
    dragRects[2] = dragRects[1].translated(item_rect.width()/2, 0);
    dragRects[3] = dragRects[2].translated(0, item_rect.height()/2);
    dragRects[4] = dragRects[3].translated(0, item_rect.height()/2);
    dragRects[5] = dragRects[4].translated(-item_rect.width()/2, 0);
    dragRects[6] = dragRects[5].translated(-item_rect.width()/2, 0);
    dragRects[7] = dragRects[6].translated(0,-item_rect.height()/2);

    rotateRect = QRectF(item_rect.x() + item_rect.width() + RIGHT_RAT*RADIUS - (dia/2.0),
                        item_rect.y() + item_rect.height()/2 - (dia/2.0),
                        dia, dia);

    if( _pTextitem != NULL )
        _pTextitem->setTextWidth(item_rect.width());
}

void TextViewItem::rrotate(qreal angle)
{
    qDebug() << "pos of rotate is: " << this->pos();
    qDebug() << "item_rect of rotate is: " << item_rect;
    this->setTransformOriginPoint(item_rect.center());
    this->setRotation(angle);
    qDebug() << "after pos of rotate is: " << this->pos();
    qDebug() << "after item_rect of rotate is: " << item_rect;
}

void TextViewItem::ttranslate(qreal dx, qreal dy)
{
    qDebug() << "item_rect of translate is: " << item_rect;
    this->setTransformOriginPoint(item_rect.center());
    this->moveBy(dx,dy);
}
