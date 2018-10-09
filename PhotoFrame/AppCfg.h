#pragma once

#include <QString>
#include <QtXml/QDomDocument>


class PhotoAppCfg
{
public:
	PhotoAppCfg();
	~PhotoAppCfg();

public:
	bool getPicViewDir(QString &dir);
	bool setPicViewDir(const QString &dir);
	bool getLang(QString &langname, QString &langfile);
	bool setLang(const QString &langname, const QString &langfile);
	bool getPrintSeam(int &printseam);
	bool setPrintSeam(const int &printseam);
	bool isMaximized();
	bool setMaximized(bool maxmized);

	bool loadCfg(const QString &cfgfile);
	bool saveCfg(const QString &cfgfile);
private:
	bool _saveStr(QDomDocument &doc,QDomElement &parent, const QString &name, const QString & value);
	bool _loadStr(QDomElement &elem, QString &value);
	bool _saveFloat(QDomDocument &doc,QDomElement &parent, const QString &name, const qreal value);
	bool _loadFloat(QDomElement &elem, qreal &value);
	bool _saveInt(QDomDocument &doc,QDomElement &parent, const QString &name, const int value);
	bool _loadInt(QDomElement &elem, int &value);

private:
	QString _picviewdir;
	QString _langname;
	QString _langfile;
	int _printseam;
	bool _mainwndmaximized;
};
