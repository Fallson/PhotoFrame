HEADERS=./PhotoFrame/pfbottomctrlpane.h \
        ./PhotoFrame/pfleftctrlpane.h \
        ./PhotoFrame/pfprjctrlpane.h \
        ./PhotoFrame/photoframe.h \
        ./PhotoFrame/textedit.h \
        ./PhotoFrame/AppCfg.h \
        ./PhotoFrame/FolderPhotoPreview.h \
        ./PhotoFrame/PfCentPane.h \
        ./PhotoFrame/PfPhotoEditView.h \
        ./PhotoFrame/PmPicView.h \
        ./PhotoFrame/PFPhotoEditScene.h \
        ./PhotoFrame/PFPhotoEditViewItem.h \
        ./PhotoFrame/PFPhotoTextViewItem.h \
        ./PhotoFrame/photoframedoc.h \
        ./PhotoFrame/pfpaper.h \
        ./PhotoFrame/base64.h \
        ./PhotoFrame/PrintCfgDlg.h \
        ./ollix-qmeta-822a818/include/qmeta/exif.h \
        ./ollix-qmeta-822a818/include/qmeta/iptc.h \
        ./ollix-qmeta-822a818/include/qmeta/standard.h \
        ./ollix-qmeta-822a818/include/qmeta/tiff_header.h \
        ./ollix-qmeta-822a818/include/qmeta/xmp.h \
        ./ollix-qmeta-822a818/include/qmeta/exif_data.h \
        ./ollix-qmeta-822a818/include/qmeta/file.h \
        ./ollix-qmeta-822a818/include/qmeta/identifiers.h \
        ./ollix-qmeta-822a818/include/qmeta/image.h \
        ./ollix-qmeta-822a818/include/qmeta/jpeg.h \
        ./ollix-qmeta-822a818/include/qmeta/qmeta.h \
        ./ollix-qmeta-822a818/include/qmeta/tiff.h \


SOURCES=./PhotoFrame/main.cpp \
        ./PhotoFrame/pfbottomctrlpane.cpp \
        ./PhotoFrame/pfleftctrlpane.cpp \
        ./PhotoFrame/pfprjctrlpane.cpp \
        ./PhotoFrame/photoframe.cpp \
        ./PhotoFrame/textedit.cpp \
        ./PhotoFrame/AppCfg.cpp \
        ./PhotoFrame/FolderPhotoPreview.cpp \
        ./PhotoFrame/PfCentPane.cpp \
        ./PhotoFrame/PfPhotoEditView.cpp \
        ./PhotoFrame/PmPicView.cpp \
        ./PhotoFrame/PFPhotoEditScene.cpp \
        ./PhotoFrame/PFPhotoEditViewItem.cpp \
        ./PhotoFrame/PFPhotoTextViewItem.cpp \
        ./PhotoFrame/photoframedoc.cpp \
        ./PhotoFrame/pfpaper.cpp \
        ./PhotoFrame/base64.cpp \
        ./PhotoFrame/PrintCfgDlg.cpp \
        ./ollix-qmeta-822a818/src/jpeg.cpp \
        ./ollix-qmeta-822a818/src/file.cpp \
        ./ollix-qmeta-822a818/src/tiff_header.cpp \
        ./ollix-qmeta-822a818/src/exif.cpp \
        ./ollix-qmeta-822a818/src/exif_data.cpp \
        ./ollix-qmeta-822a818/src/image.cpp \
        ./ollix-qmeta-822a818/src/iptc.cpp \
        ./ollix-qmeta-822a818/src/standard.cpp \
        ./ollix-qmeta-822a818/src/tiff.cpp \
        ./ollix-qmeta-822a818/src/xmp.cpp \

FORMS=./PhotoFrame/pfleftctrlpane.ui \
      ./PhotoFrame/pfprjctrlpane.ui \
      ./PhotoFrame/photoframe.ui \
      ./PhotoFrame/printercfgdlg.ui

# win32 {
#     SOURCES += hellowin.cpp
# }
# unix {
#     SOURCES += hellounix.cpp
# }

MOC_DIR = ./moc_tmps
OBJECTS_DIR = ./obj_tmps
RCC_DIR = ./rcc_tmps
UI_DIR = ./ui_tmps

RESOURCES     = ./PhotoFrame/photoframe.qrc
win32:RC_FILE       = ./PhotoFrame/PhotoFrame.pro.rc
macx:ICON          = ./PhotoFrame/Resources/images/AppIcon.icns

INCLUDEPATH += ./ollix-qmeta-822a818/include ./PhotoFrame
win32:LIBS += Winspool.lib User32.lib shell32.lib Dbghelp.lib Gdi32.lib
CONFIG += stl qt
QT += xml





