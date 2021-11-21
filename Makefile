rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
reverse = $(if $(1),$(call reverse,$(wordlist 2,$(words $(1)),$(1)))) $(firstword $(1))

CPP = g++

SRCDIR := mold3D
OBJDIR := obj

CFLAGS = -I $(shell pwd)/ -I $(shell pwd)/mold3D/3rd-Party/imgui -g -O0

SRC = $(call rwildcard,$(SRCDIR),*.cpp)  
OBJS = $(call reverse,$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC)))

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@ mkdir -p $(@D)
	$(CPP) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf $(OBJS)

link: $(OBJS)
	$(CPP) main.cpp $(OBJS) -lGL -lGLU -lSDL2 -o game $(CFLAGS)

.PHONY: build
build: link