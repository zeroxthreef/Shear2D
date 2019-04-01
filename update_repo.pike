#!/usr/bin/pike
/* this file controls increasing the version numbers in shear source files */

int main(int argc, array(string) argv)
{
	bool major_change = false, minor_change = false;
	Stdio.Readline readline = Stdio.Readline();
	string choice;
	
	/* first update the file, prompt for minor and major updates */
	
	write("Updating major? (y/N)\n");
	
	choice = readline.read();
	
	if(strlen(choice))
	{
		if(choice == "Y" || choice == "y")
		{
			incdec_attribute("version.pike", "shear_major", 1);
			major_change = true;
			write("Increased major version\n");
		}
	}
	else
		write("Major unchanged\n");
	
	
	
	/* will be 0 at new major */
	if(!major_change)
	{
		write("Updating minor? (y/N)\n");
		choice = readline.read();
	}
	
	if(strlen(choice) && !major_change)
	{
		if(choice == "Y" || choice == "y")
		{
			incdec_attribute("version.pike", "shear_minor", 1);
			minor_change = true;
			write("Increased minor version\n");
		}
	}
	else if(major_change)
	{
		/* set minor to 0 */
		set_attribute("version.pike", "shear_minor", 0);
		write("Reset minor\n");
	}
	else
		write("Minor unchanged\n");
	
	/* revision always updates no matter what */
	/* if were changing the major/minor, the revision will be at 0 */
	if(minor_change || major_change)
	{
		/* set revision to 0 */
		set_attribute("version.pike", "shear_revision", 0);
		write("Reset revision\n");
	}
	else
	{
		/* just increment */
		incdec_attribute("version.pike", "shear_revision", 1);
		write("Increased revision\n");
	}
	
	
	write("Shear updated to version %d.%d.%d\n", get_attribute("version.pike", "shear_major"), get_attribute("version.pike", "shear_minor"), get_attribute("version.pike", "shear_revision"));
	
	
	write("\n");
	/* run git commands */
	
	write("Run git commnds? (y/N)\n");
	choice = readline.read();
	
	if(choice)
	{
		object current;
		
		/* add to be committed files */
		current = Process.create_process(({"git", "add", "-A"}));
		current.wait();
		
		/* prompt for commit message */
		write("Commit message: ");
		
		choice = readline.read();
		
		/* git commit */
		current = Process.create_process(({"git", "commit", "-m", choice}));
		current.wait();
		
		/* run git push */
		current = Process.create_process(({"git", "push"}));
		current.wait();
		
		write("Finished\n");
	}
	
	
	
	return 0;
}

/* no error checking for these at the moment. Only updates versions so not really needed */

int incdec_attribute(string file, string attribute, int value_posneg)
{
	set_attribute(file, attribute, get_attribute(file, attribute) + value_posneg);
	return 0;
}

int get_attribute(string file, string attribute)
{
	int attribute_val = 0;
	string version_file = Stdio.read_file(file);
	int pos = search(version_file, attribute);
	
	pos += strlen(attribute) + strlen(" = ");
	
	attribute_val = (int)version_file[pos..];
	
	return attribute_val;
}

int set_attribute(string file, string attribute, int value)
{
	string version_file = Stdio.read_file(file), updated_file;
	int pos = search(version_file, attribute), end_pos;
	
	pos += strlen(attribute) + strlen(" =");
	
	end_pos = search(version_file[pos..], ";");
	
	updated_file = version_file[..pos] + value + version_file[pos + end_pos..];
	
	/* replace the file */
	
	Stdio.write_file(file, updated_file);
	
	return 0;
}


/* backup */
/*

constant shear_major = 0;
constant shear_minor = 0;
constant shear_revision = 0;

*/