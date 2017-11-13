#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<bitset>

using namespace std;

unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void removePunctuation(char *& text);//DA IMPLEMENTARE!!!!!

int main (int argc, char* argv[])
{
  cout<<argv[1]<<endl;

  ifstream fileInput(argv[1]);
  ofstream fileOutput(argv[2]);
  stringstream memoryStream;
  char* reservoir;
  string word;
  char* wordBuffer;
  int fileLength;

  //Stabiliamo quanto è lungo il file, e salviamo tale lunghezza in fileLength.
  fileInput.seekg(0, ios::end);
  fileLength = fileInput.tellg();
  fileInput.seekg(0, ios::beg);
  //Ora inizializziamo il puntatore a char per contenere il file per intero.
  reservoir = new char[fileLength+1];
  //Leggiamo il file per intero
  fileInput.read(reservoir, fileLength);
  reservoir[fileLength] ='\0';
  //Chiudiamo lo stream di lettura da file.
  fileInput.close();
  //Inizializziamo lo stream con il buffer.
  memoryStream.str(reservoir);
  memoryStream.seekg(0, ios::beg);
  int streamPosition = 0;

  /*
  Ora codifichiamo le parole una alla volta, scrivendole man mano in un file,
  quando sono finite (accensione di failbit per mancata estrazione), chiudiamo gli stream
  e terminiamo il programma.
  */
  while(1)
  {
    memoryStream>>word;
    if(memoryStream.fail()) break;
    fileOutput<<bitset<64>(hash(word.data()))<<endl;
  }

//CHIUDIAMO TUTTO!!
fileInput.close();
fileOutput.close();
}
