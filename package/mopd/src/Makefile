
# uncomment this to send the correct hostname to the client
# otherwise 'DEFAULT_HOSTNAME' will be sent
# REAL_HOSTNAME = "-DSEND_REAL_HOSTNAME"
REAL_HOSTNAME =""
DEFAULT_HOSTNAME="-DDEFAULT_HOSTNAME=\\\"ipc\\\""

# this is the path mopd will look for files in
MOP_PATH="-DMOP_FILE_PATH=\\\"/tftpboot/mop\\\""

# compiling on Alpha Linux 2.2.17 i needed the following:
# AOUT_SUPPORT="-DNOAOUT"
AOUT_SUPPORT=""

CFLAGS="-fcommon ${AOUT_SUPPORT} ${MOP_PATH} ${DEFAULT_HOSTNAME} ${REAL_HOSTNAME}"

#make file to build linux-mopd
SUBDIRS=common mopd mopchk mopprobe moptrace

all: 
	for dir in ${SUBDIRS}; 	\
	do		   	\
	  echo making $$dir;  	\
	  (cd $$dir; make CFLAGS=$(CFLAGS) ) ;	\
	done
	
	
clean:
	for dir in ${SUBDIRS} ;	\
	do			\
	  (cd $$dir ; make clean); \
	done
	
	
