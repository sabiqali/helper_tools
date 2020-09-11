#include <iostream>
#include <string>

int main() {
    std::string query = "CGGTAGCGCTTCGTTCGGACAATGATACGGCGACCACCGAGATCTACACCGACAGGTTCAGGAAGTTCTA-AGTCCGACGAT-CT-GCGTGGCAGTCAT--A-GCTG-ATTAGAGCGCCACCCCGCGTCTTGGACAT-CTCCAATACAGCATCTTTTATCTCATTATTACCGTCTTCTGCTTATATTACACGTG";
    std::string ref = "--------------------AATGATACGGCGACCACCGAGATCTACACCGACAGGTTCAG--AGTTCTACAGTCCGACGATCCTAGAGAGTTCGACCTGGAGGCTGCAGTCTTACGCCA--ATGATACGGCGACATCCTCC---ACGGTA-AGTTTATCTC-GTA-TGCCGTCTTCTGCTTG";
    std::string comp = "|||||||||||||||||||||||||||||||||||||||||  ||||||| ||||||||||| || |*|*|***|*|*|  | |||| |*|****|||||  **|***|***||||| ||||   ||*|*| **|||||||| *|| |*|||||||||||||**";
    std::string cigar = "20I41=2I7=1D13=1X4=1D1X1=1X22=1D32=1I8=1I1X2=1I1=1X13=2X10I";

    int match = 0,ins = 0,del = 0,refi = 0,compi = 0;
    std::string new_cigar = "";
    for(char& elem : query) {
    	if(ref[refi] == '-' && ((refi < ref.find('A')) || (refi < ref.find('G')) || (refi < ref.find('G')) || (refi < ref.find('C')))) {
	    std::cout<<"-";
	    ins++;
	    refi++;
	}
	else {
	    //new_cigar = new_cigar + std::to_string(ins) + "I";
	    if(comp[compi] == '|' || comp[compi] == '*') {
		if(ins != 0) {
		    new_cigar = new_cigar + std::to_string(ins) + "I";
		    ins = 0;
		}
		if(del != 0) {
		    new_cigar = new_cigar + std::to_string(del) + "D";
		    del = 0;
		}
		match++;
	    }
	    if(comp[compi] == ' ') {
		if(match != 0) {
		    new_cigar = new_cigar + std::to_string(match) + "M";
		    match = 0;
		}
		if(elem == '-')
		    del++;
		else
		    ins++;
	    }
	    refi++;
	    compi++;
	}
    }
    std::cout<<"\n"<<new_cigar<<"\n";

    new_cigar = "";
    for (char& elem : cigar) {
	if( elem == '=' || elem == 'X')
	    elem = 'M';
	new_cigar += elem;
    }
    new_cigar[new_cigar.find('I')] = 'S';
    new_cigar[new_cigar.length() - 1] = new_cigar[new_cigar.length() - 1] == 'D'?'D':'S';
    std::cout<<new_cigar<<"\n";
	std::string final_cigar = "";
    int num_mem1 = 0, num_mem2 = 0;
    char char_mem1, char_mem2;

    for(int i = 0; i < new_cigar.length(); i++)  {
		if(isdigit(new_cigar[i])) {
			num_mem1 = (num_mem1*10) + (new_cigar[i] - '0');
			//std::cout<<num_mem1; 
		}
		if(new_cigar[i] == 'S') {
			final_cigar = final_cigar + std::to_string(num_mem1) + "S";
			num_mem2 = num_mem1;
			char_mem2 = new_cigar[i];
			num_mem1 = 0;
		}
		if(new_cigar[i] == 'M' || new_cigar[i] == 'I' || new_cigar[i] == 'D') {
			/*char_mem1 = new_cigar[i];
			int c = i;
			if(i<new_cigar.length()) {
				c++;
				num_mem2 = (num_mem2*10) + (new_cigar[c] - '0');
				c++;
				if(isdigit(new_cigar[c])) 
					num_mem2 = (num_mem2*10) + (new_cigar[c] - '0');
				else {
					if(char_mem1)
				}
			}*/
			if(char_mem2 == new_cigar[i]) {
				num_mem2 += num_mem1;
			}
			if(char_mem2 != new_cigar[i]) {
				final_cigar = final_cigar + std::to_string(num_mem2) + char_mem2;
				num_mem2 = num_mem1;
				char_mem2 = new_cigar[i];
			}
			//final_cigar = final_cigar + std::to_string(num_mem1) + "M";
			num_mem1 = 0;
		}	
    }

	std::cout<<"\n"<<final_cigar;

    return 0;
}
