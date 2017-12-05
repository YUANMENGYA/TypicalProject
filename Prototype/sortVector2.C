#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>



bool compare(const std::pair<std::string, double>  &word_1, const std::pair<std::string, double> &word_2)
	{
		return word_1.second < word_2.second;
	}


std::vector<std::pair<std::string, double>> sortVector (std::map<std::string, double> vocabulary)
	{
		std::vector<std::pair<std::string, double> > graphVector;
		copy(vocabulary.begin(), vocabulary.end(), back_inserter(graphVector));
		sort(graphVector.begin(), graphVector.end(), compare);
		return graphVector;
	}

