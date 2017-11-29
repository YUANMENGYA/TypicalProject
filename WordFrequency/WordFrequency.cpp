#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<iterator>


using namespace std;
static int fileLength;
static int TEXTGROUPS=2;

char* deletePunctuation (char* text)

  {
    char* result = new char [fileLength];
    for (int i = 0; i < fileLength; i++)
    {
      if (!(((text[i]>64)&&(text[i]<91))||((text[i]>96)&&(text[i]<123)))) result[i] = char(32);
      else result[i] = text[i];
    }
    return result;
  }


int main (int argc, char* argv[])
{
  cout<<argv[1]<<endl;

  ifstream fileInput(argv[1]);
  fstream data;
  stringstream memoryStream;
  
  char* wordBuffer;
  char* reservoir;

  int streamPosition = 0;

  //Tentiamo di aprire data, se non esiste lo creiamo, aprendo uno stream in output e chiudendolo contestualmente.
  data.open("FrequencyDatabase.csv", ios::in);
  if (data.fail())
  {
    data.clear();
    data.close();
    data.open("FrequencyDatabase.csv", ios::out);
  }

  //Apriamo lo stream in lettura/scrittura
  data.open("FrequencyDatabase.csv", ios::in|ios::out);
  //Leggiamo la prima riga, che contiene il numero di gruppi di testi e il numero di parole lette.
  

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


//CHIUDIAMO TUTTO!!
fileInput.close();
data.close();
}
