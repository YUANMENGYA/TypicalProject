#include "Headers/english_stem.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <map>
#include <cmath>
#include <ctype.h> 

static int fileLength;
static int currentTextWordCount;
static int textsCount = 0;
static int TEXTGROUPS = 2;//Il numero di tipologie testuali è inizializzato di default a 2.

void stringToWString(std::wstring &ws, const std::string &s)
{
	std::wstring wsTmp(s.begin(), s.end());
	ws = wsTmp;
}

void wstringToString(std::string &s, const std::wstring &ws)
{
	std::string sTmp(ws.begin(), ws.end());
	s = sTmp;
}

void attemptInsertion(std::string searchedWord, std::map<std::string, int> &article)//Tentativo di inserzione di una parola nel lessico.
{
	currentTextWordCount++;
	std::map<std::string, int>::iterator index;//Apriamo un iteratore su mappe.
	article.insert(std::pair<std::string, int>(searchedWord, 0));//Inseriamo (non c'è sovrascrittura).
	index = article.find(searchedWord);
	index->second++;//Incrementiamo il numero di occorrenze di uno
}

void stringToLower (std::string &mixedCaseString)
{
	for (int i = 0; i< mixedCaseString.length(); ++i) mixedCaseString.replace(i ,1 ,1 , tolower(mixedCaseString[i]));
}

std::vector<std::string> split(const std::string &txt, const std::string &del)
{
 std::vector<std::string> token;
 std::size_t pos = txt.find_first_of(del), start = 0, end = txt.size();
 while(pos != std::string::npos)
 {
  if(pos) token.push_back(txt.substr(start, pos));
  start += pos + 1;
  pos = txt.substr(start, end).find_first_of(del);
 }
 if(start != end) token.push_back(txt.substr(start, pos));
 return token;
}

double inlineMean (double oldMean, double newDatum)
	{
		double offset_to_newMean = (newDatum-oldMean)/double(textsCount);
		double newMean =+ offset_to_newMean;
		return newMean;
	}

double inlineVariance(double oldVariance, double oldMean, double newDatum)
	{	
		if(textsCount <= 1) return 0;
		double offset1 = newDatum - oldMean;
		double newMean = inlineMean(oldMean, newDatum);
		double offset2 = newDatum - newMean;
		double newVariance = (((textsCount-1)*oldVariance+offset1*offset2))/textsCount;
		return newVariance;
	}



std::string updateVocabulary(std::map<std::string, double*> &vocabulary, std::map<std::string, int> &newData, int textType)
	{	
		std::map<std::string, double*>::iterator index;

		for (std::map<std::string,int>::iterator it=newData.begin(); it!= newData.end(); it++)
		{

		index = vocabulary.find(it->first);

		if (index == vocabulary.end())
			{
				vocabulary.insert(std::pair<std::string, double*>(it->first, new double[2*TEXTGROUPS]));
				
				for (int i = 0; i< 2*TEXTGROUPS; i++)
				vocabulary.find(it->first)->second[i]=0;
			}
		index = vocabulary.find(it->first);
		index->second[1+2*textType] = inlineVariance (index->second[1+2*textType], index->second[2*textType], double(it->second)/double(currentTextWordCount));

		index->second[2*textType] = inlineMean (index->second[2*textType], double(it->second)/double(currentTextWordCount));
		}
		return "E' terminato l'aggiornamento.\n\n";
	}

char* deletePunctuation (char* text)//IN MEMORIAM
	{
		char* result = new char[fileLength];
		for (int i=0; i<fileLength; i++)
		 {
		  text[i] = tolower(text[i]);
		  if(!(((text[i]>64)&&(text[i]<91))||((text[i]>96)&&(text[i]<123)))) result[i]= char(32);
		  else result[i] = text[i];
		 }
		return result;
	}

double computeExponent(std::map<std::string, double*> vocab, std::map<std::string, int> datum, int referenceTextType)
	{	
		double result=0;

		for(std::map<std::string, int>::iterator i = datum.begin(); i != datum.end(); ++i)
		{
			std::map<std::string, double*>::iterator itr = vocab.find(i->first);
			if(itr == vocab.end()) result += pow((double(i->second)/double(currentTextWordCount)), 2);
			if(itr != vocab.end()) result += pow((double(i->second)/double(currentTextWordCount))-(itr->second[2*referenceTextType])/itr->second[1+2*referenceTextType], 2);
		}

		return result;
	}

int main(int argc, char * argv[])
	{
	char* buffer;
	int streamPosition;
	std::string parameterisedFileName;
	//Strings
	std::string text;//Il testo viene caricato qui.
	std::string s_word;
	std::string singleWord;
	std::string delimiters=" \n\f\e\r\t\a\v\b,;.:-_'?!*+(){}[]/©—";
	std::wstring word;
	//Inizializziamo l'oggetto english stemmer.
	stemming::english_stem<> StemEnglish;
	//Inizializziamo il vettore contenente le parole
	std::vector<std::string> tokenisedText;
	//Inizializziamo il lessico.
	std::map<std::string, int> currentTextFrequencies;
	std::map<std::string, double*> vocabulary;

for (int fileIndex = 0; fileIndex<2; ++fileIndex)
{	
	currentTextFrequencies.clear();//Puliamo il vocabolario locale.
	parameterisedFileName.clear();
	parameterisedFileName.append(argv[1]);
	parameterisedFileName.append("/");
	parameterisedFileName.append(std::to_string(fileIndex));
	parameterisedFileName.append(".txt");
	//std::cout<<parameterisedFileName<<std::endl;
	std::ifstream inputf(parameterisedFileName.data());
	
	//Misuriamo la lunghezza del file.
	inputf.seekg(0, std::ios::end);
	fileLength = inputf.tellg();
	inputf.seekg(0, std::ios::beg);
	//Prepariamo un puntatore a char per contenere il testo.
	buffer = new char[fileLength+1];
	//Leggiamo tutto il file.
	inputf.read(buffer, fileLength);
	buffer[fileLength] = '\0';//Inseriamo il NULL terminatore.
	text.assign(buffer);//Carichiamo su stringa il testo letto.
	inputf.close();//Chiudiamo lo stream
	//Ora mettiamo l'intera stringa in caratteri minuscoli.
	stringToLower(text);
	//E spezzettiamo il testo.
	tokenisedText = split(text, delimiters);
	currentTextWordCount=0;//Azzeriamo il contatore delle parole lette.

	for(int j = 0; j<tokenisedText.size(); j++)
	{	
		textsCount++;
		stringToWString(word, tokenisedText[j]);
		StemEnglish(word);
		wstringToString(singleWord, word);
		attemptInsertion(singleWord, currentTextFrequencies);
		//std::cout<<singleWord<<" was successfully processed and loaded!"<<std::endl;
	}

	updateVocabulary(vocabulary, currentTextFrequencies, 0);

	std::cout<<"\n";
	std::cout<<"WORD ROOTS COUNT FOR FILE: "<<parameterisedFileName<<"\n\n";
	std::cout<<"WORD ROOT\tCOUNTS\t\tFREQUENCY\n";
	std::cout<<"---------------------------------------------\n";
	
	for (std::map<std::string,int>::iterator it=currentTextFrequencies.begin(); it!=currentTextFrequencies.end(); ++it)
	std::cout << std::setw(10)<< it->first << std::setw(10) <<it->second<<std::setw(20)<<double(it->second)/double(currentTextWordCount)<<"\n";
}
	
	std::cout<<"\n\n\n";
	std::cout<<"PRINTING VOCABULARY FOR FOLDER: "<<argv[1]<<"\n\n";
	std::cout<<std::setw(20)<<"WORD ROOT"<<std::setw(20)<<"TYPE 1"<<std::setw(20)<<" "<<std::setw(20)<<"TYPE 2\n";
	std::cout<<std::setw(20)<<" "<<std::setw(20)<<"AVERAGE"<<std::setw(20)<<"STD. DEV."<<std::setw(20)<<"AVERAGE"<<std::setw(20)<<"STD. DEV.\n";
	std::cout<<"------------------------------------------------------------------------------------------------------\n";

	for (std::map<std::string,double*>::iterator it=vocabulary.begin(); it!=vocabulary.end(); ++it)
	{std::cout << std::setw(20)<< it->first<<' ';
	for (int l = 0; l< 2*TEXTGROUPS; ++l)
	std::cout<< std::setw(20)<< it->second[l];
	std::cout<< '\n';
	}

	std::cout<<pow(2.71828,-computeExponent(vocabulary, currentTextFrequencies, 0))<<std::endl;
	return 0;
}