#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <string.h>
#include <iostream>
#include <sstream>

#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TBranch.h"
#include "TKey.h"
#include "Riostream.h"
#include "TSystem.h"
#include "TObject.h"
#include "TArrayF.h"
#include "TMath.h"
#include "TVector3.h"

using namespace std;

struct analogdata
{
    char type[4];
    unsigned int num_words;
    unsigned int data[8192];
};


void ReadAnalogData ( string filename, string newfilename )
{
    int fd = open ( filename.c_str(),O_RDONLY );

    if ( fd == -1 )
    {
        cout<<"Could not open file."<<endl;
        return;
    }

    cout<<"Opened file."<<endl;

    analogdata data;

    int readsuccess = 1;

    char type[4];
    int entries;
    int diri = 0;
    int headi = 0;
    int paci = 0;
    int scali = 0;
    int deadi = 0;
    int datai = 0;
    int otheri = 0;
    map<string,int> otherstuff;

    unsigned short mask = 0xffff;
    int value;
    int channel;
    unsigned int unusedbit = 0x8000;

    vector<unsigned short>* values = new vector<unsigned short>;
    vector<unsigned short>* channels = new vector<unsigned short>;

    while ( readsuccess != 0 )
    {
        readsuccess = read ( fd, ( void* ) &data,sizeof ( data ) );


        if ( string(data.type) ==   "DIR " )
        {
	  entries = data.data[1];
	  
            diri++;
        }
        else if ( string(data.type) == "HEAD" )
        {
            headi++;
        }
        else if ( string(data.type) == "PAC " )
        {
            paci++;

        }
        else if ( string(data.type) == "SCAD" )
        {
	   scali++;
        }
        else if ( string(data.type) == "DEAD" )
        {
            deadi++;
        }
        else if ( string(data.type) == "DATA" )
        {
            datai++;
	    float percent = 100 * datai/entries;
	    cout<<"Percent done: "<<percent<<"\r"<<flush;
	    


            for ( int word = 0; word < 8192; word++ )
	    {
	      unsigned int forshift = data.data[word];
	      channel = (short)forshift;
	      channel &= ~unusedbit;
	      forshift = data.data[word];
	      forshift = forshift>>16;
              value = (short)forshift;


                values->push_back ( value );
                channels->push_back ( channel );

            }


        }
        else 
	{
	  otheri++;
	}
    }

    cout<<diri<<" directory(ies)."<<endl;
    cout<<headi<<" header(s)."<<endl;
    cout<<datai<<" data sets."<<endl;
    cout<<paci<<" PAC(s)."<<endl;
    cout<<scali<<" Scaler(s)."<<endl;
    cout<<deadi<<" Deadtime(s)."<<endl;
    cout<<otheri<<" Other."<<endl;

    TFile* f = new TFile ( newfilename.c_str(),"recreate" );
    TTree* tree= new TTree ( "analog_data","data" );
    tree->Branch ( "val",&values );
    tree->Branch ( "channel",&channels );

    tree->Fill();
    tree->Write();

    f->Close();



        return;
}
