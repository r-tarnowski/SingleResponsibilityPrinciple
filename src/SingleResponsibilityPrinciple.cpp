#include <iostream>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>


using std::cout;
using std::endl;

void printHeader() {
   cout << endl;
   cout << "================================================" << endl;
   cout << "Design Patterns in Modern C++ by Dmitri Nesteruk" << endl;
   cout << "SOLID, Single Responsibility Principle" << endl;
   cout << "================================================" << endl;
   cout << endl;
}

struct Journal {
    std::string title;
    std::vector< std::string > entries;

    explicit Journal( const std::string & title ) : title( title ) {}
    void add( const std::string & entry );
};

void Journal::add( const std::string & entry ) {
    static int count = 1;
    entries.push_back( boost::lexical_cast<std::string>( count ++ ) +
                       ": " + entry);
}

struct PersistenceManager {
    static void save( const Journal & journal, const std::string & filename ) {
        std::ofstream ofs( filename );
        ofs << journal.title << endl;
        for ( auto& s : journal.entries ) {
            ofs << s << endl;
        }
    }

    static void print( const Journal & journal ) {
        std::cout << journal.title << endl;
        for ( auto& s : journal.entries ) {
            std::cout << s << endl;
        }
    }

};

int main(int argc, char *argv[]) {
   printHeader();

   Journal journal( "Drogi dzienniczku" );
   journal.add( "Płakałem dzisiaj" );
   journal.add( "Zjadłem robaka" );

   PersistenceManager::print( journal );
   PersistenceManager::save( journal, "MyDiary.txt" );

   cout << endl;
   return 0;
}
