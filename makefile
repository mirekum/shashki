# главная цель - конечная программа
all: res

# конечная программа зависит от объектных файлов, соответствующих файлам с исходными кодами
res: $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	g++ $^ -o $@
# объектные файлы зависят от соответствующих им файлов с исходными кодами и файлов, включённых в исходный директивой include
%.o: %.cpp
	g++ -c -MD $< -std=c++0x
# включаем зависимости, сгенерированные для каждого объектного файла
include $(wildcard *.d)

# очистка ненужностей
clean:
	rm -f *.o *.d *~

