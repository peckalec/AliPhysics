// -*- C++ -*-
#ifndef __ALIMULTIPLICITYSELECTIONCP_H__
#define __ALIMULTIPLICITYSELECTIONCP_H__

#include <TObject.h>
#include <TList.h>
#include <TArrayI.h>

class AliESDtrack;
class AliESDtrackCuts;

class AliMultiplicitySelectionCP : public TObject {

private:
  Int_t fTPCnclsS;          // Number of shared clusters in TPC, used in first loop
  Double_t fTrackDCAz;      // DCAz, used in first track loop
  Double_t fTrackEtaMin;    // EtaMin, used in second loop
  Double_t fTrackEtaMax;    // EtaMax, used in second loop
  Bool_t fkCheckReferenceMultiplicity; // should be kFALSE for LHC10{b,c} pass2

  TList *fTrackCutListPrim; // TList with primary track selection cuts

  TArrayI fIndicesN;
  TArrayI fIndicesP;

  static const Int_t fkNtrackMax = 1000; // assumed max mumber of track in ESD
  Bool_t fkIsTrackSec[fkNtrackMax]; //  array for V0 daughters
  Bool_t fkIgnoreV0s; // flag for ignoring V0 daughters in mutiplicity estimate 
  Bool_t InitV0Daughters(AliESDEvent *esd);

public:
  AliMultiplicitySelectionCP();
  ~AliMultiplicitySelectionCP();

  void SetCheckReferenceMultiplicity() {fkCheckReferenceMultiplicity = kTRUE;} 
  void SetTPCnclsS(Int_t n = 3) {fTPCnclsS = n;} 
  void SetTrackDCAz(Double_t d = 6.) {fTrackDCAz = d;} 
  void SetTrackEtaRange(Double_t min=-0.9, Double_t max = 0.9) {
    fTrackEtaMin = min;
    fTrackEtaMax = max;
  }

  Int_t GetNumberOfITSTPCtracks(AliESDEvent *esd);
  Int_t GetNumberOfITSTPCtracks(AliESDEvent *esd, TArrayI &indices);

  TArrayI GetIndicesN() {return fIndicesN;}
  TArrayI GetIndicesP() {return fIndicesP;}

  Bool_t IsTrackSelected(Int_t index);

  TList *GetPrimaryTrackCutList() { return fTrackCutListPrim;}
  AliESDtrackCuts *GetPrimaryTrackCut(const char* name) {
    return (AliESDtrackCuts *) fTrackCutListPrim->FindObject(name);
  }

  Bool_t AcceptTrack(AliESDtrack *track, Bool_t asPrimary = kFALSE);
  Bool_t TestFiredChips(AliESDEvent *esd, TArrayI indices);

  void InitDefaultTrackCuts(Int_t clusterCut);
  void AddPrimaryTrackCut(AliESDtrackCuts *cut);

  void IgnoreV0s(Bool_t k=kFALSE) {fkIgnoreV0s = k;}

  ClassDef(AliMultiplicitySelectionCP, 2)   // tbd
};
#endif
