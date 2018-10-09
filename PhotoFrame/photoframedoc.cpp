#include "photoframedoc.h"
#include <QFile>
#include <QDir> 
#include "base64.h"

PmPhotoFrameDoc::PmPhotoFrameDoc(QObject *parent)
	: QObject(parent),_printpaperpage(NULL)
{
	_printpaperpage = new PhotoFramePaper(this);
	this->_projprops.papersize = PF_PROJ_PROPS::A4;
}

PmPhotoFrameDoc::~PmPhotoFrameDoc()
{

}
	


bool PmPhotoFrameDoc::updateProjProps(const PF_PROJ_PROPS &prj)
{

	this->_projprops = prj;
	return true;
}


bool PmPhotoFrameDoc::_saveInt(QDomDocument &doc,QDomElement &parent, const QString &name, const int value)
{
    QString tmpbuf = QString("%1").arg(value);
    return this->_saveStr(doc, parent, name, tmpbuf);
}

bool PmPhotoFrameDoc::_saveFloat(QDomDocument &doc,QDomElement &parent, const QString &name, const qreal value)
{
    QString tmpbuf = QString("%1").arg(value);
    return this->_saveStr(doc, parent, name, tmpbuf);
}

bool PmPhotoFrameDoc::_saveTextItms(QDomDocument &doc,QDomElement &printpaerpageelem, const QList<PmTextItm*> &txtitmlst)
{
	QDomElement textitmlstelem = doc.createElement("TextItemLst");
	printpaerpageelem.appendChild(textitmlstelem);
	QList<PmTextItm*>::const_iterator it;
	for ( it=txtitmlst.begin(); it!=txtitmlst.end(); it++ )
	{
		this->_saveTextItm(doc, textitmlstelem, **it);
	}

	return true;
}

bool PmPhotoFrameDoc::_loadTextItms(QDomElement &textitmlsteelem,  QList<PmTextItm*> &txtitmlst)
{
	QDomElement textitmelem;

	txtitmlst.clear();

	textitmelem = textitmlsteelem.firstChildElement("TextItem");
	while(!textitmelem.isNull() )
	{
		PmTextItm *ptxtitm = NULL;
		this->_loadTextItm(textitmelem, ptxtitm);
		if ( ptxtitm )
		{
			txtitmlst.push_back(ptxtitm);
		}
		textitmelem = textitmelem.nextSiblingElement("TextItem");
	}

	return true;
}

bool PmPhotoFrameDoc::_saveTextItm(QDomDocument &doc,QDomElement &txtitmlstelem, PmTextItm &textitm)
{
	QDomElement textitmelem = doc.createElement("TextItem");
	txtitmlstelem.appendChild(textitmelem);

	// pos in printpaper
	LayoutBoxPos posinprintpaper;
	textitm.getRectInPrintPage(posinprintpaper);
	this->_savePos(doc, textitmelem, "posinprintpaper", posinprintpaper);

	QString content;
	textitm.getContent(content);
	QString orgcnt = content;
	QByteArray utf8cnt = content.toUtf8();
	int utf8cntlen = utf8cnt.length();

	int outlen = utf8cnt.length()*4; 
	char *output = new char[outlen];
	if ( output )
	{
		memset(output, 0, outlen);
		ToB64Enc(utf8cnt.data(), output, utf8cnt.length());
		//output[datalen] = 0;
		int outlen = strlen(output);
		content = output;

		/*
		{
			unsigned int delen = 0;
			char *dcode = (char *)Base64Decode(output, &delen);
			//dcode[delen] = 0;
			QString check = QString::fromUtf8(dcode);
			delete dcode;
			if ( check == orgcnt )
			{
				int err = 1;
			}
		}
		*/
		delete output;
	}
	else
	{
		content = "";
	}

	this->_saveStr(doc, textitmelem, "conent", content);

	int aligntype = textitm.getAlign();
	this->_saveInt(doc, textitmelem, "aligntype", aligntype);

	qreal scale = textitm.getScale();
	this->_saveFloat(doc, textitmelem, "scale", scale);

	qreal rotate = textitm.getRotate();
	this->_saveFloat(doc, textitmelem, "rotate", rotate);

	bool enableShadow = textitm.isShadowEnable();
	this->_saveStr(doc, textitmelem, "enableshadow", enableShadow?"true":"false");


	return true;
}

bool PmPhotoFrameDoc::_savePhotoItm(QDomDocument &doc, QDomElement &photopageelem, PmPageItm &photoitm)
{
	QDomElement photoitmelem = doc.createElement("PageItm");
	photopageelem.appendChild(photoitmelem);


	// image path
	{
		QString framepath;
		photoitm.getFramePath(framepath);
		this->_saveStr(doc, photoitmelem, "framepath", framepath);

		QString photopath;
		photoitm.getPhotoPath(photopath);
		this->_saveStr(doc, photoitmelem, "imagepath", photopath);

		int angel = 0;
		photoitm.getRotate(angel);
		this->_saveInt(doc, photoitmelem, "rotate", angel);

		qreal ratio = 0;
		photoitm.getZoom(ratio);
		this->_saveFloat(doc, photoitmelem, "scale", ratio);

		QPointF lefttop;
		photoitm.getImgLeftTop(lefttop);
		this->_saveFloat(doc, photoitmelem, "imgleftoff", lefttop.rx());
		this->_saveFloat(doc, photoitmelem, "imgtopoff", lefttop.ry());
	}

	return true;
}


bool PmPhotoFrameDoc::_savePaperPage(QDomDocument &doc, QDomElement &container, PhotoFramePaper &paper)
{
	QDomElement paperelem = doc.createElement("PhotoFramePaper");
	container.appendChild(paperelem);

	//
	QList<PmPageItm *> picitmlst;
	paper.getPicItms(picitmlst);
	QList<PmPageItm *>::iterator it;
	for ( it=picitmlst.begin(); it!=picitmlst.end(); it++ )
	{
		this->_savePhotoItm(doc, paperelem, **it);
	}


	// text item
	PmTextItm *pTextItm = NULL;
	QList<PmTextItm *> txtitmlst;
	paper.getTextbox(txtitmlst);
	if ( txtitmlst.size() )
	{
		_saveTextItms(doc, paperelem, txtitmlst);
	}

	return true;
}


bool PmPhotoFrameDoc::_saveMargin(QDomDocument &doc,QDomElement &parent, const QString &name, const LayoutBoxMargin margin)
{
	QDomElement marginelem = doc.createElement(name);
	parent.appendChild(marginelem);
	this->_saveFloat(doc, marginelem, "left", margin.left);
	this->_saveFloat(doc, marginelem, "top", margin.top);
	this->_saveFloat(doc, marginelem, "right", margin.right);
	this->_saveFloat(doc, marginelem, "bottom", margin.bottom);

	return true;
}

bool PmPhotoFrameDoc::_savePos(QDomDocument &doc,QDomElement &parent, const QString &name, const LayoutBoxPos pos)
{
	QDomElement poselem = doc.createElement(name);
	parent.appendChild(poselem);

	this->_saveFloat(doc, poselem, "x", pos.x);
	this->_saveFloat(doc, poselem, "y", pos.y);
	this->_saveFloat(doc, poselem, "width", pos.width);
	this->_saveFloat(doc, poselem, "height", pos.height);
	this->_saveMargin(doc, poselem, "margins", pos.margin);

	return true;
}


bool PmPhotoFrameDoc::_saveSize(QDomDocument &doc,QDomElement &parent, const QString &name, const QSize size)
{
// size
	QDomElement sizeelem = doc.createElement(name);
	parent.appendChild(sizeelem);
	this->_saveInt(doc, sizeelem, "width", size.width());
	this->_saveInt(doc, sizeelem, "height", size.height());

	return true;
}

bool PmPhotoFrameDoc::_addContent(QDomDocument &doc,QDomElement &elem, const QString &content)
{
	QDomText txtnode = doc.createTextNode(content);
	elem.appendChild(txtnode);
	return true;
}

bool PmPhotoFrameDoc::_getContent(QDomElement &elem, QString &content)
{
	if ( elem.isNull() )
	{
		return false;
	}
	/*
	if ( QDomNode::TextNode !=  elem.nodeType() )
	{
		return false;
	}
	*/
	content = elem.text();
	return true;
}

bool PmPhotoFrameDoc::_saveStr(QDomDocument &doc,QDomElement &parent, const QString &name, const QString & value)
{
	QDomElement elem = doc.createElement(name);
	parent.appendChild(elem);
	this->_addContent(doc, elem, value);

	return true;
}

bool PmPhotoFrameDoc::_loadPos(QDomElement &poselem, LayoutBoxPos &pos)
{
	if ( poselem.isNull() )
	{
		return false;
	}
	qreal val = 0;
	QDomElement elem = poselem.firstChildElement("x");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		pos.x = val;
	}
	elem = poselem.firstChildElement("y");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		pos.y = val;
	}
	elem = poselem.firstChildElement("width");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		pos.width = val;
	}
	elem = poselem.firstChildElement("height");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		pos.height = val;
	}
	elem = poselem.firstChildElement("margins");
	if ( !elem.isNull()  )
	{
		this->_loadMargin(elem, pos.margin);
	}

	return true;
}

bool PmPhotoFrameDoc::_loadMargin(QDomElement &marginelem, LayoutBoxMargin &margin)
{
	if ( marginelem.isNull() )
	{
		return false;
	}

	qreal val;
	QDomElement elem = marginelem.firstChildElement("left");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		margin.left = val;
	}

	elem = marginelem.firstChildElement("top");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		margin.top = val;
	}
	elem = marginelem.firstChildElement("right");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		margin.right = val;
	}
	elem = marginelem.firstChildElement("bottom");
	val = 0;
	if ( !elem.isNull()  && _loadFloat(elem, val) )
	{
		margin.bottom = val;
	}
	return true;
}

bool PmPhotoFrameDoc::_loadInt(QDomElement &elem, int &value)
{
	QString strval;
	if ( !_loadStr(elem, strval) )
	{
		return false;
	}
	sscanf(strval.toAscii().data(), "%d", &value);
	return true;
}

bool PmPhotoFrameDoc::_loadFloat(QDomElement &elem, qreal &value)
{
	QString strval;
	if ( !_loadStr(elem, strval) )
	{
		return false;
	}
	float tmp;
	QByteArray ba = strval.toAscii();
	char *data = ba.data();
	sscanf(data, "%f", &tmp);
	value = tmp;
	return true;
}

bool PmPhotoFrameDoc::_loadStr(QDomElement &elem, QString &value)
{
	return _getContent(elem, value);
}
	
bool PmPhotoFrameDoc::_saveColor(QDomDocument &doc,QDomElement &parent, const QString &name, const QColor &color)
{
	QDomElement elem = doc.createElement(name);
	parent.appendChild(elem);

	int alpha = color.alpha();
	int red = color.red();
	int green = color.green();
	int blue = color.blue();

	_saveInt(doc, elem, "alpha", alpha);
	_saveInt(doc, elem, "red", red);
	_saveInt(doc, elem, "green", green);
	_saveInt(doc, elem, "blue", blue);

	//
	return true;
}


bool PmPhotoFrameDoc::_loadColor(QDomElement &colorelem, QColor &color)
{
	//
	QDomElement elem;

	int alpha = -1;
	int red = 0;
	int green = 0;
	int blue = 0;


	elem = colorelem.firstChildElement("alpha");
	_loadInt(elem, alpha);
	elem = colorelem.firstChildElement("red");
	_loadInt(elem, red);
	elem = colorelem.firstChildElement("green");
	_loadInt(elem, green);
	elem = colorelem.firstChildElement("blue");
	_loadInt(elem, blue);

	color = QColor(red, green, blue, alpha);

	return true;
}
 
bool PmPhotoFrameDoc::_loadPaperPage(QDomElement &paperpageelem, PhotoFramePaper *&printpaperpage)
{
	//
	QString name = paperpageelem.nodeName();
	if ( name != "PhotoFramePaper" )
	{
		printpaperpage = NULL;
		return false;
	}


	printpaperpage = new PhotoFramePaper(NULL);
	

	// photo pages

	QList<PmPageItm *> picitmlst;
	QDomElement pageelem = paperpageelem.firstChildElement("PageItm");
	while( !pageelem.isNull() )
	{
		PmPageItm *photoitm = NULL;
		if ( _loadPhotoItm(pageelem, photoitm) && photoitm )
		{
			photoitm->setPaper(printpaperpage);
			picitmlst.push_back(photoitm);
		}
		
		pageelem = pageelem.nextSiblingElement("PageItm");
	}
	printpaperpage->setPicItms(picitmlst);



	// text item
	QDomElement textitmelem = paperpageelem.firstChildElement("TextItemLst");

	PmTextItm *pTxtItm = NULL;
	QList<PmTextItm *> txtitmlst; 
	this->_loadTextItms(textitmelem, txtitmlst);

	QList<PmTextItm *>::iterator it;
	for ( it=txtitmlst.begin(); it!=txtitmlst.end(); it++ )
	{
		printpaperpage->addTextbox(*it); 
	}

	return true;
}


bool PmPhotoFrameDoc::_loadTextItm(QDomElement &textitmeelem, PmTextItm *&textitm)
{
		//
	QString name = textitmeelem.nodeName();
	if ( name != "TextItem" || textitmeelem.isNull() )
	{
		textitm = NULL;
		return false;
	}

	textitm = new PmTextItm(NULL);
	if ( !textitm )
	{
		return false;
	}

	QDomElement poselem = textitmeelem.firstChildElement("posinprintpaper");
	if ( poselem.isNull() )
	{
		return false;
	}
	LayoutBoxPos pos;
	this->_loadPos(poselem, pos);
	textitm->setRectInPrintPage(pos);

	QDomElement cntelem = textitmeelem.firstChildElement("conent");
	QString content;
	this->_loadStr(cntelem, content);


	QByteArray base64str = content.toAscii();
	int base64len = base64str.length(); 
	char *base64buf = new char[base64len+1];
	memcpy(base64buf, base64str.data(), base64len);
	base64buf[base64len] = 0;

	unsigned int srccntlen = 0;
	unsigned char *srccnt = Base64Decode(base64buf, &srccntlen);
	//content = (char *)srccnt;
	char *cnt = NULL;
	if ( srccnt && srccntlen > 0 )
	{
		cnt = new char[srccntlen+1];
		if ( cnt )
		{
			memcpy(cnt, srccnt, srccntlen);
			cnt[srccntlen] = 0;
			content = content.fromUtf8((char *)cnt);
			delete cnt;
		}
		delete srccnt;
	}
	textitm->setContent(content);

	QDomElement alignelem = textitmeelem.firstChildElement("aligntype");
	int aligntype = 0;
	this->_loadInt(alignelem, aligntype);
	textitm->setAlign(aligntype);

	QDomElement scaleelem = textitmeelem.firstChildElement("scale");
	qreal scale = 0;
	this->_loadFloat(scaleelem, scale);
	textitm->setScale(scale);

	QDomElement rotateelem = textitmeelem.firstChildElement("rotate");
	qreal rotate = 0;
	this->_loadFloat(rotateelem, rotate);
	textitm->setRotate(rotate);

	QDomElement enableShadowElem = textitmeelem.firstChildElement("enableshadow");
	QString enableShadow;
	this->_loadStr(enableShadowElem, enableShadow);
	textitm->enableShadow(enableShadow=="true");

	return true;
}

bool PmPhotoFrameDoc::_loadPhotoItm(QDomElement &photoitmelem, PmPageItm *&photoitm)
{
	if ( photoitmelem.isNull() || photoitmelem.nodeName() != "PageItm" )
	{
		return false;
	}

	photoitm = new PmPageItm(NULL);
	if ( !photoitm )
	{
		return false;
	}


	{
		// image path
		QDomElement framepathelem = photoitmelem.firstChildElement("framepath");
		QString framepath;
		if ( this->_loadStr(framepathelem, framepath) )
		{
			photoitm->setFramePath(framepath);
		}



		// image path
		QDomElement imgpathelem = photoitmelem.firstChildElement("imagepath");
		QString imgpath;
		if ( this->_loadStr(imgpathelem, imgpath) )
		{
			photoitm->setPhotoPath(imgpath);
		}


		int angel = 0;
		QDomElement rotateelem = photoitmelem.firstChildElement("rotate");
		this->_loadInt(rotateelem, angel);
		photoitm->setRotate(angel);


		qreal ratio = 0;
		QDomElement scaleelem = photoitmelem.firstChildElement("scale");
		this->_loadFloat(scaleelem, ratio);
		photoitm->setZoom(ratio);

		QPointF lefttop;
		QDomElement imgleftelem = photoitmelem.firstChildElement("imgleftoff");
		QDomElement imgtopelem = photoitmelem.firstChildElement("imgtopoff");
		qreal left = 0, top = 0;
		this->_loadFloat(imgleftelem, left);
		this->_loadFloat(imgtopelem, top);
		lefttop.setX(left);
		lefttop.setY(top);
		photoitm->setImgLeftTop(lefttop);

		QString colorval;
		QDomElement colorelem = photoitmelem.firstChildElement("backgroundcolor");
		this->_loadStr(colorelem, colorval);


	}
	return true;
}



bool PmPhotoFrameDoc::_savePrjPropes(QDomDocument &doc,QDomElement &projpropselem, PF_PROJ_PROPS &prjpropes)
{
	this->_saveInt(doc, projpropselem, "papersize", prjpropes.papersize);
	this->_saveInt(doc, projpropselem, "framestyle", prjpropes.framestyle);
	return true;
}

bool PmPhotoFrameDoc::_loadPrjPropes(QDomElement &prjpropselem, PF_PROJ_PROPS &prjpropes)
{
	int value;

	prjpropes.papersize = PF_PROJ_PROPS::A4;
	prjpropes.framestyle = PF_PROJ_PROPS::BALL;

	if ( prjpropselem.isNull())
	{
		return true;
	}

	QDomElement elem  = prjpropselem.firstChildElement("papersize");
	if ( !elem.isNull() )
	{
		this->_loadInt(elem, value);
		prjpropes.papersize = (PF_PROJ_PROPS::PROJ_PAPER_SIZE)value;
	}

	elem  = prjpropselem.firstChildElement("framestyle");
	if ( !elem.isNull() )
	{
		this->_loadInt(elem, value);
		prjpropes.framestyle = (PF_PROJ_PROPS::PROJ_FRAME_STYLE)value;
	}

	return true;
}


bool PmPhotoFrameDoc::saveDoc(const QString &path)
{
	//
	// generate a xml file to represent the pages

	 QFile file(path);
     if (!file.open(QFile::ReadWrite | QFile::Text | QFile::Truncate)) 
	 {
		 return false;
	 }

	 QDomDocument domDocument("photomakerdoc");

	 QString errorStr;
     int errorLine;
     int errorColumn;
	 /*
	 if ( !domDocument.setContent(&file, true,  &errorStr, &errorLine,
                                 &errorColumn) )
	 {
		 return false;
	 }
	 */

	 QDomElement root = domDocument.createElement("PmProjStg");
	 domDocument.appendChild(root);

	 // save project properties
	 QDomElement projpropselem = domDocument.createElement("ProjectPropes");
	 root.appendChild(projpropselem);
	 this->_savePrjPropes(domDocument, projpropselem, this->_projprops);

	 QDomElement paperpageselem = domDocument.createElement("PrintPaperPages");
	 root.appendChild(paperpageselem);

	 // enum all papaer pages
	 if ( _printpaperpage )
	 {
		 //
		 this->_savePaperPage(domDocument, paperpageselem, *this->_printpaperpage);
	 }
	 //this->_savePaperPage(domDocument, paperpageselem,  *this->_printpaperpage);

	 QString xml = domDocument.toString();
	 

	 file.write(xml.toUtf8());


	// unpack the project file

	// save pictures in working folder

	// load all pages according the xml file


	// packet the xml file and all the pictures in working folder

	return true;
}

bool PmPhotoFrameDoc::loadDoc(const QString &path)
{
	 QFile file(path);
     if (!file.open(QFile::ReadOnly | QFile::Text)) 
	 {
		 return false;
	 }

	 QDomDocument domDocument;

	 QString errorStr;
     int errorLine;
     int errorColumn;
	 if ( !domDocument.setContent(&file, true,  &errorStr, &errorLine,
                                 &errorColumn) )
	 {
		 return false;
	 }

     QDomElement root = domDocument.documentElement();
     if (root.tagName() != "PmProjStg") 
	 {
         return false;
     } 

	 QDomElement prjpropselem = root.firstChildElement("ProjectPropes");
	 if ( !prjpropselem.isNull() )
	 {
		 this->_loadPrjPropes(prjpropselem, _projprops);
	 }


	 QDomElement paperpageselem = root.firstChildElement("PrintPaperPages");
	 if ( paperpageselem.isNull() )
	 {
		 return false;
	 }

	 
	 _printpaperpage = NULL;
	 QDomElement paperpageelem = paperpageselem.firstChildElement("PhotoFramePaper");
	 while( !paperpageelem.isNull() )
	 {
		 PhotoFramePaper *printpaperpage = NULL;
		 if ( _loadPaperPage(paperpageelem, printpaperpage) && printpaperpage )
		 {
			// _paperpages.push_back(printpaperpage);
			 _printpaperpage = printpaperpage;
		 }
		 paperpageelem = paperpageelem.nextSiblingElement("PhotoFramePaper");
	 }


	return true;
}

bool PmPhotoFrameDoc::newDoc(const PF_PROJ_PROPS &proj)
{
	this->_projprops = proj;
	if( _printpaperpage )
	{
		delete _printpaperpage;
	}
	_printpaperpage = new PhotoFramePaper(this);
	return true;
}
