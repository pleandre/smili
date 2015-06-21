/*=========================================================================
  The Software is copyright (c) Commonwealth Scientific and Industrial Research Organisation (CSIRO)
  ABN 41 687 119 230.
  All rights reserved.

  Licensed under the CSIRO BSD 3-Clause License
  You may not use this file except in compliance with the License.
  You may obtain a copy of the License in the file LICENSE.md or at

  https://stash.csiro.au/projects/SMILI/repos/smili/browse/license.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
=========================================================================*/
#ifndef MILXQTRegistrationNiftiReg_H
#define MILXQTRegistrationNiftiReg_H
#include "milxQtMain.h"
#include <QObject>
#include <QtCore>
#include <QFuture>

#include "_reg_ReadWriteImage.h"
#include "_reg_f3d2.h"
#include "_reg_ReadWriteImage.h"
#include "_reg_resampling.h"
#include "_reg_globalTransformation.h"
#include "_reg_localTransformation.h"
#include "_reg_tools.h"
#include "_reg_thinPlateSpline.h"
#include "_reg_aladin.h"
#include <fstream>
#include <vector>
#include <iostream>



#ifdef _USE_CUDA
#include "_reg_f3d_gpu.h"
#endif
#include "float.h"
#include <limits>

#ifdef _WINDOWS
#include <time.h>
#endif

#ifdef _USE_NR_DOUBLE
#define PrecisionTYPE double
#else
#define PrecisionTYPE float
#endif

typedef struct{
	char referenceImageName[FILENAME_MAX + 1];
	char cpp2defInputName[FILENAME_MAX + 1];
	char cpp2defOutputName[FILENAME_MAX + 1];
} PARAMSCPP2DEF;

typedef struct{
	char referenceName[FILENAME_MAX + 1];
	char floatingName[FILENAME_MAX + 1];
	char outputControlPointGridName[FILENAME_MAX + 1];
	char outputWarpedName[FILENAME_MAX + 1];
	int maxiterationNumber;  /* maxiterationNumber should be -1 by default*/
	PrecisionTYPE spacing[3]; /* spacing[0] = sx, spacing[1] = sy, spacing[2] = sz */
	unsigned int levelNumber;
	unsigned int levelToPerform;
	bool noPyramid;
	bool useSym;
} PARAMSF3D;

typedef struct{
	char referenceName[FILENAME_MAX + 1];
	char floatingName[FILENAME_MAX + 1];
	char outputWarpedName[FILENAME_MAX + 1];
	bool rigOnly; /* false by default (rigid + affine) */
	bool affDirect; /* false by default (default is rigid then affine) */
	int maxiterationNumber;  /* maxiterationNumber should be -1 by default*/
	unsigned int levelNumber;
	unsigned int levelToPerform;
	bool useSym;
	float percentBlock; /* Percentage of block to use, default 50 */
} PARAMSALADIN;

/**
    \class milxQtRegistrationNifti
    \brief NiftiReg calls
    \author 
*/
class milxQtRegistrationNifti : public QObject
{
	Q_OBJECT

public:
	milxQtRegistrationNifti(QObject *theParent);
	int cpp2def(PARAMSCPP2DEF params);
	int f3d(PARAMSF3D params);
	int aladin(PARAMSALADIN params);
	
	void cpp2def_async(PARAMSCPP2DEF params);
	void f3d_async(PARAMSF3D params);
	void aladin_async(PARAMSALADIN params);

signals:
	void cpp2defFinished();
	void registrationFinished();


protected:
	QPointer<milxQtMain> MainWindow;
	QFuture<int> future;
};


#endif // MILXQTRegistrationPLUGIN_H