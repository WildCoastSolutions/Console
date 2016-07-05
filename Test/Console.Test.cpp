//
// Author       Wild Coast Solutions
//              David Hamilton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.
//
// This file contains tests for the console library in
// Console.h
// 
// Testing is done by the unit testing library from
// https://github.com/WildCoastSolutions/UnitTesting

#include "Console.h"
#include "UnitTesting.h"

using namespace Wild::CommandLine;
using namespace Wild::Console;
using namespace std;


void Call(Args args)
{
    cout << "Creating call: address=" << args.Get("address") << " bitrate=" << args.Get("bitrate") << " source=" << args.Get("source") << endl;
}


void ReadmeSampleCode()
{
    Console console("test", 
        {    
            Command("call", "c", "create new call",
                {
                    Option("address", "a", "Remote address", Is::Required),
                    Option("bitrate", "b", "Call bitrate", "1024"),
                    Option("source", "s", "Video source", "test-media/1.mp4"),
                },
                [](Args args) { Call(args); }
            ),

            Command("disconnect", "d", "disconnect a call",
                // name, letter, description
                {
                    Arg("call", "c", "Call identifier"),
                }
            ),
        });

    console.Run();

}



void TestConstruction()
{
    AssertThrows(Args args({ }), invalid_argument);

    AssertThrows(Flag("", "", ""), invalid_argument);
    AssertThrows(Flag("version", "", ""), invalid_argument);
    AssertThrows(Flag("", "v", ""), invalid_argument);
    AssertThrows(Flag("v", "v", ""), invalid_argument);
    AssertThrows(Flag("version", "vr", ""), invalid_argument);

    AssertThrows(Arg("", "", ""), invalid_argument);
    AssertThrows(Arg("version", "", ""), invalid_argument);
    AssertThrows(Arg("", "v", ""), invalid_argument);
    AssertThrows(Arg("v", "v", ""), invalid_argument);
    AssertThrows(Arg("version", "vr", ""), invalid_argument);

    // Can't set the default to something not in the list of possibles
    AssertThrows(Arg("colour", "c", "Colour", { "red", "blue" }, "green"), invalid_argument);

}


int main(int argc, char* argv[])
{
    ReadmeSampleCode();
    

    EndTest
}

