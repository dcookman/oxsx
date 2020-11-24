#!/usr/bin/env python
VALID_FIELDS = ["header_path", "lib_path", "flags", 
                "build"]

class Dependency(object):
    '''
    A dependency for the OXSX build, contains build locations, flags etc
    Effectively a python dict where the possible attributes are limited to the above
    '''    
    def __init__(self, name, libs, check_headers):
        self.build = True
        self.name  = name
        self.libs  = libs
        self.check_headers = check_headers
        
        # initialise to None, can be set by parse_user_config or command line
        # otherwise it is assumed headers/libraries are known to the compiler
        for x in VALID_FIELDS:
            self.__setattr__(x, None)
        
