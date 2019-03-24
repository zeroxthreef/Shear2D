#!/usr/bin/pike

import Arg;

/* dont touch these constants. They will eventually be automatically increased with another tool */
constant shear_major = 0;
constant shear_minor = 0;
constant shear_revision = 0;
/* =================== */


array(string) engine_src = ({
	"engine.c",
	"events.c",
	"module.c",
	"scenegraph.c",
	"state.c",
	"timer.c",
	"util.c",
	"render.c",
});

class ShearArgs
{
	inherit Arg.LowOptions;
	
	Opt help = MaybeOpt("--help") | MaybeOpt("--h");
	Opt version = NoOpt("--version");
	Opt cc = HasOpt("--cc");
};


int main(int argc, array(string) argv)
{
	ShearArgs arguments = ShearArgs(argv);
	
	/* use the commands passed to determine what to do */
	
	
	
	
	
	return 0;
}

/* TODO make resource packing functions and stuff */