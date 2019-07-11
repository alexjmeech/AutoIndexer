#include "AutoIndexer.h"
using namespace std;

AutoIndexer::AutoIndexer(ifstream& input, ofstream& output)
{
	if (!input.good() || !output.good())
	{
		cout << "Error! The provided input and/or output files are invalid!" << endl;
		return;
	}
    
	cout << "Beginning index creation" << endl;
	loadData(input);
	outputData(output);
	cout << "Finished index creation" << endl;
}

void AutoIndexer::processLine(int page, String& line)
{
	ArrayWrapper<String> split = line.split(' ');
	String composite;
    
	for (unsigned int i = 0; i < split.arrayLength(); i++)
	{
		String word = split[i].toLower();
        
		if (word[0] == '[')
		{
			composite = word.substring(1, word.getLength());
		}
		else if (composite.getLength() > 0)
		{
			if (word[word.getLength() - 1] == ']')
			{
				String key = (composite + ' ' + word.substring(0, word.getLength() - 1)).stripCharacter([](char check)
				{
					return ispunct(check) && check != '+' && check != '-';
				});
                
				composite = String();
				indexEntries[key].push_back(page);
			}
			else
			{
				composite += (' ' + word);
			}
		}
		else
		{
			word = word.stripCharacter([](char check)
			{
				return ispunct(check) && check != '+' && check != '-';
			});
            
			if (indexEntries[word].indexOf(page) == indexEntries[word].getSize())
			{
				indexEntries[word].push_back(page);
			}
		}
	}
}

void AutoIndexer::loadData(ifstream& input)
{
	cout << "Processing Data" << endl;
	int page = -1;
    
	while (input.good())
	{
		String line;
		getline(input, line);
        
		if (line == "<-1>")
		{
			break;
		}
        
		if (line == "")
		{
			continue;
		}
        
		if (line[0] == '<')
		{
			char* c_string = line.substring(1, line.getLength() - 1).c_string();
			page = atoi(c_string);
			delete[] c_string;
		}
		else
		{
			processLine(page, line);
		}
	}
    
	cout << "Processed Data (" << indexEntries.size() << " Index Entries)" << endl;
}

void AutoIndexer::outputData(ofstream& output)
{
	cout << "Outputting Data" << endl;
	char header = '-';

	for (pair<String, ArrayList<int>> element : indexEntries)
	{
		String key = element.first;
		ArrayList<int> pages = element.second;

		if (header != toupper(key[0]))
		{
			header = toupper(key[0]);
			output << '[' << header << ']' << endl;
		}
        
		output << key << ": " << pages.pop();
        
		for (int page : pages)
		{
			output << ", " << page;
		}
        
		output << endl;
	}
    
	cout << "Output Data" << endl;
}
