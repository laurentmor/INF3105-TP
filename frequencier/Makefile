OPTIONS = -W -Wall -O3
SRC=src
.PHONY: all commit
BUILDID=$(shell date +%Y%m%d-%H:%M:%S)
	
all:frequencier commit

commit :
	git config user.name "AUTO"
	git config user.email "auto@dummy.ca"
	
	git add -A .
	git commit -m 'Build automatique - ${BUILDID}'


frequencier:${SRC}/frequencier.cpp
	g++ ${OPTIONS} -o frequencier ${SRC}/frequencier.cpp
clean :
	rm -rf dist
	rm -rf build
	rm -f frequencier* 
	
