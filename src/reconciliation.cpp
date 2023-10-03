
#include <string>
#include <bitset>
#include <iostream>
#include <vector>
#include <cmath>

#include "costanti.h"
#include "reconciliation.h"

using namespace std;

Reconciliation::Reconciliation(vector<double> aliceData, vector<double> bobData, double paramB){
	normalizeAlice(aliceData);
	normalizeBob(bobData, paramB);
}

/*bitset<K> Reconciliation::genBitString(default_random_engine gen){
    string bitString;

    for(int i = 0; i < K; i++){
        if(distribution(gen))
            bitString.append("1");
        else 
            bitString.append("0");
    }

    bitset<K> b{bitString};

    cout << "Stringa di bit Random :" << b.to_string() << endl;

    return b;
}*/

/*
*
*	I prodotti sono l'operazione binaria AND mentre le somme l'operazione XOR
*
*/

//Esegue l'AND bit a bit della bitset passato come paramentro 
string Reconciliation::andBaB(bitset<K> o){
	
	bitset<1> a ;
	if(o[2]){
		a.flip();
	}
	else{
		a.reset();
	} 
			
	for(int i = o.size()-2; i >= 0; i--){
		if(o[i])
			a ^= true;
		else 
			a ^= false;
	}

	return a.to_string();
}


//Esegue il prodotto tra un vettore di bit ed una matrice
string Reconciliation::prdMatrix(bitset<K> s, vector<bitset<K> > pMatrix){
	string outString;

	if(s.size() != pMatrix[0].size()){
		cout << "Impossibile effettuare il prodotto matriciale" << endl;
		cout << "Il numero di colonne della string di bit deve essere pari al numero di righe della matrice" << endl;
		cout << "Numero di colonne della stringa di bit: " << s.size() << endl;
		cout << "Numero di righe della matrice P: " << pMatrix[0].size() << endl;
	}
	
		for(int j = 0; j < (int)pMatrix.size(); j++){
			bitset<K> o = s;
			o &= pMatrix[j];
			//cout << j << " xor interno " << o.to_string() << endl;
			outString.append(andBaB(o)); 
		}
	return outString;
}

//Esegue una modulazione di segno dei valori misurati da Bob
vector<double> Reconciliation::signModulation(bitset<N> codeWord){
	vector<double> modulated;
	int count = 0;

	for (int i = codeWord.size()-1; i >= 0; i--){
		if(codeWord[i]){
			//cout << "Sono nell'if all'indice: " << i << endl;
			modulated.push_back(-(this->normalizedBobData[count]));
		}
		else
			modulated.push_back(this->normalizedBobData[count]);

		count++;
	}

	return modulated;
}

void Reconciliation::computeLlr(){

	for(int i = 0; i < dummyMessage.size(); i++)
		this->llr.push_back((2.0 * this->dummyMessage[i])/((1/VARIANZA)/abs(this->normalizedAliceData[i])));
}


void Reconciliation::dMessage(vector<double> modulated){

	for(int i = 0; i < (int)modulated.size(); i++){
		this->dummyMessage.push_back(modulated[i] / this->normalizedAliceData[i]);
	}

	computeLlr();

}

void Reconciliation::normalizeAlice(vector<double> aliceData){

	for(int i = 0; i < (int)aliceData.size(); i++){
		this->normalizedAliceData.push_back(aliceData[i]/sqrt(VARIANZA));
	}
	
}

void Reconciliation::normalizeBob(vector<double> bobData, double paramB){

	for(int i = 0; i < (int)bobData.size(); i++){
		this->normalizedBobData.push_back(bobData[i]/sqrt(paramB));
	}
	
}

vector<double> Reconciliation::getNormalizedAliceData(){
	return this->normalizedAliceData;
}

vector<double> Reconciliation::getLlr(){
	return this->llr;
}