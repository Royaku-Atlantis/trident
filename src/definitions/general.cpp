#include "../trident.hpp"
#include "../general.hpp"

//bool GLOBAL_ErrorTellProgrammer = false;

#include <conio.h>
void wait_interaction(){getch();}

//print functions
void print_error(const String & errortext) 
{
    std::cout << "\n\033[31m" << errortext << "\n\033[0m\n";
}

void say(const String & text)
{std::cout<<text<< WHITE "\n";}

String textFormat(int fontcolor)
{return "\033[" + std::to_string(fontcolor) + 'm';}
String textFormat(int info1, int info2)
{return "\033[" + std::to_string(info1) + ',' + std::to_string(info2) + 'm';}
String textFormat(int info1, int info2, int info3)
{return "\033[" + std::to_string(info1) + ',' + std::to_string(info2) + ',' + std::to_string(info3) + 'm';}

void assert(bool condition, String error_message)
{
	if (condition) return;
	error(error_message);
	throw -1;
}

// file text
void get_file(const String & filepath, Array<String> & file_text)
{
	//initialisation
	std::ifstream filedata (filepath);
	if(filedata.fail()){
		print_error("There wa an error trying to read the file : \"" + filepath + '"');
		return;
	}
	file_text.clear();
	//read the file
	String txtline;
	while (!filedata.eof())
	{
		std::getline(filedata, txtline);
		file_text.push_back(txtline);
	}
}

String to_string(const Array<String> & file_text)
{
	String printable = "";
	for (String line : file_text)
		printable += line + '\n';
	
	return printable;
}

unsigned int stoi2(String text_to_convert, int default_value)
{
        try{
                return stoi(text_to_convert);
        }
        catch(...){
                return (default_value);
        }
}

bool get_number_from_string(String text_to_convert, double & result)
{
        try{
                double test = stod(text_to_convert);
		result = test;
		return true;
        }
        catch(...){
                return false;
        }
}

//math type sh...
String double_to_trimmed_string(double value)
{
	String str = std::to_string(value);

	//trim the useless 0
	str.erase(str.find_last_not_of('0') + 1, String::npos );

	//remove the . if its a whole nuber
	if (str.back()=='.') str.pop_back();

	return str;
}

String string_multip(const String & str, int number)
{
	if (number <= 0) return "";
	if (number == 1) return str;

	String text = "";
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

double random_range(double mini, double maxi)
{
	//flip if wrong order
	if (maxi < mini) flip(mini, maxi);

	double random = rand()/static_cast<double>(RAND_MAX);
	return (random * (maxi - mini)) + mini;
}