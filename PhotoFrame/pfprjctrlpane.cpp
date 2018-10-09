#include "pfprjctrlpane.h"
#include "photoframe.h"

extern QString gres;

PfPrjCtrlPane::PfPrjCtrlPane(PhotoFrame *pMainFrame, QWidget *parent)
	: QLabel(parent)
{
	ui.setupUi(this);

	this->setStyleSheet("QPushButton{color:#404040}");

	ui.btnPrint->setFlat(true);
	ui.btnPrint->setCheckable(true);
	ui.btnPrint->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gres + "menu_btn.png)}"
		"QPushButton:hover{background-image:url(" + gres + "menu_btn_hover.png)}");

	ui.btnOpen->setFlat(true);
	ui.btnOpen->setCheckable(true);
	ui.btnOpen->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gres + "menu_btn.png)}"
		"QPushButton:hover{background-image:url(" + gres + "menu_btn_hover.png)}");

	ui.btnSave->setFlat(true);
	ui.btnSave->setCheckable(true);
	ui.btnSave->setStyleSheet("QPushButton{background: transparent;}"
		"QPushButton{background-image:url(" + gres + "menu_btn.png)}"
		"QPushButton:hover{background-image:url(" + gres + "menu_btn_hover.png)}");

	connect(ui.btnPrint, SIGNAL(clicked()), pMainFrame, SLOT(OnPrint()));
	connect(ui.btnOpen, SIGNAL(clicked()), pMainFrame, SLOT(OnOpen()));
	connect(ui.btnSave, SIGNAL(clicked()), pMainFrame, SLOT(OnSave()));

}

PfPrjCtrlPane::~PfPrjCtrlPane()
{

}

void PfPrjCtrlPane::reTranslate()
{
	QFont curfont = this->font();
	QString family = curfont.family();
	QFont curappfont = QApplication::font();
	curfont.setFamily(curappfont.family());
	this->setFont(curfont);
	{
		ui.btnOpen->setFont(curfont);
        ui.btnSave->setFont(curfont);
        ui.btnPrint->setFont(curfont);
	}
	ui.retranslateUi(this);
}


#define BTN_WIDTH	72
#define BTN_HEIGHT	21
#define BTN_SPAN	20

void PfPrjCtrlPane::resizeEvent(QResizeEvent *)
{
	QRect rc = this->geometry();
	QRect btnrc = rc;

	int x = rc.width()-3*(BTN_WIDTH+BTN_SPAN) - BTN_SPAN;
	int y = 45;
	ui.btnOpen->move(x, y);
	x+=BTN_WIDTH+BTN_SPAN;
	ui.btnSave->move(x,y);
	x+=BTN_WIDTH+BTN_SPAN;
	ui.btnPrint->move(x,y);

	this->setPixmap(QPixmap::fromImage(QImage(gres + "bottompanebg.png").scaled(QSize(rc.width(), rc.height()))));

}
