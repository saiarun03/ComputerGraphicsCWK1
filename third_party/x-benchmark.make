# Alternative GNU Make project makefile autogenerated by Premake

ifndef config
  config=debug_x64
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

# Configurations
# #############################################

ifeq ($(origin CC), default)
  CC = clang
endif
ifeq ($(origin CXX), default)
  CXX = clang++
endif
ifeq ($(origin AR), default)
  AR = ar
endif
INCLUDES += -Istb/include -Iglad/include -Iglfw/include -Icatch2/include -Ibenchmark/include
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MD -MP $(DEFINES) $(INCLUDES)
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LIBS += -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -framework QuartzCore
LDDEPS +=
ALL_LDFLAGS += $(LDFLAGS) -m64 -pthread
LINKCMD = $(AR) -rcs "$@" $(OBJECTS)
define PREBUILDCMDS
endef
define PRELINKCMDS
endef
define POSTBUILDCMDS
endef

ifeq ($(config),debug_x64)
TARGETDIR = ../lib
TARGET = $(TARGETDIR)/libx-benchmark-debug-x64-clang.a
OBJDIR = ../_build_/debug-x64-clang/x64/debug/x-benchmark
DEFINES += -D_DEBUG=1 -DBENCHMARK_STATIC_DEFINE=1
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -g -march=native -Wall -pthread -Werror=vla
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -g -std=c++20 -march=native -Wall -pthread -Werror=vla

else ifeq ($(config),release_x64)
TARGETDIR = ../lib
TARGET = $(TARGETDIR)/libx-benchmark-release-x64-clang.a
OBJDIR = ../_build_/release-x64-clang/x64/release/x-benchmark
DEFINES += -DNDEBUG=1 -DBENCHMARK_STATIC_DEFINE=1
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -O2 -march=native -Wall -pthread -Werror=vla
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -O2 -std=c++20 -march=native -Wall -pthread -Werror=vla

endif

# Per File Configurations
# #############################################


# File sets
# #############################################

GENERATED :=
OBJECTS :=

GENERATED += $(OBJDIR)/benchmark.o
GENERATED += $(OBJDIR)/benchmark_api_internal.o
GENERATED += $(OBJDIR)/benchmark_main.o
GENERATED += $(OBJDIR)/benchmark_name.o
GENERATED += $(OBJDIR)/benchmark_register.o
GENERATED += $(OBJDIR)/benchmark_runner.o
GENERATED += $(OBJDIR)/check.o
GENERATED += $(OBJDIR)/colorprint.o
GENERATED += $(OBJDIR)/commandlineflags.o
GENERATED += $(OBJDIR)/complexity.o
GENERATED += $(OBJDIR)/console_reporter.o
GENERATED += $(OBJDIR)/counter.o
GENERATED += $(OBJDIR)/csv_reporter.o
GENERATED += $(OBJDIR)/json_reporter.o
GENERATED += $(OBJDIR)/perf_counters.o
GENERATED += $(OBJDIR)/reporter.o
GENERATED += $(OBJDIR)/statistics.o
GENERATED += $(OBJDIR)/string_util.o
GENERATED += $(OBJDIR)/sysinfo.o
GENERATED += $(OBJDIR)/timers.o
OBJECTS += $(OBJDIR)/benchmark.o
OBJECTS += $(OBJDIR)/benchmark_api_internal.o
OBJECTS += $(OBJDIR)/benchmark_main.o
OBJECTS += $(OBJDIR)/benchmark_name.o
OBJECTS += $(OBJDIR)/benchmark_register.o
OBJECTS += $(OBJDIR)/benchmark_runner.o
OBJECTS += $(OBJDIR)/check.o
OBJECTS += $(OBJDIR)/colorprint.o
OBJECTS += $(OBJDIR)/commandlineflags.o
OBJECTS += $(OBJDIR)/complexity.o
OBJECTS += $(OBJDIR)/console_reporter.o
OBJECTS += $(OBJDIR)/counter.o
OBJECTS += $(OBJDIR)/csv_reporter.o
OBJECTS += $(OBJDIR)/json_reporter.o
OBJECTS += $(OBJDIR)/perf_counters.o
OBJECTS += $(OBJDIR)/reporter.o
OBJECTS += $(OBJDIR)/statistics.o
OBJECTS += $(OBJDIR)/string_util.o
OBJECTS += $(OBJDIR)/sysinfo.o
OBJECTS += $(OBJDIR)/timers.o

# Rules
# #############################################

all: $(TARGET)
	@:

$(TARGET): $(GENERATED) $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking x-benchmark
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning x-benchmark
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(GENERATED)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(GENERATED)) del /s /q $(subst /,\\,$(GENERATED))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild: | $(OBJDIR)
	$(PREBUILDCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) | $(PCH_PLACEHOLDER)
$(GCH): $(PCH) | prebuild
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
$(PCH_PLACEHOLDER): $(GCH) | $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) touch "$@"
else
	$(SILENT) echo $null >> "$@"
endif
else
$(OBJECTS): | prebuild
endif


# File Rules
# #############################################

$(OBJDIR)/benchmark.o: benchmark/src/benchmark.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/benchmark_api_internal.o: benchmark/src/benchmark_api_internal.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/benchmark_main.o: benchmark/src/benchmark_main.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/benchmark_name.o: benchmark/src/benchmark_name.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/benchmark_register.o: benchmark/src/benchmark_register.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/benchmark_runner.o: benchmark/src/benchmark_runner.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/check.o: benchmark/src/check.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/colorprint.o: benchmark/src/colorprint.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/commandlineflags.o: benchmark/src/commandlineflags.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/complexity.o: benchmark/src/complexity.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/console_reporter.o: benchmark/src/console_reporter.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/counter.o: benchmark/src/counter.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/csv_reporter.o: benchmark/src/csv_reporter.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/json_reporter.o: benchmark/src/json_reporter.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/perf_counters.o: benchmark/src/perf_counters.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/reporter.o: benchmark/src/reporter.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/statistics.o: benchmark/src/statistics.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/string_util.o: benchmark/src/string_util.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/sysinfo.o: benchmark/src/sysinfo.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/timers.o: benchmark/src/timers.cc
	@echo "$(notdir $<)"
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif