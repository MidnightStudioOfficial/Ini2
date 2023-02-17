#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "kittenlexer.hpp"

using namespace std;

class file
{
private:
    std::string left;
    std::string right;
public:
    file();
    std::map<string,string> parse_file(string filepath);
};
 
file::file()
{

}
 
std::map<string,string> file::parse_file(string filepath)
{
        std::string rd;
        std::ifstream fileifs;
        fileifs.open(filepath);
        while(fileifs.good()) rd += fileifs.get();
        if(!rd.empty()) rd.pop_back();
  
   KittenLexer lexer = KittenLexer()
            .add_stringq('"')
            .add_stringq('\'')
            .add_capsule('(',')')
            .add_capsule('[',']')
            .add_capsule('{','}')
            .add_backslashopt('t','\t')
            .add_backslashopt('n','\n')
            .add_backslashopt('r','\r')
            .add_backslashopt('\\','\\')
            .add_backslashopt('"','"')
            .add_ignore(' ')
            .add_ignore('\t')
            .add_linebreak('\n')
            .add_extract('=')
            .add_extract(',')
            .erase_empty()
            .add_lineskip('#');
        auto lexed = lexer.lex(rd);


        std::vector<lexed_kittens> lines;
        std::map<string,string> done;
        int cline = -1;
        for(auto i : lexed) {
            if(cline != i.line) {
                lines.push_back({});
                cline = i.line;
            }
            lines.back().push_back(i);
        }
    for(size_t i = 0; i < lines.size(); ++i) {
      if(lines[i].empty()) continue;
      left = lines[i][0].src;
      right = lines[i][2].src;
      //std::cout <<  lines[i][0].src << "\n";
      done[left] = right;
      //std::cout <<  lines[i][0].line << "\n";
      //std::cout << lines[i][2].src << "\n";
      //std::cout <<  lines[i][0].src.front() << "\n";
      }
  return done;
}