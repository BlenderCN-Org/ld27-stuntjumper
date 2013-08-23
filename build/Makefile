SRCDIR = ../src-xpl ../src/game ../src-server
INCDIR = -I../include-xpl -I../include -I../include-lib/common
CFLAGS = -g -Wall $(INCDIR) -O3 -std=gnu99
LFLAGS = -lpthread -lm -lrt
CC = gcc

SOURCES = ../src-server/echoserver_main.c ../src-xpl/k2_platform.c ../src/game/packet.c ../src/net/udpnet.c
OBJECTS = $(patsubst %.c,%.o,$(wildcard *.c))
TARGET = echoserver

.PHONY : all

all: clean import depend build

build: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(TARGET)

import:
	@echo "import"
	@rm -f *.c *~
	@for file in $(SOURCES); do ln -s $$file ; done

depend:
	@echo "depend"
	@makedepend $(INCDIR) -Y -m $(SOURCES)

clean:
	@echo "clean"
	@rm -f *.o *.bak *.c *~ *%

##### End of makefile
# DO NOT DELETE

../src-server/echoserver_main.o: ../include-lib/common/uthash.h
../src-server/echoserver_main.o: ../include-xpl/xpl.h
../src-server/echoserver_main.o: ../include/app_settings.h
../src-server/echoserver_main.o: ../include-xpl/k2_platform.h
../src-server/echoserver_main.o: ../include-xpl/k2_memory.h
../src-server/echoserver_main.o: ../include-xpl/k2_rc.h
../src-server/echoserver_main.o: ../include-xpl/k2_log.h
../src-server/echoserver_main.o: ../include-xpl/k2_file.h
../src-server/echoserver_main.o: ../include-xpl/k2_dynamic_buffer.h
../src-server/echoserver_main.o: ../include-xpl/k2_l10n.h
../src-server/echoserver_main.o: ../include-xpl/k2_hash.h
../src-server/echoserver_main.o: ../include/game/game.h
../src-server/echoserver_main.o: ../include-xpl/k2_vec2.h
../src-server/echoserver_main.o: ../include-xpl/k2_vec4.h
../src-server/echoserver_main.o: ../include-xpl/k2_vec3.h
../src-server/echoserver_main.o: ../include-xpl/k2_ivec2.h
../src-server/echoserver_main.o: ../include-xpl/k2_irect.h
../src-server/echoserver_main.o: ../include-xpl/k2_vec.h
../src-server/echoserver_main.o: ../include-xpl/k2_math.h
../src-server/echoserver_main.o: ../include-xpl/k2_ivec3.h
../src-server/echoserver_main.o: ../include-xpl/k2_ivec4.h
../src-server/echoserver_main.o: ../include-xpl/k2_rect.h
../src-server/echoserver_main.o: ../include-xpl/k2_plane.h
../src-server/echoserver_main.o: ../include-xpl/k2_sphere.h
../src-server/echoserver_main.o: ../include-xpl/k2_quaternion.h
../src-server/echoserver_main.o: ../include-xpl/k2_mat2.h
../src-server/echoserver_main.o: ../include-xpl/k2_mat3.h
../src-server/echoserver_main.o: ../include-xpl/k2_mat4.h
../src-server/echoserver_main.o: ../include/audio/audio.h
../src-server/echoserver_main.o: ../include/game/packet.h
../src-server/echoserver_main.o: ../include/net/udpnet.h
../src-xpl/k2_platform.o: ../include-xpl/xpl.h ../include/app_settings.h
../src-xpl/k2_platform.o: ../include-xpl/k2_platform.h
../src-xpl/k2_platform.o: ../include-xpl/k2_memory.h
../src-xpl/k2_platform.o: ../include-xpl/k2_rc.h ../include-xpl/k2_log.h
../src-xpl/k2_platform.o: ../include-xpl/k2_file.h
../src-xpl/k2_platform.o: ../include-xpl/k2_dynamic_buffer.h
../src-xpl/k2_platform.o: ../include-xpl/k2_l10n.h
../src/game/packet.o: ../include/game/packet.h ../include/game/game.h
../src/game/packet.o: ../include-xpl/k2_vec2.h ../include-xpl/k2_platform.h
../src/game/packet.o: ../include-xpl/xpl.h ../include/app_settings.h
../src/game/packet.o: ../include-xpl/k2_memory.h ../include-xpl/k2_rc.h
../src/game/packet.o: ../include-xpl/k2_log.h ../include-xpl/k2_file.h
../src/game/packet.o: ../include-xpl/k2_dynamic_buffer.h
../src/game/packet.o: ../include-xpl/k2_l10n.h ../include-xpl/k2_vec4.h
../src/game/packet.o: ../include-xpl/k2_vec3.h ../include-xpl/k2_ivec2.h
../src/game/packet.o: ../include-xpl/k2_irect.h ../include-xpl/k2_vec.h
../src/game/packet.o: ../include-xpl/k2_math.h ../include-xpl/k2_ivec3.h
../src/game/packet.o: ../include-xpl/k2_ivec4.h ../include-xpl/k2_rect.h
../src/game/packet.o: ../include-xpl/k2_plane.h ../include-xpl/k2_sphere.h
../src/game/packet.o: ../include-xpl/k2_quaternion.h
../src/game/packet.o: ../include-xpl/k2_mat2.h ../include-xpl/k2_mat3.h
../src/game/packet.o: ../include-xpl/k2_mat4.h ../include/audio/audio.h
../src/game/packet.o: ../include-lib/common/uthash.h
../src/net/udpnet.o: ../include/net/udpnet.h ../include-xpl/xpl.h
../src/net/udpnet.o: ../include/app_settings.h ../include-xpl/k2_platform.h
../src/net/udpnet.o: ../include-xpl/k2_memory.h ../include-xpl/k2_rc.h
../src/net/udpnet.o: ../include-xpl/k2_log.h ../include-xpl/k2_file.h
../src/net/udpnet.o: ../include-xpl/k2_dynamic_buffer.h
../src/net/udpnet.o: ../include-xpl/k2_l10n.h
