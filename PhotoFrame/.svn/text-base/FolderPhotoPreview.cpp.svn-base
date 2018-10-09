/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include "FolderPhotoPreview.h"
#include "qmeta/jpeg.h"



#define IMG_SIZE_X	120
#define IMG_SIZE_Y	147

#define IMG_SCALESIZE_X	120
#define IMG_SCALESIZE_Y	157

#define IMG_X_MARGIN 10
#define IMG_Y_MARGIN 10
#define IMG_LABEL_MARGIN	10 

#define IMG_LABEL_HEIGHT 15
FolderPicPreview::FolderPicPreview(QWidget *parent): PictureView(parent), 
	_pListThread(NULL), _skipjpgpreview(false), _imgwidth(IMG_SIZE_X), _imgheight(IMG_SIZE_Y)

{
	setStyleSheet( "QGraphicsView { border-style: none; }" );
	connect(this, SIGNAL(_filefoundsig()), this, SLOT(_newImgInserted()));
}
	
FolderPicPreview::~FolderPicPreview()
{
	if (_pListThread )
	{
		_pListThread->waitForFinished();
		delete _pListThread;
		_pListThread = NULL;
	}
}

void FolderPicPreview::showFolder(const QString &path)
{
	this->_curpath = path;
	this->clear();

	QFuture<void> future = QtConcurrent::run(_ShowFolderPicPreview1, this);
	_pListThread = new QFuture<void>(future);
}

void FolderPicPreview::_ShowFolderPicPreview1( void * context )
{
	FolderPicPreview *pThis = (FolderPicPreview*)context;
	if ( !pThis )
	{
		return ;
	}
	pThis->_listAllImgFiles();

}


void FolderPicPreview::_listAllImgFiles()
{
	QDir dir(_curpath);

	dir.setFilter(QDir::Files);
	dir.setSorting(QDir::Size | QDir::Reversed);
	QStringList filters;
	filters << "*.jpg" << "*.gif" << "*.bmp" << "*.png" << "*.jpeg";
	dir.setNameFilters(filters);

	QFileInfoList list = dir.entryInfoList();
	for (int subindex=0;subindex<list.size(); subindex++ )
	{
		if ( _curpath.length() <= 0 )
		{
			break;
		}
		QFileInfo fileInfo = list.at(subindex);
		QString check = fileInfo.absoluteFilePath();
		QString dirpath = check;
		if ( dirpath.at(dirpath.length()-1) == '/' )
		{
			dirpath = dirpath.left(dirpath.length()-1);
		}
		int lastslashpos = dirpath.lastIndexOf("\\");
		if ( lastslashpos == -1 )
		{
			lastslashpos = dirpath.lastIndexOf("/");
		}
		QString dirname;
		if ( lastslashpos > 0 & dirpath.length()-lastslashpos-1 >0 )
		{
			dirname = dirpath.right(dirpath.length()-lastslashpos-1);
		}
		else
		{
			dirname = dirpath;
		}
		if ( '/' == dirname.at(dirname.length()-1) )
		{
			dirname = dirname.left(dirname.length()-1);
		}

		//QFuture<void> future = QtConcurrent::run(AddImg, this, dirname, dirpath);
		QImage smallimg;
		if ( !_skipjpgpreview && (dirname.lastIndexOf("jpg") > 0  || dirname.lastIndexOf("JPG") > 0) )
		{
			qmeta::Jpeg jpgfile(dirpath);
			QByteArray data = jpgfile.Thumbnail();
			if ( data.size() )
			{
				QString thumbnailpath;
				thumbnailpath += ".\\";
				thumbnailpath += dirname;
				thumbnailpath += ".thumb";

				QFile file(thumbnailpath);
				file.open(QIODevice::WriteOnly);
				file.write(data);
				file.close();
				
				//QPixmap pixmap(thumbnailpath);

				//QRect pixrect = pixmap.rect();
				QImage img(thumbnailpath);
				QRect imgrect = img.rect();
				int width = img.width();
				int height = img.height();
				if ( height > width )
				{
					width = (_imgwidth*1.0)/height * width;
					height = _imgheight;
				}
				else
				{
					height = (_imgheight*1.0)/width * height;
					width = _imgwidth;
				}
				smallimg = img.scaled(_imgwidth, _imgheight, Qt::KeepAspectRatio);

				bool ret =  QFile::remove(thumbnailpath);

				if ( ret)
				{
				}

				
			}
			else
			{
				QImage img(dirpath);
				int width = img.width();
				int height = img.height();
				if ( height > width )
				{
					width = (_imgwidth*1.0)/height * width;
					height = _imgheight;
				}
				else
				{
					height = (_imgheight*1.0)/width * height;
					width = _imgwidth;
				}
				smallimg = img.scaled(width, height, Qt::KeepAspectRatio);
				//smallimg = img;
	
			}
		}
		else
		{
			QImage img(dirpath);
			int width = img.width();
			int height = img.height();
			if ( height > width )
			{
				width = (_imgwidth*1.0)/height * width;
				height = _imgheight;
			}
			else
			{
				height = (_imgheight*1.0)/width * height;
				width = _imgwidth;
			}
			smallimg = img.scaled(width, height, Qt::KeepAspectRatio);
			//smallimg = img;

		}

		IMG_ITM imgItm;
		imgItm.name = dirname;
		imgItm._img = new QImage(smallimg);
		imgItm.path = dirpath;
		_imglock.lock();
		imglst.push_back(imgItm);
		_imglock.unlock();

		emit _filefoundsig();
	}
	this->_finished = true;

}

void FolderPicPreview::_newImgInserted()
{
	bool gotone = false;
	IMG_ITM imgItm;
	list<IMG_ITM> tmpimglst;

	_imglock.lock();
	tmpimglst=imglst;
	imglst.clear();
	_imglock.unlock();

	while(!tmpimglst.empty() )
	{
		gotone = true;
		imgItm = tmpimglst.front();
		tmpimglst.pop_front();
		addItem( QPixmap::fromImage(*imgItm._img) ,imgItm.name,imgItm.path);
		delete imgItm._img;
	}

}

void FolderPicPreview::setImgSize(int width, int height)
{
	this->_imgwidth = width;
	this->_imgheight = height;
	PictureView::setImgSize(width, height);
}
