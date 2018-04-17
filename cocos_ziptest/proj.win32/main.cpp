#include "main.h"

using namespace std;
using namespace cocos2d;

int main() {
	string zip_buffer;
	string filename;
	ZipFile *ziptest = nullptr;
	unsigned char *data1;
	ssize_t data1_size;


	cout << "FileEncryption and Cocos2d-x zipUtils demo:" << endl;
	clock_t start;
	double duration;
	aes_128e_menu();
	start = clock();
	zip_buffer = aes_128d_menu();
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Decryption time: " << duration << " secs" << '\n';

	cout << "Ziputils demo will begin in 5 secs" << endl;
	Sleep(5000);
	FileUtils *pathtest = FileUtils::getInstance();
	cout << pathtest->fullPathForFilename("original.zip") << endl;
	FILE *p;
	fopen_s(&p, "original.zip", "r");
	ziptest = ZipFile::createWithBuffer(zip_buffer.c_str(), zip_buffer.size());
	if (ziptest) {
		cout << "Load archive into memory: Sucess" << endl;
		//cout << "Setting filter" << endl;
		ziptest->getFirstFilename();
		cout << "Reading file" << endl;
		filename.assign(ziptest->getNextFilename());
		cout << filename.c_str() << endl;
		while ((data1 = ziptest->getFileData(filename, &data1_size)) != nullptr) {
			cout << filename.c_str() << " : " << data1_size << " bytes" << endl;
			filename.assign(ziptest->getNextFilename());
			free(data1);
		}
		cout << "Done" << endl;
	}
	else cout << "cant load archive into memory, please check if the file is in ZIP format...." << endl;
	delete ziptest;

	cout << "demo end here" << endl;
	zip_buffer.clear();
	Sleep(60000);
	fclose(p);
	return 1;
}