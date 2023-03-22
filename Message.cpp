#include "Message.hpp"
#include "Command.hpp"

Command     g_cmd;

Message::Message(void){}

Message::~Message(void){}

Message::Message(std::vector<std::string> &tokens):_cmd(tokens[0]), _params(tokens.begin()+1, tokens.end()){
    //_params.insert(_params.begin(), tokens.begin()+1, tokens.end());
    // Display tokens
    // for (size_t i = 0; i < tokens.size(); i++)
    //     std::cout << "token " << i << ": " << tokens[i] << std::endl;

    // if cmd token is recognized: this->executeCommand()
// Merge Message and Command
}



std::string 				Message::getCMD(void){return(_cmd);}
std::vector<std::string>	Message::getParams(void){return(_params);}

void						Message::execCMD(Client &client){
    if(g_cmd._command.find(_cmd) != g_cmd._command.end())
    {
        std::cout << "[Client] (" << client.getSocket() << ") Command " << _cmd << " is being processed." << std::endl;
        g_cmd._command[_cmd](_params, client);
    }
    else
        std::cout << "[Client] (" << client.getSocket() << ") Command " << _cmd << " not found." << std::endl;
}
