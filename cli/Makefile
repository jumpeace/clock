#
#	Makefile
#

#	最終目的のファイル
TARGET = result.exe

#	ソースファイル(*.c)の一覧
SRCS = country.c city.c time.c clock.c main.c

#	オブジェクトファイル(*.o)の一覧
OBJS = $(SRCS:.c=.o)

#	ヘッダファイルの一覧(今は何もなし)
HEADERS = bool.h country.h city.h time.h clock.h

#	コンパイラ・リンカの指定
CC = gcc
CCFLAGS = -Wall -I/usr/include/opengl
LD = gcc
LDFLAGS =
LIBS = -lm

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