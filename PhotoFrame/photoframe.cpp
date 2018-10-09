#include "photoframe.h"
#include <QMouseEvent>
#include <QDesktopWidget>
#include "pfleftctrlpane.h"
#include "PfBottomCtrlPane.h"
#include "PfCentPane.h"
#include <QFileDialog>
#include "PrintCfgDlg.h"
#include <QPrinterInfo>
#include "PFPhotoEditScene.h"
#ifdef Q_OS_WIN32
#include <Windows.h>
#include "qprintengine_win_p.h"
#endif
#include <QPrintDialog>

#define BUILDIN_IMG_RES_PREFIX	"Resources/images/"
QString gres = QString(BUILDIN_IMG_RES_PREFIX);

extern QApplication *g_app;

#define TITLE_BTN_X		10
#define TITLE_BTN_Y		20
#define TITLE_BTN_HEIGHT	22
#define TITLE_BTN_WIDTH	72
#define TITLE_BTN_SPAN	10

TopInfoLabel::TopInfoLabel(QWidget *parent, PhotoFrame *pframe):
_frame(pframe), QLabel(parent),_pressed(false), _maxized(false)
{
	PhotoFrame *pFrame = dynamic_cast<PhotoFrame *>(_frame);
	if ( !pFrame )
	{
		return ;
	}
	

	//
	pMinWin = new QPushButton( this);
	pMinWin->setFlat(true);
	pMinWin->setStyleSheet("background-image:url(" + gres + "min_wind_btn.png)");
	pMinWin->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gres + "min_btn.png)}"
		"QPushButton:hover{background-image:url(" + gres + "min_btn_hover.png)}");

	pMaxWin = new QPushButton( this);
	pMaxWin->setFlat(true);
	pMaxWin->setStyleSheet("background-image:url(" + gres + "max_wind_btn.png)");
	pMaxWin->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gres + "max_btn.png)}"
		"QPushButton:hover{background-image:url(" + gres + "max_btn_hover.png)}");
	pRestoreWin = new QPushButton( this);
	pRestoreWin->setFlat(true);
	pRestoreWin->setStyleSheet("background-image:url(" + gres + "restor_wind_btn.png)");
	pRestoreWin->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gres + "max_btn.png)}"
		"QPushButton:hover{background-image:url(" + gres + "max_btn_hover.png)}");


	pCloseWin = new QPushButton( this);
	pCloseWin->setFlat(true);
	pCloseWin->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gres + "close_btn.png)}"
		"QPushButton:hover{background-image:url(" + gres + "close_btn_hover.png)}");
 

 	if ( pframe->isMaximized() )
	{
		pRestoreWin->show();
		pMaxWin->hide();
	}
	else
	{
		pRestoreWin->hide();
		pMaxWin->show();
	}

	_pLogoLabel = new QLabel(this);
	_pLogoLabel->setGeometry(30, 14, 300, 50);
	_pLogoLabel->setStyleSheet("QLabel{background: transparent;}");

	QString title;
	title += "<h2><I> <font color=white> ";
	title += tr("EZ-Baloon");
	title += "</font></i></h2>";
	//_pLogoLabel->setText(title);
	_pLogoLabel->setPixmap(QPixmap("Resources/images/logo.png"));

	_pLogoDescLabel = new QLabel(this);
	_pLogoDescLabel->setGeometry(45, 28, 200, 30);
	_pLogoDescLabel->setStyleSheet("QLabel{background: transparent;}");

	QString desc;
	desc += "<h4> <font color=white> ";
	desc += tr("designed print your baloon");
	desc += "</font></h4>";
	//_pLogoDescLabel->setText(desc);

	_pUrlLabel = new QLabel(this);
	_pUrlLabel->setGeometry(45, 28, 100, 30);
	_pUrlLabel->setStyleSheet("QLabel{background: transparent;}");
	_pUrlLabel->setText("<a href=www.ezballoon.com>www.ezballoon.com</a>");
	_pUrlLabel->setOpenExternalLinks(true);
	//connect(_pUrlLabel, SIGNAL(clicked()), this, SLOT(OnVisitWeb()));


	connect(pCloseWin,SIGNAL(clicked()), this->_frame, SLOT(OnClose()));
	connect(pMinWin,SIGNAL(clicked()), this->_frame, SLOT(OnMinimize()));
	connect(pMaxWin,SIGNAL(clicked()), this->_frame, SLOT(OnMaxmize()));
	connect(pRestoreWin,SIGNAL(clicked()), this->_frame, SLOT(OnRestore()));

	connect(pMaxWin,SIGNAL(clicked()), this, SLOT(OnMaxmize()));
	connect(pRestoreWin,SIGNAL(clicked()), this, SLOT(OnRestore()));



}

TopInfoLabel::~TopInfoLabel()
{
}

void TopInfoLabel::OnVisitWeb()
{
#ifdef Q_OS_WIN32

	QString url;
	QString str = _pUrlLabel->text();
	HWND parent = ::GetDesktopWindow();
	wchar_t *wszurl = (TCHAR *)str.utf16();
	HINSTANCE result = ::ShellExecuteW(0, NULL, wszurl, NULL, NULL, SW_SHOWNORMAL);
	return ;

	#endif

	#ifdef Q_OS_MACX

//can not compile in macx

	#endif
}

void TopInfoLabel::reTranslateLang()
{
#if 0
	pFile->setText(tr("File"));
	pEdit->setText(tr("Edit"));
	pLanguage->setText(tr("Language"));
	pHelp->setText(tr("Help"));
#endif
}

#define WIN_OP_BTN_SIZE_X	31
#define WIN_OP_BTN_SIZE_Y	17
#define WIN_OP_BTN_SPAN	5

void TopInfoLabel::resizeEvent(QResizeEvent *)
{
	/*
    QPainterPath path;
 
     QRectF rect1 = this->geometry();
	 rect1.adjust(-rect1.left(),-rect1.top(), -rect1.left(), -rect1.top());
 
     path.addRoundRect(rect1,1,1);
 
        
 
    QPolygon polygon= path.toFillPolygon().toPolygon();//获得这个路径上的所有的点
 
	QRegion region(polygon);//根据这个点构造这个区域
 
	setMask(region);
	*/


	if ( _frame->isWndMaxmized() )
	{
		pRestoreWin->show();
		pMaxWin->hide();
	}
	else
	{
		pRestoreWin->hide();
		pMaxWin->show();
	}


	//
	QRect rect = this->geometry();


	int btn_xstart_pos = rect.width()-(WIN_OP_BTN_SIZE_X+WIN_OP_BTN_SPAN)*3 - WIN_OP_BTN_SPAN;
	int btn_y_pos = WIN_OP_BTN_SPAN + 5;

	QRect urlrc;
	QRect btnrect = QRect(btn_xstart_pos,btn_y_pos, WIN_OP_BTN_SIZE_X,WIN_OP_BTN_SIZE_Y);
	urlrc = btnrect;
	pMinWin->setGeometry(btnrect);

	btnrect.adjust(WIN_OP_BTN_SIZE_X+WIN_OP_BTN_SPAN,0, WIN_OP_BTN_SIZE_X+WIN_OP_BTN_SPAN,0);
	pMaxWin->setGeometry(btnrect);

	//btnrect.adjust(WIN_OP_BTN_SIZE+WIN_OP_BTN_SPAN,0, WIN_OP_BTN_SIZE+WIN_OP_BTN_SPAN,0);
	pRestoreWin->setGeometry(btnrect);

	btnrect.adjust(WIN_OP_BTN_SIZE_X+WIN_OP_BTN_SPAN,0, WIN_OP_BTN_SIZE_X+WIN_OP_BTN_SPAN,0);
	pCloseWin->setGeometry(btnrect);

	int url_xstart_pos = rect.width()- 120;
	int url_y_pos = 35;
	urlrc = QRect(url_xstart_pos, url_y_pos, 120, 25);
	this->_pUrlLabel->setGeometry(urlrc);
	// default is not maxizable window
	//pMaxWin->show();
	//pRestoreWin->hide();
}
void TopInfoLabel::mousePressEvent( QMouseEvent * ev )
{
    if( ev->button() != Qt::LeftButton)
    {
        return;
    }
	if ( _pressed )
	{
		return ;
	}
	_oldPos = ev->globalPos();
	_pressed = true;
}

void TopInfoLabel::mouseReleaseEvent( QMouseEvent * ev )
{
	_pressed = false;
}

void TopInfoLabel::mouseDoubleClickEvent ( QMouseEvent * ev )
{
	if ( this->_frame->isWndMaxmized() )
	{
		this->_frame->OnRestore();

		pMaxWin->show();
		pRestoreWin->hide();
	}
	else
	{
		this->_frame->OnMaxmize();

		pMaxWin->hide();
		pRestoreWin->show();
	}
}


void TopInfoLabel::OnMaxmize()
{
		pMaxWin->hide();
		pRestoreWin->show();
}

void TopInfoLabel::OnRestore()
{
		pMaxWin->show();
		pRestoreWin->hide();
}


#define MOUSEMV_THRES 2

void TopInfoLabel::mouseMoveEvent( QMouseEvent * event )
{

    if( !_pressed )
        return;

	QPoint curpos = event->globalPos();

	if( qAbs(curpos.x()-_oldPos.x()) >= MOUSEMV_THRES || qAbs(curpos.y()-_oldPos.y()) >= MOUSEMV_THRES )
    {
		QRect rect = this->_frame->geometry();
		rect.adjust(curpos.x()-_oldPos.x(),curpos.y()-_oldPos.y(),
			curpos.x()-_oldPos.x(),curpos.y()-_oldPos.y());
		_frame->setGeometry(rect);
        _oldPos = curpos;
    }
}





FrameBar::FrameBar(bool left,QWidget *parent, const QWidget *pframe):
_frame(( QWidget *)pframe), QLabel(parent),_pressed(false), _left(left)
{
	setStyleSheet("background-image:url(" + gres + "BarLayout.png)");
}

FrameBar::~FrameBar()
{
}

void FrameBar::mousePressEvent( QMouseEvent * ev )
{
    if( ev->button() != Qt::LeftButton)
    {
        return;
    }
	if ( _pressed )
	{
		return ;
	}
	_oldPos = ev->globalPos();
	_pressed = true;
}

void FrameBar::mouseReleaseEvent( QMouseEvent * ev )
{
	_pressed = false;
}

#define MOUSEMV_THRES 2

void FrameBar::mouseMoveEvent( QMouseEvent * event )
{

    if( !_pressed )
        return;

	QPoint curpos = event->globalPos();

	if( qAbs(curpos.x()-_oldPos.x()) >= MOUSEMV_THRES || qAbs(curpos.y()-_oldPos.y()) >= MOUSEMV_THRES )
    {
		QRect rect = this->_frame->geometry();
		if ( this->_left )
		{
			rect.adjust(curpos.x()-_oldPos.x(),0,
				0,0);
		}
		else
		{

			rect.adjust(0,0,
				curpos.x()-_oldPos.x(),0);
		}

		_frame->setGeometry(rect);
        _oldPos = curpos;
    }
}

void FrameBar::enterEvent ( QEvent * event )
{
	_cursor = this->cursor();
	this->setCursor(Qt::SizeHorCursor);
}
void FrameBar::leaveEvent ( QEvent * event )
{
	this->setCursor(_cursor);
}


#define TOP_LABEL_HEIGHT 80
#define INFO_BANE_HEIGHT	77
#define LEFT_PANE_WIDTH	242

PhotoFrame::PhotoFrame(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), _pdoc(NULL), _langactGroup(NULL), 
	_size(PAPER_A4)
{
	ui.setupUi(this);
	
	setWindowFlags(Qt::FramelessWindowHint);
   // w.setWindowFlags(Qt::FramelessWindowHint);
	_createLangItms();
	this->_createActions();

	_pdoc = new PmPhotoFrameDoc(this);

	this->resize(1024, 768);
	this->setMinimumSize(850, 650);

	


	
	ui.statusBar->setStyleSheet(QString("background-image:url(") + gres + "BarLayout.png)");
	//_pOpWidget = new QWidget(_pCentralWidget);


	QRect rect = this->geometry();
	_toplabel = new TopInfoLabel(this,this);
	_toplabel->setGeometry(0,0, rect.width(), INFO_BANE_HEIGHT);
	//_toplabel->setText("<h2><i>This  bar will show some</i><font color=red>  message!</font></h2>");
	_toplabel->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	//QPalette palette;
	//palette.setBrush(_toplabel->backgroundRole(), QBrush(QImage(":/PhotoMaker/Resources/images/undo.png")));
	_toplabel->setStyleSheet(QString("background-image:url(") + gres + "TitleBarBackGround.png)");
	//_toplabel->setPalette(palette);
	_toplabel->show();

	_leftpane = new PFLeftCtrlPane(this);
	_leftpane->setGeometry(0, INFO_BANE_HEIGHT, LEFT_PANE_WIDTH, rect.height()-INFO_BANE_HEIGHT);

	_bottompane = new PfBottomCtrlPane(this, this);
	//_bottompane->setStyleSheet(QString("background-image:url(") + gres + "bottompanebg_small.png)");

	_centralpane = new PfCentPane(this);


	_leftBar = new FrameBar(true, this, this);
	_rightBar = new FrameBar(false, this, this);



	this->_appcfg.loadCfg("appcfg.xml");
	QString langname, langfile;
	_appcfg.getLang(langname, langfile);
	if ( !langname.length() )
	{
		langname = tr("English");
	}
	this->_chgLang(langname, langfile);
	_selLangMenu(langname);


    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - width())/2, (desktop->height() - height())/2);

	if ( _appcfg.isMaximized() )
	{
		this->OnMaxmize();
	}

	
}

PhotoFrame::~PhotoFrame()
{

}

void PhotoFrame::_createActions()
{
	_delAction = new QAction(tr("Delete"), this);
    _delAction->setShortcuts(QKeySequence::Delete);
	this->addAction(_delAction);
	connect(_delAction, SIGNAL(triggered()), this, SLOT(OnDelete()));
}

bool PhotoFrame::isWndMaxmized()
{
	QDesktopWidget* desktop = QApplication::desktop();
	QRect desktoprc = desktop->availableGeometry (); 

	QRect currc = this->geometry();

	return currc == desktoprc;

}
void PhotoFrame::OnMaxmize()
{
	_appcfg.setMaximized(true);
	_normalRc = this->geometry();

	QDesktopWidget* desktop = QApplication::desktop();
	QRect rc = desktop->availableGeometry (); 
	this->move(rc.left(), rc.top());
	this->resize(rc.width(), rc.height());
	//this->showMaximized();
}
void PhotoFrame::OnMinimize()
{
	this->showMinimized();
}
void PhotoFrame::OnRestore()
{
	_appcfg.setMaximized(false);
	//this->showNormal();
	move(_normalRc.left(), _normalRc.top());
	resize(_normalRc.width(), _normalRc.height());
}


// system button command
void PhotoFrame::OnClose()
{
	//
	/*
	if ( PmUndoActionStack::getInst().isUpdated() )
	{
		//
		QMessageBox confirmdlg(QMessageBox::Question, tr("Confirmation"),
			tr("The current project is not saved.\n Do you want to save it now?"),
			QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel ,this);
		
		int ret = confirmdlg.exec();	
		if ( ret == QMessageBox::Yes )
		{
			this->OnSaveProj();
		}
		else if ( ret == QMessageBox::Cancel )
		{
			return ;
		}
	}
	*/


	this->close();
}

void PhotoFrame::OnSetTextShadow(bool shadow)
{
	this->_centralpane->setTxtShadow(shadow);
}

void PhotoFrame::OnAlignText(int align)
{
	this->_centralpane->alignText(align);
}

void PhotoFrame::OnVAlignText(int align)
{
	this->_centralpane->valignText(align);
}

void PhotoFrame::OnSetTextCnt(const QString &cnt)
{
	this->_centralpane->setTextCnt(cnt);

}

void PhotoFrame::OnAddText()
{
	this->_centralpane->addTextBox();

}
 


void PhotoFrame::OnResizeTextBox(const QRectF &rc)
{
	_centralpane->resizeTextBox(rc);
}

void PhotoFrame::OnRotateTextBox(const QRectF &rc, qreal rotate)
{
	_centralpane->rotateTextBox(rc, rotate);
}
void PhotoFrame::OnMvTextBox(const QRectF &rc)
{
	_centralpane->mvTextBox(rc);
}

void PhotoFrame::OnPhotoFrameSize(PAPER_SIZE size)
{
	this->_size = size;
	PF_PROJ_PROPS prj;
	this->_pdoc->getProjProps(prj);
	prj.papersize = _size == PAPER_A4 ? PF_PROJ_PROPS::A4 : PF_PROJ_PROPS::A3;
	_pdoc->updateProjProps(prj);

	QString stylepicpath;
	if ( this->_size == PAPER_A4 )
	{
		stylepicpath = "./Resources/template/images/18/";
	}
	else
	{
		stylepicpath = "./Resources/template/images/28/";
	}

	switch(_style)
	{
	case BALL:
		{
			stylepicpath += "ball";
		}
		break;
	case HEART:
		{
			stylepicpath += "heart";
		}
		break;
	case STAR:
		{
			stylepicpath += "star";
		}
		break;
	default:
		return ;
	}

	this->_centralpane->showFramePath(stylepicpath);
}

void PhotoFrame::OnPhotoFrameStyle(PHOTO_FRAME_STYLE style)
{
	this->_style = style;
	PF_PROJ_PROPS prj;
	this->_pdoc->getProjProps(prj);
	if ( _style == BALL )
	{
		prj.framestyle = PF_PROJ_PROPS::BALL;
	}
	else if ( _style == HEART )
	{
		prj.framestyle = PF_PROJ_PROPS::HEART;
	}
	else if ( _style == STAR )
	{
		prj.framestyle = PF_PROJ_PROPS::STAR;
	}
	_pdoc->updateProjProps(prj);


	QString stylepicpath;
	if ( this->_size == PAPER_A4 )
	{
		stylepicpath = "./Resources/template/images/18/";
	}
	else
	{
		stylepicpath = "./Resources/template/images/28/";
	}

	switch(_style)
	{
	case BALL:
		{
			stylepicpath += "ball";
		}
		break;
	case HEART:
		{
			stylepicpath += "heart";
		}
		break;
	case STAR:
		{
			stylepicpath += "star";
		}
		break;
	default:
		return ;
	}

	this->_centralpane->showFramePath(stylepicpath);
}


void PhotoFrame::OnPhoto()
{
	// load old it
	QString olddir;
	_appcfg.getPicViewDir(olddir);

	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
		olddir,
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);
	if ( !dir.length() )
	{
		return ;
	}
	this->_centralpane->showPhotos(dir);
	_appcfg.setPicViewDir(dir);
}

void PhotoFrame::OnSelPhotoFrameStyle(const QString &stylepic)
{
	_centralpane->updateFrameStyle(stylepic);
}
void PhotoFrame::OnSelPhoto(const QString &picpath)
{
	// copy the photo to proj folder

	QString path = picpath;
	QString savedpath ;
	QFile file(picpath);

	savedpath = "prj/";
	int index = path.lastIndexOf("/");
	if ( index > 0 )
	{
		QString name = path.right(path.length()-index-1);
		savedpath += name;
		if ( file.copy(savedpath) )
		{
			path = savedpath;
		}
		else
		{
			// check if exit
			QFile savefile;
			if ( savefile.exists(savedpath) )
			{
				path = savedpath;
			}
		}
	}

	_centralpane->updatePhoto(path);
}

void PhotoFrame::OnRotatePhoto(int angel)
{
	// accumulate angel here

	_centralpane->rotatePhoto(angel);
}

void PhotoFrame::OnScalePhoto(qreal scale)
{
	// scale no need accumulate
	_centralpane->zoomPhoto(scale);

}


#define FRAME_WIDTH		2
#define BOTTOM_PANE_HEIGHT	105
void PhotoFrame::resizeEvent(QResizeEvent *)
{
	//
     QPainterPath path;
 
     QRectF rect1 = this->geometry();
	 rect1.adjust(-rect1.left(),-rect1.top(), -rect1.left(), -rect1.top());
 
     path.addRoundRect(rect1,1,1);
 
        
 
    QPolygon polygon= path.toFillPolygon().toPolygon();
 
        QRegion region(polygon);
 
	setMask(region);

	//
	QRect rect = this->geometry();
	//_pCentralWidget->setGeometry(0,0/*TITLE_BAR_HEIGHT+MENUE_BAR_HEIGHT+TOOLBAR_BTN_HEIGHT*/, rect.width(), rect.height()/*-(TITLE_BAR_HEIGHT+MENUE_BAR_HEIGHT+TOOLBAR_BTN_HEIGHT)*//* - STATUS_BAR_HEIGHT*/);


	_toplabel->setGeometry(0,0, rect.width(), INFO_BANE_HEIGHT);


	int span = 2;
	QRect statusRect = statusBar()->geometry();
	this->_leftpane->setGeometry(FRAME_WIDTH, INFO_BANE_HEIGHT, LEFT_PANE_WIDTH, rect.height()-INFO_BANE_HEIGHT-statusRect.height()-2);
	_bottompane->setGeometry(FRAME_WIDTH+LEFT_PANE_WIDTH+span, rect.height()-statusRect.height()-BOTTOM_PANE_HEIGHT-FRAME_WIDTH+1,
		rect.width()-2*FRAME_WIDTH-LEFT_PANE_WIDTH-span, BOTTOM_PANE_HEIGHT);

	_centralpane->setGeometry(FRAME_WIDTH+LEFT_PANE_WIDTH, INFO_BANE_HEIGHT, 
		rect.width()-FRAME_WIDTH*2-LEFT_PANE_WIDTH, rect.height()-INFO_BANE_HEIGHT-BOTTOM_PANE_HEIGHT-statusRect.height()-1);

	this->_leftBar->setGeometry(0, INFO_BANE_HEIGHT-4, FRAME_WIDTH,rect.height());
	this->_rightBar->setGeometry(rect.width()-FRAME_WIDTH, INFO_BANE_HEIGHT-4, FRAME_WIDTH,rect.height());

}


void PhotoFrame::closeEvent(QCloseEvent *e)
{
	// first shutdown work threads
	QString curshowpath;


	_appcfg.saveCfg("appcfg.xml");

	QMainWindow::closeEvent(e);

}



bool PhotoFrame::_getLangName(const QString &langshortname, QString &langname)
{
	QString sn = langshortname;
	if ( sn == "zh-cn" )
	{
		langname = tr("Simple Chinese");
	}
	else if ( sn == "zh-tw" )
	{
		langname = tr("Traditional Chinese");
	}
	else if ( sn == "zh-hk" )
	{
		langname = tr("Traditional Chinese");
	}
	else if ( sn == "en" )
	{
		langname = tr("English");
	}
	else if ( sn == "fi" || sn == "fi-fi" )
	{
		langname = tr("Finnish");
	}
	else if ( sn == "da" || sn== "da-dk" )
	{
		langname = tr("Danish");
	}
	else if ( sn == "ko" || sn == "ko-kr" )
	{
		langname = tr("Korean");
	}
	else if ( sn== "ja" || sn == "ja-jp" )
	{
		langname = tr("Japanese");
	}
	else if ( sn == "nl" || sn == "nl-nl" )
	{
		langname = tr("Dutch");
	}
	else if ( sn == "pt" )
	{
		langname = tr("Portuguese");
	}
	else if ( sn == "fr" )
	{
		langname = tr("French");
	}
	else if ( sn == "es" )
	{
		langname = tr("Spanish");
	}
	else if ( sn == "de" )
	{
		langname = tr("German");
	}
	else if ( sn == "ru" )
	{
		langname = tr("Russian");
	}
	else if ( sn == "it" )
	{
		langname = tr("Italian");
	}
	else if ( sn == "no" )
	{
		langname = tr("Norwegian");
	}
	else if ( sn == "hu" )
	{
		langname = tr("Hungarian");
	}
	else if ( sn == "tr" )
	{
		langname = tr("Turkish");
	}
	else if ( sn == "cs" )
	{
		langname = tr("Czech");
	}
	else if ( sn == "sl" )
	{
		langname = tr("Slovenian");
	}
	else if ( sn == "ar" )
	{
		langname = tr("Arabic");
	}
	else if ( sn == "hi" )
	{
		langname = tr("Hindi");
	}
	else if ( sn == "iw" )
	{
		langname = tr("Hebrew");
	}
	else if ( sn == "vi" )
	{
		langname = tr("Vietnamese");
	}


	return true;
}
bool PhotoFrame::_getLangFile(const QString &langname, QString &langfilename)
{
	QString str = tr("Simple Chinese");
	if ( langname == tr("Simple Chinese") )
	{
		langfilename = "photoframer_zh-cn.qm";
	}
	else if ( langname == tr("Traditional Chinese") )
	{
		langfilename = "photoframer_zh-tw.qm";
	}
	else if ( langname == tr("Traditional Chinese") )
	{
		langfilename = "photoframer_zh-hk.qm";
	}
	else if ( langname == tr("English") )
	{
		langfilename = "photoframer_en.qm";
	}
	else if ( langname == tr("Finnish") )
	{
		langfilename = "photoframer_fi.qm";
	}
	else if ( langname == tr("Danish") )
	{
		langfilename = "photoframer_da.qm";
	}
	else if ( langname == tr("Korean") )
	{
		langfilename = "photoframer_ko.qm";
	}
	else if ( langname == tr("Japanese") )
	{
		langfilename = "photoframer_ja.qm";
	}
	else if ( langname == tr("Dutch") )
	{
		langfilename = "photoframer_nl.qm";
	}
	else if ( langname == tr("Portuguese") )
	{
		langfilename = "photoframer_pt.qm";
	}
	else if ( langname == tr("French") )
	{
		langfilename = "photoframer_fr.qm";
	}
	else if ( langname == tr("Spanish") )
	{
		langfilename = "photoframer_es.qm";
	}
	else if ( langname == tr("German") )
	{
		langfilename = "photoframer_de.qm";
	}
	else if ( langname == tr("Russian") )
	{
		langfilename = "photoframer_ru.qm";
	}
	else if ( langname == tr("Italian") )
	{
		langfilename = "photoframer_it.qm";
	}
	else if ( langname == tr("Norwegian") )
	{
		langfilename = "photoframer_no.qm";
	}
	else if ( langname == tr("Hungarian") )
	{		
		langfilename = "photoframer_hu.qm";
	}
	else if ( langname == tr("Turkish") )
	{
		langfilename = "photoframer_tr.qm";
	}
	else if ( langname == tr("Czech") )
	{
		langfilename = "photoframer_cs.qm";
	}
	else if ( langname == tr("Slovenian") )
	{
		langfilename = "photoframer_sl.qm";
	}
	else if ( langname == tr("Arabic") )
	{
		langfilename = "photoframer_ar.qm";
	}
	else if ( langname == tr("Hindi") )
	{
		langfilename = "photoframer_hi.qm";
	}
	else if ( langname == tr("Hebrew") )
	{
		langfilename = "photoframer_iw.qm";
	}
	else if (langname == tr("Vietnamese") )
	{
		langfilename = "photoframer_vi.qm";
	}

	return true;
}

void PhotoFrame::_createLangItms()
{
	//
	// enum lang folder to find all languages
	//
	QDir langdir(".\\lang");
	QFileInfoList list = langdir.entryInfoList();
	if ( list.size() <= 0 )
	{
		// no language packages
		return ;
	}

	if ( _langactGroup )
	{
		delete _langactGroup;
		_langactGroup = NULL;
	}
	_langactGroup = new QActionGroup(this);
	_langshortnames.clear();
	_langActs.clear();
	for ( int i=0; i<list.size(); i++ )
	{
		QFileInfo fileInfo = list.at(i);
		if ( fileInfo.isDir() )
		{
			continue;
		}
		QString filename = fileInfo.baseName();
		QString ext = fileInfo.completeSuffix();
		if ( ext != "qm" )
		{
			continue;
		}
		QString langpart;
		langpart = filename;
		int pos = langpart.indexOf("_");
		if ( pos == -1 )
		{
			continue;
		}
		langpart = langpart.right(langpart.length()-(pos+1));
		QString langname;
		if ( !_getLangName(langpart, langname) )
		{
			continue;
		}

		QAction *pLangAct = NULL;
		pLangAct = new QAction(langname, this);
		pLangAct->setStatusTip(langname);
		pLangAct->setCheckable(true);
		this->_langActs.push_back(pLangAct);
		_langshortnames.push_back(langpart);
		_langactGroup->addAction(pLangAct);
		if ( langname == tr("English") )
		{
			pLangAct->setChecked(true);
		}
		connect(pLangAct, SIGNAL(triggered()), this, SLOT(OnLangchg()));
	}

}



void PhotoFrame::_updateLangMenuItmsLang()
{
	QList<QAction *>::iterator it;
	QList<QString>::iterator itsname;
	for ( it=_langActs.begin(), itsname=this->_langshortnames.begin(); 
		it!=_langActs.end() && itsname!=_langshortnames.end(); it++,itsname++ )
	{

		QAction *pLangAct = *it;
		QString langshortname = *itsname;
		if ( !pLangAct )
		{
			continue;
		}
		QString langname;
		this->_getLangName(langshortname, langname);
		pLangAct->setText(langname);
		pLangAct->setStatusTip(langname);
	}
}

void PhotoFrame::_chgLang(const QString &langname,  QString &langfile1)
{
	QString langfile = langfile1;
	if ( !langfile.length()  )
	{
		if (  !this->_getLangFile(langname, langfile) )
		{
			return ;
		}
		langfile = "./lang/" + langfile;
		langfile1 = langfile;
	}

	static QTranslator *translator = NULL;
	if ( translator )
	{
		g_app->removeTranslator(translator);
		delete translator;
		translator = NULL;
	}
	translator = new QTranslator(this);
	translator->load(langfile);

	g_app->installTranslator(translator);
	//QCoreApplication::instance()->installTranslator(&translator);
	if ( langname == tr("Simple Chinese") )
	{
		QFont curfont;
		curfont = QApplication::font();
		//QString family = curfont.family();
		//curfont.setFamily("NSimSun");
		curfont.setPointSizeF(9);
		QApplication::setFont(curfont);

		curfont = QApplication::font();
	}
	else
	{
		QFont curfont;
		curfont = QApplication::font();
		QString family = curfont.family();
		curfont.setPointSizeF(9);
		//curfont.setFamily("Arial");
		QApplication::setFont(curfont);

	}
	_translateLang();
}


void PhotoFrame::_selLangMenu(const QString &langname)
{
	QList<QAction *>::iterator it;
	QList<QString>::iterator itshortname;
	for ( it=this->_langActs.begin(), itshortname = this->_langshortnames.begin(); 
		it!=_langActs.end() && itshortname!=_langshortnames.end(); it++,itshortname++ )
	{
		QAction *langact = *it;
		QString shortlangname = *itshortname;
		QString chklangname ;
		this->_getLangName(shortlangname, chklangname);
		if ( chklangname == langname )
		{
			(*it)->setChecked(true);
			break;
		}

	}
}

void PhotoFrame::_translateLang()
{
	_updateLangMenuItmsLang();

	this->_leftpane->retranslate();
	this->_bottompane->reTranslate();
}


void PhotoFrame::updateEditUI(PFPhotoEditViewItem *pViewItm, TextViewItem* txtviewitm)
{
	if ( txtviewitm )
	{
		PmTextItm *txtitm = txtviewitm->getTextItm();
		QString cnt;
		txtitm->getContent(cnt);
		this->_bottompane->showEditPane(PfBottomCtrlPane::TEXT_EDIT, cnt, txtitm->isShadowEnable());

	}
	else
	{
		this->_bottompane->showEditPane();
	}
}

void PhotoFrame::OnLangchg()
{
	QList<QAction *>::iterator it;
	QList<QString>::iterator itshortname;
	for ( it=this->_langActs.begin(), itshortname = this->_langshortnames.begin(); 
		it!=_langActs.end() && itshortname!=_langshortnames.end(); it++,itshortname++ )
	{
		if ( (*it)->isChecked() )
		{
			//
			break;
		}
	}
	if ( it == _langActs.end() || itshortname == _langshortnames.end() )
	{
		return ;
	}
	QAction *langact = *it;
	QString shortlangname = *itshortname;
	QString langname , langfile;
	this->_getLangName(shortlangname, langname);

	_chgLang(langname, langfile);



	this->_appcfg.setLang(langname, langfile);
}


void PhotoFrame::OnDelete()
{
	//
	this->_centralpane->delSel();
}

#ifdef Q_OS_WIN32
void savePrintSettings(HANDLE hDevNode, const QString &printName)
{
	//
	// Devmode
	//
	DWORD   dwLen = GlobalSize(hDevNode);
	BYTE* lp     = (BYTE*)GlobalLock(hDevNode);
	// leading length
	QFile file("./printcfg.ini");
	file.open(QIODevice::WriteOnly |QIODevice::Truncate );
	file.write(printName.toAscii().data(), printName.toAscii().size());
	file.write("\n");

	file.write((char*)&dwLen, sizeof(dwLen));
	// structure data
	file.write((char *)lp, dwLen);
	GlobalUnlock(hDevNode);
}

bool loadPrintSettings(HANDLE &hDevNode, QString &printName)
{
	if(hDevNode) GlobalFree(hDevNode);
	hDevNode = NULL;
	DWORD dret = NO_ERROR;
	
	QFile  file("./printcfg.ini");
	file.open(QIODevice::ReadOnly);

	QByteArray data = file.readLine();
	printName = data.data();
	printName = printName.left(printName.length()-1);

	DWORD len;
	if ( file.read((char *)&len, sizeof(len)) <= 0 )
	{
		return false;
	}

	//
	// DEVMODE
	//
	// 
	hDevNode = GlobalAlloc(GHND, len);
	if(NULL == hDevNode) {
		dret = GetLastError();
		return false;
	}
	BYTE* lpCopy = (BYTE*)GlobalLock(hDevNode);
	// read the whole caboodle
	file.read((char *)lpCopy, len);
	GlobalUnlock(hDevNode);
	return true;
}

void release(QWin32PrintEnginePrivate* pep)
{
    if (pep->hdc == 0)
        return;

    if (pep->globalDevMode) { // Devmode comes from print dialog
        GlobalUnlock(pep->globalDevMode);
    } else {            // Devmode comes from initialize...
        // devMode is a part of the same memory block as pInfo so one free is enough...
        GlobalUnlock(pep->hMem);
        GlobalFree(pep->hMem);
    }
    if (pep->hPrinter)
        ClosePrinter(pep->hPrinter);
    DeleteDC(pep->hdc);

    pep->hdc = 0;
    pep->hPrinter = 0;
    pep->pInfo = 0;
    pep->hMem = 0;
    pep->devMode = 0;
}




static inline qreal mmToInches(double mm)
{
    return mm*0.039370147;
}

static inline qreal inchesToMM(double in)
{
    return in/0.039370147;
}

void updateOrigin(QWin32PrintEnginePrivate *pep)
{
    if (pep->fullPage) {
        // subtract physical margins to make (0,0) absolute top corner of paper
        // then add user defined margins
        pep->origin_x = -pep->devPhysicalPageRect.x();
        pep->origin_y = -pep->devPhysicalPageRect.y();
        if (pep->pageMarginsSet) {
            pep->origin_x += pep->devPageRect.left();
            pep->origin_y += pep->devPageRect.top();
        }
    } else {
        pep->origin_x = 0;
        pep->origin_y = 0;
        if (pep->pageMarginsSet) {
            pep->origin_x = pep->devPageRect.left() - pep->devPhysicalPageRect.x();
            pep->origin_y = pep->devPageRect.top() - pep->devPhysicalPageRect.y();
        }
    }
}
void initDevRects(QWin32PrintEnginePrivate *pep)
{
    pep->devPaperRect = QRect(0, 0,
                         GetDeviceCaps(pep->hdc, PHYSICALWIDTH),
                         GetDeviceCaps(pep->hdc, PHYSICALHEIGHT));
    pep->devPhysicalPageRect = QRect(GetDeviceCaps(pep->hdc, PHYSICALOFFSETX),
                                GetDeviceCaps(pep->hdc, PHYSICALOFFSETY),
                                GetDeviceCaps(pep->hdc, HORZRES),
                                GetDeviceCaps(pep->hdc, VERTRES));
    if (!pep->pageMarginsSet)
        pep->devPageRect = pep->devPhysicalPageRect;
    else
        pep->devPageRect = pep->devPaperRect.adjusted(qRound(mmToInches(pep->previousDialogMargins.left() / 100.0) * pep->dpi_x),
                                            qRound(mmToInches(pep->previousDialogMargins.top() / 100.0) * pep->dpi_y),
                                            -qRound(mmToInches(pep->previousDialogMargins.width() / 100.0) * pep->dpi_x),
                                            -qRound(mmToInches(pep->previousDialogMargins.height() / 100.0) * pep->dpi_y));
    updateOrigin(pep);
}



void initHDC(QWin32PrintEnginePrivate *pep)
{

    HDC display_dc = GetDC(0);
    pep->dpi_x = GetDeviceCaps(pep->hdc, LOGPIXELSX);
    pep->dpi_y = GetDeviceCaps(pep->hdc, LOGPIXELSY);
    pep->dpi_display = GetDeviceCaps(display_dc, LOGPIXELSY);
    ReleaseDC(0, display_dc);
    if (pep->dpi_display == 0) {
        qWarning("QWin32PrintEngine::metric: GetDeviceCaps() failed, "
                "might be a driver problem");
        pep->dpi_display = 96; // Reasonable default
    }

    switch(pep->mode) {
    case QPrinter::ScreenResolution:
        pep->resolution = pep->dpi_display;
        pep->stretch_x = pep->dpi_x / double(pep->dpi_display);
        pep->stretch_y = pep->dpi_y / double(pep->dpi_display);
        break;
    case QPrinter::PrinterResolution:
    case QPrinter::HighResolution:
        pep->resolution = pep->dpi_y;
        pep->stretch_x = 1;
        pep->stretch_y = 1;
        break;
    default:
        break;
    }

    initDevRects(pep);
}




void readDevmode(QWin32PrintEnginePrivate *pep, HGLOBAL globalDevmode)
{
    if (globalDevmode) {
        DEVMODE *dm = (DEVMODE*) GlobalLock(globalDevmode);

		release(pep);

        pep->globalDevMode = globalDevmode;
        pep->devMode = dm;
        pep->hdc = CreateDC(reinterpret_cast<const wchar_t *>(pep->program.utf16()),
                       reinterpret_cast<const wchar_t *>(pep->name.utf16()), 0, dm);

        pep->num_copies = pep->devMode->dmCopies;
        if (!OpenPrinter((wchar_t*)pep->name.utf16(), &pep->hPrinter, 0))
            qWarning("QPrinter: OpenPrinter() failed after reading DEVMODE.");
    }

    if (pep->hdc)
        initHDC(pep);
}
#endif

void PhotoFrame::OnPrint()
{
	QString printname;
#ifdef Q_OS_WIN32
	HANDLE hDevNode = NULL;
	if ( loadPrintSettings(hDevNode, printname) )
	{
	}
#endif
	QPrinterInfo ptinfo;

	QList<QPrinterInfo> printers = QPrinterInfo::availablePrinters();
	ptinfo = printers[2];
	QString name = ptinfo.printerName();
	if ( printname.length() )
	{
		name = printname;
		QList<QPrinterInfo>::Iterator it;
		for ( it=printers.begin(); it!=printers.end(); it++ )
		{
			QString curname = (*it).printerName();
			if ( curname == printname )
			{
				ptinfo = *it;
				break;
			}
		}
	}
	QPrinter svprinter(ptinfo);
	QList<int> srl = svprinter.supportedResolutions();

#ifdef Q_OS_WIN32
	QWin32PrintEngine *ep = static_cast<QWin32PrintEngine *>((&svprinter)->paintEngine());
	QWin32PrintEnginePrivate *pep = (QWin32PrintEnginePrivate *)(*(ULONG*)((ULONG)ep+0x10));
	if ( loadPrintSettings(hDevNode, printname) )
	{
		readDevmode(pep, hDevNode);
	}
#endif
	QPrintDialog dlg(&svprinter,this);


	if ( !this->_pdoc )
	{
		return ;
	}


	if (dlg.exec() == QDialog::Accepted) 
	{
		PRINT_TASK_INFO printTaskInfo;
		PF_PROJ_PROPS proj;
		_pdoc->getProjProps(proj);

		PrintTaskMgr::getPrintTaskInfo(proj, printTaskInfo);

		PhotoFramePaper*  paper = NULL;;
		paper = _pdoc->getpaper();

		int lasteditpageidx = 0;

		QPrinter *printer = dlg.printer();
#ifdef Q_OS_WIN32
	QWin32PrintEngine *ep = static_cast<QWin32PrintEngine *>((&svprinter)->paintEngine());
	QWin32PrintEnginePrivate *pep = (QWin32PrintEnginePrivate *)(*(ULONG*)((ULONG)ep+0x10));
	savePrintSettings(pep->globalDevMode,printer->printerName());
#endif

		int rs = printer->resolution();
		printer->setPageMargins(0,0,0,0, QPrinter::Point);

		QRectF pageRect ;

		QPrinter::PaperSize papersize = printer->paperSize();
		if ( printTaskInfo.pagesize == QPrinter::Custom )
		{
			printer->setPaperSize(QPrinter::Custom );
			printer->setPaperSize(QSizeF(printTaskInfo.custompagesize),QPrinter::Inch);
		}
		else
		{
			printer->setPaperSize(printTaskInfo.pagesize);
		}
		if ( printTaskInfo.landscape )
		{
			printer->setOrientation(QPrinter::Landscape);
		}
		else
		{
			printer->setOrientation(QPrinter::Portrait);
		}
		pageRect = printer->pageRect(/*QPrinter::Point*/);

		//printer->setColorMode(QPrinter::Color);
		QPainter  *painter = new QPainter(printer);
		//painter->save();


		qDebug()<< "pageRect " << pageRect;
		QRectF paperRect ;
		//paperRect = printer->paperRect();
		qDebug()<< "paperRect " << paperRect;

		PFPhotoPrintScene *printscene = new PFPhotoPrintScene(pageRect,this,this);
		if ( proj.papersize == PF_PROJ_PROPS::A4 )
		{
			if ( proj.framestyle == PF_PROJ_PROPS::HEART )
			{
				printscene->setprintoff(6.5/pageRect.width(), 9.5/pageRect.height());
			}
			else
			{
				printscene->setprintoff(8.0/pageRect.width(), 4.0/pageRect.height());
			}
		}
		else
		{
		}
		printscene->print(printer, painter, &printTaskInfo);
	}
}


void PhotoFrame::OnOpen()
{
	QFileDialog filedlg;
	filedlg.setNameFilter("Photo Framer File(*.pf)");
	filedlg.setAcceptMode(QFileDialog::AcceptOpen);
	//filedlg.exec();
	QString filepath = filedlg.getOpenFileName(this, tr("Open the project file"), QString(), "Photo Frame File(*.pf)");
	if ( filepath.length() <= 0 )
	{
		return ;
	}
	OpenProj(filepath);


	//this->updateUIStatus();
}

void PhotoFrame::OnNewProj()
{
	_prjfile = "";

	QDir prjfolder("prj/");
	//file.delte
	QFileInfoList list = prjfolder.entryInfoList();
	for (int subindex=0;subindex<list.size(); subindex++ )
	{
		QFileInfo fileinfo = list[subindex];
		QString path = fileinfo.fileName();
		prjfolder.remove(path);
	}


	PF_PROJ_PROPS projprops;
	projprops.papersize = PF_PROJ_PROPS::A4;
	projprops.framestyle = PF_PROJ_PROPS::UNKNOWN;

	if ( this->_pdoc->newDoc(projprops) )
	{
		_showProjInfo(projprops);
		this->_centralpane->updateEditView();
	}

}

void PhotoFrame::OpenProj(const QString &projfile)
{
	QString filepath = projfile;

	QDir prjfolder("prj/");
	//file.delte
	QFileInfoList list = prjfolder.entryInfoList();
	for (int subindex=0;subindex<list.size(); subindex++ )
	{
		QFileInfo fileinfo = list[subindex];
		QString path = fileinfo.fileName();
		prjfolder.remove(path);
	}

	QFile file;
	file.copy(filepath,"./prj/prj.save.tar" );


	// compress all the prj folder
	QProcess::execute("./bsdtar.exe -xf ./prj/prj.save.tar");
	prjfolder.remove("./prj.save.tar");


	QString prjfile = "prj/prjfile.xml";

	this->_pdoc->loadDoc(prjfile);
	//_pdoc->updateLastEditPage();


 	// reload
	//this->getPhotoEditView()->setpap
	PF_PROJ_PROPS projprops;
	_pdoc->getProjProps(projprops);
	this->_showProjInfo(projprops);

	this->_centralpane->updateEditView(true);

}

void PhotoFrame::_showProjInfo(const PF_PROJ_PROPS &projprops)
{
	this->_leftpane->showProjInfo(projprops);
}

void PhotoFrame::OnSave()
{
	if ( 0 == _prjfile.length() )
	{
		QFileDialog filedlg;
		filedlg.setAcceptMode(QFileDialog::AcceptSave);
		//filedlg.exec();
		QString filepath = filedlg.getSaveFileName(this, tr("Save the project file"), QString(), "Photo Frame File(*.pf)");
		if ( filepath.length() <= 0 )
		{
			return ;
		}

		_prjfile = filepath;
	}

	// first save xml in proj folder
	QDir prjfolder("prj/");

	prjfolder.remove(_prjfile);

	QString xmlsvefile = "prj/prjfile.xml";
	this->_pdoc->saveDoc(xmlsvefile);

	// compress all the prj folder
	QProcess::execute("./bsdtar.exe -cf prj.save.tar ./prj/*.*");
	QFile file;
	QDir dir;
	if ( file.exists(_prjfile) )
	{
		dir.remove(_prjfile);
	}
	bool ret = file.copy("./prj.save.tar", _prjfile);
	dir.remove("./prj.save.tar");

}
