#
#	Makefile
#

#	最終目的のファイル
TARGET = dist/result.exe

#	ソースファイル(*.c)の一覧
SRCS = \
	src/base/dim.cpp src/base/color.cpp src/base/math.cpp \
	src/cui/country.cpp src/cui/city.cpp src/cui/time.cpp src/cui/clock.cpp \
	src/gui/tool.cpp src/gui/window.cpp src/gui/draw_pattern.cpp src/gui/draw.cpp \
	src/global.cpp src/main.cpp

#	オブジェクトファイル(*.o)の一覧
OBJS = $(SRCS:.cpp=.o)

#	ヘッダファイルの一覧
HEADERS = \
	src/base/dim.h src/base/color.h src/base/math.h \
	src/cui/country.h src/cui/city.h src/cui/time.h src/cui/clock.h \
	src/gui/tool.h src/gui/window.h src/gui/draw_pattern.h src/gui/draw.h \
	src/global.h

#	コンパイラ・リンカの指定
CC = g++
CCFLAGS = -Wall -I/usr/include/opengl
LD = g++
LDFLAGS =
LIBS = -lglpng -lglut -lGLU -lGL

#	OBJSからTARGETを作る方法
$(TARGET) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET) $(LIBS)

#	*.c から *.o を作る方法
.c.o :
	$(CC) $(CCFLAGS) -c $<

#	*.o は HEADERS と Makefile に依存(これらが書き換わったときにも*.oを再構築)
$(OBJS) : $(HEADERS) Makefile

#	make cleanとしたときに実行されるコマンド
clean :
	rm -f $(OBJS)

clean-all :
	rm -f $(OBJS) $(TARGET)