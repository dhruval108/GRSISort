#ifndef TAnalysisTreeBuilder_H
#define TAnalysisTreeBuilder_H

#include "Globals.h"

#include <cstdio>
#include <vector>
#include <string>
#include <queue>

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TList.h>

#include <TFragment.h>
#include <TChannel.h>
#include <TGRSIRunInfo.h>

//#include <TTigress.h> 
#include <TSharc.h>     
//#include <TTriFoil.h>   
//#include <TRf.h>        
//#include <TCSM.h>       
//#include <TSpice.h>     
//#include <TS3.h>        
//#include <TTip.h>       
   
//#include <TGriffin.h>   
//#include <TSceptar.h>   
//#include <TPaces.h>     
//#include <TDante.h>     
//#include <TZeroDegree.h>
//#include <TDescant.h>   


class TEventQueue {
   public:
      static TEventQueue *Get();
      static void Add(std::vector<TFragment> *event); 
      static std::vector<TFragment> *Pop();
      static int Size();
      virtual ~TEventQueue();

   private:
      TEventQueue();
      static TEventQueue *fPtrToQue;
      static std::queue<std::vector<TFragment>*> fEventQueue;
      static bool lock;
      static void SetLock() {lock = true;}
      static void UnsetLock() {lock = false;}

};

class TAnalysisTreeBuilder {

   public:
      virtual ~TAnalysisTreeBuilder();

      void ProcessEvent(std::vector<TFragment>*) { };

      static void SetUpFragmentChain(TChain *chain);
      static void SetUpFragmentChain(std::vector<std::string>);
      static void SetupFragmentTree();

      static void SortFragmentChain();
      static void SortFragmentTree();

      static void InitChannels();

      static void SetupOutFile();
      static void SetupAnalysisTree();
      static void FillAnalysisTree() { };
      static void CloseAnalysisFile();

      void ProcessEvent() { };

      static void StartMakeAnalysisTree(int argc=1, char **argv=0);

   private:
      TAnalysisTreeBuilder(); 

      static TChain *fFragmentChain;
      static TTree  *fCurrentFragTree;
      static TFile  *fCurrentFragFile;
      static TTree  *fCurrentAnalysisTree;
      static TFile  *fCurrentAnalysisFile;
      static TGRSIRunInfo *fCurrentRunInfo;

   private:
     
      static TFragment *fragment;

      //static TTigress    *tigress;
        static TSharc      *sharc;  
      //static TTriFoil    *triFoil;
      //static TRf         *rf;     
      //static TCSM        *csm;    
      //static TSpice      *spice;  
      //static TS3         *s3;
      //static TTip        *tip;    
       
      //static TGriffin    *Griffin;
      //static TSceptar    *Sceptar;
      //static TPaces      *Paces;  
      //static TDante      *Dante;  
      //static TZeroDegree *ZeroDegree;
      //static TDescant    *Descant;

};



#endif

