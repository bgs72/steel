##
##  Copyright 2015-2026
##  Author(s): Bart Gysens <gysens.bart@gmail.com>
##
##  This file is part of Steel.
##
##  Steel is free software: you can redistribute it and/or modify
##  it under the terms of the GNU General Public License as published by
##  the Free Software Foundation, either version 3 of the License, or
##  (at your option) any later version.
##
##  Steel is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
##
##  You should have received a copy of the GNU General Public License
##  along with Steel.  If not, see <http://www.gnu.org/licenses/>.
##

OBJ_DIR = ../obj
CPP_SRC = $(patsubst ./%.cpp, %.cpp, $(shell find . -type f -name '*.cpp'))
CPP_OBJ = $(patsubst %.cpp, $(OBJ_DIR)/%.oo, $(CPP_SRC))
CPP_DEP = $(patsubst %.cpp, $(OBJ_DIR)/%.dd, $(CPP_SRC))

SED = sed
GCC = g++
GCC_CFL+=-Wall -g -c -I./
GCC_LIB =-lhidapi-libusb
GCC_INC = $(filter-out %git $(OBJ_DIR),$(subst �, ,$(filter �%,$(subst ./,�, $(shell find . -type d)))))
$(shell mkdir -p $(OBJ_DIR) 2>/dev/null)
$(foreach subdir,$(GCC_INC),$(shell mkdir -p $(OBJ_DIR)/$(subdir) 2>/dev/null))

TARGET = $(OBJ_DIR)/steel

$(TARGET) : $(CPP_OBJ)
	$(GCC) $(CPP_OBJ) $(GCC_LIB) -o $(TARGET)

-include $(CPP_DEP)

$(OBJ_DIR)/%.dd: %.cpp
	@set -e; \
	$(RM) $@; \
	$(GCC) -M $(GCC_CFL) $< > $@.temp; \
	$(SED) 's,\($(*F)\)\.o[ :]*,$(patsubst %.cpp,%.oo,$(OBJ_DIR)/$<) $@: ,g' < $@.temp > $@; \
	$(RM) -f $@.temp

$(OBJ_DIR)/%.oo: %.cpp
	$(GCC) $(GCC_CFL) $< -o $@

rebuild:
	@$(MAKE) --no-print-directory clean
	@$(MAKE) --no-print-directory

clean:
	@$(RM) -rf $(OBJ_DIR)
	@$(RM) -f $(TARGET)
