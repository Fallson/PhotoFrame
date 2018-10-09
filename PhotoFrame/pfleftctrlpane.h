#ifndef PFLEFTCTRLPANE_H
#define PFLEFTCTRLPANE_H

#include <QWidget>
#include "ui_pfleftctrlpane.h"
#include "pfpaper.h"

class PhotoFrame;
class PFLeftCtrlPane : public QLabel
{
	Q_OBJECT

public:
	PFLeftCtrlPane(PhotoFrame *pframe = 0);
	~PFLeftCtrlPane();

public:
	void retranslate();
	void showProjInfo(const PF_PROJ_PROPS &projprops);

protected:
    virtual void resizeEvent(QResizeEvent *);

protected slots:
	void OnAddText();
	void OnPhoto();
	void OnFrameSize();
	void OnFrameStyle();
	void OnRotateL();
	void OnRotateR();
	void OnScale(int value);

private:
	Ui::PFLeftCtrlPane ui;

	PhotoFrame *_pframe;
	int _framesize;
	int _framestyle;
	QButtonGroup *_papergrp;
	QButtonGroup *_tmplgrp; 
};

#endif // PFLEFTCTRLPANE_H
