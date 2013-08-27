#!/bin/bash -x

#
# Generated - do not edit!
#

# Macros
TOP=`pwd`
CND_PLATFORM=MinGW-Windows
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build
CND_DLIB_EXT=dll
NBTMPDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tmp-packaging
TMPDIRNAME=tmp-packaging
OUTPUT_PATH=${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/k2-win
OUTPUT_BASENAME=k2-win
PACKAGE_TOP_DIR=k2-win/

# Functions
function checkReturnCode
{
    rc=$?
    if [ $rc != 0 ]
    then
        exit $rc
    fi
}
function makeDirectory
# $1 directory path
# $2 permission (optional)
{
    mkdir -p "$1"
    checkReturnCode
    if [ "$2" != "" ]
    then
      chmod $2 "$1"
      checkReturnCode
    fi
}
function copyFileToTmpDir
# $1 from-file path
# $2 to-file path
# $3 permission
{
    cp "$1" "$2"
    checkReturnCode
    if [ "$3" != "" ]
    then
        chmod $3 "$2"
        checkReturnCode
    fi
}

# Setup
cd "${TOP}"
mkdir -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package
rm -rf ${NBTMPDIR}
mkdir -p ${NBTMPDIR}

# Copy files and create directories and links
cd "${TOP}"
makeDirectory "${NBTMPDIR}/k2-win"
copyFileToTmpDir "${OUTPUT_PATH}.exe" "${NBTMPDIR}/${PACKAGE_TOP_DIR}${OUTPUT_BASENAME}.exe" 0755

cd "${TOP}"
makeDirectory "${NBTMPDIR}/k2-win"
copyFileToTmpDir "../lib/win32/libFLAC-8.dll" "${NBTMPDIR}/${PACKAGE_TOP_DIR}libFLAC-8.dll" 0755

cd "${TOP}"
makeDirectory "${NBTMPDIR}/k2-win"
copyFileToTmpDir "../lib/win32/libjpeg-9.dll" "${NBTMPDIR}/${PACKAGE_TOP_DIR}libjpeg-9.dll" 0755

cd "${TOP}"
makeDirectory "${NBTMPDIR}/k2-win"
copyFileToTmpDir "../lib/win32/libogg-0.dll" "${NBTMPDIR}/${PACKAGE_TOP_DIR}libogg-0.dll" 0755

cd "${TOP}"
makeDirectory "${NBTMPDIR}/k2-win"
copyFileToTmpDir "../lib/win32/libpng16-16.dll" "${NBTMPDIR}/${PACKAGE_TOP_DIR}libpng16-16.dll" 0755

cd "${TOP}"
makeDirectory "${NBTMPDIR}/k2-win"
copyFileToTmpDir "../lib/win32/libvorbis-0.dll" "${NBTMPDIR}/${PACKAGE_TOP_DIR}libvorbis-0.dll" 0755

cd "${TOP}"
makeDirectory "${NBTMPDIR}/k2-win"
copyFileToTmpDir "../lib/win32/libvorbisfile-3.dll" "${NBTMPDIR}/${PACKAGE_TOP_DIR}libvorbisfile-3.dll" 0755

cd "${TOP}"
makeDirectory "${NBTMPDIR}/k2-win"
copyFileToTmpDir "../lib/win32/zlib1.dll" "${NBTMPDIR}/${PACKAGE_TOP_DIR}zlib1.dll" 0755

cd "${TOP}"
makeDirectory "${NBTMPDIR}/k2-win/resources-pkg"
copyFileToTmpDir "../resources-pkg/font.zip" "${NBTMPDIR}/${PACKAGE_TOP_DIR}resources-pkg/font.zip" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}/k2-win/resources-pkg"
copyFileToTmpDir "../resources-pkg/l10n.zip" "${NBTMPDIR}/${PACKAGE_TOP_DIR}resources-pkg/l10n.zip" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}/k2-win/resources-pkg"
copyFileToTmpDir "../resources-pkg/music.zip" "${NBTMPDIR}/${PACKAGE_TOP_DIR}resources-pkg/music.zip" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}/k2-win/resources-pkg"
copyFileToTmpDir "../resources-pkg/sound.zip" "${NBTMPDIR}/${PACKAGE_TOP_DIR}resources-pkg/sound.zip" 0644

cd "${TOP}"
makeDirectory "${NBTMPDIR}/k2-win/resources-pkg"
copyFileToTmpDir "../resources-pkg/sprite.zip" "${NBTMPDIR}/${PACKAGE_TOP_DIR}resources-pkg/sprite.zip" 0644


# Generate zip file
cd "${TOP}"
rm -f ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/k2-win.zip
cd ${NBTMPDIR}
zip -r  ../../../../${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/package/k2-win.zip *
checkReturnCode

# Cleanup
cd "${TOP}"
rm -rf ${NBTMPDIR}
