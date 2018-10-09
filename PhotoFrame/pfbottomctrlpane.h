#ifndef PMBOTTOMCTRLPANE_H
#define PMBOTTOMCTRLPANE_H

#include <QWidget>
#include <QtGui/QMainWindow>
#include <QtGui/qtoolbar.h>
#include <QtGui/qlabel.h>
#include <QtGui/qtreeview.h>
#include <QtGui/qsplitter.h>
//#include "textedit.h"
//#include "photomaker.h"



class PhotoFrame;
class TextEdit;
class PfPrjCtrlPane;

class MyTabeWidget: public QTabWidget
{
	Q_OBJECT
public:
	MyTabeWidget(QWidget *parent);
protected:
	virtual void resizeEvent ( QResizeEvent * e );
};
 
class PfBottomCtrlPane : public QLabel
{
	Q_OBJECT
public:
	typedef enum{TEXT_EDIT, PRJ_CTRL, NON_EDIT}EDIT_PANE_TYPE;

public:
	PfBottomCtrlPane(PhotoFrame *pMainFrame, QWidget *parent);
	~PfBottomCtrlPane();

public:
	bool showEditPane(EDIT_PANE_TYPE editpane = NON_EDIT, const QString &cnt = QString(""), bool shadow = false);
	bool updateEditPaneInfo();

	void reTranslate();
protected:
    virtual void resizeEvent(QResizeEvent *);


private:
	TextEdit *_pTextEdit;
	PfPrjCtrlPane *_prjctrlpane;
	PhotoFrame *_pMainFrame;

};

#endif // PMBOTTOMCTRLPANE_H
