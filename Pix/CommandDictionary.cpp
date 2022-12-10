#include "CommandDictionary.h"

#include "CmdDrawPixel.h"
#include "CmdSetColor.h"
#include "CmdBeginDraw.h"
#include "CmdAddVertex.h"
#include "CmdEndDraw.h"
#include "CmdSetResolution.h"
#include "CmdSetViewport.h"
#include "CmdShowViewport.h"
#include "CmdSetClipping.h"
#include "CmdVarBool.h"
#include "CmdVarFloat.h"
#include "CmdSetFillMode.h"
#include "CmdPushRotationX.h"
#include "CmdPushRotationY.h"
#include "CmdPushRotationZ.h"
#include "CmdPushScaling.h"
#include "CmdPushTranslation.h"
#include "CmdPopMatrix.h"
#include "CmdSetCameraDirection.h"
#include "CmdSetCameraPosition.h"
#include "CmdSetCameraNear.h"
#include "CmdSetCameraFar.h"
#include "CmdSetCameraFov.h"
#include "CmdSetCullMode.h"
#include "CmdEnableDepth.h"
#include "CmdLights.h"
#include "CmdModel.h"
#include "CmdSetShadeMode.h"
#include "CmdSetCorrectUV.h"
#include "CmdSetAddressMode.h"
#include "CmdSetTexture.h"

CommandDictionary* CommandDictionary::Get()
{
	static CommandDictionary sInstance;
	return &sInstance;
}

CommandDictionary::CommandDictionary()
{
	// Initialize dictionary

	// Setting commands
	RegisterCommand<CmdSetResolution>();
	RegisterCommand<CmdSetViewport>();
	RegisterCommand<CmdShowViewport>();
	RegisterCommand<CmdSetClipping>();

	// Variable commands
	RegisterCommand<CmdVarBool>();
	RegisterCommand<CmdVarFloat>();
	RegisterCommand<CmdPushRotationX>();
	RegisterCommand<CmdPushRotationY>();
	RegisterCommand<CmdPushRotationZ>();
	RegisterCommand<CmdPushScaling>();
	RegisterCommand<CmdPushTranslation>();
	RegisterCommand<CmdPopMatrix>();

	// Camera commands
	RegisterCommand<CmdSetCameraDirection>();
	RegisterCommand<CmdSetCameraPosition>();
	RegisterCommand<CmdSetCameraNear>();
	RegisterCommand<CmdSetCameraFar>();
	RegisterCommand<CmdSetCameraFov>();

	// Light commands
	RegisterCommand<CmdSetLightAmbient>();
	RegisterCommand<CmdSetLightDiffuse>();
	RegisterCommand<CmdSetLightSpecular>();
	RegisterCommand<CmdAddDirectionalLight>();
	RegisterCommand<CmdAddPointLight>();

	// Rasterization commands
	RegisterCommand<CmdDrawPixel>();
	RegisterCommand<CmdSetColor>();
	RegisterCommand<CmdBeginDraw>();
	RegisterCommand<CmdAddVertex>();
	RegisterCommand<CmdEndDraw>();
	RegisterCommand<CmdSetFillMode>();
	RegisterCommand<CmdSetCullMode>();
	RegisterCommand<CmdSetShadeMode>();
	RegisterCommand<CmdEnableDepth>();
	RegisterCommand<CmdModel>();
	RegisterCommand<CmdSetCorrectUV>();
	RegisterCommand<CmdSetAddressMode>();
	RegisterCommand<CmdSetTexture>();
}

TextEditor::LanguageDefinition CommandDictionary::GenerateLanguageDefinition()
{
	TextEditor::LanguageDefinition langDef;

	langDef.mName = "Pix";

	langDef.mKeywords.insert("var");

	for (auto&[keyword, command] : mCommandMap)
	{
		TextEditor::Identifier id;
		id.mDeclaration = command->GetDescription();
		langDef.mIdentifiers.insert(std::make_pair(keyword, id));
	}

	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\\$[a-zA-Z_]+", TextEditor::PaletteIndex::Keyword));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("L?\\\"(\\\\.|[^\\\"])*\\\"", TextEditor::PaletteIndex::String));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("\\'\\\\?[^\\']\\'", TextEditor::PaletteIndex::CharLiteral));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)([eE][+-]?[0-9]+)?[fF]?", TextEditor::PaletteIndex::Number));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[a-zA-Z_][a-zA-Z0-9_]*", TextEditor::PaletteIndex::Identifier));
	langDef.mTokenRegexStrings.push_back(std::make_pair<std::string, TextEditor::PaletteIndex>("[\\[\\]\\{\\}\\!\\%\\^\\&\\*\\(\\)\\-\\+\\=\\~\\|\\<\\>\\?\\/\\;\\,\\.]", TextEditor::PaletteIndex::Punctuation));

	langDef.mCommentStart = "/*";
	langDef.mCommentEnd = "*/";
	langDef.mSingleLineComment = "//";

	langDef.mAutoIndentation = true;
	langDef.mCaseSensitive = true;

	return langDef;
}

Command* CommandDictionary::CommandLookup(const std::string& keyword)
{
	auto iter = mCommandMap.find(keyword);
	if (iter == mCommandMap.end())
		return nullptr;
	return iter->second.get();
}

template <class T>
void CommandDictionary::RegisterCommand()
{
	static_assert(std::is_base_of_v<Command, T>, "Invalid command type.");
	auto newCommand = std::make_unique<T>();
	mCommandMap.emplace(newCommand->GetName(), std::move(newCommand));
}