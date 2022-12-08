ifndef SETTINGS_MK
SETTINGS_MK = 1

NAME	= solution

CFLAGS	= -Wall -Wextra -Werror -pedantic -std=c++20
IFLAGS	= -I$(IDIR)

SDIR	= ./
ODIR	= .obj/extra_directory_because_reasons
IDIR	= ../.tools/

ifdef DEBUG
	CFLAGS += -g -D DEBUG
endif

ifdef LEAKS
	CFLAGS += -D LEAKS
endif

ifdef FSANITIZE
	CFLAGS += -D FSANITIZE
	CFLAGS += -g -fsanitize=address
endif

include ./make_settings/src.mk
OBJ := $(addprefix $(ODIR)/, $(SRC:.cpp=.o))

# TEST_OBJ    := $(patsubst $(SDIR)/%.c,$(ODIR)/%.o,$(SRC))

endif
