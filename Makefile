#----------------------------------------------------------------------------------------
# Name: Makefile
# Author(s): Wimroy D'souza, Hrushikesh Kulkarni
# Comments: make a 'src' folder. It will compile all the files from the 'src' folder,
#			all the compiled object files will be placed in the obj folder
# Excecutable: The executable will be created in the folder containing the makefile
#
# NOTES: Don't forget to add OpenCV, FFMpeg in the LD_LIBRARY_PATH, in your .cshrc	
#----------------------------------------------------------------------------------------

CC = g++
CFLAGS = -c -std=c++0x 

WFLAGS = -Wall  -Warray-bounds

#Optimization Level
OPTS = -O0
OFLAGS =  -g

LFLAGS = -llapack -lm

# ENTER YOUR EXECUTABLE NAME HERE 
EXECUTABLE = $(shell basename $(PWD) )

#Opencv Includes Go here
#OPENCV_UN_USED = 
OPENCV_PATH = /usr/local/OpenCV
OPENCV_LIBS =  -lopencv_core  -lopencv_highgui -lopencv_imgproc \
  -lopencv_contrib  -lopencv_objdetect -lopencv_calib3d \
  -lopencv_flann -lopencv_gpu   -lopencv_legacy \
  -lopencv_ml -lopencv_ts -lopencv_video \
  -lopencv_features2d -lopencv_nonfree
  
OPENCV_INCPATH = -I$(OPENCV_PATH)/include/opencv/ \
-I$(OPENCV_PATH)/include/
OPENCV_LIBPATH = -L$(OPENCV_PATH)/lib/

#Boost Libs Go Here
BOOST_LIBS = -lboost_system  -lboost_filesystem  -lboost_program_options -lboost_serialization
BOOST_LIB_PATH = -L/usr/local/Boost/lib
BOOST_INC_PATH = -I/usr/local/Boost/include


SUBMIT_DIR = $(shell whoami)
BACKUP_DIR = $(shell date "+%b_%d_%Y_%I_%M")
BACKUP_REPO	= ./Backups
BACKUP_PATH = $(BACKUP_REPO)/$(BACKUP_DIR)

SRCDIR 			:= src
OBJDIR 			:= obj
CPP_FILES 		:= $(wildcard $(SRCDIR)/*.cpp)
OBJ_FILES 		:= $(addprefix $(OBJDIR)/,$(notdir $(CPP_FILES:.cpp=.o)))
PRJ_INCLUDES 	:= src/Constants.h src/Errors.h src/MyIncludes.h src/OpenCV_Includes.h src/Defines.h
OP_INCLUDES	:= src/VectorOp.h src/StringOp.h src/MapOp.h

#Assuming that my generic templates class will be named as *Op.h
$(OBJDIR)/%.o: src/%.cpp  src/%.h $(OP_INCLUDES) $(PRJ_INCLUDES)
	$(CC) $(CFLAGS) $(WFLAGS) $(OPTS) $(OFLAGS)  $(OPENCV_INCPATH) $(BOOST_INC_PATH) -c -o $@ $<

# Always force to make in parallel. nproc calculates the number of processors. 
all: 
	time make parallel -j $(shell echo `nproc` - 1 | bc );
	 
parallel: $(EXECUTABLE)	

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(OPTS) $(OPENCV_LIBPATH)   $(BOOST_LIB_PATH) $^ $(OPENCV_LIBS) $(BOOST_LIBS)  -o $@  


#http://stackoverflow.com/a/6170280
$(OBJ_FILES): | $(OBJDIR) 

$(OBJDIR):
	echo MKDIR "obj" to put .obj files in
	mkdir $(OBJDIR)

#Do Nothing Rule. This has been included, because it forces 'make' to check if there are any changes in the .h files. But at the same time
#we also did not want every .h to create a .o. Hence an empty rule.
%.h:
	

clean:
	rm -f $(OBJDIR)/* $(EXECUTABLE) 
	
	
#Create a Backup directory with <Month>_<Date>_<Year>_<Hr>_<Min>_<Sec>.tar
backup: 
	mkdir -p $(BACKUP_REPO)
	mkdir -p $(BACKUP_PATH)
	mkdir -p $(BACKUP_PATH)/src
	cp -r ./src/*.h ./$(BACKUP_PATH)/src
	cp -r ./src/*.cpp ./$(BACKUP_PATH)/src
	cp Makefile $(BACKUP_PATH)/
	cp TestScript.sh $(BACKUP_PATH)/
	tar -zcvf $(BACKUP_REPO)/$(BACKUP_DIR).tar $(BACKUP_PATH)/
	rm -rf $(BACKUP_PATH)
