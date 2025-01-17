// Fill out your copyright notice in the Description page of Project Settings.

#include "CompilerProject.h"
#include "CompilerFunctionLibrary.h"
#include "Regex.h"
#include <string>
#include "regex"



UCompilerFunctionLibrary::UCompilerFunctionLibrary(const class FObjectInitializer& OI)
:Super(OI)
{

}

/*Gets what command is being initiated.*/
ECommandsEnum UCompilerFunctionLibrary::ParseCommand(FString Command){
	//FString to std::string
	std::string CommandString(TCHAR_TO_UTF8(*Command));

	std::smatch match;
	//check if moveup()
	if (std::regex_search(CommandString, match, std::regex("^moveup(\\(\\))$")) && match.size() > 1){
		return ECommandsEnum::CE_MoveUp;
	}
	//check if movedown()
	else if (std::regex_search(CommandString, match, std::regex("^movedown(\\(\\))$")) && match.size() > 1){
		return ECommandsEnum::CE_MoveDown;
	}
	//check if moveleft()
	else if (std::regex_search(CommandString, match, std::regex("^moveleft(\\(\\))$")) && match.size() > 1){
		return ECommandsEnum::CE_MoveLeft;
	}
	//check if moveright()
	else if (std::regex_search(CommandString, match, std::regex("^moveright(\\(\\))$")) && match.size() > 1){
		return ECommandsEnum::CE_MoveRight;
	}
	//check if fire(col,row)
	else if (std::regex_search(CommandString, match, std::regex("^fire(\\(\\s*\\d+\\s*\\,\\s*\\d+\\s*\\))$")) && match.size() > 1){
		return ECommandsEnum::CE_Fire;
	}
	//invalid command input
	else{
		return ECommandsEnum::CE_InvalidCommand;
	}
}

/*Gets the firing coordinates specified in the Fire command*/
FCoordinates UCompilerFunctionLibrary::GetFiringCoordinates(FString Command){
	FCoordinates coords;
	std::string CommandString(TCHAR_TO_UTF8(*Command));
	std::_Bool flag = true;

	std::regex re("(\\d+)");

	for (std::sregex_iterator i = std::sregex_iterator(CommandString.begin(), CommandString.end(), re);
		i != std::sregex_iterator();
		++i)
	{
		std::smatch match = *i;
		if (flag){
			coords.x = std::stoi(match.str());
			flag = false;
		}
		else{
			coords.y = std::stoi(match.str());
		}
	}


	return coords;
}


