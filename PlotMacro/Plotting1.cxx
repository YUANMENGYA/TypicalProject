#include <iostream>
#include <vector>
#include "TRandom.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TAxis.h"

using namespace std;

void fill_vector(vector < pair<string, double> > &v);




void fill_vector(vector < pair<string, double> > &v) {

	double x;
	string name;

	for (int i = 1; i < 1000; ++i)
	{
		name = "banana";
		x = exp(-double(i)/1000);
		v.push_back(pair<string, double>(name, x));

	}
	
}


void plot()

{
	vector <pair <string, double> > v;
        fill_vector(v);

        int n=v.size();
        double y[n], x[n];
  
      //Controllo elementi vector
	for (int i = 0; i < v.size(); ++i)
	{
	   cout << "[posto " << i << " del primo] =" << v[i].first << endl;
	   cout << "[posto " << i << " del secondo] =" << v[i].second << endl;

	}

      //Preparazione elementi Graph
       for (int i=0;i<v.size();i++)
       {
          x[i] = i;
          y[i] = v[i].second;
        }

  
       //Graph & cosmetics
        TGraph* gr = new TGraph(n,x,y);
	TCanvas *c1 = new TCanvas("c1", "Rank-Frequency Distribution", 200, 10, 600, 400);

	c1->cd();
    gr->SetLineColor(kRed);
    gr->SetTitle("Rank-Frequency Distribution");
    gr->GetYaxis()->SetTitle("Frequency");
    gr->GetXaxis()->SetTitle("Rank");
	gr->Draw("AC");
}

