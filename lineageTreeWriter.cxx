#include <vtkSmartPointer.h>
 
#include <vtkGraphLayoutView.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTree.h>

// points in the graph
#include <vtkPoints.h>

// information in the graph
#include <vtkDataSetAttributes.h>

#include <vtkStringArray.h>
#include <vtkFloatArray.h>
#include <vtkIntArray.h>
#include <vtkIdTypeArray.h>
#include <vtkDoubleArray.h>

// Write the tree
#include <vtkTreeWriter.h>

// vtkQT tree view
#include <QApplication>
#include <vtkQtTreeView.h>

int main (int argc, char *argv[])
{
 
  //////////////////////////////////////////////////
  // REQUIERED FIELDS

  vtkSmartPointer<vtkMutableDirectedGraph> graph = 
    vtkSmartPointer<vtkMutableDirectedGraph>::New();
  vtkIdType a = graph->AddVertex();
  vtkIdType b = graph->AddChild(a);
  vtkIdType c = graph->AddChild(a);
  vtkIdType d = graph->AddChild(b);
  vtkIdType e = graph->AddChild(c);
  vtkIdType f = graph->AddChild(c);
  vtkIdType g = graph->AddChild(c);
  vtkIdType h = graph->AddChild(f);
  vtkIdType i = graph->AddChild(f);

  // First array: first column of the graph

  vtkSmartPointer<vtkStringArray> cellType =
      vtkSmartPointer<vtkStringArray>::New();
  cellType->SetName("name");
  cellType->InsertValue(a, "TypeA");
  cellType->InsertValue(b, "TypeB");
  cellType->InsertValue(c, "TypeC");
  cellType->InsertValue(d, "TypeD");
  cellType->InsertValue(e, "TypeE");
  cellType->InsertValue(f, "TypeF");
  cellType->InsertValue(g, "TypeG");
  cellType->InsertValue(h, "TypeH");
  cellType->InsertValue(i, "TypeI");
  graph->GetVertexData()->AddArray(cellType);

  // i.e. trackFamilyID for us-> to collapse a part of the tree
  vtkSmartPointer<vtkIdTypeArray> pedigree =
      vtkSmartPointer<vtkIdTypeArray>::New();
  pedigree->SetName("PedigreeVertexId");
  pedigree->InsertValue(a, 0); //  has to start at 0!
  pedigree->InsertValue(b, 1);
  pedigree->InsertValue(c, 2);
  pedigree->InsertValue(d, 3);
  pedigree->InsertValue(e, 4);
  pedigree->InsertValue(f, 5);
  pedigree->InsertValue(g, 6);
  pedigree->InsertValue(h, 7);
  pedigree->InsertValue(i, 8);
  graph->GetVertexData()->AddArray(pedigree);

  ////////////////////////////////////////////////
  // ADDITIONAL FIELDS

  vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.5, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 0.0, 2.0);
  points->InsertNextPoint(0.0, 1.0, 2.0);
  points->InsertNextPoint(1.0, 0.0, 2.0);
  points->InsertNextPoint(1.0, 3.0, 2.0);
  points->InsertNextPoint(1.0, 2.0, 5.0);
  points->InsertNextPoint(3.0, 1.0, 2.0);
  graph->SetPoints(points);

  vtkSmartPointer<vtkFloatArray> size =
      vtkSmartPointer<vtkFloatArray>::New();
  size->SetName("size");
  size->InsertValue(a, 1);
  size->InsertValue(b, 2);
  size->InsertValue(c, 3);
  size->InsertValue(d, 4);
  size->InsertValue(e, 5);
  size->InsertValue(f, 6);
  size->InsertValue(g, 7);
  size->InsertValue(h, 8);
  size->InsertValue(i, 9);
  graph->GetVertexData()->AddArray(size);

  vtkSmartPointer<vtkIntArray> gfps =
      vtkSmartPointer<vtkIntArray>::New();
  gfps->SetName("GPFs");
  gfps->InsertValue(a, 1000);
  gfps->InsertValue(b, 2000);
  gfps->InsertValue(c, 3000);
  gfps->InsertValue(d, 4000);
  gfps->InsertValue(e, 5000);
  gfps->InsertValue(f, 6000);
  gfps->InsertValue(g, 7000);
  gfps->InsertValue(h, 8000);
  gfps->InsertValue(i, 9000);
  graph->GetVertexData()->AddArray(gfps);

  vtkSmartPointer<vtkDoubleArray> start =
      vtkSmartPointer<vtkDoubleArray>::New();
  start->SetName("StartTime");
  start->InsertValue(a, 0);
  start->InsertValue(b, 12);
  start->InsertValue(c, 13);
  start->InsertValue(d, 20);
  start->InsertValue(e, 20);
  start->InsertValue(f, 21);
  start->InsertValue(g, 22);
  start->InsertValue(h, 30);
  start->InsertValue(i, 31);
  graph->GetVertexData()->AddArray(start);

  vtkSmartPointer<vtkDoubleArray> end =
      vtkSmartPointer<vtkDoubleArray>::New();
  end->SetName("EndTime");
  end->InsertValue(a, 10);
  end->InsertValue(b, 15);
  end->InsertValue(c, 16);
  end->InsertValue(d, 25);
  end->InsertValue(e, 27);
  end->InsertValue(f, 28);
  end->InsertValue(g, 30);
  end->InsertValue(h, 43);
  end->InsertValue(i, 37);
  graph->GetVertexData()->AddArray(end);

  vtkSmartPointer<vtkDoubleArray> length =
      vtkSmartPointer<vtkDoubleArray>::New();
  length->SetName("Length");
  length->InsertValue(a, 10);
  length->InsertValue(b, 15);
  length->InsertValue(c, 16);
  length->InsertValue(d, 25);
  length->InsertValue(e, 27);
  length->InsertValue(f, 28);
  length->InsertValue(g, 30);
  length->InsertValue(h, 12);
  length->InsertValue(i, 11);
  graph->GetVertexData()->AddArray(length);

  vtkSmartPointer<vtkDoubleArray> xPos =
      vtkSmartPointer<vtkDoubleArray>::New();
  xPos->SetName("XPos");
  xPos->InsertValue(a, 113);
  xPos->InsertValue(b, 51);
  xPos->InsertValue(c, 21);
  xPos->InsertValue(d, 1);
  xPos->InsertValue(e, 51);
  xPos->InsertValue(f, 5);
  xPos->InsertValue(g, 7);
  xPos->InsertValue(h, 116);
  xPos->InsertValue(i, 219);
  graph->GetVertexData()->AddArray(xPos);

  //graph->GetVertexData()->SetActiveScalars("XPos");

  //graph->GetVertexData()->SetActiveScalars("XPos");

  vtkSmartPointer<vtkTree> tree = 
    vtkSmartPointer<vtkTree>::New();
  tree->ShallowCopy(graph);
 
  vtkSmartPointer<vtkGraphLayoutView> treeLayoutView = 
    vtkSmartPointer<vtkGraphLayoutView>::New();
  treeLayoutView->AddRepresentationFromInput(tree);
  treeLayoutView->SetLayoutStrategyToTree();
  treeLayoutView->ResetCamera();
  treeLayoutView->Render();
  treeLayoutView->GetInteractor()->Start();

  // Write Tree
  vtkSmartPointer<vtkTreeWriter> writer = vtkSmartPointer<vtkTreeWriter>::New();
  writer->SetInput(tree);
  writer->SetFileName("lineageTree.vtk");
  writer->Write();

  // QT Application
  // vtkQT tree view
  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName("MegasonLab");
  QCoreApplication::setOrganizationDomain("http://gofigure2.sourceforge.net");

  vtkSmartPointer<vtkQtTreeView> qtTreeView =
      vtkSmartPointer<vtkQtTreeView>::New();
  qtTreeView->AddRepresentationFromInput(tree);

  return EXIT_SUCCESS;
}
