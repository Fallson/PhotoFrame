#include "pfbottomctrlpane.h"
#include "textedit.h"

#include "pfprjctrlpane.h"


MyTabeWidget::MyTabeWidget(QWidget *parent):QTabWidget(parent)
{
}



void MyTabeWidget::resizeEvent ( QResizeEvent * e )
{
	QTabWidget::resizeEvent(e);
	QRectF rect = this->geometry();
	int i=0;
}


void PfBottomCtrlPane::reTranslate()
{
	//_pTabContainer->setTabText(0, tr("Page Preview"));
	_prjctrlpane->reTranslate();
}


extern QString gres;

PfBottomCtrlPane::PfBottomCtrlPane(PhotoFrame *pMainFrame, QWidget *parent)
	: QLabel(parent), _pMainFrame(pMainFrame), _pTextEdit(NULL), _prjctrlpane(NULL)
{

	_prjctrlpane = new PfPrjCtrlPane(pMainFrame, this);
	showEditPane(NON_EDIT);
}

PfBottomCtrlPane::~PfBottomCtrlPane()
{

}


void PfBottomCtrlPane::resizeEvent(QResizeEvent *event)
{
	QRect rect = this->geometry();
	this->setPixmap(QPixmap::fromImage(QImage(gres + "bottompanebg_small.png").scaled(QSize(rect.width(), rect.height()))));

	//_pTabContainer->resize(rect.width(), rect.height());
	_prjctrlpane->resize(rect.width(), rect.height());
	if ( _pTextEdit )
	{
		_pTextEdit->resize(rect.width(), rect.height());
	}
}

bool PfBottomCtrlPane::updateEditPaneInfo()
{
#if 0
	if ( pTextEdit )
	{
		// update text box info
		PmPageItm *pageitm = NULL;
		PmTextItm *txtitm = NULL;
		this->_pMainFrame->getEditView()->getSelection(pageitm, txtitm);
		if ( !txtitm )
		{
			pTextEdit->setContent("");
			return false;
		}
		QString cnt;
		txtitm->getContent(cnt);
		pTextEdit->setContent(cnt);
	}

#endif
	return true;
}

bool PfBottomCtrlPane::showEditPane(EDIT_PANE_TYPE editpane, const QString &cnt, bool shadow)
{
	if ( _pTextEdit )
	{
		delete _pTextEdit;
		_pTextEdit = NULL;
	}
	
	switch(editpane)
	{
	case TEXT_EDIT:
		{
			_pTextEdit = new TextEdit(_pMainFrame, this);
			_pTextEdit->setWindowFlags(Qt::Widget);

			_pTextEdit->setContent(cnt);
			_pTextEdit->setShadow(shadow);
			_pTextEdit->show();
			_prjctrlpane->hide();
			resizeEvent(NULL);
		}
		break;

	default:
		{
			_prjctrlpane->show();
		}
	}

	return true;
}
