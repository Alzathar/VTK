/*=========================================================================

  Program:   Visualization Library
  Module:    FNormals.hh
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

This file is part of the Visualization Library. No part of this file or its 
contents may be copied, reproduced or altered in any way without the express
written consent of the authors.

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen 1993, 1994 

=========================================================================*/
// .NAME vlFloatNormals - floating point representation of 3D normals
// .SECTION Description
// vlFloatNormals is a concrete implementation of vlNormals. Normals are
// represented using float values.

#ifndef __vlFloatNormals_h
#define __vlFloatNormals_h

#include "Normals.hh"
#include "FArray.hh"

class vlFloatNormals : public vlNormals
{
public:
  vlFloatNormals() {};
  vlFloatNormals(const vlFloatNormals& fn) {this->N = fn.N;};
  vlFloatNormals(const int sz, const int ext=1000):N(3*sz,3*ext){};
  ~vlFloatNormals() {};
  int Allocate(const int sz, const int ext=1000) {return this->N.Allocate(3*sz,3*ext);};
  void Initialize() {this->N.Initialize();};
  char *GetClassName() {return "vlFloatNormals";};

  // vlNormal interface
  vlNormals *MakeObject(int sze, int ext=1000);
  int GetNumberOfNormals() {return (N.GetMaxId()+1)/3;};
  void Squeeze() {this->N.Squeeze();};
  float *GetNormal(int i) {return this->N.GetPtr(3*i);};
  void GetNormal(int i,float n[3]) {this->vlNormals::GetNormal(i,n);};
  void SetNormal(int i, float n[3]);
  void InsertNormal(int i, float *n);
  int InsertNextNormal(float *n);

  // miscellaneous
  vlFloatNormals &operator=(const vlFloatNormals& fn);
  void operator+=(const vlFloatNormals& fn);
  void Reset() {this->N.Reset();};

protected:
  vlFloatArray N;
};

inline void vlFloatNormals::SetNormal(int i, float n[3]) 
{
  i*=3; 
  this->N[i]=n[0]; 
  this->N[i+1]=n[1]; 
  this->N[i+2]=n[2];
}

inline void vlFloatNormals::InsertNormal(int i, float *n) 
{
  this->N.InsertValue(3*i+2, n[2]);
  this->N[3*i] =  n[0];
  this->N[3*i+1] =  n[1];
}

inline int vlFloatNormals::InsertNextNormal(float *n) 
{
  int id = this->N.GetMaxId() + 3;
  this->N.InsertValue(id,n[2]);
  this->N[id-2] = n[0];
  this->N[id-1] = n[1];
  return id/3;
}

#endif
