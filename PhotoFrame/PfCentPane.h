#pragma once
#include <QLabel>
#include "folderphotopreview.h"

class PfPhotoEditView;
class PhotoFrame;

class PfCentPane :
	public QLabel
{
	Q_OBJECT

public:
	PfCentPane(PhotoFrame * parent = 0 );
	~PfCentPane(void);

public:
	// for selection
	void showFramePath(const QString &framepicpath);
	void showPhotos(const QString &photopath);

	void updateEditView(bool reload = true);

	// for edit
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

	//
	void delSel();

protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual void paintEvent(QPaintEvent *);

private:
	static bool _StyleSelChanged(void *context, const QString &picpath);
	static bool _PhotoSelChanged(void *context, const QString &picpath);


private:
	PhotoFrame *_pframe;
	FolderPicPreview *_framepicselview;
	FolderPicPreview *_photosselview;
	PfPhotoEditView *_photoeditview;
};


