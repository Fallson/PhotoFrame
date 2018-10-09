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
#include "PFPhotoEditViewItem.h"
#include "photoframe.h"
#include "PFPhotoEditScene.h"
#include <QGraphicsDropShadowEffect>


PFPhotoEditViewItem::PFPhotoEditViewItem(bool print_item, PhotoFrame *pMainFrame, QGraphicsItem *parent)
    :QGraphicsItem(parent), _pMainFrame(pMainFrame), _pageitm(NULL)
{
    item_shadow = false;
    b_leftbtndown = false;
    _defscal = 1.0;

    print_view_item = print_item;

	/*
	if ( !print_view_item )
	{
		QGraphicsDropShadowEffect* gdse =  (QGraphicsDropShadowEffect*)this->graphicsEffect();
		if( gdse == 0 )
		{
			gdse = new QGraphicsDropShadowEffect(NULL);
			gdse->setOffset(3.5, 3.5);
			gdse->setBlurRadius(10);
			this->setGraphicsEffect(gdse);
		}
	}
	*/

    setAcceptDrops(true);
    setAcceptHoverEvents(true);
}

PFPhotoEditViewItem::~PFPhotoEditViewItem()
{
}

void PFPhotoEditViewItem::setFrame(const QString &framepath)
{
    load_img(framepath, &frame);
    _defscal = item_size.width()/frame.width();

    calculate_img();

    this->update();
}

void PFPhotoEditViewItem::setBGPic(const QString &picpath)
{
    load_img(picpath, &bgPic_bak);

    calculate_img();

    this->update();
}

void PFPhotoEditViewItem::scale(qreal ratio)
{
    if( bgPic_bak.isNull() )
        return;

    getLefttop();

    calculate_img(false);

    this->update();
}

void PFPhotoEditViewItem::rotate(int angel)
{
    if( bgPic_bak.isNull() )
        return;

    getLefttop();

    calculate_img(false);

    this->update();
}

void PFPhotoEditViewItem::setShadow(bool s)
{
    static int first = 1;
    if( !first && item_shadow == s )
        return;

    first = 0;
    item_shadow = s;

    QGraphicsDropShadowEffect* gdse =  (QGraphicsDropShadowEffect*)this->graphicsEffect();
    if( gdse == 0 )
    {
        gdse = new QGraphicsDropShadowEffect(NULL);
        gdse->setOffset(SHADOW_OFFSET, SHADOW_OFFSET);
        gdse->setBlurRadius(SHADOW_BLUR);
        this->setGraphicsEffect(gdse);
    }

    if( item_shadow )
    {
        gdse->setOffset(SHADOW_OFFSET, SHADOW_OFFSET);
        gdse->setBlurRadius(SHADOW_BLUR);
    }
    else
    {
        gdse->setOffset(0, 0);
        gdse->setBlurRadius(0);
    }
    this->update();
}

void PFPhotoEditViewItem::resize(const QRectF& rect)
{
    if( frame.isNull() )
        _defscal = 1.0;
    else
        _defscal = rect.width() / frame.width();

    item_size = QSizeF(rect.width(), rect.height());

    getLefttop();

    calculate_img(false);

    this->update();
}

void PFPhotoEditViewItem::reload()
{
    if ( !this->_pageitm )
    {
        return ;
    }

    QString framepath;
    _pageitm->getFramePath(framepath);
    setFrame(framepath);

    QString photopath;
    _pageitm->getPhotoPath(photopath);
    setBGPic(photopath);

    int angel = 0;
    _pageitm->getRotate(angel);
    this->rotate(angel);

    qreal ratio = 0;
    _pageitm->getZoom(ratio);
    this->scale(ratio);

    QPointF offinorgimg;
    _pageitm->getImgLeftTop(offinorgimg);
    lefttop_pnt = QPoint(bgPic_bak.width() *offinorgimg.rx()*_defscal*ratio, bgPic_bak.height()*offinorgimg.ry()*_defscal*ratio);

    calculate_img(false);
    this->update();
}


void PFPhotoEditViewItem::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
{

	painter->drawImage(0,0, resultImg);
	if ( !this->print_view_item )
	{
		//QPen oldpen = painter->pen();
		//painter->setPen(QPen(Qt::lightGray));
		//painter->drawRect(resultImg.rect());
		//painter->setPen(oldpen);
	}
    if( b_leftbtndown )
    {
		if ( bgPic.size().width() > 0 )
		{

			QRectF rect(lefttop_pnt, bgPic.size());

			QPen pen;
			pen.setColor(Qt::gray);
			pen.setStyle(Qt::DotLine);
			pen.setWidth(3);
			pen.setCapStyle(Qt::RoundCap);
			pen.setJoinStyle(Qt::RoundJoin);
			painter->setPen(pen);
			painter->setBrush(Qt::NoBrush);
			painter->drawRect(rect);

#if 0
			pen.setColor(Qt::red);
			painter->setPen(pen);
			QRectF item_rect(QPointF(0,0), item_size);
			painter->drawRect(item_rect);
#endif
		}
	}
}

QRectF PFPhotoEditViewItem::boundingRect() const
{
    QRectF rect(lefttop_pnt, bgPic.size());
    QRectF item_rect(QPointF(0,0), item_size);

    return item_rect.united(rect);
}

QPainterPath PFPhotoEditViewItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void PFPhotoEditViewItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if( event->button() != Qt::LeftButton )
    {
        return;
    }

    PFPhotoEditScene *pEditScene = dynamic_cast<PFPhotoEditScene *>(scene());
    if ( !pEditScene )
    {
        return ;
    }
    pEditScene->selectItm(this, NULL);

    setCursor(Qt::ClosedHandCursor);

    b_leftbtndown = true;

    this->update();
}

void PFPhotoEditViewItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    static QPointF d; //accumulated pos

    if( !b_leftbtndown )
        return;

    if( bgPic.isNull() )
        return;

    QPointF dd = event->pos() - event->lastPos();
    d += dd;

    if(qAbs(d.x()) >= MOUSEMV_THRES || qAbs(d.y()) >= MOUSEMV_THRES)
    {
        lefttop_pnt += QPoint((int)d.x(), (int)d.y());

        setLefttop();

        calculate_img(false);
        d = QPointF();
    }

    this->scene()->update();
}

void PFPhotoEditViewItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if( event->button() != Qt::LeftButton )
    {
        return;
    }

    setCursor(Qt::OpenHandCursor);

    b_leftbtndown = false;

    this->update();
}

void PFPhotoEditViewItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{

}

void PFPhotoEditViewItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if( b_leftbtndown )
        return;

    if( bgPic.isNull() )
        return;

    QPointF pnt = event->pos();
    QRectF rect(lefttop_pnt, bgPic.size());

    if( rect.contains(pnt) )
        setCursor(Qt::OpenHandCursor);
}

void PFPhotoEditViewItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::ArrowCursor);
}

/************************Private Part***************************/
void PFPhotoEditViewItem::getLefttop()
{
    qreal ratio = 0;
    _pageitm->getZoom(ratio);

    QPointF offinorgimg;
    _pageitm->getImgLeftTop(offinorgimg);
    lefttop_pnt = QPointF(bgPic_bak.width() *offinorgimg.rx()*_defscal*ratio, bgPic_bak.height()*offinorgimg.ry()*_defscal*ratio);
}

void PFPhotoEditViewItem::setLefttop()
{
    qreal scale = 1;
    this->_pageitm->getZoom(scale);
    qreal xoffinorgimg = lefttop_pnt.rx()/scale/_defscal;
    qreal yoffinorgimg = lefttop_pnt.ry()/scale/_defscal;
    _pageitm->setImgLeftTop(QPointF(xoffinorgimg/bgPic_bak.width(), yoffinorgimg/bgPic_bak.height()));
}

void PFPhotoEditViewItem::load_img(const QString &filepath, QImage *image)
{
    image->load(filepath);

    QImage fixedImage(image->size(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&fixedImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(fixedImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, *image);
    painter.end();

    *image = fixedImage;
}

void PFPhotoEditViewItem::savePhotoCenter(QPointF &photocenter)
{
	qreal scale = 0;
	this->_pageitm->getZoom(scale);
	photocenter.setX((-lefttop_pnt.rx() + item_size.width()/2)/(_defscal * scale) );
	photocenter.setY((-lefttop_pnt.ry() + item_size.height()/2)/(_defscal * scale) );
}
		
void PFPhotoEditViewItem::restorePhotoCenter(const QPointF photocenter)
{
	QPointF center = photocenter;
	qreal scale = 0;
	this->_pageitm->getZoom(scale);
	lefttop_pnt.setX(-(center.rx()*_defscal*scale-item_size.width()/2));
	lefttop_pnt.setY(-(center.ry()*_defscal*scale-item_size.height()/2));

	 QPointF oldleftop = lefttop_pnt;
	 setLefttop();
	 this->getLefttop();
	 if ( fabs(oldleftop.rx()-lefttop_pnt.rx())> 0.01 ||
		 fabs(oldleftop.ry()-lefttop_pnt.ry())> 0.01 )
	 {
		 int brk = 1;
	 }

}


void PFPhotoEditViewItem::getScaledPhotoSize(QSizeF &photosize)
{
   qreal ratio = 0;
    _pageitm->getZoom(ratio);
    int w = bgPic_bak.width() * ratio * _defscal;
    int h = bgPic_bak.height() * ratio * _defscal;
	photosize =QSizeF(w, h);
}

void PFPhotoEditViewItem::calculate_img(bool recal_lt)
{
    /*0. prepare bgPic*/
    qreal ratio = 0;
    _pageitm->getZoom(ratio);
    int w = bgPic_bak.width() * ratio * _defscal;
    int h = bgPic_bak.height() * ratio * _defscal;
    bgPic = bgPic_bak.scaled(w,h);
    if( bgPic.isNull() )
        bgPic = bgPic_bak;

    int angel = 0;
    _pageitm->getRotate(angel);
    QTransform myTransform;
    myTransform.rotate(angel);
    bgPic = bgPic.transformed(myTransform);

    if( recal_lt )
    {
		QPointF lefttop;
		_pageitm->getImgLeftTop(lefttop);
		if ( fabs(lefttop.rx()+1) <= 0.0001 )
		{
			lefttop_pnt = QPoint((item_size.width() - bgPic.width())/2,
				(item_size.height() - bgPic.height())/2);
			setLefttop();
		}
    }

    /*1. paint resultImg*/
    resultImg = QImage((int)item_size.width(), (int)item_size.height(), QImage::Format_ARGB32_Premultiplied);

    QPainter::CompositionMode mode = QPainter::CompositionMode_DestinationOver;

    QPainter painter(&resultImg);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImg.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    //painter.drawImage(0, 0, destinationImage);
    if( !frame.isNull() )
    {
        //if( print_view_item )
       //     painter.drawImage(0, 0, frame/*.scaled(item_size.width(), item_size.height(), Qt::KeepAspectRatioByExpanding)*/);
       // else
            painter.drawImage(0, 0, frame.scaled(item_size.width(), item_size.height(), Qt::KeepAspectRatio));
    }
    painter.setCompositionMode(mode);
    //painter.drawImage(0, 0, sourceImage);
    if( !bgPic.isNull() )
        painter.drawImage(lefttop_pnt, bgPic);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    painter.end();
}
