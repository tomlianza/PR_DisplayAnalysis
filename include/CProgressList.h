#ifndef CPROGRESSLIST_H_INCLUDED
#define CPROGRESSLIST_H_INCLUDED



typedef enum {
    PROGRESSLIST_NONE,
    PROGRESSLIST_PENDING,
    PROGRESSLIST_ACTIVE,
	PROGRESSLIST_SKIPPED,
    PROGRESSLIST_DONE
} PROGRESSLIST_STATE;

typedef struct {
    int ident;
    PROGRESSLIST_STATE state;
	int weight;
} PROGRESSLIST_ENTRY;

class CProgressList
{
	private:
		int m_TotalWeight;		//these are arbitrary ammounts, not a percentage, so we can weight stages differently
		int m_ProgressWeight;
		
		int stagePercent; // the stage will know how far done it is, but not of the total.
		
    public:
		CProgressList();
		~CProgressList();

		void SetActiveStep (int idx);
		int SetActiveStepByID(int ident);
		int FindStepByID(int ident);
		void IncrementActiveStep ();
        enum {MAX_PROGRESSLIST_ENTRIES = 10};

        int m_NumSteps;
        int m_CurStep;
		
        PROGRESSLIST_ENTRY m_PLStep[MAX_PROGRESSLIST_ENTRIES];
		
		//weight is used for calculating the total progress
		void AddWeight(int w){ m_TotalWeight+=w;}
		
		int TotalWeight(){return m_TotalWeight;}
		
		int GetProgressPercentDone() ;
		
		
		void SetStagePercent(int p); 
		void UpdatePercentages();
};
#endif
