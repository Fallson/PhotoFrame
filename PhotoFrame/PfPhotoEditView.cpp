#include <QtGui>
#include "PfPhotoEditView.h"
#include "PFPhotoEditScene.h"
#include "photoframe.h"

PfPhotoEditView::PfPhotoEditView(PhotoFrame* pMainFrame, QWidget * parent):
    _pMainFrame(pMainFrame), QGraphicsView(parent)
{
	setStyleSheet( "QGraphicsView { border-style: none; }" );

    QRect rect = this->geometry();
    qDebug() << "The view's rect is" << rect;
    setScene(new PFPhotoEditScene(rect,pMainFrame,this));
}

PfPhotoEditView::~PfPhotoEditView(void)
{
}


void PfPhotoEditView::updateFrameStyle(const QString &framepicpath)
{
	PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
	if ( !scene )
	{
		return ;
	}
	scene->updateFrameStyle(framepicpath);


}

void PfPhotoEditView::updatePhoto(const QString &photopath)
{
	PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
	if ( !scene )
	{
		return ;
	}
	scene->updatePhoto(photopath);
}


void PfPhotoEditView::rotatePhoto(int angel)
{
	PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
	if ( !scene )
	{
		return ;
	}

	scene->rotatePhoto(angel);
}

void PfPhotoEditView::zoomPhoto(qreal scale)
{
	PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
	if ( !scene )
	{
		return ;
	}
	scene->zoomPhoto(scale);
}



void PfPhotoEditView::addTextBox()
{
	PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
	if ( !scene )
	{
		return ;
	}
	scene->addTextBox();
}

void PfPhotoEditView::enableTextShadow(bool shadow)
{
	PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
	if ( !scene )
	{
		return ;
	}
	scene->enableTextShadow(shadow);
}

void PfPhotoEditView::alignText(int align)
{
	PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
	if ( !scene )
	{
		return ;
	}
	scene->alignText(align);
}

void PfPhotoEditView::valignText(int align)
{
	PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
	if ( !scene )
	{
		return ;
	}
	scene->valignText(align);
}

void PfPhotoEditView::setTextCnt(const QString &cnt)
{
	PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
	if ( !scene )
	{
		return ;
	}
	scene->setTextCnt(cnt);
}

void PfPhotoEditView::resizeTextBox(const QRectF &rc)
{
	PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
	if ( !scene )
	{
		return ;
	}
	scene->resizeTextBox(rc);
}

void PfPhotoEditView::mvTextBox(const QRectF &rc)
{
	PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
	if ( !scene )
	{
		return ;
	}
	scene->mvTextBox(rc);
}

void PfPhotoEditView::rotateTextBox(const QRectF &rc, qreal rotate)
{
	PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
	if ( !scene )
	{
		return ;
	}
	scene->rotateTextBox(rc,rotate);
}

void PfPhotoEditView:: setTxtShadow(bool shadow)
{
	PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
	if ( !scene )
	{
		return ;
	}
	scene->setTxtShadow(shadow);
}

void PfPhotoEditView::delSel()
{
	//
	PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
	if ( !scene )
	{
		return ;
	}
	scene->delSel();
}

void PfPhotoEditView::resizeEvent(QResizeEvent *)
{
    QRect rect = this->geometry();

    PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
    if ( !scene )
    {
            return ;
    }
	rect.adjust(-rect.left()+5, -rect.top()+15, -rect.left()-5, -rect.top()-15);
    scene->resize(rect);

	dynamic_cast<PFPhotoEditScene *>(this->scene())->updateScene(false);

}


void PfPhotoEditView::updateView(bool reload)
{
    PFPhotoEditScene *scene = dynamic_cast<PFPhotoEditScene *>(this->scene());
    if ( !scene )
    {
            return ;
    }

	dynamic_cast<PFPhotoEditScene *>(this->scene())->updateScene(reload);

}
