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

#include "FormMain.h"

#include <QtGui>
#include <QtXml>

FormMain::FormMain( QWidget * parent )
	: QDialog( parent )
{
	setWindowTitle( QString("%1: %2 - v%3")
			.arg( qApp->organizationName(), qApp->applicationName(), qApp->applicationVersion() ) );

	createWidgets();
	resize( 640, 100 );
}

void
FormMain::createWidgets()
{
	m_editPath = new QLineEdit( this );

	QToolButton * buttonBrowse = new QToolButton( this );
	buttonBrowse->setIcon( QIcon::fromTheme("folder", QIcon(":/folder.png") ) );
	connect( buttonBrowse, SIGNAL( clicked() ), SLOT( browse() ) );

	QHBoxLayout * layoutPath = new QHBoxLayout();
	layoutPath->addWidget( m_editPath );
	layoutPath->addWidget( buttonBrowse );

	m_editTitle = new QLineEdit( this );
	m_editTitle->setMaxLength( 24 );
	m_editTitle->setValidator( new QRegExpValidator( QRegExp("[a-zA-Z0-9_]*") ) );
	m_editTitle->setToolTip("The customer's title for the content. Used to distinguish it from other content "
			"of the same type. The title must be limited to 24 alphanumeric or underscore characters.");

	m_editDescription = new QLineEdit( this );
	m_editDescription->setMaxLength( 256 );
	m_editDescription->setToolTip("The description of the content. The descriptions must be limited to 256 "
			"alphanumeric, space and punctuation characters.");

	m_editVersion = new QLineEdit( this );
	m_editVersion->setValidator( new QIntValidator() );
	m_editVersion->setToolTip("The version number of the content. Different titles may have their own version "
			"number. Should be a single positive integer that increments each time the content is updated.");

	m_editTypeOfContent = new QLineEdit ( this );
	m_editTypeOfContent->setToolTip("The JDM Pro-defined content type assigned to the content.");

	m_editNomenclature = new QLineEdit( this );
	m_editNomenclature->setMaxLength( 24 );
	m_editNomenclature->setValidator( new QRegExpValidator( QRegExp("[a-zA-Z0-9_]*") ) );
	m_editNomenclature->setToolTip("A label for the content for display. The label must be limited to 24 "
			"alphanumeric or underscore characters.");

	m_editName = new QLineEdit( this );
	m_editName->setToolTip("The logicalName attribute is intentionally left empty and should not be populated.");

	m_editMd5 = new QLineEdit( this );
	m_editMd5->setReadOnly( true );

	m_editSha1 = new QLineEdit( this );
	m_editSha1->setReadOnly( true );

	m_radioMd5 = new QRadioButton("MD&5", this );
	m_radioMd5->setChecked( true );
	m_radioSha1 = new QRadioButton("SHA&1", this );


	QPushButton * buttonSave = new QPushButton("Сохранить ADEL_Metadata.xml файл", this );
	connect( buttonSave, SIGNAL( clicked() ), SLOT( save() ) );

	QLabel * labelTitle = new QLabel("&title", this ),
		   * labelDescription = new QLabel("&description", this ),
		   * labelVersion = new QLabel("&version", this ),
		   * labelTypeOfContent = new QLabel("type of &content", this ),
		   * labelNomenclature = new QLabel("no&menclature", this ),
		   * labelName = new QLabel("logical &name", this );
		   //* labelMd5 = new QLabel("MD&5", this ),
		   //* labelSha1 = new QLabel("SHA&1", this );

	labelTitle->setBuddy( m_editTitle );
	labelDescription->setBuddy( m_editDescription );
	labelVersion->setBuddy( m_editVersion );
	labelTypeOfContent->setBuddy( m_editTypeOfContent );
	labelNomenclature->setBuddy( m_editNomenclature );
	labelName->setBuddy( m_editName );
	//labelMd5->setBuddy( m_editMd5 );
	//labelSha1->setBuddy( m_editSha1 );

	QGridLayout * layout = new QGridLayout( this );
	layout->addLayout( layoutPath, 0, 0, 1, 2 );

	layout->addWidget( labelTitle, 1, 0, Qt::AlignRight );
	layout->addWidget( m_editTitle, 1, 1 );

	layout->addWidget( labelDescription, 2, 0, Qt::AlignRight );
	layout->addWidget( m_editDescription, 2, 1 );

	layout->addWidget( labelVersion, 3, 0, Qt::AlignRight );
	layout->addWidget( m_editVersion, 3, 1 );

	layout->addWidget( labelTypeOfContent, 4, 0, Qt::AlignRight );
	layout->addWidget( m_editTypeOfContent, 4, 1 );

	layout->addWidget( labelNomenclature, 5, 0, Qt::AlignRight );
	layout->addWidget( m_editNomenclature, 5, 1 );

	layout->addWidget( labelName, 6, 0, Qt::AlignRight );
	layout->addWidget( m_editName, 6, 1 );

	layout->addWidget( m_radioMd5, 7, 0, Qt::AlignLeft );
	layout->addWidget( m_editMd5, 7, 1 );

	layout->addWidget( m_radioSha1, 8, 0, Qt::AlignLeft );
	layout->addWidget( m_editSha1, 8, 1 );

	layout->addWidget( buttonSave, 9, 0, 1, 2, Qt::AlignRight );
}


void
FormMain::browse()		// slot
{
	QSettings settings;

	const QString fileName = QFileDialog::getOpenFileName( this, "Исходный файл",
			settings.value( LAST_DIR, QDir::homePath() ).toString() );

	if ( fileName.isEmpty() )
		return;

	m_editPath->setText( fileName );

	calcChecksum( fileName );
}

void
FormMain::calcChecksum( const QString & fileName )
{
	QFile file( fileName );

	if ( ! file.exists() ) {
		QMessageBox::critical( this, "Ошибка", "Файл не существует");
		return;
	}

	if ( ! file.open( QIODevice::ReadOnly ) ) {
		QMessageBox::critical( this, "Ошибка", "Не возможно открыть файл на чтение");
		return;
	}

	QSettings settings;
	settings.setValue( LAST_DIR, QFileInfo( fileName ).absoluteDir().absolutePath() );

	qApp->setOverrideCursor( QCursor( Qt::WaitCursor ) );

	QByteArray array = file.readAll();

	QCryptographicHash * md5 = new QCryptographicHash( QCryptographicHash::Md5 ),
					   * sha1 = new QCryptographicHash( QCryptographicHash::Sha1 );

	md5->addData( array );
	m_editMd5->setText( md5->result().toHex() );
	delete md5;

	sha1->addData( array );
	m_editSha1->setText( sha1->result().toHex() );
	delete sha1;

	qApp->restoreOverrideCursor();

	file.close();
}

void
FormMain::save()	// slot
{
	const QFileInfo fileInfo( m_editPath->text() );

	const QString xmlText = buildXmlFile( fileInfo );

	if ( xmlText.isEmpty() )
		return;

	QFile xmlFile( fileInfo.absoluteDir().filePath("ADEL_Metadata.xml") );

	if ( ! xmlFile.open( QIODevice::WriteOnly | QIODevice::Text ) ) {
		QMessageBox::critical( this, "Ошибка записи", QString("Открыть файл %1 на запись нет никакой возможности.")
				.arg( xmlFile.fileName() ) );
		return;
	}

	QTextStream out( &xmlFile );

	out << xmlText;

	xmlFile.close();

	QMessageBox::information( this, "Успех", QString("Файл %1 создан и сохранён").arg( xmlFile.fileName() ) );
}

QString
FormMain::buildXmlFile( const QFileInfo & fileInfo ) const
{
	if ( ! fileInfo.exists() )
		return QString();

	QDomDocument xml;

	QDomElement root = xml.createElement("ADEL_Metadata");
	root.setAttribute("title", m_editTitle->text() );
	root.setAttribute("description", m_editDescription->text() );
	root.setAttribute("version", m_editVersion->text() );
	root.setAttribute("typeOfContent", m_editTypeOfContent->text() );
	root.setAttribute("adelEligible", "true" );
	root.setAttribute("nomenclature", m_editNomenclature->text() );
	root.setAttribute("logicalName", m_editName->text() );
	root.setAttribute("deltaAlgorithm", "xdelta");
	root.setAttribute("loadOnEffectivity", "false");

	QDomElement filesManifest = xml.createElement("FilesManifest"),
				componentFile = xml.createElement("ComponentFile"),
				filePath = xml.createElement("FilePath"),
				fileVersion = xml.createElement("FileVersion"),
				digest = xml.createElement("Digest"),
				digestValue = xml.createElement("DigestValue"),
				digestAlgorithm = xml.createElement("DigestAlgorithm");

	filePath.appendChild( xml.createTextNode("./" + fileInfo.fileName() ) );
	digestValue.appendChild( xml.createTextNode( m_radioMd5->isChecked() ?
				m_editMd5->text() : m_editSha1->text() ) );
	digestAlgorithm.appendChild( xml.createTextNode( m_radioMd5->isChecked() ? "MD5" : "SHA1" ) );

	digest.appendChild( digestValue );
	digest.appendChild( digestAlgorithm );

	componentFile.appendChild( filePath );
	componentFile.appendChild( fileVersion );
	componentFile.appendChild( digest );

	filesManifest.appendChild( componentFile );

	root.appendChild( filesManifest );

	xml.appendChild( root );

	return xml.toString();
}

