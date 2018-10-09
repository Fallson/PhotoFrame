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

#include "pmpicView.h"
#include <QtGui/qevent.h>
#include <QPainter>
#include <QDrag>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QApplication>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsDropShadowEffect>



#define IMG_SIZE_X	120
#define IMG_SIZE_Y	147

#define IMG_SCALESIZE_X	120
#define IMG_SCALESIZE_Y	157

#define IMG_X_MARGIN 10
#define IMG_Y_MARGIN 10
#define IMG_LABEL_MARGIN	10 

#define IMG_LABEL_HEIGHT 15


// IMAGE SIZE SHOULD BE 110X122

//! [0]
PictureView::PictureView( QWidget *parent)
    : QGraphicsView(parent), _enablescale(true),_showframe(false),
	_itmdbclickCallback(NULL), _showtxt(true)
{

	setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene(this);
	QRect rect = this->geometry();
	scene->setSceneRect(0, 0, rect.width(), rect.height());

	setScene(scene);

    QGraphicsPixmapItem *logo = scene->addPixmap(QPixmap(":/logo.png"));
    logo->setPos(30, 515);

#ifndef Q_OS_SYMBIAN
    //setMinimumSize(470, 620);
    //setMaximumSize(470, 620);
#else
    setDragMode(QGraphicsPictureView::ScrollHandDrag);
#endif

	_imgsizex = IMG_SIZE_X, _imgsizey = IMG_SIZE_Y;
	_imgmarginx = IMG_X_MARGIN;
	_imgmarginy = IMG_Y_MARGIN;

	//_imgscalesizex = _imgsizex;
	//_imgscalesizey = _imgsizey + 10;


	setWindowTitle("");
}
//! [1]

void PictureView::setImgSize(int width, int height)
{
	_imgsizex = width, _imgsizey = height;
	//_imgscalesizex = _imgsizex;
	//_imgscalesizey = _imgsizey + 10;

}

void PictureView::setImgMargin(int marginx, int marginy)
{
	_imgmarginx = marginx;
	_imgmarginy = marginy;
}


bool PictureView::_getItmPos(int index, int &x, int &y)
{
	QRect rect = this->geometry();
	int cntinrow = rect.width() * 1.0/(_imgsizex + _imgmarginx);
	if ( cntinrow == 0 )
	{
		cntinrow++;
	}

	int imgswidth = cntinrow * (_imgsizex + _imgmarginx );
	int leftwidth = rect.width() - imgswidth;

	int leftmargin = leftwidth/2;

	x = (index % cntinrow) * (_imgsizex + _imgmarginx ) + _imgmarginx/2 + leftmargin;
	y = (index / cntinrow) * (_imgsizey + _imgmarginy ) + _imgmarginy/2;


	return true;
}

//! [3]

void PictureView::addItem(const QString &imgpath, const QString &labeltxt, const QString &info)
{
	int imgcnt = _imgItms.size();

	PictureViewItm *image;
	QGraphicsTextItem *label;

	QString file = imgpath;

	int x=0, y=0;
	this->_getItmPos(imgcnt, x, y);
	
	QPixmap pixmap;
	pixmap.load(file);
	
	//pixmap.scaledToHeight(
	int height4img = _imgsizey - _imgmarginy - IMG_LABEL_HEIGHT-IMG_LABEL_MARGIN;
	int width4img = _imgsizex - _imgmarginx;

	if ( _showframe )
	{
		// shrik the img show that there's space to show frmae
		height4img -= 8;
		width4img -= 8;
	}



	QRect imgrect = pixmap.rect();
	qreal scaleratio;
	if ( imgrect.width()*1.0 / imgrect.height() < width4img *1.0/ height4img )
	{
		// scale according height
		scaleratio = height4img * 1.0/ imgrect.height() ;
	}
	else
	{
		scaleratio = width4img * 1.0/ imgrect.width() ;
	}
	pixmap = pixmap.scaled(imgrect.width()*scaleratio, imgrect.height()*scaleratio, Qt::KeepAspectRatio);
	image = new PictureViewItm(this, pixmap,QSize(width4img+_imgmarginx,height4img+_imgmarginy), _showframe);
	image->setImgMargin(this->_imgmarginx, this->_imgmarginy);
	image->setShowFrame(this->_showframe);
	image->update();
	image->setFlag(QGraphicsItem::ItemIsSelectable, true);

	image->setInfo(info);
	//image->enableScale(_enablescale);

	//image->setScaleSize();
	image->setData(0, imgcnt);
	image->setPos(x, y);
	scene->addItem(image);


    QGraphicsDropShadowEffect* gdse =  (QGraphicsDropShadowEffect*)image->graphicsEffect();
    if( gdse == 0 )
    {
        gdse = new QGraphicsDropShadowEffect(NULL);
        gdse->setOffset(3.5, 3.5);
        gdse->setBlurRadius(10);
        image->setGraphicsEffect(gdse);
    }
	_imgItms.push_back(image);

	label = scene->addText(labeltxt);
	QPointF labelOffset((_imgsizex - label->boundingRect().width()) / 2, 0/* height4img + IMG_LABEL_MARGIN*/ );
	label->setPos(QPointF(x, y) + labelOffset);

	_labels.push_back(label);


	QSize scenesize;
	this->_getSceneSize(scenesize);
	scene->setSceneRect(0, 0, scenesize.width(), scenesize.height());
	//scene->update();
	//image->update();
	updateView(false);

}


void PictureView::addItem(const QPixmap &img, const QString &labeltxt,const QString &info)
{
	static int id = 0;
	static int imgcnt = 0;

	PictureViewItm *image;
	QGraphicsTextItem *label;


	int x=0, y=0;
	this->_getItmPos(imgcnt, x, y);
	
	QPixmap pixmap = img;
	//pixmap.scaledToHeight(
	int height4img = _imgsizey - _imgmarginy - IMG_LABEL_HEIGHT-IMG_LABEL_MARGIN;
	int width4img = _imgsizex - _imgmarginx;

	if ( _showframe )
	{
		// shrik the img show that there's space to show frmae
		height4img -= 8;
		width4img -= 8;
	}

	QRect imgrect = pixmap.rect();
	qreal scaleratio;
	if ( imgrect.width()*1.0 / imgrect.height()< width4img *1.0/ height4img )
	{
		// scale according height
		scaleratio = height4img * 1.0/ imgrect.height() ;
	}
	else
	{
		scaleratio = width4img * 1.0/ imgrect.width() ;
	}
	pixmap = pixmap.scaled(imgrect.width()*scaleratio, imgrect.height()*scaleratio, Qt::KeepAspectRatio);
	image = new PictureViewItm(this, pixmap,QSize(width4img+_imgmarginx, height4img+_imgmarginy), _showframe );
	image->setImgMargin(this->_imgmarginx, this->_imgmarginy);
	image->setShowFrame(this->_showframe);
	image->update();
	image->setFlag(QGraphicsItem::ItemIsSelectable, true);

	image->setInfo(info);
	//image->enableScale(_enablescale);

	//image->setScaleSize();
	image->setData(0, imgcnt);
	image->setPos(x, y);
    QGraphicsDropShadowEffect* gdse =  (QGraphicsDropShadowEffect*)image->graphicsEffect();
    if( gdse == 0 )
    {
        gdse = new QGraphicsDropShadowEffect(NULL);
        gdse->setOffset(3.5, 3.5);
        gdse->setBlurRadius(10);
        image->setGraphicsEffect(gdse);
    }
	scene->addItem(image);
	_imgItms.push_back(image);

	if ( _showtxt )
	{
		label = scene->addText(labeltxt);
	}
	else
	{
		label = scene->addText("");
	}
	QPointF labelOffset((_imgsizex - label->boundingRect().width()) / 2-20, 0/*height4img + IMG_LABEL_MARGIN*/ );
	label->setPos(QPointF(x, y) + labelOffset);

	_labels.push_back(label);

	id++;
	imgcnt++;

	QSize scenesize;
	this->_getSceneSize(scenesize);
	scene->setSceneRect(0, 0, scenesize.width(), scenesize.height());
	
	updateView(false);
}

//! [3]

//! [5]
void PictureView::mouseReleaseEvent(QMouseEvent *event)
{
    if (QGraphicsItem *item = itemAt(event->pos())) 
	{
        if (PictureViewItm *image = qgraphicsitem_cast<PictureViewItm *>(item))
		{
            //showInformation(image);
		}
    }
    QGraphicsView::mouseReleaseEvent(event);
}
//! [5]



void PictureView::updateView(bool full )
{
	//

	int imageOffset = _imgsizex;
	int leftMargin = _imgmarginx;
	int topMargin = _imgmarginy;

	QRect rect = this->geometry();

	int cntinrow = rect.width()/(_imgsizex + _imgmarginx);
	if ( cntinrow == 0 )
	{
		cntinrow++;
	}

	int height4img = _imgsizey - _imgmarginy - IMG_LABEL_HEIGHT;
	
	list<QGraphicsPixmapItem *>::iterator it;
	list<QGraphicsTextItem *>::iterator labeit;
	int i=0;
	if ( full )
	{
		for(it=_imgItms.begin(), labeit=_labels.begin(); it!=_imgItms.end(); it++ ,labeit++, i++)
		{
			//int imgcnt = _imgItms.size();
			int x=0, y=0;
			this->_getItmPos(i, x, y);
			QGraphicsPixmapItem *image = *it;

			image->setPos(x, y);

			//label = scene->addText(location);
			//label->setPos(QPointF(x, y) + labelOffset);
			QGraphicsTextItem *label = *labeit;


			QPointF labelOffset((_imgsizex - label->boundingRect().width()) / 2-5, height4img  );
			label->setPos(QPointF(x,y) + labelOffset);
		}
	}
	else
	{
		for(it=_imgItms.begin(), labeit=_labels.begin(); it!=_imgItms.end(); it++ ,labeit++, i++)
		{
			if ( i != _imgItms.size() - 1 )
			{
				continue;
			}
			int x=0, y=0;
			this->_getItmPos(i, x, y);

			QGraphicsPixmapItem *image = *it;

			image->setPos(x, y);

			//label = scene->addText(location);
			//label->setPos(QPointF(x, y) + labelOffset);
			QGraphicsTextItem *label = *labeit;
			QPointF labelOffset((_imgsizex - label->boundingRect().width()) / 2-5, height4img  );
			label->setPos(QPointF(x,y) + labelOffset);

		}
	}

	QSize scenesize;
	this->_getSceneSize(scenesize);


	scene->setSceneRect(0, 0, scenesize.width(), scenesize.height());
	scene->update();

}

bool PictureView::_getSceneSize(QSize &size)
{
	QRect rect = this->geometry();
	int cntinrow = rect.width() * 1.0/(_imgsizex + _imgmarginx);
	if ( cntinrow == 0 )
	{
		cntinrow++;
	}


	int rows = _imgItms.size()/cntinrow;
	if ( _imgItms.size()%cntinrow) rows++;
	size.setWidth(rect.width());
	int height = rows * ((_imgsizey + _imgmarginy));
	if ( height < rect.height() )
	{
		height = rect.height() - 10;
	}
	size.setHeight(height);

	return true;
}


void PictureView::resizeEvent(QResizeEvent *)
{
	updateView();
}


void PictureView::clear()
{
	//
	list<QGraphicsPixmapItem *>::iterator it;
	list<QGraphicsTextItem *>::iterator labeit;
	int i=0;
	for(it=_imgItms.begin(), labeit=_labels.begin(); it!=_imgItms.end(); it++ ,labeit++, i++)
	{
		//int imgcnt = _imgItms.size();

		QGraphicsPixmapItem *image = *it;
		this->scene->removeItem(image);
		delete image;
		QGraphicsTextItem *label = *labeit;
		this->scene->removeItem(label);
		delete label;
	}

	_imgItms.clear();
	_labels.clear();


	QRect rect = this->geometry();
	scene->setSceneRect(0, 0, rect.width(), rect.height());
}

void PictureView::subscribeItmDbClick(PItmDbClickCallBakFunc callback, void *context)
{
	_itmdbclickCallback = callback;
	_itmdbclickcontext = context;
}

void PictureView::OnDbClickItm(PictureViewItm *itm)
{
	QString info;
	itm->getInfo(info);
	if ( _itmdbclickCallback )
	{
		(*_itmdbclickCallback)(this->_itmdbclickcontext, info);
	}
}


//! [0]
PictureViewItm::PictureViewItm(PictureView *view,const QPixmap &pixmap,QSize itmsize,bool showframe, QGraphicsItem *parent,
                     QGraphicsScene *scene)
    : _pixmap(pixmap), QGraphicsPixmapItem(pixmap, parent, scene),
	_selected(false), _size(itmsize), _showframe(showframe), _view(view)
{
	_imgmarginx = IMG_X_MARGIN;
	_imgmarginy = IMG_Y_MARGIN;

	_updateImg();


	setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptedMouseButtons(Qt::LeftButton);

    setAcceptsHoverEvents(true);
}
//! [0]

void PictureViewItm::setImgMargin(int marginx, int marginy)
{
	_imgmarginx = marginx;
	_imgmarginy = marginy;
}



//#define IMG_SIZE	200
void PictureViewItm::_updateImg()
{
	
	QRect imgRect = _pixmap.rect();
	

	QBrush brush;
	if ( this->_selected )
	{
		QPixmap tempPixmap(_size.width(),_size.height());
		QPainter painter;

		painter.begin(&tempPixmap);
		QColor color;
		if ( 0 )
		{
			color = QColor(qRgb(0,162,232));
		}
		else
		{
			color = Qt::lightGray;
		}
		QRect rcselection = tempPixmap.rect();
		painter.fillRect(tempPixmap.rect(), color);
		int xoff = 0,yoff= 0;
		if ( imgRect.width()*1.0/imgRect.height() > _size.width()*1.0/_size.height() )
		{
			//
			yoff = (_size.height()-imgRect.height())/2;
			xoff = _imgmarginx/2;
		}
		else
		{
			xoff = (_size.width()-imgRect.width())/2;
			yoff = _imgmarginy/2;
		}

		imgRect.adjust(xoff, yoff, xoff, yoff);
		painter.drawPixmap(imgRect,_pixmap);
		painter.end();

		setPixmap(tempPixmap);
	}
	else
	{
		QPixmap tempPixmap(_size.width(),_size.height());
		QPainter painter;

		painter.begin(&tempPixmap);
		//color = QColor(qRgb(255,255,255));
		//brush.setTextureImage(QImage("Resources/images/imgitmbackground.png"));
		//painter.fillRect(tempPixmap.rect(),brush);
		QColor color;
		color = QColor(qRgb(255,255,255));
		painter.fillRect(tempPixmap.rect(), color);
		int xoff = 0,yoff= 0;
		if ( imgRect.width()*1.0/imgRect.height() > _size.width()*1.0/_size.height() )
		{
			//
			yoff = (_size.height()-imgRect.height())/2;
			xoff = _imgmarginx/2;
		}
		else
		{
			xoff = (_size.width()-imgRect.width())/2;
			yoff = _imgmarginy/2;
		}

		imgRect.adjust(xoff, yoff, xoff, yoff);
		painter.drawPixmap(imgRect,_pixmap);


		// dray a rect around it
		if ( _showframe )
		{
			QPen pen;
			pen.setColor(QColor(Qt::gray));
			pen.setWidth(2);
			painter.setPen(pen);
			QRect rc = tempPixmap.rect();
			rc.adjust(5, 5, -5, -5);
			painter.drawRect(rc);
		}

		painter.end();

		setPixmap(tempPixmap);

	}
//#define _imgmarginx 20
//#define _imgmarginy 20


}

//! [1]
#if 0
void PictureViewItm::hoverEnterEvent(QGraphicsSceneHoverEvent * /*event*/)
{
	 if ( this->isSelected() || !_enablescale  )
	 {
		 return ;
	 }
    timeLine.setDirection(QTimeLine::Forward);

    if (z != 1.0) {
        z = 1.0;
        updateItemPosition();
    }

    if (timeLine.state() == QTimeLine::NotRunning)
        timeLine.start();
}
//! [1]

//! [2]
void PictureViewItm::hoverLeaveEvent(QGraphicsSceneHoverEvent * /*event*/)
{
	 if ( this->isSelected()  || !_enablescale )
	 {
		 return ;
	 }
    timeLine.setDirection(QTimeLine::Backward);
    if (z != 0.0)
        z = 0.0;

    if (timeLine.state() == QTimeLine::NotRunning)
        timeLine.start();
}
//! [2]

#endif


void PictureViewItm::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if ( this->isSelected() != this->_selected )
	{
		_selected = isSelected();
		this->_updateImg();
	}
	if ( _selected )
	{
		update();
	}
	int x = pos().rx();
	int y = pos().ry();
	//painter->drawPixmap(QRect(x, y, _size.width(), _size.height()),pixmap());
	QStyleOptionGraphicsItem opt = *option;
	opt.state &= ~QStyle::State_Selected;
	QGraphicsPixmapItem::paint(painter, &opt, widget);
}


void PictureViewItm::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
	QGraphicsPixmapItem::mousePressEvent(event);
    setCursor(Qt::ClosedHandCursor);
}

void PictureViewItm::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event )
{
	QGraphicsPixmapItem::mouseDoubleClickEvent(event);

	// call view the event
	if ( _view )
	{
		_view->OnDbClickItm(this);
	}

}



void PictureViewItm::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsPixmapItem::mouseMoveEvent(event);

	if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }


    QDrag *drag = new QDrag(event->widget());

	drag->setPixmap(this->pixmap().scaled(30, 40));
	drag->setHotSpot(QPoint(15, 30));


    QMimeData *mime = new QMimeData;
	if ( _info.length() )
	{
		mime->setText(_info);
	}
	else
	{
		mime->setText("Resources/images/splash2.jpg");
	}
	mime->setData("srcloc", "filelistview");
    drag->setMimeData(mime);

	drag->exec();

	setCursor(Qt::OpenHandCursor);
}
//! [8]

//! [4]
void PictureViewItm::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
    setCursor(Qt::OpenHandCursor);
}
//! [4]


