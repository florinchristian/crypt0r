#include <iostream>
#include <fstream>

using namespace std;

enum Operation{
    Encrypt,
    Decrypt
};

void applyPasswordToFile(char* path, char* newPath, const char* password, Operation type) {
    ifstream input;
    ofstream output;

    size_t pwdLen = strlen(password);
    size_t bytesRead;

    char* buffer = new char[pwdLen];

    input.open(path, ios::binary);
    output.open(newPath, ios::binary);

    while (true) {
        bytesRead = input.read(buffer, (int)pwdLen).gcount();

        if (bytesRead == 0)
            break;

        for (int i=0;i<bytesRead;++i) {
            int newValue;

            if (type == Encrypt)
                newValue = buffer[i] + password[i];
            else
                newValue = buffer[i] - password[i];

            buffer[i] = (char)newValue;
        }

        output.write(buffer, (int)pwdLen);
    }

    input.close();
    output.close();

    delete[] buffer;
}

int main(int argc, char* args[]) {
    if (argc == 1 || argc > 5) {
        cout << "Usage:\n";
        cout << "./crypt0r type(encrypt/decrypt) file_path new_file_path password(max 32 characters)";
    } else {
        if (!strcmp(args[1], "encrypt"))
            applyPasswordToFile(args[2], args[3], args[4], Encrypt);
        else
            applyPasswordToFile(args[2], args[3], args[4], Decrypt);

        cout << "Applied password <<" << args[4] << ">> to the specified file.";
    }
}
