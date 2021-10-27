#
#	Makefile
#

#	最終目的のファイル
TARGET = dist/result.exe

#	ソースファイル(*.c)の一覧
SRCS = \
	src/base/dim.cpp src/base/color.cpp \
	src/cli/country.cpp src/cli/city.cpp src/cli/time.cpp src/cli/clock.cpp \
	src/gli/gl.cpp \
	src/main.cpp

#	オブジェクトファイル(*.o)の一覧
OBJS = $(SRCS:.cpp=.o)

#	ヘッダファイルの一覧
HEADERS = \
	src/base/dim.h src/base/color.h \
	src/cli/country.h src/cli/city.h src/cli/time.h src/cli/clock.h \
	src/gli/gl.h

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