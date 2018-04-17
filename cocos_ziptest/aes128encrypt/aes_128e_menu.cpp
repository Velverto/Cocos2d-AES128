#include"aes_128e_menu.h"
/**Make by TRUONG QUANG HIEU
*	@version 1.01 - August 2017
*/
void aes_128e_menu() {
	//Values
	char *fname = new char[200];						// file name
	string encrypt_key = "quangtaocaiboong";			// 128bits encrypt key
	string encrypted_data;								// Encrypted data buffer
	FILE * inputFile[5], *outputFile;					// Input pointer for each thread and output pointer


	/**---------------------------------I/O FILE-------------------------------*/
	do {
		puts("\n PLease enter the file name or the path to that file. Type 'exit' to quit");
		fgets(fname, 200, stdin);
		clean(fname);
		if (strcmp(fname, "exit") == 0) return;
			else {
			puts("Reading file...");
			fopen_s(&inputFile[0], fname, "rb");
			if (!inputFile[0]) puts("fail to open file, please type another name\n");
		}
	} while (!inputFile[0]);
	//Register pointer for each thread to avoid conflict
	fopen_s(&inputFile[1], fname, "rb");
	fopen_s(&inputFile[2], fname, "rb");
	fopen_s(&inputFile[3], fname, "rb");
	fopen_s(&inputFile[4], fname, "rb");
	fopen_s(&outputFile, "pack.data", "wb");


	//Encryption key
	if(encrypt_key.size() > 16) encrypt_key.resize(16);
	else {
		while (encrypt_key.length() < 16) {
			encrypt_key += 'i';
		}
	}

	/**---------------------------------DIVIDED INTO THREADS-------------------------------
	*	Fetch the size.
	*	Each thread will encrypt/decrypt a portion of the file.
	*	For example, we have 5 thread encrypting the file. Each
	*	thread will encrypt buffer_size/5 bytes independently.
	*/
	fseek(inputFile[0], 0, SEEK_END);
	size_t input_size = ftell(inputFile[0]);		//Size of the buffer
	size_t leftover = input_size % 5;				
	string leftover_bytes;							//The left over bytes at the end of file.
	rewind(inputFile[0]);

	/**Prepare threads, the number of threads is important for the decryption*/
	thread AES_threads[5];

	future<string> split_encrypted_data[5];
	promise<string> AES_encrypt_promise[5];
	for (size_t a = 0; a < 5; a++) {
		split_encrypted_data[a] = AES_encrypt_promise[a].get_future();
		AES_threads[a] = thread(AES_split, move(AES_encrypt_promise[a]), inputFile[a], encrypt_key, input_size / 5, a);
	}
	AES_threads[0].join();
	AES_threads[1].join();
	AES_threads[2].join();
	AES_threads[3].join();
	AES_threads[4].join();

	//write to outputfile
	for (size_t a = 0; a < 5; a++) {
		string aux = split_encrypted_data[a].get();
		fwrite(&aux[0], 1, aux.size(), outputFile);
		aux.clear();
		//split_encrypted_data[a].get().clear();
	}
	//Write leftover bytes
	if (leftover > 0) {
		leftover_bytes.resize(leftover);
		fseek(inputFile[0], input_size - leftover, SEEK_SET);
		fread(&leftover_bytes[0], 1, leftover, inputFile[0]);
		fwrite(&leftover_bytes[0], 1, leftover, outputFile);
	}

	cout << "encryption done...." << endl;

	//Free memory
	for (size_t a = 0; a < 5; a++) {
		fclose(inputFile[a]);
	}
	fclose(outputFile);
	delete[] fname;
}



static void purger(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

static void clean(char *chaine) {
	char *p = strchr(chaine, '\n');
	if (p) *p = 0;
	else purger();
}


void AES_split(promise<string>& prom, FILE *inputFile, string encrypt_key, size_t thread_input_size, size_t thread_number){
	prom.set_value(aes_128(inputFile, encrypt_key, thread_input_size, thread_number));
}
