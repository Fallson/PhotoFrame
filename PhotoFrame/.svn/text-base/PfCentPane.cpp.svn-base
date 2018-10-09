#include "PfCentPane.h"
#include "PfPhotoEditView.h"
#include "photoframe.h"


extern QString gres;

PfCentPane::PfCentPane(PhotoFrame * parent): QLabel(parent),_pframe(parent),
	_framepicselview(NULL), _photosselview(NULL), _photoeditview(NULL)
{
	setStyleSheet(QString("background-image:url(") + gres + "white.png)");

	_framepicselview = new FolderPicPreview(this);
	_framepicselview->setImgSize(220,235);
	//_framepicselview->showImgPath(false);
	//_framepicselview->skipUsingJpgPreview(true);
	//_framepicselview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	_framepicselview->subscribeItmDbClick(this->_StyleSelChanged, this);

	_photosselview = new  FolderPicPreview(this);
	_photosselview->subscribeItmDbClick(this->_PhotoSelChanged, this);
	_photosselview->hide();

    _photoeditview = new PfPhotoEditView(_pframe, this);
	_photoeditview->hide();
	_framepicselview->hide();
}

PfCentPane::~PfCentPane(void)
{
}


void PfCentPane::resizeEvent(QResizeEvent *)
{
	//
	QRect rc = this->geometry();
        qDebug() << "The centPane rect" << rc;
	rc.adjust(-rc.left(), -rc.top(), -rc.left(),-rc.top());
	if ( _framepicselview )
	_framepicselview->setGeometry(rc);
	if ( _photosselview )
	_photosselview->setGeometry(rc);
	if ( _photoeditview )
	_photoeditview->setGeometry(rc);

}

void PfCentPane::paintEvent(QPaintEvent *ev)
{
	QLabel::paintEvent(ev);
}

void PfCentPane::showFramePath(const QString &framepicpath)
{
	if ( _photoeditview )
	{
		this->_photoeditview->hide();
	}
	if ( _photosselview )
	{
		this->_photosselview->hide();
	}
	if ( _framepicselview )
	{
		_framepicselview->show();
		_framepicselview->showFolder(framepicpath);
	}
}


void PfCentPane::showPhotos(const QString &photopath)
{
	if ( _photoeditview )
	{
		this->_photoeditview->hide();
	}
	if ( _framepicselview )
	{
		this->_framepicselview->hide();
	}
	if ( _photosselview )
	{
		_photosselview->show();
		_photosselview->showFolder(photopath);
	}

}

void PfCentPane::updateFrameStyle(const QString &framepicpath)
{
	//
	if ( _photoeditview )
	{
		_photoeditview->updateFrameStyle(framepicpath);
		_photoeditview->show();
	}
	if ( _framepicselview )
	{
		_framepicselview->hide();
	}
	if ( _photosselview )
	{
		_photosselview->hide();
	}
}

void PfCentPane::updatePhoto(const QString &photopath)
{
	_photoeditview->updatePhoto(photopath);

	_photoeditview->show();
	_framepicselview->hide();
	_photosselview->hide();
}

void PfCentPane::rotatePhoto(int angel)
{
	if ( _photoeditview )
	{
		_photoeditview->rotatePhoto(angel);
		_photoeditview->show();
	}
	if ( _framepicselview )
	{
		_framepicselview->hide();
	}
	if ( _photosselview )
	{
		_photosselview->hide();
	}
}

void PfCentPane::zoomPhoto(qreal scale)
{
	if ( _photoeditview )
	{
		_photoeditview->zoomPhoto(scale);
		_photoeditview->show();
	}
	if ( _framepicselview )
	{
		_framepicselview->hide();
	}
	if ( _photosselview )
	{
		_photosselview->hide();
	}
}


bool PfCentPane::_StyleSelChanged(void *context, const QString &picpath)
{
	PfCentPane *pThis = (PfCentPane*)context;
	if ( !pThis )
	{
		return false;
	}
	pThis->_pframe->OnSelPhotoFrameStyle(picpath);
	return true;
}

bool PfCentPane::_PhotoSelChanged(void *context, const QString &picpath)
{
	PfCentPane *pThis = (PfCentPane*)context;
	if ( !pThis )
	{
		return false;
	}
	pThis->_pframe->OnSelPhoto(picpath);
	return true;
}

void PfCentPane::addTextBox()
{
	if ( _photoeditview )
	_photoeditview->addTextBox();
}

void PfCentPane::setTextCnt(const QString &cnt)
{
	if ( _photoeditview )
	_photoeditview->setTextCnt(cnt);
}

void PfCentPane::alignText(int align)
{
	if ( _photoeditview )
	_photoeditview->alignText(align);

}
void PfCentPane::valignText(int align)
{
	if ( _photoeditview )
	_photoeditview->valignText(align);
}


void PfCentPane::resizeTextBox(const QRectF &rc)
{
	if ( _photoeditview )
	_photoeditview->resizeTextBox(rc);
}
void PfCentPane::mvTextBox(const QRectF &rc)
{
	if ( _photoeditview )
	_photoeditview->mvTextBox(rc);
}

void PfCentPane::rotateTextBox(const QRectF &rc, qreal rotate)
{
	if ( _photoeditview )
	_photoeditview->rotateTextBox(rc, rotate);
}

void PfCentPane::setTxtShadow(bool shadow)
{
	if ( _photoeditview )
	_photoeditview->setTxtShadow(shadow);
}

void PfCentPane::delSel()
{
	if ( _photoeditview )
	_photoeditview->delSel();

}

void PfCentPane::updateEditView(bool reload)
{
	if ( _photoeditview )
	{
		this->_photoeditview->updateView(reload);
		_photoeditview->show();
	}
	if ( _framepicselview )
	{
		_framepicselview->hide();
	}
	if ( _photosselview )
	{
		_photosselview->hide();
	}
}
