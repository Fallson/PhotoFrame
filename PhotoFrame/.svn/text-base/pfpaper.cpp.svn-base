#include "PfPaper.h"
#include "photoframedoc.h"
#include <QColorDialog>


extern QString gbires;


PmPageItm::PmPageItm(QObject *parent): 
QObject(parent), _paper(NULL),_photoitm(NULL),
	_angel(0),_ratio(1),_imglefttop(-1,-1)
{
}

PmPageItm::PmPageItm(PmPageItm &pageitm)
{
	_paper = NULL;

	// image
	_frampath = pageitm._frampath;
	_photocnt = pageitm._photocnt;
	_angel = pageitm._angel;
	_ratio = pageitm._ratio;
	_imglefttop = pageitm._imglefttop;

}


PmPageItm::~PmPageItm()
{
}


bool PmPageItm::setFramePath(const QString &framepath)
{
	this->_frampath = framepath;
	return true;
}

bool PmPageItm::getFramePath(QString &framepath)
{
	framepath = _frampath;
	return true;
}

	// for image
bool PmPageItm::getPhotoPath(QString &photopath)
{
	photopath = _photocnt;
	return true;
}

bool PmPageItm::setPhotoPath(const QString &photopath)
{
	_photocnt = photopath;
	return true;
}


bool PmPageItm::setRotate(int angel)
{
	_angel = angel;
	return true;
}
bool PmPageItm::getRotate(int &angel)
{
	angel = _angel;
	return true;
}
bool PmPageItm::setZoom(qreal value)
{
	_ratio = value;
	return true;
}

bool PmPageItm::getZoom(qreal &value)
{
	value = _ratio;
	return true;
}



PmTextItm::PmTextItm(QObject *parent):_pPage(NULL),
	_aligntype(ALIGN_TOP|ALIGN_LEFT),_shadow(true), _viewitm(NULL),
	_scale(1), _rotate(0)
{
	_lastbacktime = QDateTime::currentDateTime();
}

PmTextItm::PmTextItm(PmTextItm &txtitm)
{
	_layoutbox = txtitm._layoutbox;
	_pPage = NULL; // set later

	_cnt = txtitm._cnt;
	_scale = txtitm._scale;
	_rotate = txtitm._rotate;
	_shadow = txtitm._shadow;
	_aligntype = txtitm._aligntype;

	_viewitm = NULL;  // will be set when show the item in ui

}



PhotoFramePaper::PhotoFramePaper(QObject *parent)
	: QObject(parent)
{
	// current, only one item
	PmPageItm *pageitm = new PmPageItm(this);
	_pagepicitmlst.push_back(pageitm);
}

PhotoFramePaper::PhotoFramePaper(PhotoFramePaper &srcpage)
{
	QList<PmPageItm *>::iterator it;
	for (it=srcpage._pagepicitmlst.begin(); it!=srcpage._pagepicitmlst.end(); it++ )
	{
		PmPageItm *pageitm = new PmPageItm(**it);
		pageitm->setPaper(this);
		_pagepicitmlst.push_back(pageitm);
	}

	//return true;
}

PhotoFramePaper::~PhotoFramePaper()
{

}


bool PhotoFramePaper::getPicItms(QList<PmPageItm*> &picitmlst)
{
	picitmlst = _pagepicitmlst;
	return true;
}

bool PhotoFramePaper::setPicItms(const QList<PmPageItm *> &picitmlst)
{
	_pagepicitmlst = picitmlst;
	return true;
}


bool PhotoFramePaper::addTextbox(PmTextItm *pTextItm)
{
	if ( pTextItm )
	{
		pTextItm->setPrintPage(this);
		this->_txtlst.push_back(pTextItm);
	}
	else
	{
		PmTextItm *txtitm = new PmTextItm(this);
		txtitm->setPrintPage(this);

		LayoutBoxPos rect;
		rect.x = 0.1;
		rect.y = 0.5;
		rect.width = 0.5;
		rect.height = 0.05;
		txtitm->setRectInPrintPage(rect);
		_txtlst.push_back(txtitm);
	}

	return true;
}


bool PhotoFramePaper::getTextbox(QList<PmTextItm *> &txtlst)
{

	if ( !_txtlst.size() )
	{
		return false;
	}

	txtlst = _txtlst;
	return true;
}

bool PhotoFramePaper::delTextbox(PmTextItm *pTextItm)
{
	QList<PmTextItm *>::iterator it;
	for ( it=_txtlst.begin(); it!=_txtlst.end(); it++ )
	{
		if ( *it == pTextItm )
		{
			_txtlst.erase(it);
			delete pTextItm;
			break;
		}

	}

	return true;
}



