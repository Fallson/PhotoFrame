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

#ifndef PictureView_H
#define PictureView_H

#include <QtGui/qgraphicsView.h>
#include <list>

#include <QtCore>
#include <QtGui/QGraphicsPixmapItem>


using namespace std;

class PictureViewItm;

typedef  bool (*PItmDbClickCallBakFunc)(void *context, const QString &picpath);

//! [0]
class PictureView : public QGraphicsView
{
    Q_OBJECT

public:
    PictureView(QWidget *parent = 0);

public:
	void showImgPath(bool show) {_showtxt = show;}
	void setImgSize(int width, int height);
	void setImgMargin(int marginx, int marginy);

	void clear();
	void addItem(const QString &imgpath, const QString &label, const QString &info);
	void addItem(const QPixmap &img, const QString &label,const QString &info);

	bool enableItmScale(bool enablescale){ return _enablescale = enablescale;}

	void updateView(bool full = true);

	void subscribeItmDbClick(PItmDbClickCallBakFunc callback, void *context);

	void setShowItmFrame(bool show){_showframe = show;}

public:
	void OnDbClickItm(PictureViewItm *itm);

private:
	bool _getItmPos(int index, int &x, int &y);
	bool _getSceneSize(QSize &size);
protected:
    void mouseReleaseEvent(QMouseEvent *event);
	//virtual void mousePressEvent ( QMouseEvent * event  );

protected:
    virtual void resizeEvent(QResizeEvent *);

//! [0]

//! [1]
private slots:
    //void updateImage(int id, const QString &fileName);
//! [1]

//! [2]
private:
	/*
    InformationWindow* findWindow(int id);
    void showInformation(PictureViewItm *image);
	*/

    QGraphicsScene *scene;
	/*
    QList<InformationWindow *> informationWindows;
//! [2] //! [3]
    QSqlRelationalTableModel *officeTable;
	*/

	list<QGraphicsPixmapItem *>  _imgItms;
	list<QGraphicsTextItem *> _labels;
	bool _enablescale;
	bool _showframe;


	int _imgsizex;
	int _imgsizey;
	//int _imgscalesizex;
	//int _imgscalesizey;

	int _imgmarginx;
	int _imgmarginy;

	PItmDbClickCallBakFunc _itmdbclickCallback;
	void *_itmdbclickcontext;

	bool _showtxt;
};
//! [3]



//! [0]
class PictureViewItm : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
	void setInfo(const QString &info){_info = info;}
	void getInfo(QString &info){info=_info;}
	void setImgMargin(int marginx, int marginy);

public:
    PictureViewItm(PictureView *view, const QPixmap &pixmap,QSize itmsize,bool showframe, QGraphicsItem *parent = 0,
              QGraphicsScene *scene = 0);
	void setShowFrame(bool show){_showframe = show;}

public:
	virtual void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

protected:
    //void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    //void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

	virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );
private slots:
    //void updateItemPosition();

private:
	void _updateImg();
private:
	bool _selected;

	QSize _size;
	QPixmap _pixmap;
	QString _info;
	bool _showframe;

	int _imgmarginx;
	int _imgmarginy;

	PictureView *_view;
};
//! [0]


#endif
