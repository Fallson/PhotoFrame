#ifndef PmPhotoPage_H
#define PmPhotoPage_H

#include <QObject>
#include <QRect>
#include <QImage>
#include <QRGB>
#include <QMargins>
#include <QPixmap>
#include <QPrinter>
#include <QDateTime>



typedef struct _PfProjProps
{
	typedef enum{A4, A3}PROJ_PAPER_SIZE;
	typedef enum{UNKNOWN, BALL, HEART, STAR}PROJ_FRAME_STYLE;

	PROJ_PAPER_SIZE papersize;
	PROJ_FRAME_STYLE framestyle;
	_PfProjProps():papersize(A4), framestyle(BALL){}
}PF_PROJ_PROPS;



typedef struct _PrintTaskInfo
{
	//
	QString information;
	QPrinter::PaperSize pagesize; // in mm
	QSizeF custompagesize;
	bool landscape;

	_PrintTaskInfo():pagesize(QPrinter::A4), landscape(false)
	{
	}
}PRINT_TASK_INFO, *PPRINT_TASK_INFO;

 
typedef struct _SpaceProps
{
	qreal left, top, right, bottom;
	qreal leftpad, toppad, rightpad, bottompad;
	_SpaceProps():left(0), top(0), right(0),bottom(0),
		leftpad(0), toppad(0), rightpad(0), bottompad(0)
	{
	}
}SPACE_PROPS, *PSPACE_PROPS;
    
struct LayoutBoxMargin
{
	qreal left;
    qreal top;
    qreal right;
    qreal bottom; 
	qreal mid; // for margin of horizal mid area in edit view, 
	LayoutBoxMargin():left(0), top(0), right(0), bottom(0), mid(0){}
};

typedef enum {NullType, TextType, ImgType, CalType, CalMonthType}ITEM_TYPE;

struct LayoutBoxPos
{
	ITEM_TYPE type;
	qreal x,y,width,height; 
	LayoutBoxMargin margin;
	LayoutBoxPos():type(ImgType), x(0), y(0), width(0), height(0){}
};


  

//
// pages support
//

class PhotoFramePaper;

class PmPageItm: public QObject
{
	Q_OBJECT
public:
	PmPageItm(QObject *parent);
	PmPageItm(PmPageItm &pageitm);
	~PmPageItm();

public:
	bool setFramePath(const QString &framepath);
	bool getFramePath(QString &framepath);

	// for image
	bool getPhotoPath(QString &photopath);
	bool setPhotoPath(const QString &photopath);
	bool getRotate(int &angel);
	bool setRotate(int angel);
	bool getZoom(qreal &ratio);
	bool setZoom(qreal ratio);

	bool setImgLeftTop(const QPointF &lefttop){_imglefttop = lefttop; return true;}
	bool getImgLeftTop(QPointF &lefttop){lefttop = _imglefttop; return true;}
	void clearImgLeftTop(){_imglefttop = QPointF(-1, -1);}


	// common
	void setPaper(PhotoFramePaper *paper){_paper = paper;}
	PhotoFramePaper * getPaper(){return _paper;}

	void *getViewItm(){return _photoitm;}
	void setViewItm(void *itm){_photoitm = itm;}


private:
	PhotoFramePaper *_paper;

	// image
	QString _frampath;
	QString _photocnt;
	int _angel;
	qreal _ratio;
	QPointF _imglefttop;

	// ui assist
	void * _photoitm;
};


class PmTextItm: public QObject
{
	Q_OBJECT

public:
		typedef enum{ALIGN_HMASK=0xffff0000, ALIGN_VMASK=0x0000ffff, ALIGN_TOP=0x01, ALIGN_VCENTER=0x02, ALIGN_BOTTOM=0x03,ALIGN_VJUSTIFY=0x4, ALIGN_LEFT=0x10000, ALIGN_CENTER=0x20000, ALIGN_RIGHT=0x30000, ALIGN_JUSTIFY=0x40000}ALIGN_TYPE;
public:
	PmTextItm(QObject *parent);
	PmTextItm(PmTextItm &txtitm);
	~PmTextItm(){}

public:
	// height and width is the absolute pt
	bool getRectInPrintPage(LayoutBoxPos &rect){rect = _layoutbox; return true;}
	bool setRectInPrintPage(const LayoutBoxPos &rect){_layoutbox = rect; return true;}

	bool setContent(const QString &cnt){_cnt = cnt; return true;}
	bool getContent(QString &cnt){cnt = _cnt; return true;}



	int getAlign() {return _aligntype;}
	void setAlign(int align){_aligntype = align;}

	void setScale(qreal scale){_scale = scale;}
	qreal getScale(){return _scale;}
	void setRotate(qreal rotate){_rotate = rotate;}
	qreal getRotate(){return _rotate;}
	void enableShadow(bool bEnableShadow){_shadow = bEnableShadow;}
	bool isShadowEnable(){return _shadow;}

	bool setPrintPage(PhotoFramePaper *page){_pPage=page; return true;}
	PhotoFramePaper * getPrintPage(){return _pPage;}


	void *getViewItm(){return _viewitm;}
	void setViewItm(void *itm){_viewitm = itm;}
	QDateTime getLastBackTime(){return _lastbacktime;}
	void setLastBackTime(QDateTime lastbacktime){_lastbacktime=lastbacktime;}

private:
	LayoutBoxPos _layoutbox;
	PhotoFramePaper *_pPage;

	QString _cnt;
	qreal _scale;
	qreal _rotate;
	bool _shadow;
	void * _viewitm;
	int _aligntype;

	QDateTime _lastbacktime; // asist memeber, no need to save
};


class PhotoFramePaper : public QObject
{
	Q_OBJECT

public:
	PhotoFramePaper(QObject *parent);
	~PhotoFramePaper();

	PhotoFramePaper(PhotoFramePaper &srcpage);

public:
	//
	// when a new layout is set, it create a new PmPageItm list.
	// then check if old items can be copied into the new one
	// at last, it delete the old items.
	//
	bool getPicItms(QList<PmPageItm *> &picitmlst);
	bool setPicItms(const QList<PmPageItm *> &picitmlst);
	
	bool getTextbox(QList<PmTextItm *> &txtlst);
	bool addTextbox(PmTextItm *pTextItm = NULL);
	bool delTextbox(PmTextItm *pTextItm);


private:
	QList<PmPageItm *> _pagepicitmlst;
	QList<PmTextItm *> _txtlst;
};




#endif // PmPhotoPage_H
