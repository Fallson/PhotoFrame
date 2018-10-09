#include "photoframe.h"
#include <QtGui/QApplication>
#include <QDir>
#include <QSettings>

QApplication *g_app = NULL;





void _connectFiletype()
{
	QSettings *ukenvFileReg = new QSettings("HKEY_CLASSES_ROOT\\.pf", QSettings::NativeFormat);   //

	QString appname =  QString(g_app->argv()[0]);
	int index = appname.lastIndexOf("\\");
	appname = appname.right(appname.length()-index-1);
	QString currentValue = ukenvFileReg->value("Default").toString();
	if (currentValue.isEmpty() ||
		currentValue != appname)
	{
		//QMessageBox::information(NULL,"information","Unregistered or Uncorrect");
		ukenvFileReg->setValue("Default", appname);

		QSettings *ukenvIconReg = new QSettings("HKEY_CLASSES_ROOT\\" + appname + "\\DefaultIcon", QSettings::NativeFormat);
		ukenvIconReg->setValue("Default", QString(g_app->argv()[0]) + ",0"); 
		delete ukenvIconReg;

		QSettings *ukenvProgramReg = new QSettings("HKEY_CLASSES_ROOT\\" + appname + "\\shell\\open\\command", QSettings::NativeFormat);
                ukenvProgramReg->setValue("Default", QString(qApp->argv()[0]) + " %1");
		delete ukenvProgramReg; 
	}
	delete ukenvFileReg;  

}


int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	g_app = &a;

#if defined(Q_WS_WIN)
	QString exepath = QCoreApplication::applicationFilePath();
	int index = exepath.lastIndexOf("/");
	QString workdir = exepath.left(index);
	QDir::setCurrent(workdir);

	if ( argc == 0 )
	{
		_connectFiletype();
	}

#endif

	QFont curfont;
	QString family = curfont.family();
	curfont.setFamily("Arial");
	curfont.setPointSizeF(9);
	//QApplication::setFont(curfont);

	PhotoFrame w;
    w.setWindowIcon(QIcon("Resources\\images\\AppIcon.ico"));

	if ( argc > 1 )
	{
		w.OpenProj(QString(argv[1]));
	}
	else
	{
		w.OnNewProj();
	}
	w.show();
	return a.exec();
}
