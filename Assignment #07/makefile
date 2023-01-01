all: clean compile run

compile: main.c
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@gcc -o a.out main.c 

run: 
	@echo "-------------------------------------------"
	@echo "Running..."
	./a.out
	@echo "Completed."
	
clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.out
