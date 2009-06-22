/*
 * phc -- the open source PHP compiler
 * See doc/license/README.license for licensing information
 *
 * Convenience statistics functions.
 */

#include <iostream>
#include <sstream>

#include "stats.h"

using namespace std;
using namespace boost;

void reset_stats ()
{
	stats.clear ();
}

void reset_stringset_stats ()
{
	stringset_stats.clear ();
}

void add_to_stringset_stat (string name, string s)
{
	if (!stringset_stats[name])
	{
		stringset_stats[name] = new Stringset_stats;
	}
	stringset_stats[name]->insert (s);

}

Stringset_stats* get_stringset_stat (string name)
{
	return stringset_stats[name];
}

int stringset_stats_size()
{
	return stringset_stats.size ();
}

void increment_stat (string name, string filename, int line_number)
{
	stringstream ss;
	ss << name/* << " (" << filename << ":" << line_number << ")"*/;
}


int get_stat (string name) 
{
	return stats[name];
}

void set_stat (string name, int num)
{
	stats[name]=num;
}

void dump_stats ()
{
	string name;
	int count;
	foreach (tie (name, count), stats)
	{
		cerr << name << " - " << count << endl;
	}
}

void dump_types_per_var_name () 
{
	string s;
	int n;
	foreach (tie (s, n), stats)
	{
		if ( (s.substr(0,28) == "Number of types assigned to "))
		{
			cerr << "\'" << s.substr(28) << "\'" << ',' << n << endl;
		}
	}	
}

void dump_stringset_stats ()
{
	string s;
	Stringset_stats * sss;
	
	foreach (tie (s,sss), stringset_stats)
	{
		int count=0;
		bool first=true;

		cerr << "\'" << s << "\',\'";	//name
		foreach (string str, *sss)		//elements
		{	if (!first)
			{
				cerr << ",";
			}
			first=false;
			cerr << str ;
			count++;
		}
		cerr << "\'," << count << endl;	//num of elements
	}

}
