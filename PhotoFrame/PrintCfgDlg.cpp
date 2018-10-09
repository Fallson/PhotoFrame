#include "printcfgdlg.h"
#include "photoframe.h"
#include <QPrinterInfo>


#ifdef WIN32
#define WINVER 0x0500
#include <Windows.h>
#include <Commdlg.h>
#include <Winspool.h>
#endif

//#include "pmprintseamdlg.h"


PmPrinterCfgDlg::PmPrinterCfgDlg(PhotoAppCfg &appcfg, QWidget *parent)
	: QDialog(parent), _allpages(false), _appcfg(appcfg)
{
	ui.setupUi(this);

	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint );
    setWindowIcon(QIcon("Resources\\images\\AppIcon.ico"));
	
	/*
#ifdef Q_WS_WIN
	HWND hwnd = winId();
	LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
	style &= ~WS_SYSMENU;
	SetWindowLongPtr(hwnd, GWL_STYLE, style);
#endif
	*/

	//setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint &  ~Qt::WindowSystemMenuHint);
	//setWindowIcon(QIcon());

	// insert all printer properties information
	QPrinterInfo printerinfo;
	QList<QPrinterInfo> printers = printerinfo.availablePrinters();
	
	QList<QPrinterInfo>::iterator it;
	for ( it=printers.begin(); it!=printers.end(); it++ )
	{
		ui.PrinterList->addItem((*it).printerName());
	}
	// add addition for test
	ui.PrinterList->addItem("PDF");
	ui.textEditInformation->setText(_info);

	connect(ui.btn_Printer_Preference, SIGNAL(clicked ()), this, SLOT(showPrinterPropCfgDlg()));
	connect(ui.PrinterList, SIGNAL(currentIndexChanged (int )), this, SLOT(printerSelectionChanged(int)));
	connect(ui.rbAllPages, SIGNAL(toggled(bool)), this, SLOT(pageRageSelectionChanged()));
	//connect(ui.rbSelecPages, SIGNAL(toggled(bool)), this, SLOT(pageRageSelectionChanged()));
	connect(ui.btnAdjustSeam, SIGNAL(clicked()), this, SLOT(onAdjustPrintSeam()));
	connect(ui.spinBoxBeginPage, SIGNAL(valueChanged(int)), this, SLOT(onPageRangeChange()));
	connect(ui.spinBoxToPage, SIGNAL(valueChanged(int)), this, SLOT(onPageRangeChange()));
	
	ui.rbAllPages->setChecked(true);
	_allpages = true;
	ui.spinBoxBeginPage->setEnabled(true);
	ui.spinBoxToPage->setEnabled(true);

	ui.spinBoxCopies->setValue(1);


	printerSelectionChanged(0);
	
}

PmPrinterCfgDlg::~PmPrinterCfgDlg()
{

}

void PmPrinterCfgDlg::pageRageSelectionChanged()
{
	if ( ui.rbAllPages->isChecked() )
	{
		_allpages = true;
		ui.spinBoxBeginPage->setEnabled(true);
		ui.spinBoxToPage->setEnabled(true);


	}
	else
	{
		_allpages = false;
		ui.spinBoxBeginPage->setEnabled(true);
		ui.spinBoxToPage->setEnabled(true);

	}
}

void PmPrinterCfgDlg::onPageRangeChange()
{
	ui.rbSelecPages->setChecked(true);
}

void PmPrinterCfgDlg::printerSelectionChanged(int currentindex)
{
	//
	if ( currentindex < 0 )
	{
		return ;
	}

	_printername = ui.PrinterList->itemText(currentindex);
	QStdWString name = ui.PrinterList->itemText(currentindex).toStdWString();
#ifdef WIN32
	HANDLE hPrint;
	BOOL ret = OpenPrinterW((LPWSTR)name.c_str(), &hPrint, NULL);
	if ( !ret )
	{
		return ;
	}

	DEVMODE *pDevNode;

	HWND hWnd = this->window()->winId();

	PRINTER_INFO_1W *printerinfo;
	DWORD dwRet = 0;
	ret = GetPrinterW(hPrint, 1,NULL, 0, &dwRet);
	if ( !dwRet )
	{
		CloseHandle(hPrint);
		return ;
	}

	printerinfo = (PRINTER_INFO_1W*)malloc(dwRet);
	if ( !printerinfo )
	{
		CloseHandle(hPrint);
		return ;
	}
	ret = GetPrinterW(hPrint, 1,(LPBYTE)printerinfo, dwRet, &dwRet);
	if (!ret )
	{
		CloseHandle(hPrint);
		free(printerinfo);
		return ;
	}
	//printerinfo->pComment
	if ( printerinfo->pComment )
	{
		QString comment;
		comment = QString::fromStdWString(QStdWString(printerinfo->pComment));
		ui.label_Comment->setText(comment);
	}
	if ( printerinfo->pDescription )
	{
		QString description;
		description = QString::fromStdWString(QStdWString(printerinfo->pDescription));
		ui.label_PrintType->setText(description);
	}
	free(printerinfo);
	ClosePrinter(hPrint);
#endif

}

void PmPrinterCfgDlg::onAdjustPrintSeam()
{
	QPrinterInfo printerinfo;
#if 0

	bool gotprinter = getPrinter(printerinfo);
	int seam = 0; 
	_appcfg.getPrintSeam(seam);

	PmPrintSeamDlg seamdlg(printerinfo, _printername);
	seamdlg.setCalibrationNo(seam);
	if ( QDialog::Accepted  == seamdlg.exec() )
	{
		seamdlg.getCalibrationNo(seam);
		_appcfg.setPrintSeam(seam);
	}
#endif
}

void PmPrinterCfgDlg::showPrinterPropCfgDlg()
{
	// get current selection
	int current = ui.PrinterList->currentIndex();
	QString printname = ui.PrinterList->itemText(current);
	QStdWString name = printname.toStdWString();
	
#ifdef WIN32
	HANDLE hPrint;
	BOOL ret = OpenPrinterW((LPWSTR)name.c_str(), &hPrint, NULL);
	if ( !ret )
	{
		return ;
	}

	DEVMODE *pDevNode;

	HWND hWnd = this->window()->winId();
	DWORD dwRet = DocumentPropertiesW(hWnd,hPrint, (LPWSTR)name.c_str(),NULL, NULL, 0);
	if ( dwRet <= 0 )
	{
		CloseHandle(hPrint);
		return ;
	}
	pDevNode = (DEVMODE *)malloc(dwRet);
	if ( !pDevNode )
	{
		CloseHandle(hPrint);
		return ;
	}

	memset(pDevNode, 0, dwRet);
	PRINTER_INFO_1W *printerinfo;
	dwRet = 0;
	ret = GetPrinterW(hPrint, 1,NULL, 0, &dwRet);
	if ( !dwRet )
	{
		CloseHandle(hPrint);
		free(pDevNode);
		return ;
	}

	printerinfo = (PRINTER_INFO_1W*)malloc(dwRet);
	if ( !printerinfo )
	{
		CloseHandle(hPrint);
		free(pDevNode);
		return ;
	}
	ret = GetPrinterW(hPrint, 1,(LPBYTE)printerinfo, dwRet, &dwRet);
	if (!ret )
	{
		CloseHandle(hPrint);
		free(pDevNode);
		free(printerinfo);
		return ;
	}
	wcsncpy(pDevNode->dmDeviceName,printerinfo->pName,_countof(pDevNode->dmDeviceName));
	if ( wcslen(printerinfo->pName) >= _countof(pDevNode->dmDeviceName) )
	{
		pDevNode->dmDeviceName[_countof(pDevNode->dmDeviceName)-1] = 0;
	}

	dwRet = DocumentPropertiesW(hWnd,NULL, (LPWSTR)name.c_str(),pDevNode, pDevNode, DM_IN_BUFFER|DM_OUT_BUFFER|DM_PROMPT);

	free(pDevNode);
	free(printerinfo);
	ClosePrinter(hPrint);
#endif
}


bool PmPrinterCfgDlg::getPageRange(int &begin, int &end)
{
	if ( _allpages )
	{
		begin = 0;
		end = -1;
	}
	else
	{
		begin = ui.spinBoxBeginPage->value();
		end = ui.spinBoxToPage->value();
	}
	return true;
}

bool PmPrinterCfgDlg::getPrinter(QPrinterInfo &printerInfo)
{
	int index = ui.PrinterList->currentIndex();
	QList<QPrinterInfo> printers = QPrinterInfo::availablePrinters();

	if ( index >= 0 && index <printers.size() )
	{
		if ( printers[index].printerName() ==  ui.PrinterList->itemText(index))
		{
			//
			printerInfo = printers[index];
			return true;
		}
		else
		{
			QList<QPrinterInfo>::iterator it;
			for ( it=printers.begin(); it!=printers.end(); it++ )
			{
				if ( ui.PrinterList->itemText(index) == (*it).printerName() )
				{
					printerInfo = *it;
					return true;
				}
			}
		}
	}
	return false;
}

bool PmPrinterCfgDlg::getCopies(int &copies)
{
	copies = ui.spinBoxCopies->value();
	return true;
}

bool PmPrinterCfgDlg::setInformation(const QString &info)
{
	_info = info;
	//ui.textEditInformation->setText(_info);
	ui.textEditInformation->setHtml(_info);

	return true;
}

bool PmPrinterCfgDlg::setMaxPages(int maxpages)
{
	if ( maxpages < 0 )
	{
		maxpages = 0;
	}
	ui.spinBoxBeginPage->setMaximum(maxpages);
	ui.spinBoxToPage->setMaximum(maxpages);
	ui.spinBoxBeginPage->setMinimum(1);
	ui.spinBoxToPage->setMinimum(1);

	
	ui.spinBoxToPage->setValue(maxpages);
	ui.spinBoxBeginPage->setValue(1);

	return true;
}

bool PmPrinterCfgDlg::getPrintOff(qreal &offset)
{
	int seam = 0;
	this->_appcfg.getPrintSeam(seam);

	offset = (seam - 13 ) * 1.0*12/654/49;
	offset = -offset;

	return true;
}

void PmPrinterCfgDlg::showSrintSeamBtn(bool show)
{
	if ( show )
	{
		ui.btnAdjustSeam->show();
	}
	else
	{
		ui.btnAdjustSeam->hide();
	}
}



bool PrintTaskMgr::getPrintTaskInfo(const PF_PROJ_PROPS &proj, PRINT_TASK_INFO &printTaskInfo)
{
	switch( proj.papersize )
	{
	case  PF_PROJ_PROPS::A3:
		{
			printTaskInfo.landscape = false;
			printTaskInfo.pagesize = QPrinter::Custom;
			printTaskInfo.custompagesize = QSizeF(12.958,15.75);

			//printTaskInfo.pagesize
			printTaskInfo.information = "<font color=red>";
			printTaskInfo.information += "Please select the following printer properties:";
			printTaskInfo.information += "<BR>";
			printTaskInfo.information += "<BR>";
			printTaskInfo.information += "- Paper size: A3+";
			printTaskInfo.information += "<BR>";
			printTaskInfo.information += "- Type of paper: Glossy photo paper";
			printTaskInfo.information += "<BR>";
			printTaskInfo.information += "</font>";
		}
		break;
	case  PF_PROJ_PROPS::A4:
		{
			printTaskInfo.landscape = false;
			//printTaskInfo.pagesize = QPrinter::A4;
			printTaskInfo.pagesize = QPrinter::Custom;
			printTaskInfo.custompagesize = QSizeF(8.2687 /** 827/793*/,11.698/** 827/793*/);

			

			//printTaskInfo.pagesize
			printTaskInfo.information = "<font color=red>";
			printTaskInfo.information += "Please select the following printer properties:";
			printTaskInfo.information += "<BR>";
			printTaskInfo.information += "<BR>";
			printTaskInfo.information += "- Paper size: A4";
			printTaskInfo.information += "<BR>";
			printTaskInfo.information += "- Type of paper: Glossy photo paper";
			printTaskInfo.information += "<BR>";
			printTaskInfo.information += "</font>";
		}
		break;
	default:
		break;
	}

	return true;
}