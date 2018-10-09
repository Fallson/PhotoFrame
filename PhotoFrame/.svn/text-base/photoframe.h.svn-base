#ifndef PHOTOFRAME_H
#define PHOTOFRAME_H

#include <QtGui/QMainWindow>
#include "ui_photoframe.h"
#include <QPushButton>
#include <QLabel>
#include "AppCfg.h"
#include "photoframedoc.h"
#include "PFPhotoEditViewItem.h"
#include "PFPhotoTextViewItem.h"

class TopInfoLabel ;
class PFLeftCtrlPane;
class FrameBar;
class PfBottomCtrlPane;
class PfCentPane;

typedef enum {PAPER_A4, PAPER_A3}PAPER_SIZE;
typedef enum {BALL, HEART, STAR}PHOTO_FRAME_STYLE;

class PhotoFrame : public QMainWindow
{
	Q_OBJECT

public:
	PhotoFrame(QWidget *parent = 0, Qt::WFlags flags = 0);
	~PhotoFrame();

	bool isWndMaxmized();
	QList<QAction *> &getLangActs(){return _langActs;}


	//
	void OnNewProj();
	void OpenProj(const QString &projfile);

	// selection
	void OnPhotoFrameSize(PAPER_SIZE size);
	void OnPhotoFrameStyle(PHOTO_FRAME_STYLE style);
	void OnPhoto();

	// edit
	void OnSelPhotoFrameStyle(const QString &stylepic);
	void OnSelPhoto(const QString &picpath);
	void OnRotatePhoto(int angel);
	void OnScalePhoto(qreal scale);

	void OnSetTextShadow(bool shadow);
	void OnAlignText(int align);
	void OnVAlignText(int align);
	void OnSetTextCnt(const QString &cnt);
	void OnAddText();
	void OnResizeTextBox(const QRectF &rc); 
    void OnRotateTextBox(const QRectF &rc, qreal rotate);
	void OnMvTextBox(const QRectF &rc);

	PmPhotoFrameDoc *getdoc(){return _pdoc;}

	void updateEditUI(PFPhotoEditViewItem *pViewItm, TextViewItem* txtviewitm);

public slots:
	// system button
	void OnClose();
	void OnMaxmize();
	void OnMinimize();
	void OnRestore();

	void OnPrint();
	void OnOpen();
	void OnSave();

	void OnLangchg();
	void OnDelete();

protected:
    virtual void resizeEvent(QResizeEvent *);
	virtual void closeEvent(QCloseEvent *e);

private:
	void _createActions();
	void _createLangItms();
	void _updateLangMenuItmsLang();

	bool _getLangName(const QString &langshortname, QString &langname);
	bool _getLangFile(const QString &langname, QString &langfilename);
	void _chgLang(const QString &langname,  QString &langfile1);
	void _selLangMenu(const QString &langname);
	void _translateLang();

	void _showProjInfo(const PF_PROJ_PROPS &projprops);

private:
	Ui::PhotoFrameClass ui;
	QRect _normalRc;

	QAction *_delAction;

	TopInfoLabel *_toplabel;
	PFLeftCtrlPane *_leftpane;
	PfBottomCtrlPane *_bottompane;
	PfCentPane *_centralpane;

	FrameBar *_leftBar, *_rightBar;


	PAPER_SIZE _size;
	PHOTO_FRAME_STYLE _style;

	QList<QAction *> _langActs;
	QList<QString> _langshortnames;
	QActionGroup *_langactGroup;

	PhotoAppCfg _appcfg;
	PmPhotoFrameDoc *_pdoc;
	QString _prjfile;
};




class TopInfoLabel: public QLabel
{
	Q_OBJECT

public:
	TopInfoLabel(QWidget *parent,  PhotoFrame *pframe);
	~TopInfoLabel();

public:
	void reTranslateLang();

protected:

	virtual void  mouseMoveEvent ( QMouseEvent * ev );
	virtual void  mousePressEvent ( QMouseEvent * ev );
	virtual void mouseReleaseEvent ( QMouseEvent * ev );
	virtual void mouseDoubleClickEvent ( QMouseEvent * ev );

    virtual void resizeEvent(QResizeEvent *);

protected slots:
	void OnMaxmize();
	void OnRestore();
	void OnVisitWeb();


private:
	PhotoFrame *_frame;
	bool _pressed;
	QPoint _oldPos;
	bool _maxized;

	QLabel *_pLogoLabel;
	QLabel *_pLogoDescLabel;
	QLabel *_pUrlLabel;

	QPushButton *pMinWin;
	QPushButton *pMaxWin;
	QPushButton *pRestoreWin;
	QPushButton *pCloseWin;

	QPushButton *pFile;
	QPushButton *pEdit;
	QPushButton *pLanguage;
	QPushButton *pHelp;
};


class FrameBar: public QLabel
{
	Q_OBJECT
public:
public:
	FrameBar(bool left, QWidget *parent, const QWidget *pframe);
	~FrameBar();

protected:

	virtual void  mouseMoveEvent ( QMouseEvent * ev );
	virtual void  mousePressEvent ( QMouseEvent * ev );
	virtual void mouseReleaseEvent ( QMouseEvent * ev );
	virtual void enterEvent ( QEvent * event );
	virtual void leaveEvent ( QEvent * event );
private:
	QWidget *_frame;
	bool _pressed;
	QPoint _oldPos;
	bool _left;

	QCursor _cursor;
};


#endif // PHOTOFRAME_H
