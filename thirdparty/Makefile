.PHONY: all
all: echfs limine

.PHONY: clean
clean:
	$(MAKE) -C echfs clean
	$(MAKE) -C limine clean

.PHONY: echfs
echfs:
	$(MAKE) -C echfs echfs-utils

.PHONY: limine
limine:
	$(MAKE) -C limine
