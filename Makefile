REPO_PATH := https://github.com/simon-hrabec/Algolab2020/tree/main/
REPO_PROBLEMS_PATH := $(REPO_PATH)problems/

all:
	./change-newlines.sh
	cp README-intro.source README.md
	cat README-solutions_weeks.source >> README.md
	./generate-table.sh $(REPO_PROBLEMS_PATH) >> README.md
	cat README-solutions_tags.source >> README.md
	./generate-tag-links.sh $(REPO_PROBLEMS_PATH) >> README.md
	cat README-snippets.source >> README.md
	./generate-snippet-links.sh $(REPO_PATH) >> README.md
