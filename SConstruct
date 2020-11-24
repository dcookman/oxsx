#!/usr/bin/env python
import os
import sys

# load the environment, accounting for the dependencies
env = SConscript("config/SConscript")
env.Append(CPPPATH = "#/include")
Export('env')

# now copy the headers to include and build the library
env.Replace(SRC_VARIANT_DIR =  "build")
lib = env.SConscript("src/SConscript",
                     variant_dir = env["SRC_VARIANT_DIR"], duplicate = 0)
Export('lib')

# now build the tests
env.SConscript("test/unit/SConscript", 
               variant_dir="#/test/.unitbuild", duplicate=0)

# now create the executibles for running user scripts
env.SConscript("bin/SConscript")
