TARGET := renard-phy-s2lp-hal-stm32.a
SRCDIR := src/
OBJDIR := obj/
CFGDIR := conf/

CFLAGS := -Wall -std=c99 -Og

ARCHFLAGS :=

SRCS := $(wildcard  $(SRCDIR)*.c)
OBJS := $(addprefix $(OBJDIR),$(notdir $(SRCS:.c=.o)))
DEPS := $(addprefix $(OBJDIR),$(notdir $(SRCS:.c=.d)))

all: $(OBJDIR) $(TARGET)

$(TARGET): $(OBJS)
	$(AR) cr $@ $^

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) -c $(ARCHFLAGS) $(CFLAGS) -I$(CFGDIR) -MMD -MP $< -o $@

clean:
	$(RM) -r $(TARGET)
	$(RM) -r $(OBJDIR)

-include $(DEPS)
