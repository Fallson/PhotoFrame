#ifndef PMPRINTERCFGDLG_H
#define PMPRINTERCFGDLG_H

#include <QDialog>
#include "ui_printercfgdlg.h"
#include "pfpaper.h"
#include "photoframe.h"

class PrintTaskMgr
{
public:
	static bool getPrintTaskInfo(const PF_PROJ_PROPS &proj, PRINT_TASK_INFO &printTaskInfo);
};

class QPrinterInfo;
class PmPrinterCfgDlg : public QDialog
{
	Q_OBJECT

public:
	PmPrinterCfgDlg(PhotoAppCfg &appcfg, QWidget *parent = 0);
	~PmPrinterCfgDlg();

public:
	bool getPageRange(int &begin, int &end);
	bool getPrinter(QPrinterInfo &printer);
	bool getCopies(int &copies);
	bool setInformation(const QString &info);
	bool setMaxPages(int maxpages);
	bool getPrintOff(qreal &offset);
	void showSrintSeamBtn(bool show);

protected slots:
	void showPrinterPropCfgDlg();
	void printerSelectionChanged(int currentindex);
	void pageRageSelectionChanged();
	void onAdjustPrintSeam();
	void onPageRangeChange();

private:
	Ui_PrinterConfigDlg ui;
	QString _info;
	bool _allpages;
	QString _printername;

	PhotoAppCfg &_appcfg;
};

#endif // PMPRINTERCFGDLG_H
