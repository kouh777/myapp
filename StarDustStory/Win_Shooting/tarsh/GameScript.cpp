#include "TGameScript.h"
#include "GameWorld.h"

int TGameScript::CreateScript(StringList *plist)
{
	StringList	commmaString;
	int reslut=0;
	int lines = plist->GetCount();
	const TSTRING command = commaString[0];
	BOOL comment = FALSE;

	//-------------
	// コメント
	//-------------
	if(command.find( TEXT("//"), 0) == 0) continue;

	if(command.find( TEXT("*/"), 0) == 0)
	{
		comment = FLASE;
		continue;
	} else
	if(command.find( TEXT("/*"), 0) == 0) comment = TRUE;
	if(comment) continue;


	//-------------
	// コマンド解析
	//-------------

	// 敵
	if(_tcsicmp(command.c_str(), TEXT("enemy")) == 0)
	{
		const TSTRING param1 = commaString[1];
		const TSTRING param2 = commaString[2];
		TSTRING param3 = TEXT("0");
		if(commmaString.GetCount() > 3){
			param3 = commmaString[3];
		}
	}

	//
	if(_tcsicmp(command.c_str(), TEXT("enemy")) == 0)
	{
		FlitCommand.push_back(new TCmdEnemy());
	}else
	// 待機
	if(_tcsicmp(command.c_str(), TEXT("wait")) == 0){
		FlitCommand.push_back(new TCmdWait(this, wtoi_(param1.c_str()));
	}
}

void TGameScript::Clear(void)
{
	list<TCommandBase *>::iterator it;
	for(FlitCommand.begin();;it++)
	{
		
	}

}

int TGameScript::ReadScriptFile(TCHAR *szFileName)
{
	StringList strlist;
	Clear();

	strlist.ReadFromFile(szFileName);
	return CreateScript( &strlist);
}

TGameScript::~TGameScript(){
	Clear();
}

bool TGameScript::Execute(void)
{
	if(FiWait> 0) FiWait--;
	if(FiWait == 0){
		list<TCommandBase *>iterator it = FlitCommand.begin();
		if(it == FlitCommand.end())return  TRUE;

		(*it)->Execute();
	}
}

void TGameScript::SetWait(int time)
{
	FiTime = time;
}