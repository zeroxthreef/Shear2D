#!/usr/bin/pike

import Arg;

#include "version.pike"
#include "respack.pike"


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
	
	Opt help = MaybeOpt("--help") | MaybeOpt("--h");
	Opt version = NoOpt("--version");
	Opt cc = HasOpt("-cc");
	Opt cc_lib_loc = HasOpt("-cclibloc"); /* for the compilers library location if it's any different */
	Opt cc_include_loc = HasOpt("-ccincloc"); /* for the compilers include location if it's any different */
	Opt workspace_create = HasOpt("-create");
	
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
	ShearArgs arguments = ShearArgs(argv);
	
	/* use the commands passed to determine what to do */
	
	
	
	
	
	return 0;
}

/* TODO make resource packing functions and stuff */