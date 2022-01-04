#include <regex>
#include <fstream>
#include <iostream>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

using namespace std;

int main(void)
{
	IStream* stream;
	HRESULT result = URLOpenBlockingStreamW(
		nullptr,
		L"https://asx.api.markitdigital.com/asx-research/1.0/companies/directory/file?access_token=83ff96335c2d45a094df02a206a39ff4",
		&stream,
		0,
		nullptr
	);

	if (result != S_OK)
	{
		cout << "无法下载数据~~~" << endl;
		return -1;
	}

	char buff[1024];
	string s;
	unsigned long bytesRead;

	do {
		stream->Read(buff, 1024, &bytesRead);
		s.append(buff, bytesRead);
	} while (bytesRead > 0);

	stream->Release();

	cout << s << endl;
	regex r("\\n\".*?(?=\")");
	ofstream myFile("ASX.csv");

	for (sregex_iterator i(s.begin(), s.end(), r), end_i; i != end_i; ++i) {
		myFile << i->str().substr(2) + ".AX\n";
	}

	myFile.close();

	return 0;
}