#include <iostream>
#include <fstream>
#include <cstring>
#include <getopt.h>
#include <sstream>

/*
void removeDupWord(std::string str)
{
    // Used to split string around spaces.
    std::istringstream ss(str);

    // Traverse through all words
    do {
        // Read a word
        std::string word;
        ss >> word;

        // Print the read word
        std::cout << word << std::endl;

        // While there is more to read
    } while (ss);
} */

static const char *ALIGN_MESSAGE = 
"Usage: ./align [OPTIONS] --reads reads.fastq --control control_oligos.txt --output_file output_file.txt --parasail\n"
"Align reads to control oligos provided.\n"
"\n"
"  -p, --print_alignment                display best alignment for every read\n"
"      --version                        display version\n"
"      --help                           display this help and exit\n"
"  -r, --reads=FILE                     the ONT reads are in fastq FILE\n"
"  -c, --control=FILE                   the control oligos that are in a text FILE\n"
"  -f, --output_file=FILE               the file to which the score will be output to\n"
"      --table_out                      the output to file will be in a tabular format including only the score and names of the read and the control\n"
"      --align_out                      the output to file will be in an alignment format which will include the read, control oligo and the SAM cigar\n"
"  -t, --threads=NUM                    use NUM threads (default: 1)\n"
"      --parasail                       watch the sequencing run directory DIR and call methylation as data is generated\n"
"      --edlib                          in watch mode, write the alignments for each fastq\n\n";

namespace opt
{
    static unsigned int print_alignment;
    static std::string reads_file;
    static std::string control_file;
    static std::string output_file;
    static int table_out = 0;
    static int align_out = 0;
    static int parasail = 0;
    static int edlib = 0;
    static int num_threads = 1;
}

static const char* shortopts = "r:c:f:t:p";

enum { OPT_HELP = 1, OPT_VERSION, OPT_TABLE_OUT, OPT_ALIGN_OUT, OPT_PARASAIL, OPT_EDLIB };

static const struct option longopts[] = {
    { "print_alignment",      no_argument,       NULL, 'p' },
    { "reads",                required_argument, NULL, 'r' },
    { "control",              required_argument, NULL, 'c' },
    { "output_file",          required_argument, NULL, 'f' },
    { "threads",              required_argument, NULL, 't' },
    { "table_out",            no_argument,       NULL, OPT_TABLE_OUT },
    { "align_out",            no_argument,       NULL, OPT_ALIGN_OUT },
    { "parasail",             no_argument,       NULL, OPT_PARASAIL },
    { "edlib",                no_argument,       NULL, OPT_EDLIB },
    { "help",                 no_argument,       NULL, OPT_HELP },
    { "version",              no_argument,       NULL, OPT_VERSION },
    { NULL, 0, NULL, 0 }
};

void parse_align_options(int argc, char** argv)
{
    bool die = false;
    for (char c; (c = getopt_long(argc, argv, shortopts, longopts, NULL)) != -1;) {
        std::istringstream arg(optarg != NULL ? optarg : "");
        switch (c) {
            case 'p': arg >> opt::print_alignment; break;
            case 'r': arg >> opt::reads_file; break;
            case 'c': arg >> opt::control_file; break;
            case 'f': arg >> opt::output_file; break;
            case '?': die = true; break;
            case 't': arg >> opt::num_threads; break;
            case OPT_TABLE_OUT: opt::table_out = 1; break;
            case OPT_ALIGN_OUT: opt::align_out = 1; break;
            case OPT_PARASAIL: opt::parasail = 1; break;
            case OPT_EDLIB: opt::edlib = 1; break;
            case OPT_HELP:
                std::cout << ALIGN_MESSAGE;
                exit(EXIT_SUCCESS);
            case OPT_VERSION:
                std::cout << ALIGN_MESSAGE;
                exit(EXIT_SUCCESS);
        }
    }

    /*if(argc - optind > 0) {
        opt::region = argv[optind++];
    }

    if (argc - optind > 0) {
        std::cerr << SUBPROGRAM ": too many arguments\n";
        die = true;
    }*/

    if(opt::num_threads <= 0) {
        std::cerr << "Align : invalid number of threads: " << opt::num_threads << "\n";
        die = true;
    }

    if(opt::control_file.empty()) {
        std::cerr << "Align: a --control file must be provided\n";
        die = true;
    }

    if(opt::reads_file.empty()) {
        std::cerr << "Align: a --reads file must be provided\n";
        die = true;
    }

    if(opt::output_file.empty()) {
        std::cerr << "Align: a --output file must be provided\n";
        die = true;
    }

    if(opt::parasail == 0 && opt::edlib == 0) {
        std::cerr << "Align: processing option must be selected. Please selected either --parasail or --edlib\n";
        die = true;
    }

    if (die)
    {
        std::cout << "\n" << ALIGN_MESSAGE;
        exit(EXIT_FAILURE);
    }
}

std::string removeDupWord(std::string str)
{
   std::string word = "";
   for (auto x : str)
   {
       if (x == ' ')
       {
           std::cout << word << std::endl;
           word = "";
       }
       else
       {
           word = word + x;
       }
   }
   std::cout << word << std::endl;
   return word;
}

int main(int argc, char** argv) {

    parse_align_options(argc, argv);

    std::cout<<opt::parasail<<std::endl; 
        std::ifstream control_fd("control_oligos.txt");

        std::string probe_no;
        std::string probe_name;
        std::string seq;
        
        std::string one_line;
        std::string sequence;

        while(control_fd) {
                getline(control_fd,probe_no,' ');
                getline(control_fd, probe_name,' ');
                getline(control_fd,seq,'\n');
                getline(control_fd,one_line);
                sequence = removeDupWord(one_line);
                std::cout<<sequence;
                //std::cout<<probe_no<<std::endl<<probe_name<<std::endl<<seq<<std::endl<<one_line;
                //std::cout<<"seq "<<seq<<"\nProbe_no "<<probe_no<<"\n Probe name "<<probe_name<<std::endl;
                break;
        }

        control_fd.close();
        return 0;
}

