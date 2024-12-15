one: fork run-one clean
two: fork run-two clean
three: fork run-three clean

fork: 
	gcc -o fork fork.c

run-one: 
	./fork 7 1
run-two:
	./fork 7 2
run-three:
	./fork 8 3

clean:
	rm fork

