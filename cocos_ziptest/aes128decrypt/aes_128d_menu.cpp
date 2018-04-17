#include "aes_128d_menu.h"

/**Make by TRUONG QUANG HIEU 
 *	@version 1.01 - August 2017
 */
string aes_128d_menu() {
	FILE *inputFile[5];										//Input pointer for each thread
	FILE *testoutputFile;									//OutputFile pointer
	string encrypt_key = "quangtaocaiboong";				//Encrypt key
	string decrypted_data;									//Decrypted data buffer

	fopen_s(&inputFile[0], "pack.data", "rb");
		if (!inputFile[0]) {
		cout << "fail to open file pack.data" << endl;
		Sleep(3000);
		exit(-1);
	}
	//Register pointer for each thread to avoid conflict
	fopen_s(&inputFile[1], "pack.data", "rb");
	fopen_s(&inputFile[2], "pack.data", "rb");
	fopen_s(&inputFile[3], "pack.data", "rb");
	fopen_s(&inputFile[4], "pack.data", "rb");
	fopen_s(&testoutputFile, "original.zip", "wb");


	/**---------------------------------DIVIDED INTO THREADS-------------------------------
	*   Fetch the size.
	*	Each thread will encrypt/decrypt a portion of the file.
	*	For example, we have 5 thread encrypting the file. Each
	*	thread will encrypt buffer_size/5 bytes independently.
	*/
	fseek(inputFile[0], 0, SEEK_END);
	size_t input_size = ftell(inputFile[0]);	//Size of the buffer
	size_t leftover = input_size % 5;			
	string leftover_bytes;						//The left over bytes at the end of file.
	rewind(inputFile[0]);

	/**Prepare threads, the number of threads must be matched with encryption process*/
	thread AES_decrypt_threads[5];

	future<string> split_decrypted_data[5];
	promise<string> AES_decrypt_promise[5];
	for (size_t a = 0; a < 5; a++) {
		split_decrypted_data[a] = AES_decrypt_promise[a].get_future();
		AES_decrypt_threads[a] = thread(AES_decrypt_split, move(AES_decrypt_promise[a]), inputFile[a], encrypt_key, input_size / 5, a);
	}
	AES_decrypt_threads[0].join();
	AES_decrypt_threads[1].join();
	AES_decrypt_threads[2].join();
	AES_decrypt_threads[3].join();
	AES_decrypt_threads[4].join();


	//write to outputfile
	for (size_t a = 0; a < 5; a++) {
		string aux = split_decrypted_data[a].get();
		fwrite(&aux[0], 1, aux.size(), testoutputFile);
		decrypted_data.append(aux);
		aux.clear();
		//split_decrypted_data[a].get().clear();
	}

	//Write leftover bytes
	if (leftover > 0) {
		leftover_bytes.resize(leftover);
		fseek(inputFile[0], input_size - leftover, SEEK_SET);
		fread(&leftover_bytes[0], 1, leftover, inputFile[0]);
		fwrite(&leftover_bytes[0], 1, leftover, testoutputFile);
		decrypted_data.append(leftover_bytes);
	}

	cout << "decryption done...." << endl;

	//Free memory
	for (size_t a = 0; a < 5; a++) {
		fclose(inputFile[a]);
	}
	fclose(testoutputFile);
	return decrypted_data;
}

void AES_decrypt_split(promise<string>& prom, FILE* inputFile, string encrypt_key, size_t thread_input_size, size_t thread_number){
	prom.set_value(aest_128_decrypt(inputFile, encrypt_key, thread_input_size, thread_number));
}