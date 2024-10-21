#include "MyDetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction() {}

MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume *MyDetectorConstruction::Construct() {
  // Define materials
  DefineMaterials();

  // Define volumes
  return DefineVolumes();
}

void MyDetectorConstruction::DefineMaterials() {
  // NIST
  G4NistManager *nist = G4NistManager::Instance();

  // Air
  Air = nist->FindOrBuildMaterial("G4_AIR");

  // Al
  Al = nist->FindOrBuildMaterial("G4_Al");

  // Li
  Li = nist->FindOrBuildMaterial("G4_Li");

  // Ge
  Ge = nist->FindOrBuildMaterial("G4_Ge");

  // Mylar
  Mylar = nist->FindOrBuildMaterial("G4_MYLAR");

  // Vacuum
  Vacuum = nist->FindOrBuildMaterial("G4_Galactic");

  // GeB
  G4Element *elGe = nist->FindOrBuildElement("Ge");
  G4Element *elB = nist->FindOrBuildElement("B");
  GeB = new G4Material("GeB", 5.32 * g / cm3, 2);
  GeB->AddElement(elGe, 50 * perCent);
  GeB->AddElement(elB, 50 * perCent);

  // GeLi
  G4Element *elLi = nist->FindOrBuildElement("Li");
  GeLi = new G4Material("GeB", 5.32 * g / cm3, 2);
  GeLi->AddElement(elGe, 50 * perCent);
  GeLi->AddElement(elLi, 50 * perCent);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume *MyDetectorConstruction::DefineVolumes() {
  // ------------------------------------------------------------------------------------------
  // Mother world volume
  // ------------------------------------------------------------------------------------------
  solidWorld = new G4Box("solidWorld", 500 * cm, 500 * cm, 500 * cm);
  logicWorld = new G4LogicalVolume(solidWorld, Air, "logicWorld");
  physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0,
                                false, 0, check_overlap);
  logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

  // ------------------------------------------------------------------------------------------
  // Ge Crystal - Blue
  // ------------------------------------------------------------------------------------------
  G4double radius_GeCrystal = (65.9 - 0.7) / 2 * mm;
  G4double length_GeCrystal = 77 * mm;
  G4double startPhi = 0. * deg;
  G4double deltaPhi = 360. * deg;
  G4double radius_torus_GeCrystal = 8. * mm;
  // 1 cylinder under torus
  G4Tubs *cylinder_GeCrystal = new G4Tubs(
      "Cylinder", 0, radius_GeCrystal,
      (length_GeCrystal - radius_torus_GeCrystal) / 2, startPhi, deltaPhi);
  // 2 cylinder in torus
  G4Tubs *cylinder_inTorus_GeCrystal = new G4Tubs(
      "CylinderInTorus", 0, radius_GeCrystal - radius_torus_GeCrystal,
      radius_torus_GeCrystal, startPhi, deltaPhi);
  G4double posTorusZ = (length_GeCrystal - radius_torus_GeCrystal) / 2;
  G4double posInnerCylinderZ = posTorusZ;
  G4UnionSolid *crystalGeTotal = new G4UnionSolid(
      "FinalShape", cylinder_GeCrystal, cylinder_inTorus_GeCrystal, nullptr,
      G4ThreeVector(0., 0., posInnerCylinderZ));
  // 3 (1/4) torus
  G4Torus *torus_GeCrystal =
      new G4Torus("Torus", 0, radius_torus_GeCrystal, radius_GeCrystal - 8,
                  startPhi, deltaPhi);
  G4SubtractionSolid *total_torus = new G4SubtractionSolid(
      "torus", torus_GeCrystal, cylinder_inTorus_GeCrystal, nullptr,
      G4ThreeVector(0., 0., 0.));
  G4Tubs *cylinder_underTorusSubtract =
      new G4Tubs("cylinderUnderTorusSubtract", 0, radius_GeCrystal, 4 * mm,
                 startPhi, deltaPhi);
  G4SubtractionSolid *total_torusOnCylinderGeCrystal = new G4SubtractionSolid(
      "torusGeCrystal", total_torus, cylinder_underTorusSubtract, nullptr,
      G4ThreeVector(0., 0., -radius_torus_GeCrystal / 2));
  G4ThreeVector position_torusOnTop(
      0., 0., (length_GeCrystal - radius_torus_GeCrystal + 0.7) / 2);
  // 4 hole Crystal
  // 4.1 top sphere
  G4double radius_hole_GeCrystal = 11.5 / 2 * mm;
  G4double depth_hole_GeCrystal = 64.9 * mm;
  G4double radius_holeSphere_GeCrystal = 5 * mm;
  G4Sphere *sphere_hole_GeCrystal =
      new G4Sphere("HoleSphere", 0, radius_hole_GeCrystal, startPhi, deltaPhi,
                   startPhi, deltaPhi / 4);
  // 4.2 cylinder under sphere
  G4Tubs *cylinder_hole_GeCrystal =
      new G4Tubs("HoleCylinder", 0, radius_hole_GeCrystal,
                 (depth_hole_GeCrystal - 5 * mm) / 2, startPhi, deltaPhi);
  G4ThreeVector position_hole_sphere(
      0., 0., (depth_hole_GeCrystal - radius_holeSphere_GeCrystal) / 2);
  G4UnionSolid *total_hole_GeCrystal =
      new G4UnionSolid("TotalHoleGeCrystal", cylinder_hole_GeCrystal,
                       sphere_hole_GeCrystal, nullptr, position_hole_sphere);
  G4ThreeVector posTopSphere(
      0., 0., -(length_GeCrystal - depth_hole_GeCrystal - 3) / 2);
  G4SubtractionSolid *total_withHole_GeCrystal =
      new G4SubtractionSolid("GeWithHole", crystalGeTotal, total_hole_GeCrystal,
                             nullptr, posTopSphere);
  G4UnionSolid *total_GeCrystal = new G4UnionSolid(
      "TotalGeCrystal", total_withHole_GeCrystal,
      total_torusOnCylinderGeCrystal, nullptr, position_torusOnTop);
  logic_GeCrystal = new G4LogicalVolume(total_GeCrystal, Ge, "logicGeCrystal");
  new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 0.), logic_GeCrystal,
                    "GeCrystal", logicWorld, false, 0, true);
  //  5 set color
  G4VisAttributes *visGeCrystal = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
  visGeCrystal->SetVisibility(true);
  logic_GeCrystal->SetVisAttributes(visGeCrystal);

  // ------------------------------------------------------------------------------------------
  // DeadLayer - Green - Red
  // ------------------------------------------------------------------------------------------
  // 1 Ge/B deadLayer in hole
  // 1.1 cylinder B deadLayer hole
  G4double thickness_BdeadLayer = 0.0003 * mm;
  G4Sphere *sphere_hole_BDeadLayer = new G4Sphere(
      "HoleSphere", radius_hole_GeCrystal - thickness_BdeadLayer,
      radius_hole_GeCrystal, startPhi, deltaPhi, startPhi, deltaPhi / 4);
  // 1.2 cylinder under sphere B deadLayer
  G4Tubs *cylinder_hole_BDeadLayer = new G4Tubs(
      "HoleCylinder", radius_hole_GeCrystal - 3 * mm, radius_hole_GeCrystal,
      (depth_hole_GeCrystal - radius_holeSphere_GeCrystal) / 2, startPhi,
      deltaPhi);
  G4UnionSolid *total_BDeadLayer =
      new G4UnionSolid("TotalHoleGeCrystal", cylinder_hole_GeCrystal,
                       sphere_hole_GeCrystal, nullptr, position_hole_sphere);
  G4ThreeVector posBDeadLayer(
      0., 0., -(length_GeCrystal - depth_hole_GeCrystal - 3) / 2);
  logic_BDeadLayer =
      new G4LogicalVolume(total_BDeadLayer, Ge, "logicBDeadLayer");
  new G4PVPlacement(nullptr, posBDeadLayer, logic_BDeadLayer, "BDeadLayer",
                    logicWorld, false, 0, true);
  //   1.3 set color
  G4VisAttributes *visBdeadLayer = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
  visBdeadLayer->SetVisibility(true);
  logic_BDeadLayer->SetVisAttributes(visBdeadLayer);
  // 2 Ge/Li deadLayer cover Ge Crystal
  // 2.1 cylinder under the torus
  G4double thickness_LiDeadLayer = 0.7 * mm;
  G4Tubs *cylinder_LiDeadLayer = new G4Tubs(
      "LiDeadLayer", radius_GeCrystal, radius_GeCrystal + thickness_LiDeadLayer,
      (length_GeCrystal - 8 * mm) / 2, startPhi, deltaPhi);
  // 2.2 torus Li deadLayer

  logic_LiDeadLayer =
      new G4LogicalVolume(cylinder_LiDeadLayer, GeLi, "logicLiDeadLayer");
  new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 0.), logic_LiDeadLayer,
                    "LiDeadLayer", logicWorld, false, 0, true);
  G4VisAttributes *visLiDeadLayer =
      new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
  visLiDeadLayer->SetVisibility(true);
  logic_LiDeadLayer->SetVisAttributes(visLiDeadLayer);

  // ------------------------------------------------------------------------------------------
  // Window Al - Gray / Mylar - Cyan
  // ------------------------------------------------------------------------------------------
  // 1 Al Window 0.03mm
  G4double thickness_alWindow = 0.03 * mm;
  G4double space_crystal_housing = 2.75 * mm;
  G4Tubs *cylinder_alWindow = new G4Tubs(
      "AlWindow", 0, radius_GeCrystal + space_crystal_housing + 0.8 * mm,
      thickness_alWindow / 2, startPhi, deltaPhi);
  G4ThreeVector posAlWindow(0., 0.,
                            (length_GeCrystal + thickness_alWindow + 8.7) / 2);
  logic_AlWindow = new G4LogicalVolume(cylinder_alWindow, Al, "logicAlWindow");
  new G4PVPlacement(nullptr, posAlWindow, logic_AlWindow, "AlWindow",
                    logicWorld, false, 0, true);
  G4VisAttributes *visAlWindow = new G4VisAttributes(G4Colour(0.7, 0.7, 0.7));
  visAlWindow->SetVisibility(true);
  logic_AlWindow->SetVisAttributes(visAlWindow);
  // 2 Mylar Window 0.03mm
  G4double thickness_mylarWindow = 0.03 * mm;
  G4Tubs *cylinder_mylarWindow = new G4Tubs(
      "MylarWindow", 0, radius_GeCrystal + space_crystal_housing + 0.8 * mm,
      thickness_mylarWindow / 2, startPhi, deltaPhi);
  G4ThreeVector posMylarWindow(0., 0.,
                               (length_GeCrystal + thickness_alWindow + 8.7) /
                                       2 +
                                   thickness_mylarWindow);
  logic_mylarWindow =
      new G4LogicalVolume(cylinder_mylarWindow, Mylar, "logicMylarWindow");
  new G4PVPlacement(nullptr, posMylarWindow, logic_mylarWindow, "MylarWindow",
                    logicWorld, false, 0, true);
  G4VisAttributes *visMylarWindow = new G4VisAttributes(G4Colour(0, 1, 1));
  visMylarWindow->SetVisibility(true);
  logic_mylarWindow->SetVisAttributes(visMylarWindow);

  // ------------------------------------------------------------------------------------------
  // Housing Al 0.8 mm
  // ------------------------------------------------------------------------------------------
  // 1 cylinder on top
  G4double thickness_alHousing = 0.8 * mm;
  G4double length_housing =
      105 * mm - thickness_mylarWindow - thickness_alWindow;
  G4double radius_alHousing =
      radius_GeCrystal + 0.7 + space_crystal_housing + thickness_alHousing;
  G4Tubs *cylinder_alHousing = new G4Tubs(
      "AlHousing", radius_alHousing - thickness_alHousing, radius_alHousing,
      (length_housing - 3 * mm) / 2, startPhi, deltaPhi);
  // 2 double half cylinder
  G4double thickness_cylinderUnderAlHousing = 3 * mm;
  G4double radius_cylinderUnderAlHousing =
      radius_GeCrystal + 0.7 + space_crystal_housing + thickness_alHousing;
  G4Tubs *cylinder_underAlHousing =
      new G4Tubs("CylinderUnderAlHousing", 0, radius_cylinderUnderAlHousing,
                 thickness_cylinderUnderAlHousing / 2, startPhi, deltaPhi);
  G4ThreeVector posCylinderUnderAlHousing(
      0., 0., -(length_housing - thickness_cylinderUnderAlHousing) / 2);
  G4UnionSolid *total_alHousing =
      new G4UnionSolid("AlHousing", cylinder_alHousing, cylinder_underAlHousing,
                       nullptr, posCylinderUnderAlHousing);
  // 3 SubtractionSolid cylinder under Al housing
  G4Box *box_underAlHousing =
      new G4Box("BoxUnderAlHousing", radius_hole_GeCrystal * 2,
                radius_cylinderUnderAlHousing + 10 * mm, 3 * mm);
  G4ThreeVector posBoxUnderAlHousing(
      0., 0., -(length_housing - thickness_cylinderUnderAlHousing) / 2);
  G4SubtractionSolid *total_alHousingWithSubtraction =
      new G4SubtractionSolid("AlHousing", total_alHousing, box_underAlHousing,
                             nullptr, posBoxUnderAlHousing);
  logic_alHousing =
      new G4LogicalVolume(total_alHousingWithSubtraction, Al, "AlHousing");
  G4ThreeVector posAlHousing(0., 0.,
                             -(105 * mm - 3 * mm - length_GeCrystal - 8.7) / 2);
  new G4PVPlacement(nullptr, posAlHousing, logic_alHousing, "AlHousing",
                    logicWorld, false, 0, true);
  G4VisAttributes *visAlHousing = new G4VisAttributes(G4Colour(0.7, 0.7, 0.7));
  visAlHousing->SetVisibility(true);
  logic_alHousing->SetVisAttributes(visAlHousing);

  // ------------------------------------------------------------------------------------------
  // Al Cover Crystal 1mm
  // ------------------------------------------------------------------------------------------
  // 1 cylinder cover
  G4double thickness_alCover = 1 * mm;
  G4double radius_alCover =
      radius_cylinderUnderAlHousing + 5.5 + thickness_alCover;
  G4Tubs *cylinder_alCover =
      new G4Tubs("AlCover", radius_alCover - thickness_alCover, radius_alCover,
                 (105 * mm + 8 * mm + 4 * mm) / 2, startPhi, deltaPhi);
  // 2 cylinder on top
  G4double space_windowAlCover = 4 * mm;
  G4Tubs *cylinder_alCoverOnTop = new G4Tubs(
      "AlCover", 0, radius_alCover, thickness_alCover / 2, startPhi, deltaPhi);
  G4ThreeVector posAlCoverOnTop(0., 0.,
                                (105 + 8 + 4 + thickness_alCover) / 2 * mm);
  G4UnionSolid *total_alCover =
      new G4UnionSolid("AlCover", cylinder_alCover, cylinder_alCoverOnTop,
                       nullptr, posAlCoverOnTop);
  logic_AlCover = new G4LogicalVolume(total_alCover, Al, "AlCover");
  G4ThreeVector posAlCover(0., 0.,
                           -(105 + 8 - length_GeCrystal - 0.06 - 8.7) / 2);
  new G4PVPlacement(nullptr, posAlCover, logic_AlCover, "AlCover", logicWorld,
                    false, 0, true);
  G4VisAttributes *visAlCover = new G4VisAttributes(G4Colour(0.7, 0.7, 0.7));
  visAlCover->SetVisibility(true);
  logic_AlCover->SetVisAttributes(visAlCover);

  // for add scoring
  fScoringVolume = logic_GeCrystal;

  return physWorld;
}

void MyDetectorConstruction::ConstructSDandField() {}
