#include<string>
#define TEXTGROUPS 2
#ifndef WORD_H
#define WORD_H

using namespace std;

class word
{
	//Attributes
  	string fWord;
  	double ftypeMeans[TEXTGROUPS];
  	double ftypeSigmas[TEXTGROUPS];
  	int fOccurrences;
  	static int wordsEverRead;
  	static int wordsReadFromCurrentFile;//Conta le parole lette nel testo in esame.

	public:
    //General methods
    void eraseCurrentWordCount();
    //Getters
  	string getWord();//Estrae la parola
  	double* getMeans();//Estrae le medie per tipo di testo
  	double* getSigmas();//Estrae le varianze per tipo di testo
  	//Setters
  	void setWord(string newName);//Imposta la parola
  	void setMeans(double* newMeans); //Imposta le medie per tipo di testo
  	void setSigmas(double* newSigmas); //Imposta le varianze per tipo di testo
  	void increaseOccurrences(int texType);//Aumenta di uno le occorrenze nel testo in esame.
  	//Constructors (to be updated)
  	word(string newWord);
  	word();
  	//Destructor
  	~word();
};
#endif