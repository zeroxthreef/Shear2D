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
	Compiles and runs game\n\
\n\
--runonly\n\
	Just runs game binary. Usefulif just changing scripts\n\
\n\
--compile\n\
	Compiles game (debug mode by default if you leave game.json in debug mode)\n\
\n\
--compile_release\n\
	Explicitly compiles as release (changes the json in game.json)\n\
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
		mapping module_settings, module_libs_srcs = (["srcs":({}), "libs":({})]);
		
		write("Handling modules...\n");
		
		foreach(modules, string data)
		{
			/* make sure enabled in the module.json */
			module_settings = Standards.JSON.decode(Stdio.read_file("modules/" + data + "/module.json"));
			
			if(module_settings->enabled == "true")
			{
				write("Handling module %s, prefix %s\n", data, module_settings->prefix);
				
				/* add the module sources to the mapping */
				
				/*
				if(module_settings->c_src)
					foreach(module_settings->c_src, string m_src)
					{
						//Array.push(module_libs_srcs->srcs, "modules/" + data + "/" + m_src);
						module_libs_srcs->src += ({(string)("modules/" + data + "/" + m_src)});
					}
				*/
				/* wish i could do the above method, but that doesnt work for whatever reason */
				if(module_settings->c_src)
				{
					/* loop through each one first and modify the path */
					for(int i = 0; i < sizeof(module_settings->c_src); i++)
						module_settings->c_src[i] = "modules/" + data + "/" + module_settings->c_src[i];
					
					/* add it to the source array */
					module_libs_srcs->srcs += module_settings->c_src;
				}
				
				/* test for module pike compile scripts. indicates module is using an external library */
				
				if(Stdio.is_file("modules/" + data + "/module.pike"))
				{
					/* compile the external libraries if necessary */
					write("Handling %s's external librar(y/ies)\n", data);
					
					/* need to somehow return a string array from the other script */
				}
				
			}
			else
				write("Skipping module %s\n", data);
			
			
		}
		
		write("Module sources added to compile step\n");
		
		foreach(module_libs_srcs->srcs, string mod_srcs)
			write("%s\n", mod_srcs);
		
		write("Module libraries added to linking step\n");
		
		foreach(module_libs_srcs->libs, string mod_libs)
			write("%s\n", mod_libs);
		
		
		return module_libs_srcs;
	}
	
	/* returns a path to the object file */
	private string _compile_individual(string cc, array(string) cflags, string lloc, string iloc, string file)
	{
		object current;
		int return_val;
		string I_cflag, object_loc = "output/tmp/", temp_str;
		array(string) temp_filter, command = ({cc, "-c", "-o"});
		
		if(iloc)
			I_cflag = "-I" + iloc;
		
		
		/* rename to object file */
		
		temp_filter = file / "/";
		temp_str = temp_filter * "_";
		
		temp_str = replace(temp_str, ".c", ".o");
		
		object_loc += temp_str;
		
		write("Compiling %s -> %s\n", file, object_loc);
		
		/* add to the command */
		
		command += ({object_loc});
		if(iloc)
			command += ({I_cflag});
		command += ({"-Isrc"});
		command += cflags;
		command += ({file});
		
		/* temporary debugging */
		//foreach(command, string arg)
			//write("commandpart: %s\n", arg);
		
		/* finally run the command and respond to errors (TODO */
		
		current = Process.create_process(command);
		return_val = current.wait();
		
		/* handle errors */
		if(return_val)
			return 0;
		else
			return object_loc;
	}
	
	int compile(string cc, string bin_name, array(string) cflags, string lloc, string iloc)
	{
		mapping sources_libraries = add_module_sources(), game_settings = Standards.JSON.decode(Stdio.read_file("game_src/game.json"));
		array(string) objects = ({});
		
		write("Compiling \"%s\"\n", bin_name);
		
		/* add the engine sources to the mapping aswell */
		for(int i = 0; i < sizeof(engine_src); i++)
			engine_src[i] = "src/" + engine_src[i];
		
		sources_libraries->srcs += engine_src;
		
		/* add the game sources */
		
		for(int i = 0; i < sizeof(game_settings->c_src); i++)
			game_settings->c_src[i] = "game_src/" + game_settings->c_src[i];
		
		sources_libraries->srcs += game_settings->c_src;
		
		
		/* make the dir */
		
		if(!Stdio.is_dir("output/tmp"))
			if(!mkdir("output") && !mkdir("output/tmp"))
			{
				write("Unable to create the output & tmp directory\n");
				return 1;
			}
		
		/* compile objects for all source files */
		foreach(sources_libraries->srcs, string src)
		{
			string object_current = _compile_individual(cc, cflags, lloc, iloc, src);
			
			if(!object_current)
			{
				write("Compile error\n");
				return 1;
			}
			
			objects += ({object_current});
		}
		
		
		/* link everything */
		write("Linking \"%s\"\n", bin_name);
		
		return 0;
	}
};


int main(int argc, array(string) argv)
{
	/* ShearArgs arguments = ShearArgs(argv); */
	mapping arguments = Arg.parse(argv), game_settings = Standards.JSON.decode(Stdio.read_file("game_src/game.json"));
	CompilerController ccontroller = CompilerController(engine_src);
	string cc = "cc", cclibloc, ccincloc;
	array(string) final_flags, default_flags = ({"-Wall"}), debug_flags = ({"-g"}); /* TODO add debug defines */
	
	/* get necessary variables */
	if(arguments->cc)
		cc = arguments->cc;
	
	/* modify flags */
	final_flags = default_flags;
	
	if(game_settings->debug == "true")
	{
		write("Debug mode\n");
		final_flags += debug_flags;
	}
	else
		write("Release mode\n");
	
	final_flags += game_settings->cflags;
	
	
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
	else if(arguments->compile)
	{
		write("Compiling...\n");
		if(ccontroller.compile(cc, replace(game_settings->name, " ", "_"), final_flags, cclibloc, ccincloc))
			write("Error compiling engine or game\n");
		else
			write("everything compiled successfully\n");
	}
	else
		write("No command selected\n");
	
	
	
	
	return 0;
}

/* TODO make resource packing functions and stuff */