
# Makefile

e :=
sp := $(e) $(e)
qs = $(subst ?,$(sp),$1)
sq = $(subst $(sp),?,$1)

# Get name of this Makefile (avoid getting word 0 and a starting space)
makefile_name := $(wordlist 1,1000,$(MAKEFILE_LIST))

# Get path of this Makefile
makefile_path := $(call qs,$(dir $(call sq,$(abspath $(call sq,$(makefile_name))))))

# Get path where the Application is
application_path := $(call qs,$(abspath $(call sq,$(makefile_path)..)))

# Change makefile_name to a relative path
makefile_name_relative := $(subst $(call sq,$(application_path))/,,$(call sq,$(abspath $(call sq,$(makefile_name)))))

# Get relative path to makefile from application_path
project_folder := $(subst $(call sq,$(application_path))/,,$(call sq,$(abspath $(call sq,$(makefile_path)))))



# Finds files that matches the specified pattern. The directory list
# is searched recursively. It is safe to invoke this function with an
# empty list of directories.
#
# Param $(1): List of directories to search
# Param $(2): The file pattern to search for
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
# example SOURCES = $(call rwildcard, $(user_modules), *.c)



#Рекурсивно искать папки с названием arg2 в дериктории arg1
# define findPaths
# 	$(find $(1) -type d -iname "*$(2)*")
# endef
# findPaths=$(find $(1) -type d -iname "*$(2)*")

# define findPaths
# 	$(shell find $(1) -type d -iname "*$(2)*")
# endef

listEcho=$(foreach var,$1,echo $(var);)