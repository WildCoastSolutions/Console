# C++ Console Handling

This is a simple, header only, no dependency, cross platform console library.

More on this library and others like it can be found at [http://wildcoast.nz/open-source](http://wildcoast.nz/open-source).

[Download the latest version directly (right click, download)](https://raw.githubusercontent.com/WildCoastSolutions/Console/master/Console.h).

Travis CI build & test status: [![Build Status](https://api.travis-ci.org/WildCoastSolutions/Console.svg?branch=master)](https://travis-ci.org/WildCoastSolutions/Console)




# Sample Code

```C++
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
```

The above code with the sample command line results in the following being printed to console

# Installing

## Download

All you need to use this library is to put `Console.h` in your project and include it in your code.

[Download the latest version here (right click, download)](https://raw.githubusercontent.com/WildCoastSolutions/Console/master/Console.h).

## Namespace

All code is in the `Wild::Console` namespace.
