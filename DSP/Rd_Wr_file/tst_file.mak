# Generated by the VisualDSP++ IDDE

# Note:  Any changes made to this Makefile will be lost the next time the
# matching project file is loaded into the IDDE.  If you wish to preserve
# changes, rename this file and run it externally to the IDDE.

# The syntax of this Makefile is such that GNU Make v3.77 or higher is
# required.

# The current working directory should be the directory in which this
# Makefile resides.

# Supported targets:
#     tst_file_Debug
#     tst_file_Debug_clean

# Define this variable if you wish to run this Makefile on a host
# other than the host that created it and VisualDSP++ may be installed
# in a different directory.

ADI_DSP=D:\Programas\VisualDSP


# $VDSP is a gmake-friendly version of ADI_DIR

empty:=
space:= $(empty) $(empty)
VDSP_INTERMEDIATE=$(subst \,/,$(ADI_DSP))
VDSP=$(subst $(space),\$(space),$(VDSP_INTERMEDIATE))

RM=cmd /C del /F /Q

#
# Begin "tst_file_Debug" configuration
#

ifeq ($(MAKECMDGOALS),tst_file_Debug)

tst_file_Debug : ./Debug/tst_file.dxe 

./Debug/main.doj :./main.c 
	@echo ".\main.c"
	$(VDSP)/ccblkfn.exe -c .\main.c -file-attr ProjectName=tst_file -g -structs-do-not-overlap -no-multiline -double-size-32 -decls-strong -warn-protos -proc ADSP-BF533 -o .\Debug\main.doj -MM

./Debug/proc_rot.doj :./proc_rot.c 
	@echo ".\proc_rot.c"
	$(VDSP)/ccblkfn.exe -c .\proc_rot.c -file-attr ProjectName=tst_file -g -structs-do-not-overlap -no-multiline -double-size-32 -decls-strong -warn-protos -proc ADSP-BF533 -o .\Debug\proc_rot.doj -MM

./Debug/tst_file.dxe :./Debug/main.doj ./Debug/proc_rot.doj 
	@echo "Linking..."
	$(VDSP)/ccblkfn.exe .\Debug\main.doj .\Debug\proc_rot.doj -L .\Debug -add-debug-libpaths -flags-link -od,.\Debug -o .\Debug\tst_file.dxe -proc ADSP-BF533 -MM

endif

ifeq ($(MAKECMDGOALS),tst_file_Debug_clean)

tst_file_Debug_clean:
	-$(RM) ".\Debug\main.doj"
	-$(RM) ".\Debug\proc_rot.doj"
	-$(RM) ".\Debug\tst_file.dxe"
	-$(RM) ".\Debug\*.ipa"
	-$(RM) ".\Debug\*.opa"
	-$(RM) ".\Debug\*.ti"
	-$(RM) ".\Debug\*.pgi"
	-$(RM) ".\*.rbld"

endif


