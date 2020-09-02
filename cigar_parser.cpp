#include <iostream>
#include <string>

int main() {
    std::string query = "CGGTAGCGCTTCGTTCGGACAATGATACGGCGACCACCGAGATCTACACCGACAGGTTCAGGAAGTTCTA-AGTCCGACGAT-CT-GCGTGGCAGTCAT--A-GCTG-ATTAGAGCGCCACCCCGCGTCTTGGACAT-CTCCAATACAGCATCTTTTATCTCATTATTACCGTCTTCTGCTTATATTACACGTG";
    std::string ref = "--------------------AATGATACGGCGACCACCGAGATCTACACCGACAGGTTCAG--AGTTCTACAGTCCGACGATCCTAGAGAGTTCGACCTGGAGGCTGCAGTCTTACGCCA--ATGATACGGCGACATCCTCC---ACGGTA-AGTTTATCTC-GTA-TGCCGTCTTCTGCTTG";
    std::string comp = "|||||||||||||||||||||||||||||||||||||||||  ||||||| ||||||||||| || |*|*|***|*|*|  | |||| |*|****|||||  **|***|***||||| ||||   ||*|*| **|||||||| *|| |*|||||||||||||**";
    std::string cigar = "20I41=2I7=1D13=1X4=1D1X1=1X22=1D32=1I8=1I1X2=1I1=1X13=2X10I";

    std::string new_cigar = "";
    for (char& elem : cigar) {
	if( elem == '=' || elem == 'X')
	    elem = 'M';
	new_cigar += elem;
    }
    new_cigar[new_cigar.find('I')] = 'S';
    new_cigar[new_cigar.length() - 1] = new_cigar[new_cigar.length() - 1] == 'D'?'D':'S';
    std::cout<<new_cigar<<"\n";

    return 0;
}
