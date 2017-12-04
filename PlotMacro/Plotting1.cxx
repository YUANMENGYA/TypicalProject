#include <iostream>
#include <vector>
#include "TRandom.h"
#include "TCanvas.h"
#include "TH1D.h"

using namespace std;

void fill_vector(vector < pair<string, double> > &v);




void fill_vector(vector < pair<string, double> > &v) {

	double x;
	string name;

	for (int i = 1; i < 100000; ++i)
	{
		name = "banana";
		x = gRandom->Gaus();
		v.push_back(pair<string, double>(name, x));

	}
	
}


void plot()

{
	vector <pair <string, double> > v;
        fill_vector(v);

	TH1D *h1 = new TH1D("h1", "Plot", v.size(),-5 , 5);

	//Cosmetics
	h1->SetMarkerStyle(20);
	h1->SetMarkerSize(0.5);
	h1->SetLineColor(1);
	h1->GetYaxis()->SetTitleOffset(1.2);
	h1->GetXaxis()->SetTitleSize(0.04);
	h1->GetYaxis()->SetTitleSize(0.04);
	h1->GetXaxis()->SetTitle("Rank");
	h1->GetYaxis()->SetTitle("Entries");
	h1->SetFillColor(kRed);

	 // costruisco il mio vector di pair fittizio 

	for (int i = 0; i < v.size(); ++i)
	{
	   cout << "[posto " << i << " del primo] =" << v[i].first << endl;
	   cout << "[posto " << i << " del secondo] =" << v[i].second << endl;

	}

	//Filling
	for (int i = 0; i < v.size(); ++i)
	{
		h1->Fill(v[i].second);
	}

	TCanvas *c1 = new TCanvas("c1", "PlotCanvas", 200, 10, 600, 400);

	c1->cd();
	h1->DrawCopy();
	c1->Print("PlotMacro.gif");
	c1->Print("PlotMacro.C");

}

