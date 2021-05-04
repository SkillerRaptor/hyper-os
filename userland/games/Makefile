GAMES := $(wildcard */.)

.PHONY: all
all: $(GAMES)

.PHONY: $(GAMES)
$(GAMES):
	$(MAKE) -C $@ ABSOLUTE_PATH=$(ABSOLUTE_PATH)
