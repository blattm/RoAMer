import os

# RoAMer related
THIS_FILE_PATH = str(os.path.abspath(__file__))
PROJECT_ROOT = str(os.path.abspath(os.sep.join([THIS_FILE_PATH, ".."])))
BIN_ROOT = str(os.path.abspath(os.sep.join([PROJECT_ROOT, "roamer", "bin"])))

BUILD_INSTANCE = {
    "client_paths": {
        "receiver": "{USERPATH}Desktop\\roamer.exe", # used for update_receiver
        "repo": "{USERPATH}roamer_repo", #used for compiling source / storing binaries
        "repo_zip": "{USERPATH}roamer.zip", #used for compiling source
        "to_whitelist": "C:\\", #used to create whitelist
        # Next two entries only required for deploying hooks
        "vs_path": r"C:\Program Files\Microsoft Visual Studio\2022\Community", # Path of Visual Studio
        "dev_shell_x86_relative_to_vs_path":  r"VC\Auxiliary\Build\vcvars32.bat",       # Path of the 32bit Developer Console relative to vs_path 
        "dev_shell_x64_relative_to_vs_path":  r"VC\Auxiliary\Build\vcvars64.bat",       # Path of the 64bit Developer Console relative to vs_path 
    },

    "host_ip": '192.168.56.1',
    "host_port": 10000,
    "guest_ip": "1.1.1.1",
    "guest_port": 10000,
    "debug_sleep": 0,
    "socket_timeout": 480,

    "staged_update": True,    # requires python on client, SHOULD BE DISABLED FOR PROD
    "requires_cleaning_before_snapshot": False,

    # Virtualization related
    # VM_CONTROLLER choose "VboxManageController" for VirtualBox or "KvmManageController" for KVM
    "VM_CONTROLLER": "VboxManageController",
    "VM_NAME": "vm_name_build",
    "SNAPSHOT_NAME": "snapshot_name_build",
}

PROD_INSTANCE = {
    "client_paths": {
        "receiver": "{USERPATH}Desktop\\roamer.exe", # used for update_receiver
        "repo": "{USERPATH}roamer_repo", #used for compiling source / storing binaries
        "repo_zip": "{USERPATH}roamer.zip", #used for compiling source
        "to_whitelist": "C:\\", #used to create whitelist
        # Next two entries only required for deploying hooks
        "vs_path": r"C:\Program Files\Microsoft Visual Studio\2022\Community", # Path of Visual Studio
        "dev_shell_x86_relative_to_vs_path":  r"VC\Auxiliary\Build\vcvars32.bat",       # Path of the 32bit Developer Console relative to vs_path 
        "dev_shell_x64_relative_to_vs_path":  r"VC\Auxiliary\Build\vcvars64.bat",       # Path of the 64bit Developer Console relative to vs_path 
    },

    "host_ip": '192.168.56.1',
    "host_port": 10000,
    "guest_ip": "1.1.1.1",
    "guest_port": 10000,
    "debug_sleep": 0,
    "socket_timeout": 480,

    "staged_update": False,    # requires python on client, SHOULD BE DISABLED FOR PROD
    "requires_cleaning_before_snapshot": True,

    # Virtualization related
    # VM_CONTROLLER choose "VboxManageController" for VirtualBox or "KvmManageController" for KVM
    "VM_CONTROLLER": "VboxManageController",
    "VM_NAME": "vm_name_prod",
    "SNAPSHOT_NAME": "snapshot_name_prod",
}

# Use the following line instead of specifying a PROD_INSTANCE
# if you are building roamer on the same vm instance you are dumping with

# PROD_INSTANCE = BUILD_INSTANCE


                     
TASKS = [
    "unpacker",
    #"receiver",   
    #"whitelister",
    #"whitelist",  
    #"bootstrap"   
]

