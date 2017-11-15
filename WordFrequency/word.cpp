#include<iostream>
#include<string>
#include"word.h"
#define TEXTGROUPS 2

using namespace std;
	
	//General methods
	void word::eraseCurrentWordCount(){wordsReadFromCurrentFile=0;}//Azzera il conteggio delle parole lette
	//Getters
  	string word::getWord() {return fWord;}//Estrae la parola
  	double* word::getMeans() {return ftypeMeans;}//Estrae le medie per tipo di testo
  	double* word::getSigmas() {return ftypeSigmas;}//Estrae le varianze per tipo di testo
  	//Setters
  	void word::setWord(string newName) {fWord = newName;}//Imposta la parola
  	void word::setMeans(double* newMeans) //Imposta le medie per tipo di testo
  	{
  		for (int i = 0; i < TEXTGROUPS; i++)
  			ftypeMeans[i] = newMeans[i];
  	}
  	void word::setSigmas(double* newSigmas) //Imposta le varianze per tipo di testo
  	{
  		for (int i = 0; i < TEXTGROUPS; i++)
  			ftypeSigmas[i] = newSigmas[i];
  	}
  	void word::increaseOccurrences()//Aumenta di uno le occorrenze nel testo in esame.
  	{
  		fOccurrences++;
  		wordsReadFromCurrentFile++;
  		wordsEverRead++;
  	}
  	//Constructors (to be updated)
  	word::word(string newWord):fWord(newWord){};
  	word::word():fWord("\0"), fOccurrences(0){};
  	//Destructor
  	word::~word()
	{
		fWord = "\0";
		fOccurrences = 0;
	}