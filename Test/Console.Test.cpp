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


// Example class that performs the tasks we want to create commands for.
// Video phone that can call a remote phone and send some video.
// The Video being sent can be switched mid call.
class VideoPhone
{
public:

    void Call(string address, string bitrate, string source)
    {
        cout << "Creating call to: address=" << address << " bitrate=" << bitrate << " source=" << source << endl;
    }

    void ChangeVideoSource(string source)
    {
        cout << "Changing source to: " << source << endl;
    }

    void Disconnect()
    {
        cout << "Disconnecting" << endl;
    }
};


void ReadmeSampleCode()
{
    // Make a video phone
    auto phone = make_shared<VideoPhone>();

    // Create and configure the console
    // name, version
    Console console("test", "1.0.0",
        {    
            // List of supported commands. help & quit are built in

            // Command name, letter, description, and options and flags
            Command("call", "c", "create new call",
                {
                    // Required positional arg - parsing will fail if this isn't supplied
                    PositionalArg("address", "Remote address"),
                    // Optional option which is set to the default value if not specified
                    Option("bitrate", "b", "Call bitrate", "1024"),
                    // Optional option which is set to the default value if not specified
                    Option("source", "s", "Video source", "test-media/1.mp4"),
                },
                // Handler function for when this command is called
                [phone](Args args) 
                    { phone->Call(
                        args.Get("address"),
                        args.Get("bitrate"),
                        args.Get("source")); }
            ),
            
            Command("change-source", "s", "change video source",
                // name, letter, description
                {
                    PositionalArg("source", "New video source")
                },
                    [phone](Args args) { phone->ChangeVideoSource(args.Get("source")); }
                ),

            Command("disconnect", "d", "disconnect a call",
                // name, letter, description
                {
                    Arg("call", "c", "Call identifier"),
                },
                [phone](Args args) { phone->Disconnect(); }
            ),
        });

    // Runs the console, returns when the quit command is given
    console.Run();

}



void TestConstruction()
{
    //ReadmeSampleCode();
    AssertThrows(Console console("", "", {}), invalid_argument);
    AssertThrows(Console console("test", "", {}), invalid_argument);
    AssertThrows(Console console("test", "1.0", {}), invalid_argument);
}


int main(int argc, char* argv[])
{
    TestConstruction();

    EndTest
}

