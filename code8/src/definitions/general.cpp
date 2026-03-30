#include "../trident.hpp"
#include "../general.hpp"

bool GLOBAL_ErrorTellProgrammer = false;

std::string textFormat(int fontcolor)
{
	return "\033[" + std::to_string(fontcolor) + "m";
}

void get_file(const std::string & filepath, std::vector<std::string> & file_text)
{
	//initialisation
	std::ifstream filedata (filepath);
	if(filedata.fail()){
		print_error("There wa an error trying to read the file : \"" + filepath + '"');
		return;
	}
	file_text.clear();
	//read the file
	std::string txtline;
	while (!filedata.eof())
	{
		std::getline(filedata, txtline);
		file_text.push_back(txtline);
	}
}

std::string to_string(const std::vector<std::string> & file_text)
{
	std::string printable = "";
	for (std::string line : file_text)
		printable += line + '\n';
	
	return printable;
}

void print_error(const std::string & errortext)
{
    std::cout << "\n\033[31m" << errortext << "\n\033[0m\n";
}

void say(const std::string & text)
{std::cout<<text<<std::endl;}

std::string double_to_trimmed_string(double value)
{
	std::string str = std::to_string(value);

	//trim the useless 0
	str.erase(str.find_last_not_of('0') + 1, std::string::npos );

	//remove the . if its a whole nuber
	if (str.back()=='.') str.pop_back();

	return str;
}

std::string string_multip(const std::string & str, int number)
{
	if (number <= 0) return "";
	if (number == 1) return str;

	std::string text = "";
	text.reserve( str.size() * number );

	for (int i=0; i<number; i++)
		text += str;

	return text;
}

double modulo(double numb, double div)
{
	if (div==0) return 0;

	double hres = numb / div;
	hres -= std::floor(hres);
	hres *= div;
	return hres;
}
