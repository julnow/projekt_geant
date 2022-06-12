//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file electromagnetic/TestEm2/include/DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4VPhysicalVolume.hh"
#include "globals.hh"
#include "G4Cache.hh"


class G4Box;
class G4LogicalVolume;
class DetectorMessenger;
class G4GlobalMagFieldMessenger;

const G4int kMaxBin = 1000;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

  DetectorConstruction();
  virtual ~DetectorConstruction();

public:

  void SetWorldMaterial(const G4String&);
  void SetLBining (G4ThreeVector);
  void SetRBining (G4ThreeVector);
  void SetAbsorberThickness(G4double val);
  void SetAbsorberMaterial(const G4String& materialChoice);

  virtual G4VPhysicalVolume* Construct();

  virtual void ConstructSDandField();

  const
  G4VPhysicalVolume* GetWorld() const    {return fPhysiWorld;};
  const G4Material* GetWorldMaterial() const {return fWorldMaterial;};

  // Subdivision of absorber
  G4int    GetnLtot() const      {return fNLtot;};
  G4int    GetnRtot() const      {return fNRtot;};
  G4double GetdLradl() const     {return fDLradl;};
  G4double GetdRradl() const     {return fDRradl;};
  G4double GetdLlength() const   {return fDLlength;};
  G4double GetdRlength() const   {return fDRlength;};  
  G4double GetfullLength() const {return fWorldLength;}; 
  G4double GetfullRadius() const {return fWorldRadius;}; 
  

private:

  void DefineMaterials();
  void UpdateParameters();
 

  G4int    fNLtot,    fNRtot;       // nb of bins: longitudinal and radial
  G4double fDLradl,   fDRradl;      // bin thickness (in radl unit)
  G4double fDLlength, fDRlength;    // bin thickness (in length unit)

  G4Material* fWorldMaterial;            //pointer to the material
    
  G4double fWorldLength;             //full length of the Calorimeter
  G4double fWorldRadius;             //radius  of the Calorimeter

  G4Box*            fSolidWorld;    //pointer to the solid calorimeter
  G4LogicalVolume*   fLogicWorld;    //pointer to the logical calorimeter
  G4VPhysicalVolume* fPhysiWorld;    //pointer to the physical calorimeter

  G4Material*        fAbsorberMaterial;
  G4double           fAbsorberThickness;
  G4double           fAbsorberSizeXY;
  G4Box*             fSolidAbsorber;
  G4LogicalVolume*   fLogicAbsorber;
  G4VPhysicalVolume* fPhysiAbsorber;

  DetectorMessenger* fDetectorMessenger;  //pointer to the Messenger

  G4Cache<G4GlobalMagFieldMessenger*> fFieldMessenger;
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

