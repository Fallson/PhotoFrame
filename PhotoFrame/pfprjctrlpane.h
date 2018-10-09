#ifndef PFPRJCTRLPANE_H
#define PFPRJCTRLPANE_H

#include <QLabel>
#include "ui_pfprjctrlpane.h"

class PhotoFrame;
class PfPrjCtrlPane : public QLabel
{
	Q_OBJECT

public:
	PfPrjCtrlPane(PhotoFrame *pMainFrame,QWidget *parent = 0);
	~PfPrjCtrlPane();

public:
	void reTranslate();

protected:
    virtual void resizeEvent(QResizeEvent *);

private:
	Ui::PfPrjCtrlPane ui;
};

#endif // PFPRJCTRLPANE_H
