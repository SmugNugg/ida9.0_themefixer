#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <regex>

std::unordered_map<std::string , std::string> loadVariables ( const std::string& content )
{
    std::unordered_map<std::string , std::string> variables;
    std::regex varRegex ( R"(@def\s+(\S+)\s+(.+?);)" );
    std::smatch match;
    std::string::const_iterator searchStart ( content.cbegin ( ) );

    while ( std::regex_search ( searchStart , content.cend ( ) , match , varRegex ) )
    {
        variables [ match [ 1 ] ] = match [ 2 ];
        searchStart = match.suffix ( ).first;
    }

    std::regex varUsageRegex ( R"(\$\{(\S+?)\})" );

    for ( auto& [key , value] : variables )
    {
        std::smatch match;
        while ( std::regex_search ( value , match , varUsageRegex ) )
        {
            std::string refName = match [ 1 ];
            if ( variables.find ( refName ) != variables.end ( ) )
            {
                value.replace ( match.position ( 0 ) , match.length ( 0 ) , variables [ refName ] );
            }
            else
            {
                std::cerr << "Warning: Variable " << refName << " referenced in " << key << " is undefined.\n";
                break;
            }
        }
    }

    return variables;
}

std::string removeFunctions ( const std::string& content )
{
    std::string result = content;
    std::regex functionRegex ( R"(@[a-zA-Z_]+\((\s*#[a-fA-F0-9]{6})(?:,.*)?\))" );
    std::smatch match;

    while ( std::regex_search ( result , match , functionRegex ) )
    {
        result.replace ( match.position ( 0 ) , match.length ( 0 ) , match [ 1 ] );
    }

    return result;
}

std::string replaceVariables ( const std::string& content , const std::unordered_map<std::string , std::string>& variables )
{
    std::string result = content;
    std::regex varUsageRegex ( R"(\$\{(\S+?)\})" );
    std::smatch match;

    while ( std::regex_search ( result , match , varUsageRegex ) )
    {
        std::string varName = match [ 1 ];
        auto it = variables.find ( varName );
        if ( it != variables.end ( ) )
        {
            result.replace ( match.position ( 0 ) , match.length ( 0 ) , it->second );
        }
        else
        {
            std::cerr << "Warning: Variable " << varName << " not defined. Skipping replacement.\n";
        }
    }

    result = removeFunctions ( result );

    return result;
}

int main ( int argc , char* argv [ ] )
{
    if ( argc != 2 )
    {
        std::cerr << "Usage: " << argv [ 0 ] << " <path to .css file>\n";
        return 1;
    }

    std::string inputFilePath = argv [ 1 ];
    std::ifstream inputFile ( inputFilePath );

    if ( !inputFile.is_open ( ) )
    {
        std::cerr << "Error: Could not open file " << inputFilePath << "\n";
        std::cin.get ( );
        return 1;
    }

    std::ostringstream buffer;
    buffer << inputFile.rdbuf ( );
    std::string content = buffer.str ( );
    inputFile.close ( );

    auto variables = loadVariables ( content );
    std::string updatedContent = replaceVariables ( content , variables );

    std::ofstream outputFile ( inputFilePath );

    if ( !outputFile.is_open ( ) )
    {
        std::cerr << "Error: Could not write to file " << inputFilePath << "\n";
        std::cin.get ( );
        return 1;
    }

    outputFile << updatedContent;
    outputFile.close ( );

    std::cout << "File successfully updated and saved as " << inputFilePath << "\n";
    std::cin.get ( );
    return 0;
}
