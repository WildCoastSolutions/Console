# C++ Console Handling

This is a simple, header only, no dependency, cross platform console library.

More on this library and others like it can be found at [http://wildcoast.nz/open-source](http://wildcoast.nz/open-source).

[Download the latest version directly (right click, download)](https://raw.githubusercontent.com/WildCoastSolutions/Console/master/Console.h).

Travis CI build & test status: [![Build Status](https://api.travis-ci.org/WildCoastSolutions/Console.svg?branch=master)](https://travis-ci.org/WildCoastSolutions/Console)




# Sample Code

```C++
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
            // List of supported commands. help & quit are built in.

            // Command name, letter, description, and options/flags/positional args
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
```

The above code with the sample command line results in the following being printed to console

# Installing

## Download

All you need to use this library is to put `Console.h` in your project and include it in your code.

[Download the latest version here (right click, download)](https://raw.githubusercontent.com/WildCoastSolutions/Console/master/Console.h).

## Namespace

All code is in the `Wild::Console` namespace.
