#ifndef PMPHOTOMAKERDOC_H
#define PMPHOTOMAKERDOC_H

#include <QObject>
#include <QtXml/QDomDocument>
#include "pfpaper.h"

class PmPhotoFrameDoc : public QObject
{
	Q_OBJECT

public:
	PmPhotoFrameDoc(QObject *parent);
	~PmPhotoFrameDoc();

public:
	bool newDoc(const PF_PROJ_PROPS &proj);
	bool saveDoc(const QString &path);
	bool loadDoc(const QString &path);

public:
	bool getProjProps(PF_PROJ_PROPS &prj){prj = this->_projprops; return true;}
	bool updateProjProps(const PF_PROJ_PROPS &prj);
	PhotoFramePaper *getpaper(){return _printpaperpage;}

private:
	//
	void _maketmpfolder();

private:
	bool _savePrjPropes(QDomDocument &doc,QDomElement &prjpropelem, PF_PROJ_PROPS &prjpropes);
	bool _loadPrjPropes(QDomElement &prjpropselem, PF_PROJ_PROPS &prjpropes);


	bool _saveTextItms(QDomDocument &doc,QDomElement &printpaerpageelem, const QList<PmTextItm*> &txtitmlst);
	bool _loadTextItms(QDomElement &textitmeelem,  QList<PmTextItm*> &txtitmlst);

	bool _saveTextItm(QDomDocument &doc,QDomElement &printpaerpageelem, PmTextItm &textitm);
	bool _loadTextItm(QDomElement &textitmeelem, PmTextItm *&textitm);

	bool _savePhotoItm(QDomDocument &doc, QDomElement &photopageelem, PmPageItm &photoitm);
	bool _loadPhotoItm(QDomElement &photoitmelem, PmPageItm *&photoitm);

	bool _savePaperPage(QDomDocument &doc, QDomElement &container, PhotoFramePaper &printpaperpage);
	bool _loadPaperPage(QDomElement &paperpageelem, PhotoFramePaper *&printpaperpage);

	//
	bool _addContent(QDomDocument &doc,QDomElement &elem, const QString &content);
	bool _getContent(QDomElement &elem, QString &content);

	// basic types
	bool _savePos(QDomDocument &doc,QDomElement &parent, const QString &name, const LayoutBoxPos pos);
	bool _loadPos(QDomElement &poselem, LayoutBoxPos &pos);

	bool _saveMargin(QDomDocument &doc,QDomElement &parent, const QString &name, const LayoutBoxMargin margin);
	bool _loadMargin(QDomElement &marginelem, LayoutBoxMargin &margin);

	bool _saveSize(QDomDocument &doc,QDomElement &parent, const QString &name, const QSize size);
	bool _loadSize(QDomElement &sizeelem,  QSize &size);

	bool _saveInt(QDomDocument &doc,QDomElement &parent, const QString &name, const int value);
	bool _loadInt(QDomElement &elem, int &value);

	bool _saveFloat(QDomDocument &doc,QDomElement &parent, const QString &name, const qreal value);
	bool _loadFloat(QDomElement &elem, qreal &value);

	bool _saveStr(QDomDocument &doc,QDomElement &parent, const QString &name, const QString & value);
	bool _loadStr(QDomElement &elem, QString &value);

	bool _saveColor(QDomDocument &doc,QDomElement &parent, const QString &name, const QColor &color);
	bool _loadColor(QDomElement &elem, QColor &color);
 	bool _saveSpaceProps(QDomDocument &doc,QDomElement &parent, const QString &name, const SPACE_PROPS &spaceprops);
	bool _loadSpaceProps(QDomElement &fontpropselem, SPACE_PROPS  &spaceprops);

private:
	PF_PROJ_PROPS _projprops;
	PhotoFramePaper *_printpaperpage;
};

#endif // PMPHOTOMAKERDOC_H
