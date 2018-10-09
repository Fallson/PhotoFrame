

#ifndef FolderPictureView_H
#define FolderPictureView_H


#include "PmPicView.h"
#include <QtConcurrentRun> 

typedef struct _ImgItm
{
	QString name;
	QImage *_img;
	QString path;
}IMG_ITM, *PIMG_ITM;

class FolderPicPreview: public PictureView
{
	Q_OBJECT
public:
	FolderPicPreview(QWidget *parent = 0);
	~FolderPicPreview();

public:
	void showFolder(const QString &path);
	bool skipUsingJpgPreview(bool skip){_skipjpgpreview = skip; return true;}
	void setImgSize(int width, int height);

private:
	static void  _ShowFolderPicPreview1( void * context );
	void _listAllImgFiles();

signals:
	void _filefoundsig();

protected slots:
	void _newImgInserted();

private:
	QString _curpath;
	QFuture<void>  *_pListThread;

	QDir  *_pCurDir;
	int _curPicIndex;
	QMutex _imglock;
	list<IMG_ITM> imglst;
	bool _finished;
	bool _skipjpgpreview;
	int _imgwidth, _imgheight;
};


#endif
