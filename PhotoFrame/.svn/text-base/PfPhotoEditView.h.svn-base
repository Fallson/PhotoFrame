#pragma once

#include <QGraphicsView>

class PhotoFrame;
class PfPhotoEditView:
	public QGraphicsView
{
	Q_OBJECT

public:
        PfPhotoEditView(PhotoFrame* _pMainFrame, QWidget * parent = 0 );
	~PfPhotoEditView(void);

public:
	void updateView(bool reload = true);
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

protected:
    virtual void resizeEvent(QResizeEvent *);


private:
    PhotoFrame* _pMainFrame;
};

