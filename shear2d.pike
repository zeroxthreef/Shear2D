#!/usr/bin/pike

import Arg;

#include "version.pike" /* when this gets installed, we cant do this. Need to replace this exact string with the new install path */
#include "respack.pike" /* same here */ /* wait, scratch that. Just put all of these files in the bin */

/* note: https://www.freeformatter.com/java-dotnet-escape.html#ad-output is super helpful */
string help = "\
=== Shear workspace tool help ===\n\
  _________.__                         \r\n /   _____/|  |__   ____ _____ _______ \r\n \\_____  \\ |  |  \\_/ __ \\\\__  \\\\_  __ \\\r\n /        \\|   Y  \\  ___/ / __ \\|  | \\/\r\n/_______  /|___|  /\\___  >____  /__|   \r\n        \\/      \\/     \\/     \\/       \r\n\r\n\
============ Commands ============\n\
--help=[*command]\n	Prints this page\n\
\n--version\n\
	Prints the global shear version\n\
\n\
--cc=[path/to/C_compiler]\n\
	Used to port Shear to other systems\n\
\n\
--cclibloc=[path/to/C_compiler/libraries]\n\
	Used to change system library path (where the compiler libraries are located)\n\
\n\
--ccincloc=[path.to/C_compiler/includes]\n\
	Used to change the system include path (where the compiler includes are located)\n\
\n\
--create\n\
	Asks questions for features and qualities\n\
	Initializes a directory inside the one this is run under to become the project workspace\n\
\n\
--run\n\
	Runs the current workspace and game in debug mode (doesn't pack the game files)\n\
--test_compilation\n\
	Tests if the engine and game compile in debug mode\n\
\n\
--output\n\
	Creates a binary and necessary files in /output\n\
";

array(string) engine_src = ({ /* these all will be appended to a "src/" string */
	"engine.c",
	"events.c",
	"module.c",
	"scenegraph.c",
	"state.c",
	"timer.c",
	"util.c"
});

class ShearArgs
{
	inherit Arg.LowOptions;
	
	Opt help = MaybeOpt("--help") | MaybeOpt("-h");
	Opt version = NoOpt("--version");
	Opt cc = HasOpt("--cc");
	Opt cc_lib_loc = HasOpt("--cclibloc"); /* for the compilers library location if it's any different */
	Opt cc_include_loc = HasOpt("--ccincloc"); /* for the compilers include location if it's any different */
	Opt workspace_create = HasOpt("--create");
	
};

class CompilerController
{
	private array(string) srcs;
	
	
	void create(array(string) eng_src, void|array(string) game_srcs)
	{
		srcs = eng_src;
		if(game_srcs)
			srcs += game_srcs;
	}
	
	/* scan for modules and add their sources and libraries */
	mapping add_module_sources()
	{
		array(string) modules = get_dir("modules");
		mapping module_settings;
		
		write("Handling modules...\n");
		
		foreach(modules, string data)
		{
			/* make sure enabled in the module.json */
			module_settings = Standards.JSON.decode(Stdio.read_file("modules/" + data + "/module.json"));
			
			if(module_settings->enabled == "true")
			{
				write("Handling module %s, prefix %s\n", data, module_settings->prefix);
				
				/* test for module pike compile scripts. indicates module is using an external library */
				
			}
			else
				write("Skipping module %s\n", data);
			
			/* compile the external libraries if necessary */
		}
		
	}
	
	int compile(string cc, string lloc, string iloc)
	{
		mapping sources_libraries = add_module_sources();
		
		/* add the engine sources to the mapping aswell */
		
		
		return 0;
	}
};


int main(int argc, array(string) argv)
{
	/* ShearArgs arguments = ShearArgs(argv); */
	mapping arguments = Arg.parse(argv);
	CompilerController ccontroller = CompilerController(engine_src);
	string cc = "cc", cclibloc, ccincloc;
	
	/* get necessary variables */
	if(arguments->cc)
		cc = arguments->cc;
	
	
	/* use the commands passed to determine what to do */
	
	
	if(arguments->help)
	{
		/* determine if the help is specific to a command */
		if(arguments->help == "version")
			write("placeholder\n");
		else
			write(help);
	}
	else if(arguments->version)
		write("Shear version %d.%d.%d by 0x3F\n", shear_major, shear_minor, shear_revision);
	else if(arguments->test_compile)
	{
		write("Testing if everything compiles smoothly...\n");
		if(ccontroller.compile(cc, cclibloc, ccincloc))
			write("Error compiling engine or game\n");
		else
			write("everything compiled successfully\n");
	}
	else
		write("No command selected\n");
	
	
	
	
	return 0;
}

/* TODO make resource packing functions and stuff */