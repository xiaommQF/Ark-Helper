#include<bits/stdc++.h>
#include<Windows.h>
//#include<opencv2/core/core.hpp>
//#include<opencv2/highgui/highgui.hpp>
using namespace std;
//using namespace cv;

typedef pair<int,int> POS;

const POS 
	_StartLU={31,626},_StartRD={40,653},
	_LoginLU={190,580},_LoginRD={234,699},
	_HubLU={130,295},_HubRD={159,324}, 
	
	_Startpos={635,513},
	_CloseSign={1218,65},
	_JoinLevel={822,179}; 
	
const string 
	_StartPic="START.png",
	_LoginPic="LOGIN.png",
	_HubPic="Hub.png",
	_SameCol="#CCCCCCCC";
	
const int
	_LeftRotate=-90,
	_DelayTime=2000;


string itos(int _x){bool f=0;if(_x<0)_x=-_x,f=1;string _res="";do{_res=_res+(char)(_x%10+'0');_x/=10;}while(_x);_res+=f?"-":"";reverse(_res.begin(),_res.end());return _res;}

//API
namespace adb{
	void Run(string _CMD){string R="adb "+_CMD;system(R.c_str());}
	void Openapp(string _PKG){string _Rcom="shell am start "+_PKG;Run(_Rcom);}
	void Tap(POS _pos){string _Rcom="shell input tap "+itos(_pos.first)+" "+itos(_pos.second);Run(_Rcom);}
	void Getscreen(){Run("shell screencap -p /sdcard/screen.png");Run("pull /sdcard/screen.png temp/");}
}	

namespace magick{
	void Run(string _CMD){string R="magick "+_CMD;system(R.c_str());}
	void Rotatepic(int _FOV,string _SRC="screen.png",string _TAR="TMPIC.png"){
		string _Rcom="convert temp/"+_SRC+" -rotate "+itos(_FOV)+" temp/"+_TAR;
		Run(_Rcom);
	}
	void Cutpic(POS _pos,POS _pos2,string _SRC="screen.png",string _TAR="TMPIC.png"){	
		int len1=_pos2.first-_pos.first+1,len2=_pos2.second-_pos.second+1;
		string _Rcom="convert temp/"+_SRC+" -crop "+itos(len1)+"x"+itos(len2)+"+"+itos(_pos.first)+"+"+itos(_pos.second)+" temp/"+_TAR;
		Run(_Rcom);
	}
	void Getarea(POS _pos,POS _pos2,string _SRC="screen.png",string _TAR="_TMPIC.png"){Cutpic(_pos,_pos2,_SRC,"~temp.png");Rotatepic(_LeftRotate,"~temp.png",_TAR);}
	void Compare(string _P1,string _P2,string Tmpname="diff.png"){string _Rcom="compare -compose src temp/"+_P1+" temp/"+_P2+" temp/"+Tmpname;Run(_Rcom);}
	void P2rgb(string _SRC,string _TAR="RGB.txt"){string _Rcom="convert temp/"+_SRC+" -depth 8 temp/"+_TAR;Run(_Rcom);}
}

bool TheSamePic(POS _pos,POS _pos2,string PicName){
	adb::Getscreen();
	magick::Getarea(_pos,_pos2,"screen.png","Cpr.png");
	magick::Compare("Cpr.png",PicName);
	magick::P2rgb("diff.png");
	fstream fin("temp/RGB.txt");
	string _S;getline(fin,_S);
	while(fin>>_S){
		if(_S[0]=='#'&&_S!=_SameCol)return false;
	}
	return true;
}
void StartGame(){
	adb::Openapp("com.hypergryph.arknights/com.u8.sdk.U8UnityContext");
	while(!TheSamePic(_StartLU,_StartRD,_StartPic))Sleep(_DelayTime);
	adb::Tap(_Startpos);
} 
void JoinGame(){
	while(!TheSamePic(_LoginLU,_LoginRD,_LoginPic))Sleep(_DelayTime);
	adb::Tap(_Startpos);
}
bool InHub(){return TheSamePic(_HubLU,_HubRD,_HubPic);}


signed main(){
	StartGame();
//	GetScreen();
	JoinGame();
//	JoinTheHub();
//	Touchpos(_JoinLevel);
//	Cutscreen({190,580},{190+45-1,580+120-1},"DEBUG.png");
//	Run("shell am force-stop com.hypergryph.arknights");
	return 0;
} 
