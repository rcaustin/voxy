CXX = clang++
EDIR = /home/ryan/Development/proj/voxy/blackbox
CXXFLAGS = -std=c++14 -Wall -Werror -I$(EDIR)

# Application
PRGM = voxy
DEPS = Application.hh Chunk.hh
OBJS = Application.o Chunk.o
LIBS = -lSDL2 -lsoil2 -lGL -lGLEW

# Engine
_DEP = Camera.hh Input.hh Shader.hh Texture.hh Timer.hh VoxelMesh.hh Window.hh
EDEP = $(patsubst %,$(EDIR)/%,$(_DEP))
_OBJ = Camera.o Input.o Shader.o Texture.o Timer.o VoxelMesh.o Window.o
EOBJ = $(patsubst %,$(EDIR)/%,$(_OBJ))

# Application Target
$(PRGM): $(OBJS) $(EOBJ)
	$(CXX) Main.cc -o $@ $^ $(CXXFLAGS) $(LIBS)

# Application Object Files
%.o: %.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Engine Target
engine: $(EOBJ)

# Engine Object Files
$(EDIR)/%.o: %.cc $(EDEP)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Clean Target
.PHONY: clean

clean:
	rm -f $(PRGM) *.o $(EDIR)/*.o
