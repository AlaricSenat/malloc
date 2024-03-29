TEST_CC			:= g++
TEST_CFLAGS		:= -I. -I$(CPPUNIT_PATH)/include -std='c++14' -g -Wno-deprecated-declarations
ifeq ($(shell uname -s), Darwin)
TEST_LFLAGS		:= -L$(CPPUNIT_PATH)/lib -ldl -lcppunit -L./libft -lft
else
TEST_LFLAGS		:= -L$(CPPUNIT_PATH)/lib -ldl -lcppunit -L./libft -Wl,--whole-archive -lft -Wl,--no-whole-archive
endif
COMPLINK		:= $(CC) $(TEST_CFLAGS) $(TEST_LFLAGS) -o

CURR_DIR		:= tests
TEST_FILES		:= 	utest-utils.cpp \
					utest-alloc_block.cpp \
					utest-search_in_areas.cpp \
					utest-defrag_around_and_free.cpp \
					realloc_tests.cpp \
					manual-tests.cpp \
					simulation.cpp
TEST_OBJECTS	:= $(addprefix $(CURR_DIR)/$(OBJECT_DIR)/, $(TEST_FILES:.cpp=.o))
RUN_TEST_RULES	:= $(addprefix run-, $(TEST_FILES:.cpp=))

TEST_FILES		:= $(addprefix $(CURR_DIR)/, $(TEST_FILES))
TEST_TARGETS	:= $(TEST_FILES:.cpp=)
TEST_OBJ_DIR	:= $(CURR_DIR)/$(OBJECT_DIR)

OBJ_DIRS 		+= $(TEST_OBJ_DIR)

.PRECIOUS: $(TEST_TARGETS) $(TEST_OBJECTS)
.PHONY: run-all-tests
run-all-tests: $(RUN_TEST_RULES)

.PHONY: clear-tests
clear-tests:
	rm -rf $(TEST_OBJ_DIR)
	rm -f $(TEST_TARGETS)

run-%: all $(TEST_OBJ_DIR) $(CURR_DIR)/% $(CURR_DIR)/utils.hpp
	$(eval TEST_NAME := $(subst run-,, $@))
	$(eval FAIL := $(shell $(addprefix $(CURR_DIR)/, $(TEST_NAME)) > $(TEST_NAME).out; $(ECHO) $$?))
	@if [ $(FAIL) -gt 0 ]; \
	then \
		$(ECHO) "["$(RED)KO$(RESET)"] -" $(TEST_NAME); \
		cat $(TEST_NAME).out; \
	else \
		$(ECHO)  "["$(GREEN)OK$(RESET)"] -" $(TEST_NAME); \
	fi
	@rm -f $(TEST_NAME).out

$(CURR_DIR)/%: $(CURR_DIR)/$(OBJECT_DIR)/%.o $(NAME)
	$(TEST_CC) $(TEST_LFLAGS) -o $@ $< $(OBJECTS)

$(CURR_DIR)/$(OBJECT_DIR)/%.o: $(CURR_DIR)/%.cpp
	$(TEST_CC) $(TEST_CFLAGS) -c -o $@ $<
$(TEST_OBJ_DIR):
	mkdir $@
