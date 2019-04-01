#!/usr/bin/pike

import Arg;

#include "version.pike"
#include "respack.pike"

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
	
	
	void create(array(string) eng_src)
	{
		srcs = eng_src;
	}
	
	/* scan the game dir and add c files wherever it finds them */
	void scan_game_dir()
	{
		
	}
};


int main(int argc, array(string) argv)
{
	/* ShearArgs arguments = ShearArgs(argv); */
	mapping arguments = Arg.parse(argv);
	
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
	else
		write("No command selected\n");
	
	
	
	
	return 0;
}

/* TODO make resource packing functions and stuff */