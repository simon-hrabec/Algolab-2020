REPO_PATH = 'https://github.com/simon-hrabec/Algolab2020/tree/main/'

all:
# 	./change-newlines.sh
	cp README.source README.md
	./generate-table.sh $(REPO_PATH) >> README.md 
	./generate-tag-links.sh $(REPO_PATH) >> README.md
	./generate-snippet-links.sh $(REPO_PATH) >> README.md
