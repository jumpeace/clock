#
#	Makefile
#

#	最終目的のファイル
TARGET = result.exe

#	ソースファイル(*.c)の一覧
SRCS = country.cpp city.cpp time.cpp clock.cpp main.cpp

#	オブジェクトファイル(*.o)の一覧
OBJS = $(SRCS:.c=.o)

#	ヘッダファイルの一覧
HEADERS = country.h city.h time.h clock.h

#	コンパイラ・リンカの指定
CC = g++
CCFLAGS = -Wall -I/usr/include/opengl
LD = g++
LDFLAGS =
LIBS = 

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