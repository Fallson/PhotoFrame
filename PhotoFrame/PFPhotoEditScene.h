#ifndef PFPHOTOEDITSCENE_H
#define PFPHOTOEDITSCENE_H

#include <QGraphicsScene>
#include "pfpaper.h"
#include "PFPhotoEditViewItem.h"
#include "PFPhotoTextViewItem.h"

class PhotoFrame;
class PFPhotoEditScene : public QGraphicsScene
{
    Q_OBJECT

public:
    PFPhotoEditScene(const QRectF& rect, PhotoFrame *pMainFrame, QObject *parent = 0);

public:
    void updateScene(bool bReload = true);

protected:
	virtual void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );


public:
	void selectItm(PFPhotoEditViewItem *pViewItm, TextViewItem* txtviewitm );
	bool getSelection(PmPageItm *&pageitm, PmTextItm *&txtitm);

    void cutSelection();
    void copySelection();
    void pasteSelection();
    void delSelction();

    // photo edit

	void updateFrameStyle(const QString &framepicpath);
	void updatePhoto(const QString &photopath);

	void rotatePhoto(int angel);
	void zoomPhoto(qreal scale);

	void addTextBox();
	void enableTextShadow(bool shadow);
	void alignText(int align);
	void valignText(int align);
	void setTextCnt(const QString &cnt);
	void resizeTextBox(const QRectF &rc); 
	void mvTextBox(const QRectF &rc);
	void rotateTextBox(const QRectF &rc, qreal rotate);
	void setTxtShadow(bool shadow);
	
	void delSel();

    void resize(const QRectF& rect);

private:
	virtual bool _isPrintScene(){return false;}

private:
	void _loadPaper(PhotoFramePaper *paper);
	void _updatePaper(PhotoFramePaper *paper);
	void _addTextBox(PmTextItm *pTextItm);

private:
    PhotoFrame *_pMainFrame;
	PFPhotoEditViewItem *_pViewItm;
	TextViewItem *_txtviewitm;
	QRectF _paperrc;


	QGraphicsItem *_editframe;
};

class PFPhotoPrintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    PFPhotoPrintScene(const QRectF& rect, PhotoFrame *pMainFrame, QObject *parent = 0);
        ~PFPhotoPrintScene();

public:
	void print(QPrinter *printer, QPainter *painter, PRINT_TASK_INFO* printInfo);	
	void setprintoff(qreal xoff, qreal yoff);

private:
	void _loadPaper();

private:
	virtual bool _isPrintScene(){return true;}

private:
	PhotoFrame *_pMainFrame;
	qreal _xoff, _yoff;

};


#endif // PFPHOTOEDITSCENE_H
