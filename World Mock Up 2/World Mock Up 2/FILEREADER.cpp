/*
COPYRIGHT COLE WILLISON 25/02/2014
THIS SOFTWARE IS INTENDED FOR OPEN SOURCE USE, REDISTRIBUTION
IS ENCOURAGE

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef FILE_READER_METHODS
#define FILE_READER_METHODS

#include "FileReader.h"

using namespace std;

FileReader::FileReader(string fn)
{
	fileName = fn; 
	vector<int> tempLineVec;

	ifstream infile;
	string line;

	infile.open(fileName);
	getline(infile,line);

	while(line !="*") 
	{
		getline(infile, line);
		if (line != "*") 
			currentMap.push_back(removeSlashAndParse(line));
	}

	infile.close();
}

vector<vector<int>> FileReader::getMap(void) {return currentMap;}

int FileReader::getX(void)  {return currentMap.at(0).size();}

int FileReader::getY(void) {return currentMap.size();}

void FileReader::print2dIntVector(vector<vector<int>> vec2d)
{
	//(+) debugging
	cout << endl;
	for (unsigned int i = 0; i<vec2d.size(); i++)
	{
		for(unsigned int j = 0; j<vec2d.at(0).size(); j++)
			cout<<vec2d.at(i).at(j)<<"-";
		cout<<endl;
	}
	//(-)
}

/*This method takes one a string like /34/4/342/32/
and returns a vector of the values within the slash.
*/
vector<int> FileReader::removeSlashAndParse(string line)
{
	int temp = 0;
	vector<int> slashLoc;
	vector<int> IDs;
	for(unsigned int i = 0; i <line.size();i++)
		if (line[i] == '/') slashLoc.push_back(i);

	for(unsigned int i = 0; i<slashLoc.size()-1;i++)
	{	
		temp = stoi(line.substr(slashLoc.at(i)+1,slashLoc.at(i+1)-slashLoc.at(i)-1));
		IDs.push_back(temp);
		cout<<temp;
	}

	slashLoc.clear();
	return IDs;
}

#endif