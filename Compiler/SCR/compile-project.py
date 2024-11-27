import os
import sys

def CallMSVC(arguments):
    vspath = '"C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat"'
    os.system(vspath + ' x64' + ' && ' + arguments)

def Compile():

    is_release = len(sys.argv) == 2;
    print("Compiling in " + ("PRODUCTION" if is_release else "DEVELOPMENT") + " mode");

    # Config Settings
    cpp_version     = "c++20"
    
    # Export Paths
    output_exe_path = ".\\Build\\game.exe"
    include_folders = ".\\Source\\"
    include_project_folder = ".\\Source\\Project\\"
    include_vendors_folder = ".\\Source\\Engine\\Vendors\\"
    obj_file_path   = ".\\Compiler\\OBJ\\Project\\"
    pdb_file_path   = ".\\Compiler\\PDB\\project.pdb"

    # Import Paths
    preprocessor_definitions_by_default     = "/D _CONSOLE /D _UNICODE /D UNICODE"
    preprocessor_definitions_for_debugging  = "/D _DEBUG"
    libs_path_from_third_party              = ""
    libs_linked_by_default                  = "kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib delayimp.lib"
    libs_to_be_extra_linked                 = ".\\Compiler\\LIBS\\Project\\*.lib"
    dll_to_be_delayed_on_load               = ""

    # Debug Flags Settings
    debug_flags = "/MD" if is_release else "/MDd"

    # Build Flags Settings
    building_flags = "/Gm"

    # Add compilation files to txt file
    # files_vendors_cpp = IterateFile(include_project_folder + "Vendors\\", ".cpp");
    files_source_cpp  = IterateFile(include_project_folder, ".cpp");

    with open('cpp_sources.txt', 'w') as f:
        # for i in files_vendors_cpp: f.write(i + "\n")
        for i in files_source_cpp:  f.write(i + "\n")

    # MSVC Compiler Settings
    compiler_flags = "/Od "                                            # Code Optimization
    compiler_flags += "/std:"+ cpp_version + " /sdl- /permissive- "    # Language Configuration
    compiler_flags += "/await /fp:precise /Zc:forScope /Zc:inline "
    compiler_flags += building_flags + " /nologo "                     # General Configuration
    compiler_flags += "/EHsc /diagnostics:caret /W3 /FC " #/WX "       # Error Handling            
    compiler_flags += "/Zi /RTC1 /GS"                                  # Debugging Configuration

    # MSVC Linker Settings
    linker_flags = "/NOLOGO /INCREMENTAL /DEBUG /NXCOMPAT /ERRORREPORT:PROMPT /SUBSYSTEM:CONSOLE /MACHINE:X64 /DYNAMICBASE"

    # Execute MSVC Compilation
    result_arguments = "cl.exe " + compiler_flags + " "
    result_arguments += preprocessor_definitions_by_default + " "
    result_arguments += preprocessor_definitions_for_debugging + " "
    result_arguments += "/I " + include_folders + " "
    result_arguments += "/I " + include_project_folder + " "
    result_arguments += "/I " + include_vendors_folder + " "
    result_arguments += "@cpp_sources.txt" + " "
    result_arguments += "/Fo:" + obj_file_path + " /Fd:" + pdb_file_path + " "
    result_arguments += "/Fe:" + output_exe_path + " "
    result_arguments += debug_flags + " "
    result_arguments += "/link " + linker_flags + " "
    result_arguments += libs_linked_by_default + " " + libs_to_be_extra_linked + " "
    result_arguments += libs_path_from_third_party + " "
    result_arguments += dll_to_be_delayed_on_load + " "
    result_arguments += "/PDB:" + pdb_file_path + " "

    # print(result_arguments)
    CallMSVC(result_arguments);

    os.remove('cpp_sources.txt');

def IterateFile(path, extension):
    arr = []
    for subdir, dirs, files in os.walk(path):
        
        for file in files:
        
            ext = os.path.splitext(file)[-1].lower()
        
            if (ext == extension):
                final_path = os.path.abspath(subdir + "/" + file)
                arr.append('\"' + final_path + '\"')
    return arr


Compile();