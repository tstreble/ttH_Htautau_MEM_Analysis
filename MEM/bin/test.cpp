#include <iostream>
#include <vector>
#include "ttH_Htautau_MEM_Analysis/MEM/interface/PyRun2EventData_t.h"
#include "ttH_Htautau_MEM_Analysis/MEM/interface/EventReader.h"

#include "ttH_Htautau_MEM_Analysis/MEMAlgo/interface/Processes.h"
#include "ttH_Htautau_MEM_Analysis/MEMAlgo/interface/ThreadScheduler.h"

///////  Main program /////////

NodeScheduler *scheduler; 

int main (int argc, char** argv)
{


   //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  //@@@                   Configuration                                      @@@
  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  // 
  // Configuration argv[argc-1].py
  string configName( argv[argc-1] );
  // Remove ".py"
  size_t pos = configName.find(".py", configName.length()-3);
  if ( pos != string::npos )
    configName.resize( configName.length()-3 );
  if (argc == 1) configName = "defaultConfig";
  //
  const RunConfig* runConfig = new RunConfig(configName.c_str());  
  scheduler = new ThreadScheduler();
  

  PyRun2EventData_t eventFields;
  EventReader<PyRun2EventData_t> evRead(runConfig->inputFileNames_,runConfig->skipEvents_,runConfig->maxNbrOfEventsToRead_);

  eventList_t eventList;
  evRead.fillEvent( eventList, runConfig->maxNbrOfEventsToRead_  );

  scheduler->initNodeScheduler( runConfig, 0 );
  
  scheduler->runNodeScheduler ( eventList, runConfig->maxNbrOfEventsToRead_ );
  
  for(int event=0;event<runConfig->maxNbrOfEventsToRead_;event++){
    std::cout<<std::endl;
    std::cout<<"======"<<std::endl;
    std::cout<<"nbrOfPermut_ : "<<eventList[event].nbrOfPermut_<<std::endl;
    for(int perm=0; perm<eventList[event].nbrOfPermut_; perm++){
      std::cout<<"perm="<<perm<<std::endl;
      std::cout<<"w(ttH)="<<eventList[event].integralttH_[perm]<<" +/- "<<eventList[event].stderrttH_[perm]<<std::endl;
      std::cout<<"w(ttZ,Z->tautau)="<<eventList[event].integralttZ_[perm]<<" +/- "<<eventList[event].stderrttZ_[perm]<<std::endl;
      std::cout<<"w(ttZ,Z->ll)="<<eventList[event].integralttZ_Zll_[perm]<<" +/- "<<eventList[event].stderrttZ_Zll_[perm]<<std::endl;
      std::cout<<"w(tt,fake from tlep)="<<eventList[event].integralttbar_DL_fakelep_tlep_[perm]<<" +/- "<<eventList[event].stderrttbar_DL_fakelep_tlep_[perm]<<std::endl;
      std::cout<<"w(tt,fake from ttau)="<<eventList[event].integralttbar_DL_fakelep_ttau_[perm]<<" +/- "<<eventList[event].stderrttbar_DL_fakelep_ttau_[perm]<<std::endl;

    }

    cout<<"Sum over perm"<<endl;
    std::cout<<"w(ttH)="<<eventList[event].weight_ttH_<<" +/- "<<eventList[event].weight_error_ttH_<<std::endl;
    std::cout<<"w(ttZ,Z->tautau)="<<eventList[event].weight_ttZ_<<" +/- "<<eventList[event].weight_error_ttZ_<<std::endl;
    std::cout<<"w(ttZ,Z->ll)="<<eventList[event].weight_ttZ_Zll_<<" +/- "<<eventList[event].weight_error_ttZ_Zll_<<std::endl;
    std::cout<<"w(tt,fake)="<<eventList[event].weight_ttbar_DL_fakelep_<<" +/- "<<eventList[event].weight_error_ttbar_DL_fakelep_<<std::endl;

  }

  return 0 ;
}

