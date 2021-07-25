REPO_PATH := https://github.com/simon-hrabec/Algolab2020/tree/main/
REPO_PROBLEMS_PATH := $(REPO_PATH)problems/
CHAPTER_DIR := readme-chapters

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
CHAPTERS := $(call rwildcard,$(CHAPTER_DIR),*Makefile)

all: README.md
	./change-newlines.sh

README.md: $(CHAPTERS)
	cat $(CHAPTER_DIR)/order | sed 's|^|"'"$(CHAPTER_DIR)"/'|' | sed 's|$$|/README.md"|' | xargs cat > README.md

FORCE:

$(CHAPTERS): FORCE
	echo $(subst Makefile,,$@)
	@$(MAKE) --no-print-directory -C $(subst Makefile,,$@)
