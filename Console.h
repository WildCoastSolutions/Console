//
// Author       Wild Coast Solutions
//              David Hamilton
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.
//
// This file contains an implementation of a simple console command libary. 
//
// Project url: https://github.com/WildCoastSolutions/Console

#ifndef WILD_CONSOLE_CONSOLE_H
#define WILD_CONSOLE_CONSOLE_H

#include <string>
#include <initializer_list>
#include <memory>
#include <list>
#include <set>
#include <map>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <functional>
#include "../CommandLine/CommandLine.h"

namespace Wild
{
    namespace Console
    {
        typedef std::function<void(CommandLine::Args args)> CommandHandler;
        void Split(std::list<std::string> &tokens, const std::string &s, const std::string &separator);

        // Represents a single command
        // e.g. call -a <address> -b <bitrate> -d
        class Command
        {
        private:
            CommandLine::Args args;
            CommandHandler handler;

        public:
            std::string name;
            std::string letter;
            std::string description;

            Command(
                const std::string &name, 
                const std::string &letter,
                const std::string &description,
                CommandHandler commandHandler = nullptr)
                : name(name), letter(letter), description(description), args({}), handler(commandHandler)
            {

            }

            Command(
                const std::string &name,
                const std::string &letter,
                const std::string &description,
                const std::initializer_list<CommandLine::Arg> &args,
                CommandHandler commandHandler = nullptr)
                : name(name), letter(letter), description(description), args(args), handler(commandHandler)
            {

            }

            bool Handle(const std::string &command, std::list<std::string> &arguments)
            {
                bool result = args.Parse(arguments);
                if (result == true && handler != nullptr)
                    handler(args);
                return result;
            }
        };

        class Console
        {
        private:
            typedef std::function<void(std::string command, CommandLine::Args args)> CommandHandler;
            std::string consoleName;
            std::map<std::string, std::unique_ptr<Command>> commandMap;
            std::map<std::string, std::string> letterLookup;
            std::list<Command> commands;
            std::string currentCommand;
            CommandHandler commandHandler;

        public:

            Console(
                const std::string &consoleName,
                const std::list<Command> &commands,
                CommandHandler commandHandler = nullptr)
                : consoleName(consoleName), commands(commands), commandHandler(commandHandler)
            {
                commandMap["help"] = std::make_unique<Command>(
                    "help",
                    "h",
                    "display help",
                    [this](CommandLine::Args args) { Help(args); });
                letterLookup["h"] = "help";

                commandMap["quit"] = std::make_unique<Command>(
                    "quit",
                    "q",
                    "quit console");
                letterLookup["q"] = "quit";

                for (auto command : commands)
                {
                    if (commandMap.count(command.name) > 0)
                        throw std::runtime_error("Cannot have two arguments with the same name");
                    
                    commandMap[command.name] = std::make_unique<Command>(command);

                    if (letterLookup.count(command.letter) > 0)
                        throw std::runtime_error("Cannot have two arguments with the same name");
                    
                    letterLookup[command.letter] = command.name;
                }
            }

            void Help(CommandLine::Args args)
            {
                std::cout << consoleName << " commands" << std::endl << std::endl;
                std::cout << "\"help <command>\" for more info" << std::endl << std::endl;
                for (auto command : commands)
                {
                    std::cout << std::left << std::setw(20) << command.name << command.description << std::endl;
                }
                std::cout << std::endl;
            }

            std::string CurrentCommand()
            {
                return currentCommand;
            }

            bool Handle(const std::string &command)
            {
                std::list<std::string> argumentList;
                Split(argumentList, command, " ");

                // Just hitting enter is ok, do nothing
                if (argumentList.size() == 0) return true;

                std::string commandString = argumentList.front();
                argumentList.pop_front();

                if (letterLookup.find(commandString) != letterLookup.end())
                    currentCommand = letterLookup[commandString];
                else
                    currentCommand = commandString;

                if (commandMap.find(currentCommand) == commandMap.end())
                {
                    std::cerr << "Could not find command: " << commandString << std::endl;
                    return false;
                }

                return commandMap[currentCommand]->Handle(currentCommand, argumentList);

            }

            void Run()
            {
                std::string commandString;

                while (CurrentCommand() != "quit")
                {
                    std::cout << consoleName << ">";
                    std::getline(std::cin, commandString);
                    try {
                        Handle(commandString);
                    }
                    catch (std::runtime_error &e)
                    {
                        std::cerr << "Could not process command: " << e.what() << std::endl;
                    }
                }
            }

        };

        // Splits a string based on a separator string (not the characters inside the separator string)
        // separators at the start or end of the string are ignored
        void Split(std::list<std::string> &tokens, const std::string &s, const std::string &separator)
        {
            if (s.size() == 0) throw std::runtime_error("no string passed in");
            if (separator.size() == 0) throw std::runtime_error("no separator passed in");
            tokens.clear();

            size_t prev = 0;
            size_t pos = s.find(separator);
            while (pos != std::string::npos)
            {
                if (pos != 0) // if we found a separator at the beginning, ignore it
                    tokens.push_back(s.substr(prev, pos - prev));
                prev = pos + separator.size();
                pos = s.find(separator, prev);
            }
            std::string last = s.substr(prev);
            if (last.size())
                tokens.push_back(last);
        }

    }
}

#endif // #ifndef WILD_CONSOLE_CONSOLE_H
