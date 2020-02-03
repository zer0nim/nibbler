$ python3 prog.py --help
usage: prog.py [-h]

optional arguments:
  -h, --help  show this help message and exit


$ python3 prog.py --verbose
usage: prog.py [-h]
prog.py: error: unrecognized arguments: --verbose


$ python3 prog.py foo
usage: prog.py [-h]
prog.py: error: unrecognized arguments: foo

# ------------------------------------------------------------------------------

$parser.add_argument("--verbosity", help="increase output verbosity")

$ python3 prog.py --verbosity
usage: prog.py [-h] [--verbosity VERBOSITY]
prog.py: error: argument --verbosity: expected one argument
# ------------------------------------------------------------------------------

parser.add_argument("--verbose", help="increase output verbosity", action="store_true")

$ python3 prog.py --verbose
verbosity turned on

$ python3 prog.py --verbose 1
usage: prog.py [-h] [--verbose]

prog.py: error: unrecognized arguments: 1
$ python3 prog.py --help
usage: prog.py [-h] [--verbose]

optional arguments:
  -h, --help  show this help message and exit
  --verbose   increase output verbosity
# ------------------------------------------------------------------------------

parser.add_argument("-v", "--verbose", help="increase output verbosity", action="store_true")
parser.add_argument("square", type=int, help="display a square of a given number")

$ python3 prog.py
usage: prog.py [-h] [-v] square
prog.py: error: the following arguments are required: square

$ python3 prog.py 4
16

$ python3 prog.py 4 --verbose
the square of 4 equals 16

$ python3 prog.py --verbose 4
the square of 4 equals 16

# ------------------------------------------------------------------------------
shortName:		"-v"
longName:		"--verbose"
help:			"increase output verbosity"
required:		true/false
type:			bool/int/string/float
min/max:		42 # for numbers
storeTrue:		true/false
default:		42

















int		argparse( int ac, char **av, Instruction &instruction ) {
	struct option long_options[] = {
		{"interactive",	no_argument, 0, 'i'},
		{"continue",	no_argument, 0, 'c'},
		{"verbose",		no_argument, 0, 'v'},
		{"help",		no_argument, 0, 'h'},
		{"usage",		no_argument, 0, 'h'},
		{0, 0, 0, 0}
	};
	int opt;
	int option_index = 0;
	while ( (opt = getopt_long( ac, av, "icvh", long_options, &option_index ))
	!= EOF ) {
		switch (opt) {
			case 'i':
				instruction.interactive = true;
				break;
			case 'v':
				instruction.verbose = true;
				break;
			case 'c':
				instruction.continue_error = true;
				break;
			case '?':
				return short_usage( av[0] );
			case 'h': default:
				return (usage( av[0] ));
		}
	}
	return (EXIT_SUCCESS);
}
