/***************************************************************************
 *   Copyright (C) 2014 by Sergey N Chursanov                              *
 *                                                                         *
 *   email: masakra@mail.ru                                                *
 *   jabber: masakra@jabber.ru                                             *
 *                                                                         *
 *   Permission is hereby granted, free of charge, to any person obtaining *
 *   a copy of this software and associated documentation files (the       *
 *   "Software"), to deal in the Software without restriction, including   *
 *   without limitation the rights to use, copy, modify, merge, publish,   *
 *   distribute, sublicense, and/or sell copies of the Software, and to    *
 *   permit persons to whom the Software is furnished to do so, subject to *
 *   the following conditions:                                             *
 *                                                                         *
 *   The above copyright notice and this permission notice shall be        *
 *   included in all copies or substantial portions of the Software.       *
 *                                                                         *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       *
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    *
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. *
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR     *
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR *
 *   OTHER DEALINGS IN THE SOFTWARE.                                       *
 ***************************************************************************/

#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include "FormMain.h"

int
main( int argc, char ** argv )
{
	QApplication app( argc, argv );

	app.setApplicationName("skala");
	app.setApplicationVersion( VERSION );
	app.setOrganizationName("Nordavia-RA");

	QTranslator qtTranslator;
#ifdef Q_OS_FREEBSD
	qtTranslator.load("/usr/local/share/qt4/translations/qt_ru.qm");
//#elif Q_OS_LINUX
#else
	qtTranslator.load("qt_ru.qm");
#endif
	app.installTranslator( &qtTranslator );

	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("UTF-8") );

	FormMain fm;
	fm.show();

	return app.exec();
};

