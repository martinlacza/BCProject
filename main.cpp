#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <ctime>
#include <list>
#include <climits>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

class Vrchol{
public:
    int hodnota;
    int index;
    Vrchol *lavy;
	Vrchol *pravy;    
   
   Vrchol() {
        this->lavy = nullptr;
        this->pravy = nullptr;
    }
    
   
    Vrchol(int hod) {
        this->hodnota = hod;
        this->lavy = nullptr;
        this->pravy = nullptr;
    }
    
    int getHodnota() const{
    	return hodnota;
	}
	
	int getCount(Vrchol *tree) const{
	
	    int c =  1;             //Node itself should be counted
	    if (tree ==NULL)
	        return 0;
	    else
	    {
	        c += getCount(tree->lavy);
	        c += getCount(tree->pravy);
	        return c;
	    }
	}
};

struct Hrany{
	
	Hrany *predch;
	string str;
	
	Hrany(Hrany *predch, string str){
		this->predch = predch;
		this->str = str;
	}
};

Vrchol* newNode (int data)  
{  
    Vrchol* temp = new Vrchol(); 
  
    temp->hodnota = data;  
    temp->lavy = temp->pravy = NULL;  
  
    return temp;  
} 

void ukazHrany(Hrany *p){
	if (p == nullptr){
		return;
	}
	
	ukazHrany(p->predch);
	cout << p->str;
}

void printStrom(Vrchol *root, Hrany *prev, bool isLeft)
{
    if (root == nullptr)
        return;
    
    string prev_str = "    ";
    Hrany *hrana = new Hrany(prev, prev_str);

    printStrom(root->lavy, hrana, true);

    if (!prev)
        hrana->str = "---";
    else if (isLeft)
    {
        hrana->str = ".---";
        prev_str = "   |";
    }
    else
    {
        hrana->str = "`---";
        prev->str = prev_str;
    }

    ukazHrany(hrana);
    cout << root->hodnota << endl;

    if (prev)
        prev->str = prev_str;
    hrana->str = "   |";

    printStrom(root->pravy, hrana, false);
}

Vrchol* rotationLL (Vrchol* vrchol) {
	if (vrchol->pravy == NULL) {
        cout << "No right child!" << endl;
        return vrchol;
    }
    Vrchol* n = vrchol->pravy;
    vrchol->pravy = n->lavy;
    n->lavy = vrchol;
    return n;
}

Vrchol* rotationRR (Vrchol* vrchol) {
    if (vrchol->lavy == NULL) {
        cout << "No left child!" << endl;
        return vrchol;
    }
    
   Vrchol* n = vrchol->lavy;
    vrchol->lavy = n->pravy;
    n->pravy = vrchol;

        // update height
    /*x = updateHeight(x);
    root = updateHeight(root);*/

    return n;
}

Vrchol* rotationLR (Vrchol* Vrchol) {
    cout << "Rotation LR:" << endl;
    Vrchol->lavy = rotationLL(Vrchol->lavy);
    Vrchol = rotationRR(Vrchol);
    return Vrchol;
}

Vrchol* rotationRL (Vrchol* Vrchol) {
    cout << "Rotation RL:" << endl;
    Vrchol->pravy = rotationRR(Vrchol->pravy);
    Vrchol = rotationLL(Vrchol);
    return Vrchol;
}

//funkcia na vytvorenie vectora s random hodnotami
vector<int> myVector()
  {
  	vector<int> v;
  	srand((unsigned)time(NULL));
	int a = rand() % 20 + 1; //1 to 20    
	for (int i =0; i < a; i++){
        int b = rand() % 20 + 1;
        v.push_back(b);
        
    }
    
     
     return v;  
  }

//insert funkcia na naplnenie stromu
void insert(Vrchol** treeOrig, int val) {
    if (!(*treeOrig))
        *treeOrig = new Vrchol(val);
    Vrchol* tree = *treeOrig;
    if (val < tree->hodnota) {
        if (tree->lavy) {
            insert(&tree->lavy, val);
        } else {
            tree->lavy = new Vrchol(val);
        }
    }
    if (tree->hodnota < val) {
        if (tree->pravy) {
            insert(&tree->pravy, val);
        } else {
            tree->pravy = new Vrchol(val);
        }
    }
}

//funkcia ktora hlada vrchol s danou hodnotou
Vrchol* najdiVrchol(Vrchol* root, int hod) 
{ 
    // Traverse untill root reaches to dead end 
    while (root != NULL) { 
        // pass right subtree as new tree 
        if (hod > root->hodnota) 
            root = root->pravy; 
  
        // pass left subtree as new tree 
        else if (hod < root->hodnota) 
            root = root->lavy; 
        else
            return root; // if the key is found return 1 
    } 
    return nullptr; 
} 

void fillSubtrees(vector<vector<int> >& subtrees, vector<int>& sub){
	subtrees.push_back(sub);
}

//funkcia naplni vector sub s hodnotami vrcholov v preorder poradi
void preorder(vector<int>& sub, Vrchol* vrchol){
	if(vrchol==nullptr) return;
	sub.push_back(vrchol->hodnota);
	preorder(sub,vrchol->lavy);
	preorder(sub,vrchol->pravy);
}

void preorderVector(vector<Vrchol>& sub, Vrchol* vrchol){
	if(vrchol==nullptr) return;
	sub.push_back(*vrchol);
	preorderVector(sub, vrchol->lavy);
	preorderVector(sub, vrchol->pravy);
	return;
}

//https://www.techiedelight.com/print-vector-cpp/
void printVector(std::vector<Vrchol>  &input)
{
	unsigned int size = input.size();
	for (unsigned int i = 0; i< size; i++)
	{
		std::cout << input[i].getHodnota() << ' ';
	}
}

//funkcia vymaze z vectoru input vsektky listy, teda hodnoty ktore su vo vektore osamotene
void deleteLeaves(std::vector<vector<int> > &input)
{
	int singletons[100];
	int j = 0;
	for (int i = 0; i <= input.size(); i++)
	{
		if(input[i].size() == 1){
			singletons[j]=i;
			j++;	
		}
			
	}
	int y = 0;
	for(int x = 0; x < j; x++){
		input.erase(input.begin() + (singletons[x] - y));
		y++;
		
	}
	input.erase(input.begin());
	cout << "Vsetky podstromy Stromu su:" << endl;
}

void printSubtrees(std::vector<int> const &input)
{
	unsigned int size = input.size();
	for (unsigned int i = 0; i< size; i++)
	{
		std::cout << input[i] << ' ';
	}
}

//funckia na porovnanie dvoch vectorov A a B, 100% totozne vectory dame do outputFullDuplicate, len totozne dame do outputDuplicate
void compareSubtrees(std::vector<vector<int> > &inputA ,std::vector<vector<int> > &inputB , std::vector<vector<int> > &outputFullDuplicate, std::vector<vector<int> > &outputDuplicate){
	unsigned int sizeA = inputA.size();
	unsigned int sizeB = inputB.size();
	cout << inputA.size() << endl;
	cout << inputB.size() << endl;
	vector<int> sortedSubtreesA;
	vector<int> sortedSubtreesB;
	for(int i=0; i< sizeA; i++){
		for(int j = 0; j< sizeB; j++){
			if(inputA[i] == inputB[j]){
				outputFullDuplicate.push_back(inputA[i]);
				printSubtrees(inputA[i]);
				printSubtrees(inputB[j]);
				cout << "100 % Totozny podstrom:" << endl;
			}
			else{
			sortedSubtreesA = inputA[i];
			sort(sortedSubtreesA.begin(), sortedSubtreesA.end());
			sortedSubtreesB = inputB[j];
			sort(sortedSubtreesB.begin(), sortedSubtreesB.end());
			if(sortedSubtreesA == sortedSubtreesB){
				outputDuplicate.push_back(inputA[i]);
				outputDuplicate.push_back(inputB[j]);
				printSubtrees(inputA[i]);
				printSubtrees(inputB[j]);
				cout << "Totozny podstrom:" << endl;
				}
		 	}
		}
	}
}

//funkcia potrebna pri deletovani podstromov
void addPadding(std::vector<vector<int> > &BiggerSize, std::vector<vector<int> > &SmallerSize){
	int hranica = BiggerSize.size() - SmallerSize.size();
	//cout << BiggerSize.size() <<  SmallerSize.size() << endl;
	for(int i = 0; i < hranica; i++){
		vector<int> zero = {0};
		SmallerSize.push_back(zero);
	
	}
	
}

//funkcia potrebna pri deletovani podstromov
void eraseEmptySpaces(std::vector<vector<int> > &FullDuplicate){
	int j = 0;
	for(int i=0; i< FullDuplicate.size() + j; i++){
	
		if(FullDuplicate[i].empty()){
			FullDuplicate.erase(FullDuplicate.begin() + i);
			j++;
		}
	
	}
	
}


void printVectorHodnota(std::vector<vector<int> > &input)
{
	for (int i = 0; i < input.size(); i++)
	{
		for(int j = 0; j <input[i].size();j++){
			cout << input[i][j] << ' ';
			}
	 	cout << endl;
	}
}

//funkcia vymaze duplikaty, najprv porovnava vector duplicate a hlada vnom rovnake hodnoty, potom porovnava FullDuplicate, a na koniec porovnava obe vectory
void deleteDuplicateSubtrees(std::vector<vector<int> > &FullDuplicate, std::vector<vector<int> > &Duplicate){
	std::vector<int>::iterator it;
	int fullDuplSize = FullDuplicate.size();
	int DuplSize = Duplicate.size();
		for(int i=0; i< (fullDuplSize - 1); i++){
			for(int k=i+1; k< (fullDuplSize - 1); k++){
				for(int j=0; j < FullDuplicate[i].size(); j++){
					if(std::find(FullDuplicate[k].begin(), FullDuplicate[k].end(), FullDuplicate[i][j])!= FullDuplicate[k].end()){
						if(FullDuplicate[i].size() > FullDuplicate[k].size()){
								FullDuplicate[k].erase(FullDuplicate[k].begin(), FullDuplicate[k].end());
						}
						else if(FullDuplicate[i].size() < FullDuplicate[k].size()){
								FullDuplicate[i].erase(FullDuplicate[i].begin(), FullDuplicate[i].end());
						}
						else if(FullDuplicate[i].size() == FullDuplicate[k].size()){
								cout << "Rovnaka velkost podstromov, Podstromy sa zachovaju" << endl;					
						}
					}
					
				}
			}
		}	
	
	
	
	for(int i=0; i< (DuplSize - 1); i++){
		for(int k=i+1; k< (DuplSize - 1); k++){
			for(int j=0; j < Duplicate[i].size(); j++){
				if(std::find(Duplicate[k].begin(), Duplicate[k].end(), Duplicate[i][j])!= Duplicate[k].end()){
					if(Duplicate[i].size() > Duplicate[k].size()){
							cout <<  "Found Duplicate When comparing" <<  endl;
							printSubtrees(Duplicate[i]);
							cout <<  "Erasing:" <<  endl;
							printSubtrees(Duplicate[k]);
							Duplicate[k].erase(Duplicate[k].begin(), Duplicate[k].end());
					}
					else if(Duplicate[i].size() < Duplicate[k].size()){
							cout <<  "Found Duplicate When comparing " << endl;
							 printSubtrees(Duplicate[k]);
							 cout <<  "Erasing:" <<  endl;
							 printSubtrees(Duplicate[i]);
							Duplicate[i].erase(Duplicate[i].begin(), Duplicate[i].end());
					}
					else if(Duplicate[i].size() == Duplicate[k].size()){
							cout << "Rovnaka velkost podstromov, Podstromy sa zachovaju" << endl;					
					}
				}
			}
		}
	}	
	
	
	eraseEmptySpaces(Duplicate);
	eraseEmptySpaces(FullDuplicate);

	if(FullDuplicate.size() > Duplicate.size()){
		addPadding(FullDuplicate,Duplicate);
	}
	if(FullDuplicate.size() < Duplicate.size()){
		addPadding(Duplicate,FullDuplicate);
	}
	
	
	fullDuplSize = FullDuplicate.size();
	DuplSize = Duplicate.size();
	for(int i=0; i < fullDuplSize  ; i++){
		for(int k=i+1; k < (fullDuplSize - 1); k++){
			for(int j=0; j < FullDuplicate[i].size(); j++){
				
				if(j < DuplSize){
					if(std::find(Duplicate[j].begin(), Duplicate[j].end(), FullDuplicate[i][j])!= Duplicate[j].end()){
							if(FullDuplicate[i].size() > Duplicate[j].size()){
									
									Duplicate[j].erase(Duplicate[j].begin(), Duplicate[j].end());
							}
							else if(FullDuplicate[i].size() < Duplicate[j].size()){
								
									FullDuplicate[i].erase(FullDuplicate[i].begin(), FullDuplicate[i].end());
							}
							else if(FullDuplicate[i].size() == Duplicate[j].size()){
									cout << "Rovnaka velkost podstromov, Podstromy sa zachovaju" << endl;					
							}
						}
					}
				}
			}
		}
}


void eraseZeroes(std::vector<vector<int> > &input){
	for (int i = 0; i < input.size(); i++)
	{
		for(int j = 0; j <input[i].size();j++){
			if(input[i][j] == 0){
					input[i].erase(input[i].begin() + j);
				}
			
			}
	}
}

//funkcia na mazanie podstromov z hlavneho stromu
void removeSubtrees(std::vector<vector<int> > &FullDuplicate, Vrchol* vrchol, int i){
	if(vrchol==nullptr) return;
	cout << vrchol->hodnota << endl;;
	if(vrchol->lavy != nullptr){
		if(vrchol->lavy->hodnota == FullDuplicate[i][0]) {
			vrchol->lavy = nullptr;
			return;
		}
	}
	if(vrchol->pravy != nullptr){
		
		if(vrchol->pravy->hodnota == FullDuplicate[i][0]) {
			vrchol->pravy = nullptr;
			return;
		}
	}
	if(vrchol->lavy != nullptr){
			removeSubtrees(FullDuplicate, vrchol->lavy, i);
		}
	if(vrchol->pravy != nullptr){
			removeSubtrees(FullDuplicate, vrchol->pravy, i);
	}
	
}

//funkcia na mazanie podstromov z hlavneho stromu
void deleteSubtrees(std::vector<vector<int> > &FullDuplicate, Vrchol* vrchol){
	for (int i = 0; i < FullDuplicate.size(); i++)
	{
		removeSubtrees(FullDuplicate, vrchol, i);
	}
}


//funkcia na konstrukciu stromu podla preorder poradia
Vrchol* constructTreeUtil( std::vector<int>  &pre, int* preIndex, int key,  
                                int min, int max, int size )  
{  
    // Base case  
    if( *preIndex >= size )  
        return NULL;  
  
    Vrchol* root = NULL;  
  
    // If current element of pre[] is in range, then  
    // only it is part of current subtree  
    if( key > min && key < max )  
    {  
        // Allocate memory for root of this  
        // subtree and increment *preIndex  
        root = newNode(key);  
        *preIndex = *preIndex + 1;  
          
        if (*preIndex < size)  
        {  
            // Construct the subtree under root  
            // All nodes which are in range  
            // {min .. key} will go in left  
            // subtree, and first such node  
            // will be root of left subtree.  
            root->lavy = constructTreeUtil( pre, preIndex, pre[*preIndex],  
                                        min, key, size );  
  
            // All nodes which are in range  
            // {key..max} will go in right  
            // subtree, and first such node 
            // will be root of right subtree.  
            root->pravy = constructTreeUtil( pre, preIndex, pre[*preIndex],  
                                        key, max, size );  
        }  
    }  
  
    return root;  
}  

Vrchol *constructTree (std::vector<int>  &pre, int size)  
{  
    int preIndex = 0;  
    return constructTreeUtil ( pre, &preIndex, pre[0], INT_MIN,  
                            INT_MAX, size );  
}  

//funkcia na vytvorenie stromov z podstromov
vector<Vrchol* > createVectorOfDuplicateTrees(std::vector<vector<int> > &FullDuplicate){
	vector<Vrchol* > duplicateSubtrees;
	for(int i=0; i < FullDuplicate.size(); i++ ){
		Vrchol* root3 = constructTree(FullDuplicate[i], FullDuplicate[i].size());
		duplicateSubtrees.push_back(root3);
	}
	return duplicateSubtrees;
}

//splayovacia funkcia, prevzata a upravena z funckie v praci pana Stanka
//https://www.geeksforgeeks.org/splay-tree-set-1-insert/
Vrchol *splay(Vrchol *root, int key, int* i)
{
    // Base cases: root is NULL or
    // key is present at root
    if (root == NULL || root->hodnota == key)
        return root;
    
    // Key lies in left subtree
    if (root->hodnota > key)
    {
        // Key is not in tree, we are done
        if (root->lavy == NULL) return root;
        
        // Zig-Zig (Left Left)
        if (root->lavy->hodnota > key)
        {
            // First recursively bring the
            // key as root of left-left
            root->lavy->lavy = splay(root->lavy->lavy, key, i);
            
            // Do first rotation for root,
            // second rotation is done after else
            root = rotationRR(root);
            (*i)++;
        }
        else if (root->lavy->hodnota < key) // Zig-Zag (Left Right)
        {
            // First recursively bring
            // the key as root of left-right
            root->lavy->pravy = splay(root->lavy->pravy, key, i);
            
            // Do first rotation for root->left
            if (root->lavy->pravy != NULL) {
                root->lavy = rotationLL(root->lavy);
                (*i)++;
            }
        }
        
        // Do second rotation for root
        if (root->lavy != NULL)
            (*i)++;
        return (root->lavy == NULL)? root: rotationRR(root);
    }
    else // Key lies in right subtree
    {
        // Key is not in tree, we are done
        if (root->pravy == NULL) return root;
        
        // Zag-Zig (Right Left)
        if (root->pravy->hodnota > key)
        {
            // Bring the key as root of right-left
            root->pravy->lavy = splay(root->pravy->lavy, key, i);
            
            // Do first rotation for root->right
            if (root->pravy->lavy != NULL) {
                root->pravy = rotationRR(root->pravy);
                (*i)++;
            }
        }
        else if (root->pravy->hodnota < key)// Zag-Zag (Right Right)
        {
            // Bring the key as root of
            // right-right and do first rotation
            root->pravy->pravy = splay(root->pravy->pravy, key, i);
            root = rotationLL(root);
            (*i)++;
        }
        
        // Do second rotation for root
        if (root->pravy != NULL)
            (*i)++;
        return (root->pravy == NULL)? root: rotationLL(root);
    }  
}

//hladanie odhadu rot dist
void rotationDistanceRec1(Vrchol* root1, Vrchol** root2, int* i, int* i_splay) {
    if (root1 == NULL)
        return;
    *root2 = splay(*root2, root1->hodnota, i);
    (*i_splay)++;
    rotationDistanceRec1(root1->lavy, &((*root2)->lavy), i, i_splay);
    rotationDistanceRec1(root1->pravy, &((*root2)->pravy), i, i_splay);
}

//hladanie odhadu rot dist
int rotationDistance1(Vrchol* root1, Vrchol** root2) {
    int i = 0, i_splay = 0;
    rotationDistanceRec1(root1, root2, &i, &i_splay);
    return i;
}

int sumOfVysledok(std::vector<int>  &input){
	int x=0;
	for(int i=0; i < input.size(); i++ ){
		x=x+input[i];
	}
	return x;
}

void randomizeVector(std::vector<int>  &vect, int size){
	for(int i = 1; i <= size ; i++){
		vect.push_back(i);
	}
	std::random_shuffle ( vect.begin(), vect.end() );
}

int main(int argc, char * argv[]) {
	int found=0;
	int treeSize = 18;
	int iterations = 1000;
	if(argc == 2){
		treeSize = atoi(argv[1]);
		
	}
	if(argc == 3){
		treeSize = atoi(argv[1]);
		iterations = atoi(argv[2]) ;
	}
	vector<int> vysledky;
	srand(time(0));
	for(int opak = 0; opak < iterations ; opak++){
		cout << "New Trees" << endl;
		Vrchol* root= nullptr;
	    Vrchol* root2 = nullptr;
	    vector<int> vysledok;
		std::vector<int> v ;//= {10,1,3,2,5,4,7,6,8,9,13,11,12,15,14,17,16,18} ; 
		randomizeVector(v,treeSize);
		//Ak chcem random urobit strom:
		//myVector();
		for(std::vector<int>::iterator it = std::begin(v); it != std::end(v); ++it) { 
	   		insert(&root, *it);
		}
		printStrom(root, nullptr, false);
	//	Vrchol* search = najdiVrchol(root, 12);
		vector<vector<int> > subtreesA;
		vector<int> subA;
		vector<Vrchol > listOfVrcholsA;
		preorderVector(listOfVrcholsA, root);
		preorder(subA, root);
		
		unsigned int size = listOfVrcholsA.size();
		for (unsigned int i = 0; i< size; i++)
		{
			subA.clear();
			preorder(subA, &listOfVrcholsA[i]);
			fillSubtrees(subtreesA, subA);
			
		}
		deleteLeaves(subtreesA);
		printVectorHodnota(subtreesA);
		
		std::vector<int> w ;//= {10,1,7,2,4,3,6,5,8,9,15,11,14,12,13,18,16,17};
		randomizeVector(w,treeSize) ;
		for(std::vector<int>::iterator it = std::begin(w); it != std::end(w); ++it) { 
	   		insert(&root2, *it);
		}
		
		vector<vector<int> > subtreesB;
		vector<int> subB;
		vector<Vrchol > listOfVrcholsB;
		preorderVector(listOfVrcholsB, root2);
		preorder(subB, root2);
			
		
		printStrom(root2, nullptr, false);
		
	//	printVector(listOfVrchols);
		unsigned int sizeB = listOfVrcholsB.size();
		for (unsigned int i = 0; i< sizeB; i++)
		{
			subB.clear();
			preorder(subB, &listOfVrcholsB[i]);
			fillSubtrees(subtreesB, subB);
			
		}
		deleteLeaves(subtreesB);
		printVectorHodnota(subtreesB);
		vector<vector<int> > outputFullDuplicate;
		vector<vector<int> > outputDuplicate;
		compareSubtrees(subtreesA, subtreesB, outputFullDuplicate , outputDuplicate);
		if(!outputFullDuplicate.empty() && !outputDuplicate.empty()){
			found++;
			deleteDuplicateSubtrees(outputFullDuplicate, outputDuplicate);
		}
		if(!outputFullDuplicate.empty()){
			eraseEmptySpaces(outputFullDuplicate);
			eraseZeroes(outputFullDuplicate);
			eraseEmptySpaces(outputFullDuplicate);
			printVectorHodnota(outputFullDuplicate);
			deleteSubtrees(outputFullDuplicate, root);
		    deleteSubtrees(outputFullDuplicate, root2);
		}
		if(!outputDuplicate.empty()){
			eraseEmptySpaces(outputDuplicate);
			eraseZeroes(outputDuplicate);
			eraseEmptySpaces(outputDuplicate);
			printVectorHodnota(outputDuplicate);
		    deleteSubtrees(outputDuplicate, root);
		    deleteSubtrees(outputDuplicate, root2);
			vector<Vrchol* > duplicateSubtrees = createVectorOfDuplicateTrees(outputDuplicate);
			vector<int> duplA;
			vector<int> duplB;
			for(int x=0; x < duplicateSubtrees.size(); x+=2){
				int y;
				if(x + 1 >= duplicateSubtrees.size()){
					y = x;
				}
				else{
					y = x + 1;
				}
				duplA = outputDuplicate[x];
				duplB = outputDuplicate[y];
				sort(duplA.begin(),duplA.end());
				sort(duplB.begin(),duplB.end());
				printSubtrees(duplA);
				printSubtrees(duplB);
				if(duplA == duplB && !duplA.empty()){
					printVectorHodnota(outputDuplicate);
					vysledok.push_back(rotationDistance1(duplicateSubtrees[x], &duplicateSubtrees[y]));
					printStrom(duplicateSubtrees[x], nullptr, false);
					printStrom(duplicateSubtrees[y], nullptr, false);
				}
				else if(duplA != duplB){
					if(duplA < duplB){
						vysledok.push_back(duplA.size()-1);
					}
					else{
						vysledok.push_back(duplB.size()-1);
					}
				}
			}
		}	
		
		
		if(root != nullptr && root2 != nullptr && root->getCount(root)== root2->getCount(root2) ){
			vysledok.push_back(rotationDistance1(root, &root2));
		}
		if(root == nullptr || root2 == nullptr ){
			vysledok.push_back(1);
		}
		if(root != nullptr){
			printStrom(root, nullptr, false);
		}
		if(root2 != nullptr){
			printStrom(root2, nullptr, false);
		}
		int sum = sumOfVysledok(vysledok);
		vysledky.push_back(sum);
	}
	double priemer = sumOfVysledok(vysledky)/static_cast<double>(iterations);
	cout << "Pocet Rotacii v priemere: " << priemer << endl;
	cout << found << endl;
	system("pause");
	return 0;
	
}
