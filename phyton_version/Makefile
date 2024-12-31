##
## LANGUAGE PROJECT, 2024
## Makefile
## File description:
## Makefile to create a link kmc to the compiler
##

TARGET = kmc

KAMION_PATH = $(shell readlink -f kamion.py)
OS := $(shell \grep "^ID=" /etc/os-release | cut -d'=' -f2 | tr -d '"')

all: $(TARGET)

$(TARGET):
ifeq ("$(OS)", "fedora")
	@echo "Creating symlink for Fedora..."
	@\sudo ln -sf $(KAMION_PATH) /usr/local/bin/$(TARGET)
else
	@\echo -e "[\033[31mERROR\033[0m] Unsupported OS: $(OS)"
	@\exit 1
endif

.PHONY: all
