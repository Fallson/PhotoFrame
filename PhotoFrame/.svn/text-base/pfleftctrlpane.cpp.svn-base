#include "pfleftctrlpane.h"
#include "photoframe.h"
#include <QMenu>

extern QString gres;

#define VIEW_ZOOM_SPAN_RANGE 500

PFLeftCtrlPane::PFLeftCtrlPane(PhotoFrame *parent)
	: QLabel(parent),_pframe(parent),_framesize(0), _framestyle(0)
{
	ui.setupUi(this);
	setStyleSheet("QLabel{background-image:url(" + gres + "leftpanebg.png)}"
		"QLabel{color:#404040}");
	//QPalette palette;
	//palette.setBrush(this->backgroundRole(), QBrush(QImage(gres + "TitleBarBackGround.png")));
	//this->setPalette(palette);



	ui.btnLang->setFlat(true);
	ui.btnLang->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{color:#404040}"
		"QPushButton{background-image:url(" + gres + "Lanage_btn.png)}"
		"QPushButton:hover{background-image:url(" + gres + "Lanage_btn_hover.png)}");


	QMenu  *langmenu = new QMenu(parent);
	QList<QAction *> &langactlst = parent->getLangActs();

	QList<QAction *>::iterator it;
	for ( it=langactlst.begin(); it!=langactlst.end(); it++ )
	{
		//
		langmenu->addAction(*it);
	}
	ui.btnLang->setMenu(langmenu);


	ui.btnA3Paper->setFlat(true);
	ui.btnA3Paper->setCheckable(true);
	ui.btnA3Paper->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{color:#404040}"
		"QPushButton{background-image:url(" + gres + "menu_btn.png)}"
		"QPushButton:checked{background-image:url(" + gres + "menu_btn_hover.png)}"
		"QPushButton:hover{background-image:url(" + gres + "menu_btn_hover.png)}");

	ui.btnA4Paper->setFlat(true);
	ui.btnA4Paper->setCheckable(true);
	ui.btnA4Paper->setStyleSheet("background-image:url(" + gres + "restor_wind_btn.png)");
	ui.btnA4Paper->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{color:#404040}"
		"QPushButton{background-image:url(" + gres + "menu_btn.png)}"
		"QPushButton:checked{background-image:url(" + gres + "menu_btn_hover.png)}"
		"QPushButton:hover{background-image:url(" + gres + "menu_btn_hover.png)}");

	_papergrp = new QButtonGroup(this);
	_papergrp->addButton(ui.btnA3Paper);
	_papergrp->addButton(ui.btnA4Paper);

	ui.btnBall->setFlat(true);
	ui.btnBall->setCheckable(true);
	ui.btnBall->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{color:#404040}"
		"QPushButton{background-image:url(" + gres + "menu_btn.png)}"
		"QPushButton:checked{background-image:url(" + gres + "menu_btn_hover.png)}"
		"QPushButton:hover{background-image:url(" + gres + "menu_btn_hover.png)}");

	ui.btnHeart->setFlat(true);
	ui.btnHeart->setCheckable(true);
	ui.btnHeart->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{color:#404040}"
		"QPushButton{background-image:url(" + gres + "menu_btn.png)}"
		"QPushButton:checked{background-image:url(" + gres + "menu_btn_hover.png)}"
		"QPushButton:hover{background-image:url(" + gres + "menu_btn_hover.png)}");

	ui.btnStar->setFlat(true);
	ui.btnStar->setCheckable(true);
	ui.btnStar->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{color:#404040}"
		"QPushButton{background-image:url(" + gres + "menu_btn.png)}"
		"QPushButton:checked{background-image:url(" + gres + "menu_btn_hover.png)}"
		"QPushButton:hover{background-image:url(" + gres + "menu_btn_hover.png)}");
	_tmplgrp = new QButtonGroup(this);
	_tmplgrp->addButton(ui.btnBall);
	_tmplgrp->addButton(ui.btnHeart);
	_tmplgrp->addButton(ui.btnStar);


	ui.btnPhoto->setFlat(true);
	ui.btnPhoto->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{color:#404040}"
		"QPushButton{background-image:url(" + gres + "menu_long_btn.png)}"
		"QPushButton:hover{background-image:url(" + gres + "menu_long_btn_hover.png)}");

	ui.btnRotateR->setFlat(true);
	ui.btnRotateR->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{color:#404040}"
		"QPushButton{background-image:url(" + gres + "rrbtn.png)}"
		"QPushButton:hover{background-image:url(" + gres + "rrbtn_hover.png)}");

	ui.btnRotateL->setFlat(true);
	ui.btnRotateL->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{color:#404040}"
		"QPushButton{background-image:url(" + gres + "rlbtn.png)}"
		"QPushButton:hover{background-image:url(" + gres + "rlbtn_hover.png)}");

	ui.btnText->setFlat(true);
	ui.btnText->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{color:#404040}"
		"QPushButton{background-image:url(" + gres + "addtxt.png)}"
		"QPushButton:hover{background-image:url(" + gres + "addtxthover.png)}");

	ui.lbZoomPic->setStyleSheet("background-image:url(" + gres + "ZoomInOut.png)");
	ui.sliderPhotoScale->setRange(0, VIEW_ZOOM_SPAN_RANGE);
	ui.sliderPhotoScale->setSingleStep(1);
	ui.sliderPhotoScale->setPageStep(2);
	ui.sliderPhotoScale->setSliderPosition(VIEW_ZOOM_SPAN_RANGE/2-1);

	ui.msl_label->setPixmap(QPixmap::fromImage(QImage(gres + "misilandLOGO.png")));

	connect(ui.btnText, SIGNAL(clicked()), this, SLOT(OnAddText()));
	connect(ui.btnPhoto, SIGNAL(clicked()), this, SLOT(OnPhoto()));
	connect(ui.btnA3Paper, SIGNAL(clicked()), this, SLOT(OnFrameSize()));
	connect(ui.btnA4Paper, SIGNAL(clicked()), this, SLOT(OnFrameSize()));

	connect(ui.btnBall, SIGNAL(clicked()), this, SLOT(OnFrameStyle()));
	connect(ui.btnHeart, SIGNAL(clicked()), this, SLOT(OnFrameStyle()));
	connect(ui.btnStar, SIGNAL(clicked()), this, SLOT(OnFrameStyle()));

	connect(ui.sliderPhotoScale, SIGNAL(valueChanged ( int  )), this, SLOT(OnScale(int)));
	connect(ui.btnRotateL, SIGNAL(clicked()), this, SLOT(OnRotateL()));
	connect(ui.btnRotateR, SIGNAL(clicked()), this, SLOT(OnRotateR()));

	ui.btnA4Paper->setChecked(true);


}

PFLeftCtrlPane::~PFLeftCtrlPane()
{

}

void PFLeftCtrlPane::retranslate()
{
	QFont curfont = this->font();
	QString family = curfont.family();
	QFont curappfont = QApplication::font();
	curfont.setFamily(curappfont.family());
	this->setFont(curfont);
	{
		ui.btnLang->setFont(curfont);
        ui.label->setFont(curfont);
        ui.label_2->setFont(curfont);
        ui.btnA4Paper->setFont(curfont);
        ui.btnA3Paper->setFont(curfont);
        ui.label_3->setFont(curfont);
        ui.label_4->setFont(curfont);
        ui.btnBall->setFont(curfont);
        ui.btnHeart->setFont(curfont);
        ui.btnStar->setFont(curfont);
        ui.label_5->setFont(curfont);
        ui.label_6->setFont(curfont);
        ui.btnPhoto->setFont(curfont);
		curfont.setBold(true);
		ui.label->setFont(curfont);
		ui.label_4->setFont(curfont);
		ui.label_5->setFont(curfont);

	}

	ui.retranslateUi(this);
}

void PFLeftCtrlPane::showProjInfo(const PF_PROJ_PROPS &projprops)
{
	if ( projprops.papersize == PF_PROJ_PROPS::A3 )
	{
		ui.btnA3Paper->setChecked(true);
	}
	else
	{
		ui.btnA4Paper->setChecked(true);
	}

	if ( projprops.framestyle == PF_PROJ_PROPS::BALL )
	{
		ui.btnBall->setChecked(true);
	}
	else if ( projprops.framestyle == PF_PROJ_PROPS::HEART )
	{
		ui.btnHeart->setChecked(true);
	}
	else if ( projprops.framestyle == PF_PROJ_PROPS::STAR)
	{
		ui.btnStar->setChecked(true);
	}
	else
	{
		ui.btnBall->setChecked(false);
		ui.btnHeart->setChecked(false);
		ui.btnStar->setChecked(false);
	}

}

void PFLeftCtrlPane::OnAddText()
{
	_pframe->OnAddText();
}

void PFLeftCtrlPane::OnPhoto()
{
	_pframe->OnPhoto();
}

void PFLeftCtrlPane::OnFrameSize()
{
	PAPER_SIZE papersize = PAPER_A4;
	QAbstractButton *pselbtn = this->_papergrp->checkedButton();
	if ( pselbtn == ui.btnA4Paper )
	{
		papersize = PAPER_A4;
	}
	else if ( pselbtn == ui.btnA3Paper )
	{
		papersize = PAPER_A3;
	}
	_pframe->OnPhotoFrameSize(papersize);
}

void PFLeftCtrlPane::OnFrameStyle()
{
	PHOTO_FRAME_STYLE style = BALL;
	QAbstractButton *pselbtn = this->_tmplgrp->checkedButton();
	if ( pselbtn == ui.btnBall )
	{
		style = BALL;
	}
	else if ( pselbtn == ui.btnHeart )
	{
		style = HEART;
	}
	else if ( pselbtn == ui.btnStar )
	{
		style = STAR;
	}
	_pframe->OnPhotoFrameStyle(style);

}


void PFLeftCtrlPane::OnRotateL()
{
	int angel = -90;
	_pframe->OnRotatePhoto(angel);
}

void PFLeftCtrlPane::OnRotateR()
{
	int angel = 90;
	_pframe->OnRotatePhoto(angel);
}

void PFLeftCtrlPane::OnScale(int value)
{
	qreal scale = 1.0/(1.0*VIEW_ZOOM_SPAN_RANGE/2) + value * 1.0/(1.0*VIEW_ZOOM_SPAN_RANGE/2);
	_pframe->OnScalePhoto(scale);
}

void PFLeftCtrlPane::resizeEvent(QResizeEvent *)
{
	QLabel::resizeEvent(NULL);

	//
	const QRect rc = this->geometry();
	QRect lbRc = ui.msl_label->geometry();

	lbRc.setBottom(rc.height()-50);
	lbRc.setTop(lbRc.bottom()-50);
	ui.msl_label->setGeometry(lbRc);
}
