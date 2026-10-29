CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = daytime_client

all: $(TARGET)

$(TARGET): client.cpp
	$(CXX) $(CXXFLAGS) client.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)
