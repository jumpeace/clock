#
#	Makefile
#

#	最終目的のファイル
TARGET = j18411.exe

#	ソースファイル(*.c)の一覧
SRCS = \
	dim.cpp color.cpp funcs.cpp \
	country.cpp city.cpp clock.cpp \
	my_gl.cpp window.cpp draw_pattern.cpp draw.cpp \
	global.cpp main.cpp

#	オブジェクトファイル(*.o)の一覧
OBJS = $(SRCS:.cpp=.o)

#	ヘッダファイルの一覧
HEADERS = \
	dim.h color.h funcs.h \
	country.h city.h clock.h \
	my_gl.h window.h draw_pattern.h draw.h \
	global.h

ICONRC = myicon.rc
ICONOBJ = myicon.o

#	コンパイラ・リンカの指定
CC = i686-pc-cygwin-g++
CCFLAGS = -Wall -I/usr/include/opengl
LD = i686-pc-cygwin-g++
LD = g++
LDFLAGS =
LIBS = -lglpng -lglut32 -lglu32 -lopengl32 -lm

#	OBJSからTARGETを作る方法
$(TARGET) : $(OBJS)
	i686-pc-cygwin-windres -i $(ICONRC) -o $(ICONOBJ)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS) $(ICONOBJ) $(LIBS)

.cpp.o :
	$(CC) $(CCFLAGS) -c $<

#	*.o は HEADERS と Makefile に依存(これらが書き換わったときにも*.oを再構築)
$(OBJS) : $(HEADERS) Makefile


#	make cleanとしたときに実行されるコマンド
clean :
	rm -f $(OBJS)
