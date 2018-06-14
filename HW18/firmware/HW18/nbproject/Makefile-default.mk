#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/HW18.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/HW18.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../../HW14/firmware/src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c ../../../HW14/firmware/src/system_config/default/framework/system/devcon/src/sys_devcon.c ../../../HW14/firmware/src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c ../../../HW14/firmware/src/system_config/default/framework/system/ports/src/sys_ports_static.c ../../../HW14/firmware/src/system_config/default/system_init.c ../../../HW14/firmware/src/system_config/default/system_interrupt.c ../../../HW14/firmware/src/system_config/default/system_exceptions.c ../../../HW14/firmware/src/system_config/default/system_tasks.c ../../../HW14/firmware/src/app.c ../../../HW14/firmware/src/main.c ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/system/int/src/sys_int_pic32.c ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device.c ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device_cdc.c ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device_cdc_acm.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o ${OBJECTDIR}/_ext/1845572747/sys_devcon.o ${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/1009144140/sys_ports_static.o ${OBJECTDIR}/_ext/253851475/system_init.o ${OBJECTDIR}/_ext/253851475/system_interrupt.o ${OBJECTDIR}/_ext/253851475/system_exceptions.o ${OBJECTDIR}/_ext/253851475/system_tasks.o ${OBJECTDIR}/_ext/897323550/app.o ${OBJECTDIR}/_ext/897323550/main.o ${OBJECTDIR}/_ext/1494652961/drv_usbfs.o ${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o ${OBJECTDIR}/_ext/758627871/sys_int_pic32.o ${OBJECTDIR}/_ext/1920725038/usb_device.o ${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o ${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o.d ${OBJECTDIR}/_ext/1845572747/sys_devcon.o.d ${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o.d ${OBJECTDIR}/_ext/1009144140/sys_ports_static.o.d ${OBJECTDIR}/_ext/253851475/system_init.o.d ${OBJECTDIR}/_ext/253851475/system_interrupt.o.d ${OBJECTDIR}/_ext/253851475/system_exceptions.o.d ${OBJECTDIR}/_ext/253851475/system_tasks.o.d ${OBJECTDIR}/_ext/897323550/app.o.d ${OBJECTDIR}/_ext/897323550/main.o.d ${OBJECTDIR}/_ext/1494652961/drv_usbfs.o.d ${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o.d ${OBJECTDIR}/_ext/758627871/sys_int_pic32.o.d ${OBJECTDIR}/_ext/1920725038/usb_device.o.d ${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o.d ${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o ${OBJECTDIR}/_ext/1845572747/sys_devcon.o ${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o ${OBJECTDIR}/_ext/1009144140/sys_ports_static.o ${OBJECTDIR}/_ext/253851475/system_init.o ${OBJECTDIR}/_ext/253851475/system_interrupt.o ${OBJECTDIR}/_ext/253851475/system_exceptions.o ${OBJECTDIR}/_ext/253851475/system_tasks.o ${OBJECTDIR}/_ext/897323550/app.o ${OBJECTDIR}/_ext/897323550/main.o ${OBJECTDIR}/_ext/1494652961/drv_usbfs.o ${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o ${OBJECTDIR}/_ext/758627871/sys_int_pic32.o ${OBJECTDIR}/_ext/1920725038/usb_device.o ${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o ${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o

# Source Files
SOURCEFILES=../../../HW14/firmware/src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c ../../../HW14/firmware/src/system_config/default/framework/system/devcon/src/sys_devcon.c ../../../HW14/firmware/src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c ../../../HW14/firmware/src/system_config/default/framework/system/ports/src/sys_ports_static.c ../../../HW14/firmware/src/system_config/default/system_init.c ../../../HW14/firmware/src/system_config/default/system_interrupt.c ../../../HW14/firmware/src/system_config/default/system_exceptions.c ../../../HW14/firmware/src/system_config/default/system_tasks.c ../../../HW14/firmware/src/app.c ../../../HW14/firmware/src/main.c ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/system/int/src/sys_int_pic32.c ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device.c ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device_cdc.c ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device_cdc_acm.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/HW18.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX250F128B
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o: ../../../HW14/firmware/src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/107765508" 
	@${RM} ${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o.d" -o ${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o ../../../HW14/firmware/src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1845572747/sys_devcon.o: ../../../HW14/firmware/src/system_config/default/framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1845572747" 
	@${RM} ${OBJECTDIR}/_ext/1845572747/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1845572747/sys_devcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1845572747/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1845572747/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/1845572747/sys_devcon.o ../../../HW14/firmware/src/system_config/default/framework/system/devcon/src/sys_devcon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o: ../../../HW14/firmware/src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1845572747" 
	@${RM} ${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o ../../../HW14/firmware/src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1009144140/sys_ports_static.o: ../../../HW14/firmware/src/system_config/default/framework/system/ports/src/sys_ports_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1009144140" 
	@${RM} ${OBJECTDIR}/_ext/1009144140/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1009144140/sys_ports_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1009144140/sys_ports_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1009144140/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/1009144140/sys_ports_static.o ../../../HW14/firmware/src/system_config/default/framework/system/ports/src/sys_ports_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/253851475/system_init.o: ../../../HW14/firmware/src/system_config/default/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/253851475" 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/253851475/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/253851475/system_init.o.d" -o ${OBJECTDIR}/_ext/253851475/system_init.o ../../../HW14/firmware/src/system_config/default/system_init.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/253851475/system_interrupt.o: ../../../HW14/firmware/src/system_config/default/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/253851475" 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/253851475/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/253851475/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/253851475/system_interrupt.o ../../../HW14/firmware/src/system_config/default/system_interrupt.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/253851475/system_exceptions.o: ../../../HW14/firmware/src/system_config/default/system_exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/253851475" 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/253851475/system_exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/253851475/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/253851475/system_exceptions.o ../../../HW14/firmware/src/system_config/default/system_exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/253851475/system_tasks.o: ../../../HW14/firmware/src/system_config/default/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/253851475" 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/253851475/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/253851475/system_tasks.o.d" -o ${OBJECTDIR}/_ext/253851475/system_tasks.o ../../../HW14/firmware/src/system_config/default/system_tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/897323550/app.o: ../../../HW14/firmware/src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/897323550" 
	@${RM} ${OBJECTDIR}/_ext/897323550/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/897323550/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/897323550/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/897323550/app.o.d" -o ${OBJECTDIR}/_ext/897323550/app.o ../../../HW14/firmware/src/app.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/897323550/main.o: ../../../HW14/firmware/src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/897323550" 
	@${RM} ${OBJECTDIR}/_ext/897323550/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/897323550/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/897323550/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/897323550/main.o.d" -o ${OBJECTDIR}/_ext/897323550/main.o ../../../HW14/firmware/src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1494652961/drv_usbfs.o: ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1494652961" 
	@${RM} ${OBJECTDIR}/_ext/1494652961/drv_usbfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494652961/drv_usbfs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494652961/drv_usbfs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1494652961/drv_usbfs.o.d" -o ${OBJECTDIR}/_ext/1494652961/drv_usbfs.o ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o: ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1494652961" 
	@${RM} ${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o.d" -o ${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/758627871/sys_int_pic32.o: ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/758627871" 
	@${RM} ${OBJECTDIR}/_ext/758627871/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/758627871/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/758627871/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/758627871/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/758627871/sys_int_pic32.o ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/system/int/src/sys_int_pic32.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1920725038/usb_device.o: ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1920725038" 
	@${RM} ${OBJECTDIR}/_ext/1920725038/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1920725038/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1920725038/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1920725038/usb_device.o.d" -o ${OBJECTDIR}/_ext/1920725038/usb_device.o ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o: ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1920725038" 
	@${RM} ${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device_cdc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o: ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device_cdc_acm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1920725038" 
	@${RM} ${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -DPICkit3PlatformTool=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device_cdc_acm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o: ../../../HW14/firmware/src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/107765508" 
	@${RM} ${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o.d" -o ${OBJECTDIR}/_ext/107765508/sys_clk_pic32mx.o ../../../HW14/firmware/src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1845572747/sys_devcon.o: ../../../HW14/firmware/src/system_config/default/framework/system/devcon/src/sys_devcon.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1845572747" 
	@${RM} ${OBJECTDIR}/_ext/1845572747/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/1845572747/sys_devcon.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1845572747/sys_devcon.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1845572747/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/1845572747/sys_devcon.o ../../../HW14/firmware/src/system_config/default/framework/system/devcon/src/sys_devcon.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o: ../../../HW14/firmware/src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1845572747" 
	@${RM} ${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o.d 
	@${RM} ${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o.d" -o ${OBJECTDIR}/_ext/1845572747/sys_devcon_pic32mx.o ../../../HW14/firmware/src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1009144140/sys_ports_static.o: ../../../HW14/firmware/src/system_config/default/framework/system/ports/src/sys_ports_static.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1009144140" 
	@${RM} ${OBJECTDIR}/_ext/1009144140/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1009144140/sys_ports_static.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1009144140/sys_ports_static.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1009144140/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/1009144140/sys_ports_static.o ../../../HW14/firmware/src/system_config/default/framework/system/ports/src/sys_ports_static.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/253851475/system_init.o: ../../../HW14/firmware/src/system_config/default/system_init.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/253851475" 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_init.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/253851475/system_init.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/253851475/system_init.o.d" -o ${OBJECTDIR}/_ext/253851475/system_init.o ../../../HW14/firmware/src/system_config/default/system_init.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/253851475/system_interrupt.o: ../../../HW14/firmware/src/system_config/default/system_interrupt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/253851475" 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_interrupt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/253851475/system_interrupt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/253851475/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/253851475/system_interrupt.o ../../../HW14/firmware/src/system_config/default/system_interrupt.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/253851475/system_exceptions.o: ../../../HW14/firmware/src/system_config/default/system_exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/253851475" 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/253851475/system_exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/253851475/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/253851475/system_exceptions.o ../../../HW14/firmware/src/system_config/default/system_exceptions.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/253851475/system_tasks.o: ../../../HW14/firmware/src/system_config/default/system_tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/253851475" 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/253851475/system_tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/253851475/system_tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/253851475/system_tasks.o.d" -o ${OBJECTDIR}/_ext/253851475/system_tasks.o ../../../HW14/firmware/src/system_config/default/system_tasks.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/897323550/app.o: ../../../HW14/firmware/src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/897323550" 
	@${RM} ${OBJECTDIR}/_ext/897323550/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/897323550/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/897323550/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/897323550/app.o.d" -o ${OBJECTDIR}/_ext/897323550/app.o ../../../HW14/firmware/src/app.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/897323550/main.o: ../../../HW14/firmware/src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/897323550" 
	@${RM} ${OBJECTDIR}/_ext/897323550/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/897323550/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/897323550/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/897323550/main.o.d" -o ${OBJECTDIR}/_ext/897323550/main.o ../../../HW14/firmware/src/main.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1494652961/drv_usbfs.o: ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1494652961" 
	@${RM} ${OBJECTDIR}/_ext/1494652961/drv_usbfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494652961/drv_usbfs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494652961/drv_usbfs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1494652961/drv_usbfs.o.d" -o ${OBJECTDIR}/_ext/1494652961/drv_usbfs.o ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o: ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1494652961" 
	@${RM} ${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o.d" -o ${OBJECTDIR}/_ext/1494652961/drv_usbfs_device.o ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/driver/usb/usbfs/src/dynamic/drv_usbfs_device.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/758627871/sys_int_pic32.o: ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/system/int/src/sys_int_pic32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/758627871" 
	@${RM} ${OBJECTDIR}/_ext/758627871/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/758627871/sys_int_pic32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/758627871/sys_int_pic32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/758627871/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/758627871/sys_int_pic32.o ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/system/int/src/sys_int_pic32.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1920725038/usb_device.o: ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1920725038" 
	@${RM} ${OBJECTDIR}/_ext/1920725038/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1920725038/usb_device.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1920725038/usb_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1920725038/usb_device.o.d" -o ${OBJECTDIR}/_ext/1920725038/usb_device.o ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o: ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device_cdc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1920725038" 
	@${RM} ${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o.d" -o ${OBJECTDIR}/_ext/1920725038/usb_device_cdc.o ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device_cdc.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o: ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device_cdc_acm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1920725038" 
	@${RM} ${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework" -I"../src/system_config/default/framework" -MMD -MF "${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o.d" -o ${OBJECTDIR}/_ext/1920725038/usb_device_cdc_acm.o ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/framework/usb/src/dynamic/usb_device_cdc_acm.c    -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/HW18.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/bin/framework/peripheral/PIC32MX250F128B_peripherals.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -DPICkit3PlatformTool=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/HW18.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/bin/framework/peripheral/PIC32MX250F128B_peripherals.a      -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC00490:0x1FC00BEF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=PICkit3PlatformTool=1,--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/HW18.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/bin/framework/peripheral/PIC32MX250F128B_peripherals.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/HW18.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ../../../../../2018_Winter/ME_333/Software/harmony/v2_05_01/bin/framework/peripheral/PIC32MX250F128B_peripherals.a      -DXPRJ_default=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/HW18.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
