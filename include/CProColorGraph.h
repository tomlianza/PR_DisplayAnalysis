#include "CGraph.h"
#include "ColorStats.h"
#include "MeasurementSet.h"
#include "resource.h"

typedef struct
{
	int ctlVal;
	double colorTempVal;
} COLOR_TEMP_MAP;

class CProColorGraph : public CGraph
{
public:
	DECLARE_DYNCREATE(CProColorGraph)
		CProColorGraph() {}
	CProColorGraph(CWnd *parent, int left=0, int top=0, int wwidth=400, int wheight=300, 
			   int gPct=20, COLORREF wColor = RGB(255,255,255), COLORREF gColor= RGB(230,230,230));

	void MakeAgingGraph(int numPts, double *lumValues, CString *strDates);
	
	void MakeAccuracyGraph (ColorStatData *csd);
	
	void MakeDeltaGraph (ColorStatData *csd);

	void MakeCIEGraph (ColorStatData *csd);

	void MakePurityGraph (sicmMeasurementSet *ms);

	void MakeColorTempGraph (int numMeasures, COLOR_TEMP_MAP *ms);

	virtual ~CProColorGraph();
};

