# ===== Colors for pretty output =====
_GREY   = \033[1;30m
_RED    = \033[1;31m
_GREEN  = \033[1;32m
_YELLOW = \033[1;33m
_BLUE   = \033[1;34m
_PURPLE = \033[1;35m
_CYAN   = \033[1;36m
_WHITE  = \033[1;37m
_NC     = \033[0m

# Colored messages
SUCCESS   = $(_GREEN)SUCCESS[✔]$(_NC)
COMPILING = $(_BLUE)COMPILING[●]$(_NC)

# ===== Executable name =====
NAME = lib_rb_tree.a

# ===== Directories =====
SRCDIR = src
INCDIR = include
OBJDIR = obj
LIBDIR = lib
TARGET = $(LIBDIR)/$(NAME)

# ===== Source files =====
SRCFILES =	$(shell find $(SRCDIR) -name "*.c")\
			$(shell find $(SRCDIR) -name "*.cc")\
			$(shell find $(SRCDIR) -name "*.cpp")

# ===== Include directories =====
INCDIRS  = $(shell find $(INCDIR) -type d)
IFLAGS   = $(foreach dir,$(INCDIRS),-I$(dir))

# ===== Object files =====
OBJFILES =	$(patsubst %.c,$(OBJDIR)/%.o,$(filter %.c,$(SRCFILES)))\
			$(patsubst %.cc,$(OBJDIR)/%.o,$(filter %.cc,$(SRCFILES)))\
			$(patsubst %.cpp,$(OBJDIR)/%.o,$(filter %.cpp,$(SRCFILES)))

# ===== Include files =====
INC = $(shell find $(INCDIR) -name "*.h" -o -name "*.hh" -o -name "*.hpp")

# ===== Compiler and flags =====
CC       = clang
CXX      = clang++
CCFLAGS  = -std=c11   -Wall -Wextra -Werror -fsanitize=address -DNDEBUG -pedantic-errors
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -fsanitize=address -DNDEBUG -pedantic-errors
AR       = ar
ARFLAGS  = rcs

# ===== Default target =====
.PHONY: all
all: pretty $(TARGET)

# ===== Linking final static library =====
$(TARGET): $(OBJFILES)
	@echo
	@echo "$(_CYAN)Creating Lib $(_WHITE)$@ ...$(_NC)"
	@mkdir -p $(LIBDIR)
	@$(AR) $(ARFLAGS) $@ $^
	@echo "$(SUCCESS)\n$(_WHITE)Linked $@$(_NC)"

# ===== Generic object build rule =====
$(OBJDIR)/%.o: %.c Makefile $(INC)
	@mkdir -p $(@D)
	@$(CC) $(CCFLAGS) -c $< -o $@ $(IFLAGS)
	@echo "$(COMPILING) $(_WHITE) [$(CC)] $< -> $@$(_NC)"

$(OBJDIR)/%.o: %.cc Makefile $(INC)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -c $< -o $@ $(IFLAGS)
	@echo "$(COMPILING) $(_WHITE) [$(CXX)] $< -> $@$(_NC)"

$(OBJDIR)/%.o: %.cpp Makefile $(INC)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -c $< -o $@ $(IFLAGS)
	@echo "$(COMPILING) $(_WHITE) [$(CXX)] $< -> $@$(_NC)"

# ===== Clean object files only =====
.PHONY: clean
clean:
	@rm -rf $(OBJDIR)
	@echo "$(_YELLOW)[✗] Removed object files$(_NC)"

# ===== Clean everything =====
.PHONY: fclean
fclean: clean
	@rm -f $(TARGET)
	@rm -rf $(LIBDIR)
	@echo "$(_YELLOW)[✗] Removed library $(TARGET)$(_NC)"

# ===== Rebuild everything =====
.PHONY: re
re: fclean all

# ===== Beautify output =====
.PHONY: pretty
pretty:
	@echo "$(_CYAN)=============================$(_NC)"
	@echo "$(_CYAN) Building $(NAME) Project$(_NC)"
	@echo "$(_CYAN)=============================$(_NC)"

# Show macro details
.PHONY: show
show:
	@echo "$(_BLUE)SRCFILES:\t$(_YELLOW)$(SRCFILES)$(_NC)"
	@echo "$(_BLUE)OBJFILES:\t$(_YELLOW)$(OBJFILES)$(_NC)"
	@echo "$(_BLUE)Compilers:\t$(_YELLOW)$(CXX) $(CC)$(_NC)"
	@echo "$(_BLUE)CXXFLAGS:\t$(_YELLOW)$(CXXFLAGS)$(_NC)"
	@echo "$(_BLUE)CCFLAGS:\t$(_YELLOW)$(CCFLAGS)$(_NC)"
	@echo "$(_BLUE)IFLAGS:\t\t$(_YELLOW)$(IFLAGS)$(_NC)"
