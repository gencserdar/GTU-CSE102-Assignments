all: clean compile run

compile: driver1.cpp driver2.cpp
	@echo "-------------------------------------------"
	@echo "Compiling..."
	@g++ -o driver1.out driver1.cpp
	@g++ -o driver2.out driver2.cpp

run: 
	@echo "-------------------------------------------"
	@echo "Running..."
	./driver1.out
	./driver2.out
	@echo "Completed."
	
clean:
	@echo "-------------------------------------------"
	@echo "Removing compiled files..."
	@rm -f *.out
