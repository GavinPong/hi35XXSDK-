include Makefile.param
include Makefile.srcs
include Makefile.libs

TARGET := SmartVC


all:$(TARGET)
	

$(TARGET):$(OBJS_C) $(OBJS_CPP)
	$(CC) $(SRCS_MACRO) $(CFLAGS) $(CPPFLAGS)  $(SRCS_INC) $(LIBS_INC) $(LIBS_LIB) $(OBJS_C) $(OBJS_CPP) $(LDFLAGS) -o  $@ -g
	#$(STRIP)   $(STRIPFLAGS)  $@

libmdd.so:$(OBJS_C) $(OBJS_CPP)
	$(CC) $(SRCS_MACRO) $(CFLAGS) $(CPPFLAGS) $(OBJS_C) $(OBJS_CPP) $(LDFLAGS) -o  $@  -shared -fPIC
	#$(STRIP)   $(STRIPFLAGS)  $@


libmdd.a:$(OBJS_C) $(OBJS_CPP)
	$(AR)  rv $@   $(OBJS_C) $(OBJS_CPP)
	#$(STRIP)   $(STRIPFLAGS)  $@

$(OBJS_C):%.o:%.c
	$(CC) -o $@ -c $< $(SRCS_MACRO) $(CFLAGS) $(CPPFLAGS) $(SRCS_INC) $(LIBS_INC)

$(OBJS_CPP):%.o:%.cpp
	$(CC) -o $@ -c $< $(SRCS_MACRO) $(CFLAGS) $(CPPFLAGS) $(SRCS_INC) $(LIBS_INC)

$(DEF_C):%.d:%.c
	$(MAKEDEPEND) $(<:.c=.o) $< $(SRCS_INC) $(LIBS_INC) > $@ 

$(DEF_CPP):%.d:%.cpp
	$(MAKEDEPEND) $(<:.cpp=.o) $< $(SRCS_INC) $(LIBS_INC) > $@ 

include $(DEF_C)  $(DEF_CPP)

clean:
	rm -rf $(OBJS_C) $(OBJS_CPP)
	rm -rf $(TARGET)

depend:
	rm -rf $(DEF_C) $(DEF_CPP)

distclean:
	rm -rf $(OBJS_C) $(OBJS_CPP)
	rm -rf $(TARGET)
	rm -rf $(DEF_C) $(DEF_CPP)

install:
	cp 	src/*.h /home/disk2/zp/work_space/thirdlib/mdd/inc -rf
	cp 	*.so /home/disk2/zp/work_space/thirdlib/mdd/ -rf

.PHONY:$(TARGET)
.PHONY: clean
.PHONY: depend
.PHONY: distclean 
.PHONY: install 