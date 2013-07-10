# included by bld/$(SPLICE_HOST)/makefile

TARGET_EXEC := reader

include $(OSPL_HOME)/setup/makefiles/test_idl_c.mak
include	$(OSPL_HOME)/setup/makefiles/target.mak

CINCS += -I$(OSPL_HOME)/src/api/dcps/sac/include

CINCS += -I$(OSPL_HOME)/src/database/database/include
CINCS += -I$(OSPL_HOME)/src/kernel/include
CINCS += -I$(OSPL_HOME)/src/user/include
CINCS += -I$(OSPL_HOME)/src/configuration/config/include

LDLIBS += -l$(DDS_DCPSSAC) -l$(DDS_OS) 

-include $(DEPENDENCIES)