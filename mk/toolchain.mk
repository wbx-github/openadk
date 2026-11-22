prepare: ${WRKDIST}/.prepared
configure: ${WRKBUILD}/.configured
compile: $(WRKBUILD)/.compiled
install: $(WRKBUILD)/.installed
final: $(WRKBUILD)/.final
TOOLCHAIN_CLEAN_DIR?=	$(WRKDIR)
clean:
	rm -rf $(TOOLCHAIN_CLEAN_DIR)
