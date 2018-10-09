#include <QtGui>
#include "PFPhotoEditScene.h"
#include "photoframe.h"
#include "PFPhotoEditViewItem.h"

#define PRINT_PREFERED_HEIGHT	800

PFPhotoEditScene::PFPhotoEditScene(const QRectF& rect,  PhotoFrame *pMainFrame, QObject *parent)
    : QGraphicsScene(parent),_editframe(NULL), 
      _pMainFrame(pMainFrame), _txtviewitm(NULL),_pViewItm(NULL)
{
    qDebug() << "scene rect is" << rect;

    setSceneRect(rect);
    setBackgroundBrush(Qt::white);
    setItemIndexMethod(NoIndex);
    //addItem(new PFPhotoEditViewItem(QRectF(0,0,rect.width(),rect.height()), pMainFrame));
	updateScene(true);
}

void PFPhotoEditScene::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
	QGraphicsScene::mousePressEvent(mouseEvent);
	if (this->selectedItems().size() == 0)
	{
		selectItm(NULL, NULL);
	}
}


void PFPhotoEditScene::updateScene(bool bReload)
{
	PmPhotoFrameDoc *pdoc = this->_pMainFrame->getdoc();
	if ( !pdoc )
	{
		return;
	}
	PhotoFramePaper *paper = pdoc->getpaper();
	if ( !paper )
	{
		return ;
	}

	PF_PROJ_PROPS proj;
	pdoc->getProjProps(proj);

	if ( bReload )
	{
		// reload
		this->clear();
		this->_editframe = NULL;
		_loadPaper(paper);
	}

	// update position
	QRectF scrc = this->sceneRect();
	QRectF paperrc = scrc;
	if ( proj.papersize == PF_PROJ_PROPS::A3 )
	{
		//11.69 X 16.54
		if ( scrc.width()/scrc.height() > 1296/1575 )
		{
			//too wider, calculate width according height
			qreal width = scrc.height() * 1296/1575;
			paperrc.setLeft((scrc.width()-width)/2);
			paperrc.setRight((scrc.width()-width)/2+width);
		}
		else
		{
			// too narrow, caculate height according width
			qreal height = scrc.width() * 1296/1575;
			paperrc.setTop((scrc.height()-height)/2);
			paperrc.setBottom((scrc.height()-height)/2+height);
		}
	}
	else if ( proj.papersize == PF_PROJ_PROPS::A4)
	{
		//8.27X11.69
		if ( scrc.width()/scrc.height() > 8.27/11.69 )
		{
			//too wider, calculate width according height
			qreal width = scrc.height() * 8.27/11.69;
			paperrc.setLeft((scrc.width()-width)/2);
			paperrc.setRight((scrc.width()-width)/2+width);
		}
		else
		{
			// too narrow, caculate height according width
			qreal height = scrc.width() * 11.69/8.27;
			paperrc.setTop((scrc.height()-height)/2);
			paperrc.setBottom((scrc.height()-height)/2+height);
		}
	}

	_paperrc = paperrc;



	//
	QList<PmPageItm *> picitmlst;
	paper->getPicItms(picitmlst);
	// current should be only one
	if ( picitmlst.size() != 1 )
	{
		return ;
	}
	PmPageItm *pageitm = picitmlst.first();
	PFPhotoEditViewItem *viewitm = (PFPhotoEditViewItem *)pageitm->getViewItm();
	if ( viewitm )
	{

		viewitm->setX(paperrc.left());
		viewitm->setY(paperrc.top());
        viewitm->resize(paperrc);
	}

	QList<PmTextItm *> txtlst;
	paper->getTextbox(txtlst);
	QList<PmTextItm *>::iterator it;
	for ( it=txtlst.begin(); it!=txtlst.end(); it++ )
	{
		PmTextItm *pTextItm = *it;

		LayoutBoxPos itmpos;
		pTextItm->getRectInPrintPage(itmpos);

		QRectF paperpagerect = this->_paperrc;
		qreal papaerpagexoff = paperpagerect.left();
		qreal papaerpageyoff = paperpagerect.top();
		qreal height = paperpagerect.height();
		qreal width = paperpagerect.width();


		QRectF textrect;
		textrect = QRectF(papaerpagexoff + width*itmpos.x, 
			papaerpageyoff + height*itmpos.y, 
			itmpos.width*_paperrc.width(),
			itmpos.height*_paperrc.height());

		TextViewItem* txtviewitm = (TextViewItem*)pTextItm->getViewItm();
		txtviewitm->setPos(int(textrect.left()),(int)(textrect.top()));
		txtviewitm->setWidthHeight(textrect.width(), textrect.height());
		txtviewitm->reload();
		txtviewitm->setFontViewRatio(_paperrc.height()/PRINT_PREFERED_HEIGHT);
		//txtviewitm->rrotate(pTextItm->getRotate());
	}

	if ( dynamic_cast<QGraphicsRectItem*>(this->_editframe) )
	{
		dynamic_cast<QGraphicsRectItem*>(this->_editframe)->setRect(_paperrc.adjusted(-1,-1,0,0));
	}
	update();
}

void PFPhotoEditScene::_updatePaper(PhotoFramePaper *paper)
{
	//
}


void PFPhotoEditScene::_loadPaper(PhotoFramePaper *paper)
{
	//
	if ( !paper )
	{
		// 
		return ;
	}
	QList<PmPageItm *> picitmlst;
	paper->getPicItms(picitmlst);
	// current should be only one
	if ( picitmlst.size() != 1 )
	{
		return ;
	}
	PmPageItm *pageitm = picitmlst.first();
        PFPhotoEditViewItem *viewitm  = new PFPhotoEditViewItem(false, this->_pMainFrame);
	viewitm->setPageItm(pageitm);
	pageitm->setViewItm(viewitm);
	viewitm->reload();
    viewitm->update();
	this->addItem(viewitm);
	viewitm->setZValue(1);

	QList<PmTextItm *> txtlst;
	paper->getTextbox(txtlst);
	QList<PmTextItm *>::iterator txtit;
	for ( txtit = txtlst.begin(); txtit!=txtlst.end(); txtit++ )
	{
		TextViewItem *txtviewitm = new TextViewItem(_isPrintScene(),this->_pMainFrame);
		txtviewitm->setTextItm(*txtit);
		(*txtit)->setViewItm(txtviewitm);
		this->addItem(txtviewitm);
		txtviewitm->reload();
		txtviewitm->setZValue(2);
	}

	QGraphicsRectItem *prcitm = new QGraphicsRectItem(NULL);
	_editframe = prcitm;
	prcitm->setBrush(Qt::white);
	prcitm->setPen(QPen(Qt::lightGray));

	QGraphicsDropShadowEffect* gdse =  (QGraphicsDropShadowEffect*)_editframe->graphicsEffect();
	if( gdse == 0 )
	{
		gdse = new QGraphicsDropShadowEffect(NULL);
		gdse->setOffset(3.5, 3.5);
		gdse->setBlurRadius(10);
		_editframe->setGraphicsEffect(gdse);
	}
	this->addItem(_editframe);
	_editframe->setZValue(0);

}


void PFPhotoEditScene::updateFrameStyle(const QString &framepicpath)
{
	PhotoFramePaper *paper = this->_pMainFrame->getdoc()->getpaper();
	if ( !paper )
	{
		return ;
	}
	QList<PmPageItm *> picitmlst;
	paper->getPicItms(picitmlst);
	if ( picitmlst.size() == 0 )
	{
		return ;
	}

	PFPhotoEditViewItem* pfitm = (PFPhotoEditViewItem*)picitmlst[0]->getViewItm();
	if ( !pfitm )
	{
		return ;
	}
	PmPageItm* pageitm = pfitm->getPageItm();
	if ( !pageitm )
	{
		return ;
	}
	pageitm->setFramePath(framepicpath);
    pfitm->setFrame(framepicpath);
    pfitm->update();
	update();
	this->updateScene(false);
}

void PFPhotoEditScene::updatePhoto(const QString &photopath)
{
	PhotoFramePaper *paper = this->_pMainFrame->getdoc()->getpaper();
	if ( !paper )
	{
		return ;
	}
	QList<PmPageItm *> picitmlst;
	paper->getPicItms(picitmlst);
	if ( picitmlst.size() == 0 )
	{
		return ;
	}

	PFPhotoEditViewItem* pfitm = (PFPhotoEditViewItem*)picitmlst[0]->getViewItm();
	if ( !pfitm )
	{
		return ;
	}
	PmPageItm* pageitm = pfitm->getPageItm();
	if ( !pageitm )
	{
		return ;
	}
	pageitm->clearImgLeftTop();
	pageitm->setPhotoPath(photopath);
	pfitm->setBGPic(photopath);
    pfitm->update();
	update();
	//this->updateScene(false);
   // pfitm->setBGPic(photopath);
}


void PFPhotoEditScene::rotatePhoto(int angel)
{
	PhotoFramePaper *paper = this->_pMainFrame->getdoc()->getpaper();
	QList<PmPageItm *> picitmlst;
	paper->getPicItms(picitmlst);
	if ( picitmlst.size() == 0 )
	{
		return ;
	}


	PmPageItm* pageitm = picitmlst[0];
	if ( !pageitm )
	{
		return ;
	}
	PFPhotoEditViewItem* pfitm = (PFPhotoEditViewItem*)pageitm->getViewItm();
	if ( !pfitm )
	{
		return ;
	}
	int oldangel = 0;
	pageitm->getRotate(oldangel);
	pageitm->setRotate(oldangel+angel);
        pfitm->rotate(oldangel+angel);
    pfitm->update();
	update();
}

void PFPhotoEditScene::zoomPhoto(qreal scale)
{
  	PhotoFramePaper *paper = this->_pMainFrame->getdoc()->getpaper();
	QList<PmPageItm *> picitmlst;
	paper->getPicItms(picitmlst);
	if ( picitmlst.size() == 0 )
	{
		return ;
	}


	PmPageItm* pageitm = picitmlst[0];
	if ( !pageitm )
	{
		return ;
	}
	PFPhotoEditViewItem* pfitm = (PFPhotoEditViewItem*)pageitm->getViewItm();
	if ( !pfitm )
	{
		return ;
	}
	QSizeF photosize;
	pfitm->getScaledPhotoSize(photosize);
	qreal oldscale;
	pageitm->getZoom(oldscale);
	if ( ((photosize.width() < 50 || photosize.height() < 50) && scale < oldscale) ||
		photosize.width()*scale/oldscale < 50 || photosize.height()*scale/oldscale < 50)
	{
		// no need to scale anymore
		return ;
	}
	QPointF photocenter;
	pfitm->savePhotoCenter(photocenter);
	pageitm->setZoom(scale);
	pfitm->restorePhotoCenter(photocenter);
	QPointF newphotocenter;
	pfitm->savePhotoCenter(newphotocenter);
	if ( fabs(newphotocenter.rx()-photocenter.rx() ) > 0.01 ||
		 fabs(newphotocenter.ry()-photocenter.ry() ) > 0.01 )
	{
		int err = 1;
	}

    pfitm->scale(scale);

    pfitm->update();
	update();

}



void PFPhotoEditScene::addTextBox()
{
	PhotoFramePaper *pPringPaperPage = this->_pMainFrame->getdoc()->getpaper();

	int index = 0;
	pPringPaperPage->addTextbox();


	QList<PmTextItm *> txtitmlst;
	pPringPaperPage->getTextbox(txtitmlst);
	if ( !txtitmlst.size() )
	{
		return ;
	}


	PmTextItm *pTextItm = txtitmlst.last();
	_addTextBox(pTextItm);

	this->update();
}


#define PRINT_PREFERED_HEIGHT	800


void PFPhotoEditScene::_addTextBox(PmTextItm *pTextItm)
{
	LayoutBoxPos itmpos;
	pTextItm->getRectInPrintPage(itmpos);

	QRectF paperpagerect = _paperrc;
	qreal papaerpagexoff = paperpagerect.left();
	qreal papaerpageyoff = paperpagerect.top();
	qreal height = paperpagerect.height();
	qreal width = paperpagerect.width();


	QRectF textrect = QRectF(papaerpagexoff + width*itmpos.x+itmpos.margin.left, 
		papaerpageyoff + height*itmpos.y+itmpos.margin.top, 
		width*itmpos.width-itmpos.margin.left-itmpos.margin.right,
		height*itmpos.height-itmpos.margin.top-itmpos.margin.bottom);

	TextViewItem* txtviewitm = new TextViewItem(this->_isPrintScene(), _pMainFrame,NULL);
	txtviewitm->setTextItm(pTextItm);
	pTextItm->setViewItm(txtviewitm);
	QString cnt;
	pTextItm->getContent(cnt);
	txtviewitm->setText(cnt);
	txtviewitm->setShadow(pTextItm->isShadowEnable());
	this->addItem(txtviewitm);
	QRectF scrc = this->sceneRect();
	txtviewitm->setFontViewRatio(_paperrc.height()/PRINT_PREFERED_HEIGHT);
	txtviewitm->setPos(int(textrect.left()),(int)(textrect.top()));
	txtviewitm->setZValue(3);

	this->selectItm(NULL, txtviewitm);

}

void PFPhotoEditScene::enableTextShadow(bool shadow)
{
	if ( !this->_txtviewitm )
	{
		return ;
	}
	PmTextItm *txtitm = _txtviewitm->getTextItm();
	if ( !txtitm )
	{
		return ;
	}
	txtitm->enableShadow(shadow);
	_txtviewitm->setShadow(shadow);

}

void PFPhotoEditScene::alignText(int align)
{
	if ( !this->_txtviewitm )
	{
		return ;
	}
	PmTextItm *txtitm = _txtviewitm->getTextItm();
	if ( !txtitm )
	{
		return ;
	}


	int oldalign = txtitm->getAlign();
	oldalign &= PmTextItm::ALIGN_VMASK;
	oldalign |= align;
	align = oldalign;
	txtitm->setAlign(align);

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
	_txtviewitm->setHorAlignment(haligninview);
	_txtviewitm->update();
	_txtviewitm->scene()->update();
}

void PFPhotoEditScene::valignText(int align)
{
	if ( !this->_txtviewitm )
	{
		return ;
	}
	PmTextItm *txtitm = _txtviewitm->getTextItm();
	if ( !txtitm )
	{
		return ;
	}

	int oldalign = txtitm->getAlign();
	oldalign &= PmTextItm::ALIGN_HMASK;
	align |= oldalign;
	txtitm->setAlign(align);

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
	_txtviewitm->setVerAlignment(verigninview);
	_txtviewitm->update();
	_txtviewitm->scene()->update();
}

void PFPhotoEditScene::setTextCnt(const QString &cnt)
{
	if ( !this->_txtviewitm )
	{
		return ;
	}
	PmTextItm *txtitm = _txtviewitm->getTextItm();
	if ( !txtitm )
	{
		return ;
	}
	txtitm->setContent(cnt);
    _txtviewitm->setText(cnt);
	_txtviewitm->setFontViewRatio(_paperrc.height()/PRINT_PREFERED_HEIGHT);
}

void PFPhotoEditScene::resizeTextBox(const QRectF &rc)
{
	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;

	this->getSelection(pageitm, txtitm);
	if ( !txtitm )
	{
		return ;
	}


	LayoutBoxPos pos;
	txtitm->getRectInPrintPage(pos);
	QRectF rcInScene ;
	
	pos.width = rc.width()*1.0/this->_paperrc.width();
	pos.height = rc.height()*1.0/_paperrc.height();
	pos.y = (rc.top()-this->_paperrc.top())/_paperrc.height();
	pos.x = (rc.left()-_paperrc.left())/_paperrc.width();

	txtitm->setRectInPrintPage(pos);

}

void PFPhotoEditScene::mvTextBox(const QRectF &rc)
{
	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;

	this->getSelection(pageitm, txtitm);
	if ( !txtitm )
	{
		return ;
	}


	LayoutBoxPos pos;
	txtitm->getRectInPrintPage(pos);
	QRectF rcInScene ;
	
	pos.width = rc.width()*1.0/this->_paperrc.width();
	pos.height = rc.height()*1.0/_paperrc.height();
	pos.y = (rc.top()-this->_paperrc.top())/_paperrc.height();
	pos.x = (rc.left()-_paperrc.left())/_paperrc.width();

	txtitm->setRectInPrintPage(pos);
}
void PFPhotoEditScene::rotateTextBox(const QRectF &rc, qreal rotate)
{
	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;

	this->getSelection(pageitm, txtitm);
	if ( !txtitm )
	{
		return ;
	}


	LayoutBoxPos pos;
	txtitm->getRectInPrintPage(pos);
	QRectF rcInScene ;
	
	pos.width = rc.width()*1.0/this->_paperrc.width();
	pos.height = rc.height()*1.0/_paperrc.height();
	pos.y = (rc.top()-this->_paperrc.top())/_paperrc.height();
	pos.x = (rc.left()-_paperrc.left())/_paperrc.width();

	txtitm->setRectInPrintPage(pos);
	
	qreal angel = 0;
	angel += rotate;
	txtitm->setRotate(angel);
}

void PFPhotoEditScene::setTxtShadow(bool shadow)
{
	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;

	this->getSelection(pageitm, txtitm);
	if ( !txtitm )
	{
		return ;
	}

	txtitm->enableShadow(shadow);
	TextViewItem * txtviewitm = (TextViewItem *)txtitm->getViewItm();
	if ( !txtviewitm )
	{
		return ;
	}
	txtviewitm->setShadow(shadow);
}

void PFPhotoEditScene::delSel()
{
	PmPageItm *pageitm = NULL;
	PmTextItm *txtitm = NULL;

	this->getSelection(pageitm, txtitm);
	if ( !txtitm )
	{
		return ;
	}

	this->removeItem(_txtviewitm);
	delete _txtviewitm;
	_txtviewitm = NULL;

	_pMainFrame->getdoc()->getpaper()->delTextbox(txtitm);

	update();
	_pMainFrame->updateEditUI(NULL, NULL);
}



void PFPhotoEditScene::resize(const QRectF &rect)
{
    setSceneRect(rect);

    updateScene(false);
}


void PFPhotoEditScene::selectItm(PFPhotoEditViewItem *pViewItm, TextViewItem* txtviewitm )
{
	if ( _pViewItm )
	{
		if ( pViewItm == _pViewItm )
		{
			//
			return ;
		}
		_pViewItm->setSelected(false);
		_pViewItm = pViewItm;

		if ( _txtviewitm )
		{
			_txtviewitm->setSelected(false);
			_txtviewitm = NULL;
		}
	}
	else if ( _txtviewitm )
	{
		if ( _txtviewitm == txtviewitm )
		{
			return ;
		}
		_txtviewitm->setSelected(false);
		_txtviewitm = txtviewitm;
		if ( _pViewItm )
		{
			_pViewItm->setSelected(false);
			_pViewItm = NULL;
		}
	}
	else
	{
		_txtviewitm = txtviewitm;
		if ( _txtviewitm )
		{
			_txtviewitm->setSelected(true);
		}
		_pViewItm = pViewItm;
		if ( _pViewItm )
		{
			_pViewItm->setSelected(true);
		}
	}
	this->_pMainFrame->updateEditUI(_pViewItm, _txtviewitm);


	return ;
}


bool PFPhotoEditScene::getSelection(PmPageItm *&pageitm, PmTextItm *&txtitm)
{
	if ( _pViewItm )
	{
		pageitm = this->_pViewItm->getPageItm();
	}
	else
	{
		pageitm = NULL;
	}

	if ( _txtviewitm )
	{
		txtitm = this->_txtviewitm->getTextItm();
	}
	else
	{
		txtitm = NULL;
	}

	return true;
}



// print

PFPhotoPrintScene::PFPhotoPrintScene(const QRectF& rect, PhotoFrame *pMainFrame, QObject *parent):
QGraphicsScene( parent), _pMainFrame(pMainFrame), _xoff(0), _yoff(0)
{
	setSceneRect(rect);

	// i am not sure why we should set this
	// but if we do not set, nothing will be printed
	setBackgroundBrush(Qt::transparent);

}

PFPhotoPrintScene::~PFPhotoPrintScene()
{
}

void PFPhotoPrintScene::_loadPaper()
{
	//
	PmPhotoFrameDoc *pdoc = this->_pMainFrame->getdoc();
	if ( !pdoc )
	{
		return;
	}
	PhotoFramePaper *paper = pdoc->getpaper();
	if ( !paper )
	{
		return ;
	}

	PF_PROJ_PROPS proj;
	pdoc->getProjProps(proj);
	QRectF scrc = this->sceneRect();
	QRectF paperrc = scrc;
	if ( fabs(_xoff) > 0.00001 || fabs(_yoff) > 0.0001 )
	{
		qreal oldwidth = paperrc.width();
		qreal oldheight = paperrc.height();
		paperrc.adjust(oldwidth * _xoff, oldheight * _yoff, oldwidth*_xoff, oldheight * _yoff);
	}
	if ( proj.papersize == PF_PROJ_PROPS::A3 )
	{
		//11.69 X 16.54
		/*
		if ( scrc.width()/scrc.height() > 1296/1575 )
		{
			//too wider, calculate width according height
			qreal width = scrc.height() * 1296/1575;
			paperrc.setLeft((scrc.width()-width)/2);
			paperrc.setRight((scrc.width()-width)/2+width);
		}
		else
		{
			// too narrow, caculate height according width
			qreal height = scrc.width() * 1296/1575;
			paperrc.setTop((scrc.height()-height)/2);
			paperrc.setBottom((scrc.height()-height)/2+height);
		}
		*/
	}
	else if ( proj.papersize == PF_PROJ_PROPS::A4)
	{
		//8.27X11.69
		/*
		if ( scrc.width()/scrc.height() > 8.27/11.69 )
		{
			//too wider, calculate width according height
			qreal width = scrc.height() * 8.27/11.69;
			paperrc.setLeft((scrc.width()-width)/2);
			paperrc.setRight((scrc.width()-width)/2+width);
		}
		else
		{
			// too narrow, caculate height according width
			qreal height = scrc.width() * 11.69/8.27;
			paperrc.setTop((scrc.height()-height)/2);
			paperrc.setBottom((scrc.height()-height)/2+height);
		}
		*/
	}


	QList<PmPageItm *> picitmlst;
	paper->getPicItms(picitmlst);
	// current should be only one
	if ( picitmlst.size() != 1 )
	{
		//return ;
	}
	PmPageItm *pageitm = picitmlst.first();
    PFPhotoEditViewItem *viewitm  = new PFPhotoEditViewItem(true, this->_pMainFrame);
	viewitm->setPageItm(pageitm);
	//pageitm->setViewItm(viewitm);
	viewitm->reload();
	viewitm->update();
	this->addItem(viewitm);
	viewitm->setX(paperrc.left());
	viewitm->setY(paperrc.top());
	viewitm->resize(paperrc);

	QList<PmTextItm *> txtlst;
	paper->getTextbox(txtlst);
	QList<PmTextItm *>::iterator txtit;
	for ( txtit = txtlst.begin(); txtit!=txtlst.end(); txtit++ )
	{
		TextViewItem *txtviewitm = new TextViewItem(_isPrintScene(),this->_pMainFrame);
		txtviewitm->setTextItm(*txtit);
		//(*txtit)->setViewItm(txtviewitm);
		this->addItem(txtviewitm);

		PmTextItm *pTextItm = *txtit;

		LayoutBoxPos itmpos;
		pTextItm->getRectInPrintPage(itmpos);

		QRectF paperpagerect = paperrc;
		qreal papaerpagexoff = paperpagerect.left();
		qreal papaerpageyoff = paperpagerect.top();
		qreal height = paperpagerect.height();
		qreal width = paperpagerect.width();


		QRectF textrect;
		textrect = QRectF(papaerpagexoff + width*itmpos.x, 
			papaerpageyoff + height*itmpos.y, 
			itmpos.width*width,
			itmpos.height*height);

		txtviewitm->setPos(int(textrect.left()),(int)(textrect.top()));
		txtviewitm->setWidthHeight(textrect.width(), textrect.height());
				
		txtviewitm->reload();
		txtviewitm->setFontViewRatio(paperrc.height()/PRINT_PREFERED_HEIGHT);


		//txtviewitm->rotate(pTextItm->getRotate()-txtviewitm->getRotateAngel());
	}
}


void PFPhotoPrintScene::print(QPrinter *printer, QPainter *painter, PRINT_TASK_INFO* printInfo)
{
	_loadPaper();
	this->render(painter);

	delete painter;
	//delete printer;
}

void PFPhotoPrintScene::setprintoff(qreal xoff, qreal yoff)
{
	_xoff = xoff; _yoff = yoff;
	clear();
	this->_loadPaper();
}
