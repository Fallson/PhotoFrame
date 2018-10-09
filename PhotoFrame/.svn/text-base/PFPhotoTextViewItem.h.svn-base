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

#ifndef PhotoTextViewItm_H
#define PhotoTextViewItm_H

#include <QCursor>
#include <QGraphicsTextItem>
#include "PFPhotoEditViewItem.h"


class TextViewItem : public QGraphicsItem
{
public:
    TextViewItem(bool print_item, PhotoFrame* pMainFrame, QGraphicsItem* parent = 0);
    virtual ~TextViewItem();

    void setText(const QString& txt);
    QString getText() const {return text;}

    void setShadow(bool s);
    bool getShadow() const { return item_shadow; }

    void setHorAlignment(HorAlignment ha);
    HorAlignment getHorAlignment() const { return text_horalign; }

    void setVerAlignment(VerAlignment va);
    VerAlignment getVerAlignment() const { return text_veralign; }

    void setFontViewRatio(qreal fontratio);
    void setWidthHeight(int width, int height);

	qreal getRotateAngel(){return rot_angle;}
    void reload();

public:
    void setTextItm(PmTextItm *pTextItm){_txtitm = pTextItm;}
    PmTextItm *getTextItm(){return _txtitm;}

protected:
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    void calItemRect(const QRectF& rect);
    void rrotate(qreal angle);
    void ttranslate(qreal dx, qreal dy);

private:
    QGraphicsTextItem* _pTextitem;
    PhotoFrame* _pMainFrame;

    QString text;
    HorAlignment text_horalign;
    VerAlignment text_veralign;

    QRectF item_rect;
    QRectF dragRects[8];
    QRectF rotateRect;
    qreal rot_angle;

    bool item_shadow;
    bool print_text_item;

    enum MouseMovStyle{MM0=0,MM1,MM2,MM3,MM4,MM5,MM6,MM7,MMR,MMT,MMN};
    MouseMovStyle mm_style;
    bool b_leftbtn_dwn;

    qreal text_font_ratio;
    PmTextItm *_txtitm;

    QCursor rotate_cur;

    QPoint _mv_d; //accumulated pos

};

#endif
