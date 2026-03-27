# ========================================
# Numele executabilului final
# ========================================
TARGET = arcana

# ========================================
# Compilator C++
# ========================================
CXX = g++

# ========================================
# Flag-uri de compilare
# -Wall : afișează toate warning-urile
# -g : informații de debug 
# -std=c++17 : standard C++17
# ========================================
CXXFLAGS = -Wall -g -std=c++17

# ========================================
# Unelte pentru lexer și parser
# ========================================
FLEX = flex
BISON = bison

# ========================================
# Fișiere sursă
# ========================================
LEX_FILE  = expr.l
YACC_FILE = expr.y
MAIN_FILE = main.cpp
HEADERS   = globals.h

# ========================================
# Fișiere generate
# ========================================
LEX_CPP = lex.yy.c
YACC_CPP = expr.tab.c
YACC_H   = expr.tab.h

# ========================================
# Regula default (se execută la 'make')
# ========================================
all: $(TARGET)

# ========================================
# Construirea executabilului final
# ========================================
$(TARGET): $(LEX_CPP) $(YACC_CPP) $(YACC_H) $(MAIN_FILE) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(LEX_CPP) $(YACC_CPP) $(MAIN_FILE) -lfl -o $(TARGET)

# ========================================
# Generare parser (Bison)
# -d : generează header-ul expr.tab.h
# ========================================
$(YACC_CPP) $(YACC_H): $(YACC_FILE)
	$(BISON) -d $(YACC_FILE)

# ========================================
# Generare lexer (Flex)
# ========================================
$(LEX_CPP): $(LEX_FILE)
	$(FLEX) $(LEX_FILE)

# ========================================
# Curățare fișiere generate
# ========================================
clean:
	rm -f $(TARGET) $(LEX_CPP) $(YACC_CPP) $(YACC_H) symbol_tables.txt *.o

