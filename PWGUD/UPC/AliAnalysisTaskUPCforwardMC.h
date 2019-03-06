/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. */
/* See cxx source for full Copyright notice */
/* $Id$ */

#ifndef AliAnalysisTaskUPCforwardMC_H
#define AliAnalysisTaskUPCforwardMC_H

/**
 * @file   AliAnalysisTaskUPCforwardMC.h
 * @author Simone Ragoni <Simone.Ragoni@cern.ch>
 * @date   February 2019
 */

#include "AliAnalysisTaskSE.h"
#include "TBits.h"

class AliMuonTrackCuts; 					// Include class for standard muon tack cuts

/**
 * \file AliAnalysisTaskUPCforwardMC.h
 * \brief Contains the declaration of the AliAnalysisTaskUPCforwardMC class
 */

/**
 * \class AliAnalysisTaskUPCforwardMC
 * \brief Contains the tools to every part of my analysis
 */
class AliAnalysisTaskUPCforwardMC : public AliAnalysisTaskSE
{
    public:
                                /**
                                 * Create a new AliAnalysisTaskUPCforwardMC with
                                 * default constructor. Based on my understanding
                                 * this is mostly related to input/output
                                 * processes.
                                 */
                                AliAnalysisTaskUPCforwardMC();

                                /**
                                 * Create a new AliAnalysisTaskUPCforwardMC with
                                 * a specific name. This serves to instantiate
                                 * the AliAnalysisTaskSE object built with the
                                 * constructor, that will take this specific
                                 * name.
                                 *
                                 * \param name , the name taken by the AliAnalysisTaskSE object.
                                 * \param isMC , 0 if Data, 1 if MC(look at the AddTask please).
                                 */
                                AliAnalysisTaskUPCforwardMC(const char *name);

                                /**
                                 * Virtual destructor for the class. It will
                                 * take care of all the particular objects to be
                                 * destroyed for the class.
                                 */
        virtual                 ~AliAnalysisTaskUPCforwardMC();

                                /**
                                 * The function related to the instantiation of
                                 * all the histograms and the output list.
                                 */
        virtual void            UserCreateOutputObjects();

                                /**
                                 * Everything happens here. Here, the cuts are
                                 * applied, the histograms are filled and the
                                 * J/Psi peak is manifested inside the histograms.
                                 *
                                 * \param option , actually it is not used for now...
                                 */
        virtual void            UserExec(Option_t* option);

                                /**
                                 * Called at the END of the analysis (when all
                                 * events are processed). But it is not actually
                                 * doing anything! I guess it is mostly needed
                                 * for I/O purposes and GRID interfacing...
                                 */
        virtual void            Terminate(Option_t* option);

                                /**
                                 * Implement the NotifyRun to search for the new
                                 * parameters at each new runs. Sets the run
                                 * number for the successive cuts.
                                 */
        virtual void   			    NotifyRun();

                                /**
                                 * This will fill the vector containing the good
                                 * run numbers. For now this function will be
                                 * inside the constructor of the class.
                                 */
        void   			            FillGoodRunVector(std::vector<Int_t> &fVectorGoodRunNumbers);

                                /**
                                 * This function substitutes the roel of the
                                 * triggers for the MC.
                                 */
        Bool_t                  IsTriggered();

                                /**
                                 * This function is needed to record the MC
                                 * truth information inside the nanoAODs.
                                 * Everything MC related should go in here.
                                 * This should help for a subsequent merging
                                 * of the MC and DATA classes.
                                 */
        void                    ProcessMCParticles(AliMCEvent* fMCEvent);

                                /**
                                 * Use the class as a data member. It contains
                                 * the cuts for the muon track.
                                 */
        AliMuonTrackCuts* 		  fMuonTrackCuts;



        // Bool_t                  CheckIfPassedCuts(vector<>)

    private:

                                /// The input events for the analysis.
        AliAODEvent*            fAOD;               //!

                                /**
                                 * The output list containing all the histograms
                                 * required for the analysis. In a second time
                                 * I will probably make it so to include every
                                 * possible cut variation to better compute the
                                 * systematics.
                                 */
        TList*                  fOutputList;        //!

                                /**
                                 * The corresponding MC event as explained in
                                 * the Analysis Tutorial...
                                 */
        AliMCEvent*             fMCEvent;       //!

                                /**
                                 * Utility type histo. It counts the GOOD muons
                                 * per event.
                                 */
        TH1F*                   fNumberMuonsH;      //!

                                /**
                                 * In this histogram the number of events passing
                                 * each cut is recorded. So it is highest at the
                                 * 0-th cut, and lowest, even possibly null, at
                                 * the last possible cut.
                                 */
        TH1F*                   fCounterH;          //!

                                /**
                                 * As far as I understand, it should be the
                                 * pseudorapidity distribution of the many muons.
                                 */
	      TH1F*                   fEtaMuonH;          //!

                                /**
                                 *
                                 */
	      TH1F*                   fRAbsMuonH;         //!

                                /**
                                 * This histogram records the invariant mass
                                 * distribution of the dimuon system.
                                 */
        TH1F*                   fInvariantMassDistributionH;         //!

                                /**
                                 * This histogram records the number of entries
                                 * against the respective run number.
                                 */
        TH1F*                   fEntriesAgainstRunNumberH;         //!

                                /**
                                 * This histogram records the number of entries
                                 * against the respective run number, but the
                                 * binning is done properly, like normally
                                 * found for this type of histograms.
                                 */
        TH1F*                   fEntriesAgainstRunNumberProperlyH;         //!

                                /**
                                 * This histogram records the invariant mass
                                 * distribution of the dimuon system, only
                                 * coherent component, so as to say, only
                                 * pt < 0.25 GeV/c for pt of the dimuon pair.
                                 */
        TH1F*                   fInvariantMassDistributionCoherentH;       //!

                                /**
                                 * This histogram records the invariant mass
                                 * distribution of the dimuon system, only
                                 * coherent component, so as to say, only
                                 * pt > 0.25 GeV/c for pt of the dimuon pair.
                                 */
        TH1F*                   fInvariantMassDistributionIncoherentH;     //!

                                /**
                                 * This histogram records the pt-ditribution
                                 * of the dimuon pairs.
                                 */
        TH1F*                   fDimuonPtDistributionH;         //!

                                /**
                                 * This histogram records the invariant mass
                                 * distribution of the dimuon system, but the
                                 * novelty is the use of a different method to
                                 * extract the data. While before we were always
                                 * using the fMomentum, this histogram will be
                                 * filled wth the information from the
                                 * fMomentumAtDCA, hopefully this may lead to a
                                 * change in the sigma of the peaks. If not, it
                                 * will just do nothing!
                                 */
        TH2F*                   fDcaAgainstInvariantMassH;         //!


        //_______________________________
        // Cloned histograms with EXTENDED Range (0,20)->(0,40).

                                /**
                                 * This histogram records the invariant mass
                                 * distribution of the dimuon system.
                                 */
        TH1F*                   fInvariantMassDistributionExtendedH;         //!

                                /**
                                 * This histogram records the invariant mass
                                 * distribution of the dimuon system, only
                                 * coherent component, so as to say, only
                                 * pt < 0.25 GeV/c for pt of the dimuon pair.
                                 */
        TH1F*                   fInvariantMassDistributionCoherentExtendedH;       //!

                                /**
                                 * This histogram records the invariant mass
                                 * distribution of the dimuon system, only
                                 * coherent component, so as to say, only
                                 * pt > 0.25 GeV/c for pt of the dimuon pair.
                                 */
        TH1F*                   fInvariantMassDistributionIncoherentExtendedH;     //!

                                /**
                                 * This histogram shows the angular distribution
                                 * of the positive muon in the rest frame of the
                                 * J/Psi. This histogram is needed to evaluate
                                 * the polarization of the J/Psi!
                                 */
        TH1F*                   fAngularDistribOfPositiveMuonRestFrameJPsiH;

                                /**
                                 * This histogram shows the angular distribution
                                 * of the negative muon in the rest frame of the
                                 * J/Psi. This histogram is needed to evaluate
                                 * the polarization of the J/Psi!
                                 */
        TH1F*                   fAngularDistribOfNegativeMuonRestFrameJPsiH;

        //_______________________________
        // MC TRUTH PLOTS
                                /**
                                 * This histogram records the pdgCodes of all
                                 * the MC GENERATED particles...
                                 */
        TH1F*                   fMCpdgCodesH;

                                /**
                                 * This histogram records the pdgCodes of all
                                 * the MC GENERATED PRIMARY particles...
                                 */
        TH1F*                   fMCpdgCodesOnlyPrimaryH;

        // MC TRUTH GENERATED FEATURES
                                /**
                                 * This histogram records the PHI of all
                                 * the MC GENERATED particles...
                                 */
        TH1F*                   fMCphiGeneratedTruthH;

                                /**
                                 * This histogram records the ETA of all
                                 * the MC GENERATED PRIMARY particles...
                                 */
        TH1F*                   fMCetaGeneratedTruthH;

                                /**
                                 * This histogram records the PSEUDORAPIDITY of
                                 * all the MC GENERATED PRIMARY particles...
                                 */
        TH1F*                   fMCpseudorapidityGeneratedTruthH;

                                /**
                                 * This histogram records the Pt of all
                                 * the MC GENERATED particles...
                                 */
        TH1F*                   fMCptGeneratedTruthH;

        // MC TRUTH GENERATED DIMUONS FEATURES
                                /**
                                 * This histogram records the PHI of all
                                 * the MC GENERATED muons of the J/Psi...
                                 */
        TH1F*                   fMCphiDimuonGeneratedTruthH;

                                /**
                                 * This histogram records the ETA of all
                                 * the MC GENERATED muons of the J/Psi...
                                 */
        TH1F*                   fMCetaDimuonGeneratedTruthH;

                                /**
                                 * This histogram records the PSEUDORAPIDITY of
                                 * all the MC GENERATED muons of the J/Psi...
                                 */
        TH1F*                   fMCpseudorapidityDimuonGeneratedTruthH;

                                /**
                                 * This histogram records the Pt of all
                                 * the MC GENERATED muons of the J/Psi...
                                 */
        TH1F*                   fMCptDimuonGeneratedTruthSingleMuonsH;

                                /**
                                 * This histogram records the Pt of all
                                 * the MC GENERATED J/Psi.
                                 */
        TH1F*                   fMCptDimuonGeneratedTruthH;






                                /**
                                 * Invariant Mass Distribution of the J/Psi
                                 * before EVENT and TRACK selection for the MC
                                 * (aka GENERATED).
                                 */
        TH1F*                   fMCinvariantMassDistrJPsiGeneratedTruthH;

                                /**
                                 * Invariant Mass Distribution of the J/Psi
                                 * after EVENT and TRACK selection for the MC
                                 * WITH MC TRUTH.
                                 */
        TH1F*                   fMCinvariantMassDistrJPsiAfterEvtAndTrkSelectionTruthH;

                                /**
                                 * This histogram shows the angular distribution
                                 * of the positive muon in the rest frame of the
                                 * J/Psi. This histogram is needed to evaluate
                                 * the polarization of the J/Psi!
                                 */
        TH1F*                   fMCthetaDistribOfPositiveMuonRestFrameJPsiGeneratedTruthH;

                                /**
                                 * This histogram shows the angular distribution
                                 * of the negative muon in the rest frame of the
                                 * J/Psi. This histogram is needed to evaluate
                                 * the polarization of the J/Psi!
                                 */
        TH1F*                   fMCthetaDistribOfNegativeMuonRestFrameJPsiGeneratedTruthH;





        //_______________________________

        //_______________________________
        // CUTS
        /*
         * The following is all the possible checks for the event selections
         * and the track selection as well. Enjoy.
         */
        Int_t                   fRunNum;        //!
        Int_t                   fTracklets;     //!

        UInt_t                  fL0inputs;      //!
      	UInt_t                  fL1inputs;      //!

      	Double_t                fZem1Energy;    //!
      	Double_t                fZem2Energy;    //!

      	Double_t                fZNCEnergy;     //!
      	Double_t                fZNAEnergy;     //!
      	Double_t                fZPCEnergy;     //!
      	Double_t                fZPAEnergy;     //!
      	Double_t                fZNATDC[4];     //!
      	Double_t                fZNCTDC[4];     //!
      	Double_t                fZPATDC[4];     //!
      	Double_t                fZPCTDC[4];     //!
      	Double_t                fZNATime;       //!
      	Double_t                fZNCTime;       //!
      	Int_t                   fV0ADecision;   //!
      	Int_t                   fV0CDecision;   //!
      	Int_t                   fADADecision;   //!
      	Int_t                   fADCDecision;   //!
        TBits                   fIR1Map;        //!
        TBits                   fIR2Map;        //!


        Bool_t                  fV0Hits[64];    //!
        Int_t                   fV0TotalNCells; //!
        //_______________________________


        //_______________________________
        // TRIGGER INPUTS for MC

        // V0 inputs
        Bool_t                  fBBFlag[64];    //!
        Bool_t                  fBGFlag[64];    //!
        UInt_t                  fBBAFlags;      //!
        UInt_t                  fBBCFlags;      //!
        UInt_t                  fBGAFlags;      //!
        UInt_t                  fBGCFlags;      //!

        // AD inputs
        Bool_t                  fBBFlagAD[16];  //!
        Bool_t                  fBGFlagAD[16];  //!
        UInt_t                  fBBAFlagsAD;    //!
        UInt_t                  fBBCFlagsAD;    //!
        UInt_t                  fBGAFlagsAD;    //!
        UInt_t                  fBGCFlagsAD;    //!

        // FINISHED TRIGGER INPUTS for MC
        //_______________________________


        /**
         * This is the vector containing the GOOD RunNumbers.
         */
        std::vector<Int_t> fVectorGoodRunNumbers;

        /**
         * Not implemented yet...
         */
        AliAnalysisTaskUPCforwardMC(const AliAnalysisTaskUPCforwardMC&);

        /**
         * Not implemented yet...
         */
        AliAnalysisTaskUPCforwardMC& operator=(const AliAnalysisTaskUPCforwardMC&);

        /**
         * This is important for ROOT only. I do not remember the reason anymore.
         * If I happen to encounter it again in the future, I will make sure to
         * record it!
         */
        ClassDef(AliAnalysisTaskUPCforwardMC, 1);
};

#endif
