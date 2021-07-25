REPO_PATH := https://github.com/simon-hrabec/Algolab2020/tree/main/
REPO_PROBLEMS_PATH := $(REPO_PATH)problems/
CHAPTER_DIR := readme-chapters

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
CHAPTERS := $(call rwildcard,$(CHAPTER_DIR),*Makefile)

all: README.md
	@./change-newlines.sh
	@echo "Newlines changed to unix style!"

README.md: $(CHAPTERS) FORCE
	@cat $(CHAPTER_DIR)/order | sed 's|^|"'"$(CHAPTER_DIR)"/'|' | sed 's|$$|/README.md"|' | xargs cat > README.md
	@echo "README.md assembled!"

FORCE:

$(CHAPTERS): FORCE
	@echo $$(echo $@ | sed 's|[^/]*/\(.*\)/[^/]*|\1|') readme chapter generated!
	@$(MAKE) --no-print-directory -s -C $(subst Makefile,,$@)

