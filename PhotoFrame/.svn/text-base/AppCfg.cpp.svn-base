
#include "AppCfg.h"
#include <QFile>



PhotoAppCfg::PhotoAppCfg():_printseam(0)
{
}

PhotoAppCfg::~PhotoAppCfg()
{
}

bool PhotoAppCfg::getPicViewDir(QString &dir)
{
	dir = this->_picviewdir;
	return true;
}
	
bool PhotoAppCfg::setPicViewDir(const QString &dir)
{
	_picviewdir = dir;
	return true;
}

bool PhotoAppCfg::getLang(QString &langname, QString &langfile)
{
	langname = this->_langname;
	langfile = _langfile;
	return true;
}

bool PhotoAppCfg::setLang(const QString &langname, const QString &langfile)
{
	this->_langname = langname;
	_langfile = langfile;
	return true;
}

bool PhotoAppCfg::getPrintSeam(int &printseam)
{
	if ( _printseam == 0 )
	{
		_printseam = 13;
	}
	printseam = _printseam;
	return true;
}

bool PhotoAppCfg::setPrintSeam(const int &printseam)
{
	_printseam = printseam;
	return true;
}

bool PhotoAppCfg::isMaximized()
{
	return this->_mainwndmaximized;
}

bool PhotoAppCfg::setMaximized(bool maxmized)
{
	this->_mainwndmaximized = maxmized;
	return true;
}



bool PhotoAppCfg::_saveStr(QDomDocument &doc,QDomElement &parent, const QString &name, const QString & value)
{
	QDomElement elem = doc.createElement(name);
	parent.appendChild(elem);

	QDomText txtnode = doc.createTextNode(value);
	elem.appendChild(txtnode);

	return true;
}

bool PhotoAppCfg::_loadStr(QDomElement &elem, QString &value)
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
	value = elem.text();
	return true;
}


bool PhotoAppCfg::_saveFloat(QDomDocument &doc,QDomElement &parent, const QString &name, const qreal value)
{
    QString tmpbuf = QString("%1").arg(value);
    return this->_saveStr(doc, parent, name, tmpbuf);
}
bool PhotoAppCfg::_loadFloat(QDomElement &elem, qreal &value)
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

bool PhotoAppCfg::_loadInt(QDomElement &elem, int &value)
{
	QString strval;
	if ( !_loadStr(elem, strval) )
	{
		return false;
	}
	sscanf(strval.toAscii().data(), "%d", &value);
	return true;
}
bool PhotoAppCfg::_saveInt(QDomDocument &doc,QDomElement &parent, const QString &name, const int value)
{
    QString tmpbuf = QString("%1").arg(value);
    return this->_saveStr(doc, parent, name, tmpbuf);
}


bool PhotoAppCfg::loadCfg(const QString &cfgfile)
{
	 QFile file(cfgfile);
     if (!file.open(QFile::ReadOnly | QFile::Text)) 
	 {
		 return false;
	 }

	 QDomDocument appcfgdoc;

	 QString errorStr;
     int errorLine;
     int errorColumn;
	 if ( !appcfgdoc.setContent(&file, true,  &errorStr, &errorLine,
                                 &errorColumn) )
	 {
		 return false;
	 }

     QDomElement root = appcfgdoc.documentElement();
     if (root.tagName() != "PmAppCfg") 
	 {
         return false;
     } 

	 QDomElement lastpicviewfolderelem = root.firstChildElement("LastPictureViewFolder");
	 if ( !lastpicviewfolderelem.isNull() )
	 {
		 this->_loadStr(lastpicviewfolderelem, this->_picviewdir);
	 }


	 QDomElement lstlangnameelem = root.firstChildElement("LastLangName");
	 if ( !lstlangnameelem.isNull() )
	 {
		 this->_loadStr(lstlangnameelem, this->_langname);
	 }
	 QDomElement lstlangfileelem = root.firstChildElement("LastLangFilePath");
	 if ( !lstlangfileelem.isNull() )
	 {
		 this->_loadStr(lstlangfileelem, this->_langfile);
	 }


	 QDomElement printseamelem = root.firstChildElement("PrintSeam");
	 if ( !printseamelem.isNull() )
	 {
		 this->_loadInt(printseamelem, this->_printseam);
	 }



	 QDomElement wndmaxelem = root.firstChildElement("MainwndMaximized");
	 if ( !wndmaxelem.isNull() )
	 {
		 int val  =0;
		 this->_loadInt(wndmaxelem,val);
		 this->_mainwndmaximized = val!=0;
	 }

	 this->_saveInt(appcfgdoc, root, "MainwndMaximized", this->_mainwndmaximized?1:0);

	 return true;
}

bool PhotoAppCfg::saveCfg(const QString &cfgfile)
{
	 QFile file(cfgfile);
     if (!file.open(QFile::ReadWrite | QFile::Text | QFile::Truncate)) 
	 {
		 return false;
	 }

	 QDomDocument appcfgdoc("photomakerdoc");

	 QString errorStr;
     int errorLine;
     int errorColumn;

	 QDomElement root = appcfgdoc.createElement("PmAppCfg");
	 appcfgdoc.appendChild(root);

	 // save app configures
	 this->_saveStr(appcfgdoc, root, "LastPictureViewFolder", this->_picviewdir);

	 this->_saveStr(appcfgdoc, root, "LastLangName", this->_langname);
	 this->_saveStr(appcfgdoc, root, "LastLangFilePath", this->_langfile);

	 this->_saveInt(appcfgdoc, root, "PrintSeam", this->_printseam);

	 this->_saveInt(appcfgdoc, root, "MainwndMaximized", this->_mainwndmaximized?1:0);

	 //this->_savePaperPage(domDocument, paperpageselem,  *this->_printpaperpage);

	 QString xml = appcfgdoc.toString();
	 
	 file.write(xml.toUtf8());

	 return true;
}


