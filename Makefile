CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2
TARGET = mcal

PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

SRC = main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

install: $(TARGET)
	install -Dm755 $(TARGET) $(BINDIR)/$(TARGET)
	@echo "安装完成: $(BINDIR)/$(TARGET)"

uninstall:
	rm -f $(BINDIR)/$(TARGET)
	@echo "已卸载: $(BINDIR)/$(TARGET)"

.PHONY: all clean install uninstall
