#include<bits/stdc++.h>
#include<Windows.h>
//#include<opencv2/core/core.hpp>
//#include<opencv2/highgui/highgui.hpp>
using namespace std;

typedef pair<int,int> POS;

const POS 
	_FirstST={45,640},
	_Startpos={635,513};
	
const string 
	_Start_RGB="#FFD802";
	
bool Run(string _CMD){string R="adb "+_CMD;return system(R.c_str());}
string itos(int _x){
	string _res="";
	do{
		_res=_res+(char)(_x%10+'0');
		_x/=10;
	}while(_x);
	reverse(_res.begin(),_res.end());
	return _res;
}
void Touchpos(POS _pos){string _Rcom="shell input tap "+itos(_pos.first)+" "+itos(_pos.second);Run(_Rcom);}
void GetScreen(){Run("shell screencap -p /sdcard/screen.png");Run("pull /sdcard/screen.png temp/");}
void Cutscreen(POS _pos,POS _pos2,string _FILENAME="_TMPIC.png"){
	GetScreen();
	int len1=_pos2.first-_pos.first+1,len2=_pos2.second-_pos.second+1;
	string _Rcom="magick convert temp/screen.png -crop "+itos(len1)+"x"+itos(len2)+"+"+itos(_pos.first)+"+"+itos(_pos.second)+" temp/_TMPIC.png";
	system(_Rcom.c_str());
}
string GetRGBINFO(POS _pos,string _FILE="_TMPIC.png"){
	Cutscreen(_pos,_pos);
	system("magick convert temp/_TMPIC.png -depth 8 temp/RGB.txt");
	fstream fin("temp/RGB.txt");
	string T;getline(fin,T);fin>>T>>T>>T;
	return T;
}
bool WaitTrueRGB(POS _pos,string RGB){
	string tmp=GetRGBINFO(_pos);
	while(tmp!=RGB){
		tmp=GetRGBINFO(_pos);
		Sleep(100);
	}
	Sleep(1000);
	return true;
}
/*
magick convert -crop 50x180+180+550 -rotate -90 screen.png _TMPIC.png
*/
void StartGame(){
	Run("shell am start com.hypergryph.arknights/com.u8.sdk.U8UnityContext");
	WaitTrueRGB(_FirstST,_Start_RGB);
	Touchpos(_Startpos);
} 
void JoinGame(){
	
}
signed main(){
	GetScreen();
	return 0;
}
