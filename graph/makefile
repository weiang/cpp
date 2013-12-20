a.out: main.o 
	g++ -g main.o 

main.o: main.cc graph.cc graph.h
	g++ -c main.cc

test_udg: 
	./a.out < input_udg 
	dot -Tpdf g.dot -o g.pdf
	evince g.pdf

test_udn:

test_dg:
	./a.out < input_dg
	dot -Tpdf g.dot -o g.pdf
	evince g.pdf

test_dn:

bfs:
	dot -Tpdf BFS.dot -o bfs.pdf
	evince bfs.pdf

dfs:
	dot -Tpdf DFS.dot -o dfs.pdf
	evince dfs.pdf
clean:
	-rm *.dot *.o a.out *.pdf
