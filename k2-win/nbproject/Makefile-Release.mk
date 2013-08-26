#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/810000161/k2_error.o \
	${OBJECTDIR}/_ext/810000161/k2_l10n.o \
	${OBJECTDIR}/_ext/810000161/k2_log.o \
	${OBJECTDIR}/_ext/810000161/k2_physfs.o \
	${OBJECTDIR}/_ext/810000161/k2_random.o \
	${OBJECTDIR}/_ext/692619436/gl3w.o \
	${OBJECTDIR}/_ext/86820599/cJSON.o \
	${OBJECTDIR}/_ext/281919435/SOIL.o \
	${OBJECTDIR}/_ext/281919435/image_DXT.o \
	${OBJECTDIR}/_ext/281919435/image_helper.o \
	${OBJECTDIR}/_ext/281919435/stb_image_aug.o \
	${OBJECTDIR}/_ext/1360937237/_main.o \
	${OBJECTDIR}/_ext/1360937237/app.o \
	${OBJECTDIR}/_ext/1360937237/audio.o \
	${OBJECTDIR}/_ext/1360937237/config.o \
	${OBJECTDIR}/_ext/1360937237/core.o \
	${OBJECTDIR}/_ext/1360937237/create_level.o \
	${OBJECTDIR}/_ext/1360937237/display.o \
	${OBJECTDIR}/_ext/1360937237/event.o \
	${OBJECTDIR}/_ext/1360937237/game.o \
	${OBJECTDIR}/_ext/1360937237/keyboard.o \
	${OBJECTDIR}/_ext/1360937237/physfsrwops.o \
	${OBJECTDIR}/_ext/1360937237/process.o \
	${OBJECTDIR}/_ext/1360937237/processes.o \
	${OBJECTDIR}/_ext/1360937237/score.o \
	${OBJECTDIR}/_ext/1360937237/sprites.o \
	${OBJECTDIR}/_ext/1360937237/thing.o \
	${OBJECTDIR}/_ext/1360937237/timer.o \
	${OBJECTDIR}/_ext/1360937237/timer_blit.o \
	${OBJECTDIR}/_ext/1360937237/util.o \
	${OBJECTDIR}/_ext/1360937237/view.o \
	${OBJECTDIR}/_ext/1360937237/view_building.o \
	${OBJECTDIR}/_ext/1360937237/view_fade.o \
	${OBJECTDIR}/_ext/1360937237/view_score.o \
	${OBJECTDIR}/_ext/1360937237/view_title.o \
	${OBJECTDIR}/_ext/1519371020/view_pause.o \
	${OBJECTDIR}/_ext/1360937237/window.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/k2-win.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/k2-win.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/k2-win ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/810000161/k2_error.o: ../src-k2/k2_error.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/810000161
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/810000161/k2_error.o ../src-k2/k2_error.c

${OBJECTDIR}/_ext/810000161/k2_l10n.o: ../src-k2/k2_l10n.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/810000161
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/810000161/k2_l10n.o ../src-k2/k2_l10n.c

${OBJECTDIR}/_ext/810000161/k2_log.o: ../src-k2/k2_log.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/810000161
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/810000161/k2_log.o ../src-k2/k2_log.c

${OBJECTDIR}/_ext/810000161/k2_physfs.o: ../src-k2/k2_physfs.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/810000161
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/810000161/k2_physfs.o ../src-k2/k2_physfs.c

${OBJECTDIR}/_ext/810000161/k2_random.o: ../src-k2/k2_random.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/810000161
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/810000161/k2_random.o ../src-k2/k2_random.c

${OBJECTDIR}/_ext/692619436/gl3w.o: ../src-lib/GL3/gl3w.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/692619436
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/692619436/gl3w.o ../src-lib/GL3/gl3w.c

${OBJECTDIR}/_ext/86820599/cJSON.o: ../src-lib/cJSON/cJSON.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/86820599
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/86820599/cJSON.o ../src-lib/cJSON/cJSON.c

${OBJECTDIR}/_ext/281919435/SOIL.o: ../src-lib/soil-20080707/src/SOIL.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/281919435
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/281919435/SOIL.o ../src-lib/soil-20080707/src/SOIL.c

${OBJECTDIR}/_ext/281919435/image_DXT.o: ../src-lib/soil-20080707/src/image_DXT.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/281919435
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/281919435/image_DXT.o ../src-lib/soil-20080707/src/image_DXT.c

${OBJECTDIR}/_ext/281919435/image_helper.o: ../src-lib/soil-20080707/src/image_helper.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/281919435
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/281919435/image_helper.o ../src-lib/soil-20080707/src/image_helper.c

${OBJECTDIR}/_ext/281919435/stb_image_aug.o: ../src-lib/soil-20080707/src/stb_image_aug.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/281919435
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/281919435/stb_image_aug.o ../src-lib/soil-20080707/src/stb_image_aug.c

${OBJECTDIR}/_ext/1360937237/_main.o: ../src/_main.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/_main.o ../src/_main.c

${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c

${OBJECTDIR}/_ext/1360937237/audio.o: ../src/audio.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/audio.o ../src/audio.c

${OBJECTDIR}/_ext/1360937237/config.o: ../src/config.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/config.o ../src/config.c

${OBJECTDIR}/_ext/1360937237/core.o: ../src/core.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/core.o ../src/core.c

${OBJECTDIR}/_ext/1360937237/create_level.o: ../src/create_level.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/create_level.o ../src/create_level.c

${OBJECTDIR}/_ext/1360937237/display.o: ../src/display.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/display.o ../src/display.c

${OBJECTDIR}/_ext/1360937237/event.o: ../src/event.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/event.o ../src/event.c

${OBJECTDIR}/_ext/1360937237/game.o: ../src/game.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/game.o ../src/game.c

${OBJECTDIR}/_ext/1360937237/keyboard.o: ../src/keyboard.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/keyboard.o ../src/keyboard.c

${OBJECTDIR}/_ext/1360937237/physfsrwops.o: ../src/physfsrwops.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/physfsrwops.o ../src/physfsrwops.c

${OBJECTDIR}/_ext/1360937237/process.o: ../src/process.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/process.o ../src/process.c

${OBJECTDIR}/_ext/1360937237/processes.o: ../src/processes.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/processes.o ../src/processes.c

${OBJECTDIR}/_ext/1360937237/score.o: ../src/score.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/score.o ../src/score.c

${OBJECTDIR}/_ext/1360937237/sprites.o: ../src/sprites.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/sprites.o ../src/sprites.c

${OBJECTDIR}/_ext/1360937237/thing.o: ../src/thing.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/thing.o ../src/thing.c

${OBJECTDIR}/_ext/1360937237/timer.o: ../src/timer.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/timer.o ../src/timer.c

${OBJECTDIR}/_ext/1360937237/timer_blit.o: ../src/timer_blit.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/timer_blit.o ../src/timer_blit.c

${OBJECTDIR}/_ext/1360937237/util.o: ../src/util.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/util.o ../src/util.c

${OBJECTDIR}/_ext/1360937237/view.o: ../src/view.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/view.o ../src/view.c

${OBJECTDIR}/_ext/1360937237/view_building.o: ../src/view_building.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/view_building.o ../src/view_building.c

${OBJECTDIR}/_ext/1360937237/view_fade.o: ../src/view_fade.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/view_fade.o ../src/view_fade.c

${OBJECTDIR}/_ext/1360937237/view_score.o: ../src/view_score.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/view_score.o ../src/view_score.c

${OBJECTDIR}/_ext/1360937237/view_title.o: ../src/view_title.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/view_title.o ../src/view_title.c

${OBJECTDIR}/_ext/1519371020/view_pause.o: ../src/views/view_pause.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1519371020
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1519371020/view_pause.o ../src/views/view_pause.c

${OBJECTDIR}/_ext/1360937237/window.o: ../src/window.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1360937237
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1360937237/window.o ../src/window.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/k2-win.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
