#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<set>
#include<iterator>


using namespace std;
static int fileLength;

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

class word
{
  //Attributes
    string fWord;
    int fOccurrences;
  
  public:
  //Getters
    string getWord() {return fWord;}
    int getOccurrences() {return fOccurrences;}
    //Setters
    void setWord(string newName) {fWord = newName;}
    void setOccurrences(int newOccurrences) {fOccurrences = newOccurrences;}
    void increaseOccurrences() {fOccurrences++;}
    //Constructors
    word(string newWord, int inOccurrences):fWord(newWord),fOccurrences(inOccurrences){};
    word():fWord("\0"), fOccurrences(0){};
    //Destructor
    ~word()
  {
    fWord = "\0";
    fOccurrences = 0;
  }
};

int main (int argc, char* argv[])
{
  cout<<argv[1]<<endl;

  ifstream fileInput(argv[1]);
  fstream data;
  stringstream memoryStream;
  
  char* wordBuffer;
  char* reservoir;

  int streamPosition = 0;

  set<word> vocabulary;

  //Tentiamo di aprire data, se non esiste lo creiamo, aprendo uno stream in output e chiudendolo contestualmente.
  data.open("FrequencyDatabase.txt", ios::in);
  if (data.fail())
  {
    data.clear();
    data.close();
    data.open("FrequencyDatabase.txt", ios::out);
  }

  //Apriamo lo stream in lettura/scrittura
  data.open("FrequencyDatabase.txt", ios::in|ios::out);
  


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
