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
 
  vtkSmartPointer<vtkMutableDirectedGraph> graph = 
    vtkSmartPointer<vtkMutableDirectedGraph>::New();
  vtkIdType a = graph->AddVertex();
  vtkIdType b = graph->AddChild(a);
  vtkIdType c = graph->AddChild(a);
  vtkIdType d = graph->AddChild(b);
  vtkIdType e = graph->AddChild(c);
  vtkIdType f = graph->AddChild(c);
  vtkIdType g = graph->AddChild(c);

  vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(0.0, 0.5, 0.0);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);
  points->InsertNextPoint(0.0, 0.0, 2.0);
  points->InsertNextPoint(0.0, 1.0, 2.0);
  points->InsertNextPoint(1.0, 0.0, 2.0);
  points->InsertNextPoint(1.0, 3.0, 2.0);
  graph->SetPoints(points);

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
  graph->GetVertexData()->AddArray(cellType);
 
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
  graph->GetVertexData()->AddArray(gfps);

  vtkSmartPointer<vtkIdTypeArray> pedigree =
      vtkSmartPointer<vtkIdTypeArray>::New();
  pedigree->SetName("PedigreeVertexId");
  pedigree->InsertValue(a, 10001);
  pedigree->InsertValue(b, 20002);
  pedigree->InsertValue(c, 30003);
  pedigree->InsertValue(d, 40004);
  pedigree->InsertValue(e, 50005);
  pedigree->InsertValue(f, 60006);
  pedigree->InsertValue(g, 70007);
  graph->GetVertexData()->AddArray(pedigree);

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
  graph->GetVertexData()->AddArray(end);

  //graph->GetVertexData()->SetActiveScalars("size");

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
