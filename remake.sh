#!/bin/sh


TARGET="adel"
VERSION="0.1.1"
MODULES="xml"

if [ ${OS} ]	# На Win* выдает что-то типа Windows_NT, на других платформах не определена
then
	GMAKE="/c/MinGW/bin/mingw32-make";
	QMAKE="/c/Qt/4.8.4/bin/qmake";
	#LIBS="-L../../naragui/release -L../../narapg/release -lnaragui -lnarapg"
else
	GMAKE="/usr/local/bin/gmake";
	QMAKE="/usr/local/bin/qmake-qt4";
	CXX_FLAGS="-mmmx -msse -msse2 -msse3"
	SPEC="-spec freebsd-clang"
	#SPEC="-spec freebsd-g++"
	#LIBS="-L../../naragui -L../../narapg -lnaragui -lnarapg"
fi

DEFINES="VERSION=\\\\\\\"${VERSION}\\\\\\\""	# aaaaaaaaaaaaaaaaa fuck !!
#INCLUDEPATH="../../naragui"

${GMAKE} distclean

${QMAKE} -project

if [ -e ${TARGET}.pro ]
then
	echo "QT += ${MODULES}" >> ${TARGET}.pro;
	echo "modules \"${MODULES}\" was added.";
	# C++ flags
	echo "QMAKE_CXXFLAGS += ${CXX_FLAGS}" >> ${TARGET}.pro;
	echo "C++ flags \"${CXX_FLAGS}\" was added.";
	# includepath
	echo "INCLUDEPATH += ${INCLUDEPATH}" >> ${TARGET}.pro;
	echo "include += ${INCLUDEPATH}";
	# defines
	echo "DEFINES += ${DEFINES}" >> ${TARGET}.pro;
	echo "defines += ${DEFINES}";
	# libraries
	echo "LIBS += ${LIBS}" >> ${TARGET}.pro;
	echo "libraries += ${LIBS}";
	${QMAKE} ${SPEC}
else
	echo "ERROR: file ${TARGET}.pro not found."
fi

