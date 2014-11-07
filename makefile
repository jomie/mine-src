TARGET = out
CPP = g++ -g

OBJ_PATH = ./build
OUT_PATH = ./bin
CPPFLAGS += -I./include
CPP_SRCDIR = ./src
CPP_TOOLDIR= ./tools

LDFLAGS = -ljpeg -lpng -lGraphicsMagick -lGraphicsMagick++ -lwebp -llentpdec -llentpenc

CPP_SOURCES = $(foreach d, $(CPP_SRCDIR), $(wildcard $(d)/*.cpp))
CPP_OBJFILES = $(patsubst %.cpp, $(OBJ_PATH)/%.o,$(notdir $(CPP_SOURCES))) 

CPP_TOOLSRC = $(foreach tmp, $(CPP_TOOLDIR), $(wildcard $(tmp)/*.cpp))
CPP_TOOLBIN = $(patsubst %.cpp, $(OUT_PATH)/%, $(notdir $(CPP_TOOLSRC)))
CPP_TOOLOBJ = $(patsubst %.cpp, $(OBJ_PATH)/%.o, $(notdir $(CPP_TOOLSRC)))

vpath %.cpp $(dir $(CPP_SOURCES))
vpath %.o $(OBJ_PATH)

all:target

target: $(TARGET)

$(CPP_OBJFILES): $(OBJ_PATH)/%.o: %.cpp
	@mkdir -p $(OBJ_PATH)
	$(CPP) -c $(CPPFLAGS) -o $@ $<

$(TARGET): $(CPP_OBJFILES)
	@mkdir -p $(OUT_PATH)
	$(CPP) -o  $@ $^ $(LDFLAGS)

.PHONY : clean install tool

tool: $(CPP_TOOLBIN)
$(CPP_TOOLBIN): $(CPP_TOOLOBJ)
	@mkdir -p $(OUT_PATH)
	$(CPP) -o $@ $(OBJ_PATH)/$(notdir $@).o -lpthread 
	
$(CPP_TOOLOBJ): $(OBJ_PATH)/%.o: $(CPP_TOOLDIR)/%.cpp
	@mkdir -p $(OBJ_PATH)
	$(CPP) -c -o $@ $<


clean:
	rm -fr $(OBJ_PATH)
	rm -fr $(TARGET)
	rm -fr $(OUT_PATH)

install:
	mv $(TARGET) $(OUT_PATH)
