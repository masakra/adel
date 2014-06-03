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

/*! \class FormMain
 *
 * \brief 
 */

#ifndef FORMMAIN_H
#define FORMMAIN_H

#define LAST_DIR "last_dir"

#include <QDialog>

class QFileInfo;
class QLineEdit;
class QRadioButton;

class FormMain : public QDialog
{
	Q_OBJECT

	private:
		void createWidgets();

		QLineEdit * m_editPath,
				  * m_editTitle,
				  * m_editDescription,
				  * m_editVersion,
				  * m_editTypeOfContent,
				  * m_editNomenclature,
				  * m_editName,
				  * m_editMd5,
				  * m_editSha1;

		QRadioButton * m_radioMd5,
					 * m_radioSha1;

		void calcChecksum( const QString & fileName );

		QString buildXmlFile( const QFileInfo & fileInfo ) const;

	private Q_SLOTS:
		void browse();
		void save();

	public:
		FormMain( QWidget * parent = 0 );
};

#endif

